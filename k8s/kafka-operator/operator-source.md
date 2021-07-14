## listeners jsonDeserializer
@SuppressFBWarnings("SIC_INNER_SHOULD_BE_STATIC_ANON")
    public static class Deserializer extends JsonDeserializer<ArrayOrObjectKafkaListeners> {
        @Override
        public ArrayOrObjectKafkaListeners deserialize(JsonParser jsonParser, DeserializationContext context) throws IOException {
            ObjectCodec oc = jsonParser.getCodec();

            if (jsonParser.currentToken() == JsonToken.START_ARRAY) {
                return new ArrayOrObjectKafkaListeners(oc.readValue(jsonParser, new TypeReference<List<GenericKafkaListener>>() { }));
            } else if (jsonParser.currentToken() == JsonToken.START_OBJECT) {
                return new ArrayOrObjectKafkaListeners(oc.readValue(jsonParser, new TypeReference<KafkaListeners>() { }));
            } else {
                throw new RuntimeException("Failed to deserialize ArrayOrObjectKafkaListeners. Please check .spec.kafka.listeners configuration.");
            }
        }
    }

## listener configuration generator
public KafkaBrokerConfigurationBuilder withListeners(String clusterName, String namespace, List<GenericKafkaListener> kafkaListeners)  {
        List<String> listeners = new ArrayList<>();
        List<String> advertisedListeners = new ArrayList<>();
        List<String> securityProtocol = new ArrayList<>();

        // Replication listener
        listeners.add("REPLICATION-9091://0.0.0.0:9091");
        advertisedListeners.add(String.format("REPLICATION-9091://%s:9091",
                // Pod name constructed to be templatable for each individual ordinal
                DnsNameGenerator.podDnsNameWithoutClusterDomain(namespace, KafkaResources.brokersServiceName(clusterName),
                        KafkaResources.kafkaStatefulSetName(clusterName) + "-${STRIMZI_BROKER_ID}")
        ));
        securityProtocol.add("REPLICATION-9091:SSL");
        configureReplicationListener();

        for (GenericKafkaListener listener : kafkaListeners) {
            int port = listener.getPort();
            String listenerName = ListenersUtils.identifier(listener).toUpperCase(Locale.ENGLISH);
            String envVarListenerName = ListenersUtils.envVarIdentifier(listener);

            printSectionHeader("Listener configuration: " + listenerName);

            listeners.add(listenerName + "://0.0.0.0:" + port);
            advertisedListeners.add(String.format("%s://${STRIMZI_%s_ADVERTISED_HOSTNAME}:${STRIMZI_%s_ADVERTISED_PORT}", listenerName, envVarListenerName, envVarListenerName));
            configureAuthentication(listenerName, securityProtocol, listener.isTls(), listener.getAuth());

            if (listener.isTls())   {
                CertAndKeySecretSource customServerCert = null;
                if (listener.getConfiguration() != null) {
                    customServerCert = listener.getConfiguration().getBrokerCertChainAndKey();
                }

                configureTls(listenerName, customServerCert);
            }

            writer.println();
        }

        printSectionHeader("Common listener configuration");
        writer.println("listeners=" + String.join(",", listeners));
        writer.println("advertised.listeners=" + String.join(",", advertisedListeners));
        writer.println("listener.security.protocol.map=" + String.join(",", securityProtocol));
        writer.println("inter.broker.listener.name=REPLICATION-9091");
        writer.println("sasl.enabled.mechanisms=");
        writer.println("ssl.secure.random.implementation=SHA1PRNG");
        writer.println("ssl.endpoint.identification.algorithm=HTTPS");
        writer.println();

        return this;
    }

## convert
public static List<GenericKafkaListener> convertToNewFormat(KafkaListeners oldListeners)    {
        List<GenericKafkaListener> newListeners = new ArrayList<>(3);

        if (oldListeners != null)   {
            if (oldListeners.getPlain() != null)    {
                newListeners.add(convertPlainListener(oldListeners.getPlain()));
            }

            if (oldListeners.getTls() != null)    {
                newListeners.add(convertTlsListener(oldListeners.getTls()));
            }

            if (oldListeners.getExternal() != null)    {
                newListeners.add(convertExternalListener(oldListeners.getExternal()));
            }
        }

        return newListeners;
    }

## node port
/**
     * Converts Node Port listener from old to new configuration
     *
     * @param newListener   New listener which will be configured
     * @param oldListener   Old listener
     */
    private static void convertNodePortListener(GenericKafkaListener newListener, KafkaListenerExternalNodePort oldListener)    {
        newListener.setType(KafkaListenerType.NODEPORT);
        newListener.setTls(oldListener.isTls());

        if (oldListener.getConfiguration() == null && oldListener.getOverrides() == null) {
            return;
        }

        GenericKafkaListenerConfiguration configuration = new GenericKafkaListenerConfiguration();

        if (oldListener.getConfiguration() != null) {
            configuration.setBrokerCertChainAndKey(oldListener.getConfiguration().getBrokerCertChainAndKey());
            configuration.setPreferredNodePortAddressType(oldListener.getConfiguration().getPreferredAddressType());
        }

        if (oldListener.getOverrides() != null) {
            if (oldListener.getOverrides().getBootstrap() != null) {
                GenericKafkaListenerConfigurationBootstrap bootstrapConfiguration = new GenericKafkaListenerConfigurationBootstrap();
                bootstrapConfiguration.setNodePort(oldListener.getOverrides().getBootstrap().getNodePort());
                bootstrapConfiguration.setAnnotations(oldListener.getOverrides().getBootstrap().getDnsAnnotations());

                if (oldListener.getOverrides().getBootstrap().getAddress() != null) {
                    bootstrapConfiguration.setAlternativeNames(Collections.singletonList(oldListener.getOverrides().getBootstrap().getAddress()));
                }

                configuration.setBootstrap(bootstrapConfiguration);
            }

            if (oldListener.getOverrides().getBrokers() != null) {
                List<GenericKafkaListenerConfigurationBroker> brokers = new ArrayList<>(oldListener.getOverrides().getBrokers().size());

                for (NodePortListenerBrokerOverride oldBroker : oldListener.getOverrides().getBrokers()) {
                    GenericKafkaListenerConfigurationBroker brokerConfiguration = new GenericKafkaListenerConfigurationBroker();
                    brokerConfiguration.setBroker(oldBroker.getBroker());
                    brokerConfiguration.setNodePort(oldBroker.getNodePort());
                    brokerConfiguration.setAnnotations(oldBroker.getDnsAnnotations());
                    brokerConfiguration.setAdvertisedHost(oldBroker.getAdvertisedHost());
                    brokerConfiguration.setAdvertisedPort(oldBroker.getAdvertisedPort());

                    brokers.add(brokerConfiguration);
                }

                configuration.setBrokers(brokers);
            }
        }

        newListener.setConfiguration(configuration);
    }

## kafka node port service
/**
     * Generates list of service for pod. These services are used for exposing it externally.
     *
     * @param pod Number of the pod for which this service should be generated
     * @return The list with generated Services
     */
    public List<Service> generateExternalServices(int pod) {
        List<GenericKafkaListener> externalListeners = ListenersUtils.externalListeners(listeners);
        List<Service> services = new ArrayList<>(externalListeners.size());

        for (GenericKafkaListener listener : externalListeners)   {
            String serviceName = ListenersUtils.backwardsCompatibleBrokerServiceName(cluster, pod, listener);

            List<ServicePort> ports = Collections.singletonList(
                    createServicePort(ListenersUtils.backwardsCompatiblePortName(listener),
                            listener.getPort(),
                            listener.getPort(),
                            ListenersUtils.brokerNodePort(listener, pod),
                            "TCP")
            );

            Labels selector = getSelectorLabels().withStatefulSetPod(kafkaPodName(cluster, pod));

            Service service = createService(
                    serviceName,
                    //ListenersUtils.serviceType(listener),
                    "NodePort",
                    ports,
                    getLabelsWithStrimziName(name, templatePerPodServiceLabels),
                    selector,
                    Util.mergeLabelsOrAnnotations(ListenersUtils.brokerAnnotations(listener, pod), templatePerPodServiceAnnotations)
            );
            /*
            if (KafkaListenerType.LOADBALANCER == listener.getType()) {
                String loadBalancerIP = ListenersUtils.brokerLoadBalancerIP(listener, pod);
                if (loadBalancerIP != null) {
                    service.getSpec().setLoadBalancerIP(loadBalancerIP);
                }
            }

            if (KafkaListenerType.LOADBALANCER == listener.getType()) {
                List<String> loadBalancerSourceRanges = ListenersUtils.loadBalancerSourceRanges(listener);
                if (loadBalancerSourceRanges != null
                        && !loadBalancerSourceRanges.isEmpty()) {
                    service.getSpec().setLoadBalancerSourceRanges(loadBalancerSourceRanges);
                } else if (templatePerPodServiceLoadBalancerSourceRanges != null) {
                    service.getSpec().setLoadBalancerSourceRanges(templatePerPodServiceLoadBalancerSourceRanges);
                }
            }
            */
            if (KafkaListenerType.LOADBALANCER == listener.getType() || KafkaListenerType.NODEPORT == listener.getType()) {
                ExternalTrafficPolicy etp = ListenersUtils.externalTrafficPolicy(listener);
                if (etp != null) {
                    service.getSpec().setExternalTrafficPolicy(etp.toValue());
                } else if (templatePerPodServiceTrafficPolicy != null) {
                    service.getSpec().setExternalTrafficPolicy(templatePerPodServiceTrafficPolicy.toValue());
                }
            }

            services.add(service);
        }

        return services;
    }