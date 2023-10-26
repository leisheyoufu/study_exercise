#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/queue.h>
#include <signal.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_cycles.h>
#include <rte_lcore.h>
#include <rte_mbuf.h>
#include <rte_ip.h>
#include <rte_udp.h>
#include <rte_ether.h>
#include <rte_malloc.h>
#include <rte_ring.h>
#include <rte_atomic.h>
#include <rte_branch_prediction.h>
#include <rte_byteorder.h>
#include <rte_spinlock.h>
#include <rte_errno.h>

#define RX_RING_SIZE 128
#define TX_RING_SIZE 512
#define NUM_MBUFS 8191
#define MBUF_CACHE_SIZE 250
#define BURST_SIZE 32

static const struct rte_eth_conf port_conf_default = {
    .rxmode = {
        .max_rx_pkt_len = ETHER_MAX_LEN,
    },
};

struct lcore_queue_conf {
    uint16_t n_rx_port;
    uint16_t rx_port_list[2];
    struct rte_ring *rx_queues[2];
    struct rte_ring *tx_queues[2];
};

struct lcore_queue_conf lcore_queue_conf[RTE_MAX_LCORE];

static volatile bool force_quit;

static inline int
port_init(uint16_t port, struct rte_mempool *mbuf_pool)
{
    struct rte_eth_conf port_conf = port_conf_default;
    const uint16_t rx_rings = 1, tx_rings = 1;
    int retval;
    uint16_t q;
    struct rte_eth_dev_info dev_info;
    struct rte_eth_txconf txconf;

    if (!rte_eth_dev_is_valid_port(port))
        return -1;

    retval = rte_eth_dev_info_get(port, &dev_info);
    if (retval != 0) {
        printf("Error during getting device (port %u) info: %s\n",
               port, strerror(-retval));
        return retval;
    }

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MBUF_FAST_FREE)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_MBUF_FAST_FREE;

    if (dev_info.rx_offload_capa & DEV_RX_OFFLOAD_VLAN_STRIP)
        port_conf.rxmode.offloads |= DEV_RX_OFFLOAD_VLAN_STRIP;

    if (dev_info.rx_offload_capa & DEV_RX_OFFLOAD_IPV4_CKSUM)
        port_conf.rxmode.offloads |= DEV_RX_OFFLOAD_IPV4_CKSUM;

    if (dev_info.rx_offload_capa & DEV_RX_OFFLOAD_UDP_CKSUM)
        port_conf.rxmode.offloads |= DEV_RX_OFFLOAD_UDP_CKSUM;

    if (dev_info.rx_offload_capa & DEV_RX_OFFLOAD_TCP_CKSUM)
        port_conf.rxmode.offloads |= DEV_RX_OFFLOAD_TCP_CKSUM;

    if (dev_info.rx_offload_capa & DEV_RX_OFFLOAD_TCP_LRO)
        port_conf.rxmode.offloads |= DEV_RX_OFFLOAD_TCP_LRO;

    if (dev_info.rx_offload_capa & DEV_RX_OFFLOAD_QINQ_STRIP)
        port_conf.rxmode.offloads |= DEV_RX_OFFLOAD_QINQ_STRIP;

    if (dev_info.rx_offload_capa & DEV_RX_OFFLOAD_JUMBO_FRAME)
        port_conf.rxmode.jumbo_frame = 1;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MBUF_FAST_FREE)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_MBUF_FAST_FREE;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_IPV4_CKSUM)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_IPV4_CKSUM;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_UDP_CKSUM)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_UDP_CKSUM;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_TCP_CKSUM)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_TCP_CKSUM;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_SCTP_CKSUM)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_SCTP_CKSUM;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_TCP_TSO)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_TCP_TSO;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_UDP_TSO) 
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_UDP_TSO;
    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_OUTER_IPV4_CKSUM)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_OUTER_IPV4_CKSUM;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_QINQ_INSERT)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_QINQ_INSERT;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MULTI_SEGS)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_MULTI_SEGS;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MBUF_FAST_FREE)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_MBUF_FAST_FREE;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_TCP_TSO)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_TCP_TSO;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_UDP_TSO)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_UDP_TSO;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_OUTER_IPV4_CKSUM)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_OUTER_IPV4_CKSUM;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_QINQ_INSERT)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_QINQ_INSERT;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MULTI_SEGS)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_MULTI_SEGS;

    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_SCTP_TSO)
        port_conf.txmode.offloads |= DEV_TX_OFFLOAD_SCTP_TSO;

    retval = rte_eth_dev_configure(port, rx_rings, tx_rings, &port_conf);
    if (retval != 0) {
        printf("Error during configuring device (port %u): %s\n",
            port, strerror(-retval));
        return retval;
    }

    for (q = 0; q < rx_rings; q++) {
        retval = rte_eth_rx_queue_setup(port, q, RX_RING_SIZE,
                                        rte_eth_dev_socket_id(port),
                                        NULL, mbuf_pool);
        if (retval < 0) {
            printf("Error during rx_queue_setup (port %u): %s\n",
                port, strerror(-retval));
            return retval;
        }
    }

    txconf = dev_info.default_txconf;
    txconf.offloads = port_conf.txmode.offloads;
    for (q = 0; q < tx_rings; q++) {
        retval = rte_eth_tx_queue_setup(port, q, TX_RING_SIZE,
                                        rte_eth_dev_socket_id(port),
                                        &txconf);
        if (retval < 0) {
            printf("Error during tx_queue_setup (port %u): %s\n",
                port, strerror(-retval));
            return retval;
        }
    }

    retval = rte_eth_dev_start(port);
    if (retval < 0) {
        printf("Error during starting device (port %u): %s\n",
            port, strerror(-retval));
        return retval;
    }

    rte_eth_promiscuous_enable(port);

    printf("Port %u, MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n\n",
        port,
        rte_eth_macaddr_get(port)->addr_bytes[0],
        rte_eth_macaddr_get(port)->addr_bytes[1],
        rte_eth_macaddr_get(port)->addr_bytes[2],
        rte_eth_macaddr_get(port)->addr_bytes[3],
        rte_eth_macaddr_get(port)->addr_bytes[4],
        rte_eth_macaddr_get(port)->addr_bytes[5]);

    return 0;    
}

static void signal_handler(int signum) {
    if (signum == SIGINT || signum == SIGTERM) {
         printf("\n\nSignal %d received, preparing to exit...\n\n", signum); force_quit = true; 
    } 
}

static int lcore_main(void *arg) {
    uint16_t port; 
    uint16_t queue; 
    uint32_t lcore_id = rte_lcore_id(); 
    struct lcore_queue_conf *qconf;
    if (lcore_id >= RTE_MAX_LCORE) {
        printf("Error: lcore index %u >= RTE_MAX_LCORE %u\n",
            lcore_id, RTE_MAX_LCORE);
        return -1;
    }

    qconf = &lcore_queue_conf[lcore_id];
    if (!qconf->n_rx_port) { 
        printf("lcore %u has nothing to do\n", lcore_id); 
        return 0; 
    }
    printf("entering main loop on lcore %u\n", lcore_id);

    for (queue = 0; queue < qconf->n_rx_port; ++queue) {
        port = qconf->rx_port_list[queue];
        printf(" -- lcoreid=%u portid=%u rxqueueid=%u\n",
            lcore_id, port, queue);
    }

    while (!force_quit) {
        for (queue = 0; queue < qconf->n_rx_port; ++queue) {
            struct rte_mbuf *bufs[BURST_SIZE];
            const uint16_t nb_rx = rte_eth_rx_burst(
                qconf->rx_port_list[queue], queue, bufs, BURST_SIZE);

            if (unlikely(nb_rx == 0))
                continue;

            uint16_t i;
            for (i = 0; i < nb_rx; i++) {
                struct rte_mbuf *buf = bufs[i];
                uint16_t dst_port = (queue + 1) % 2;
                rte_pktmbuf_free(buf);
                rte_eth_tx_burst(
                    qconf->rx_port_list[dst_port], 0, &buf, 1);
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    struct rte_mempool *mbuf_pool; 
    uint16_t nb_ports; uint16_t portid, nb_rx_queue, nb_tx_queue; 
    uint16_t queueid; 
    unsigned lcore_id, rx_lcore_id; 
    uint8_t nb_ports_available = 0; 
    uint8_t portid_list[2]; 
    uint8_t queueid_list[2]; 
    uint8_t nb_queues; 
    uint32_t n_tx_queue, nb_lcores; 
    int ret; 
    uint16_t socketid; 
    char *pool_name = "mbuf_pool"; 
    struct rte_eth_dev_info dev_info; 
    struct rte_eth_txconf txconf;
    ret = rte_eal_init(argc, argv);
    if (ret < 0)
        rte_exit(EXIT_FAILURE, "Error with EAL initialization\n");

    argc -= ret;
    argv += ret;

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    nb_ports = rte_eth_dev_count_avail();
    if (nb_ports == 0)
        rte_exit(EXIT_FAILURE, "No Ethernet ports - bye\n");

    nb_ports_available = nb_ports;

    if (nb_ports_available > 2)
        nb_ports_available = 2;

    nb_queues = nb_ports_available;

    if (rte_lcore_count() < nb_queues)
        rte_exit(EXIT_FAILURE, "Error: the number of cores (%u) "
                "should be equal or greater than the number of ports (%u)\n",
                rte_lcore_count(), nb_queues);

    nb_rx_queue = 1;
    nb_tx_queue = 1;

    mbuf_pool = rte_pktmbuf_pool_create(
        pool_name, NUM_MBUFS * nb_ports_available,
        MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE,
        rte_socket_id());
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot init mbuf pool\n");

    for (portid = 0; portid < nb_ports_available; portid++) {
        if (!rte_eth_dev_is_valid_port(portid))
            continue;

        rte_eth_dev_info_get(portid, &dev_info);
        if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MBUF_FAST_FREE)
            txconf.offloads |= DEV_TX_OFFLOAD_MBUF_FAST_FREE;

        portid_list[portid] = portid;
        queueid_list[portid] = portid;
        printf("Initializing port %u... ", (unsigned)portid);
        fflush(stdout);
        ret = port_init(portid, mbuf_pool);
        if (ret < 0)
            rte_exit(EXIT_FAILURE, "Cannot init port %" PRIu16 "\n",
                    portid);
    }

    if (nb_ports_available == 1) {
        lcore_queue_conf[0].n_rx_port = 1;
        lcore_queue_conf[0].rx_port_list[0] = portid_list[0];
        lcore_queue_conf[0].rx_queues[0] =
            rte_ring_create("rx_port0", RX_RING_SIZE,
                            rte_socket_id(), RING_F_SP_ENQ | RING_F_SC_DEQ);
        if (lcore_queue_conf[0].rx_queues[0] == NULL)
            rte_exit(EXIT_FAILURE, "Cannot create ring for RX port 0\n");
            

        lcore_queue_conf[0].tx_port_id[portid_list[0]] = 0;
        lcore_queue_conf[0].tx_queues[portid_list[0]][0] =
        rte_ring_create("tx_port0", TX_RING_SIZE,
                        rte_socket_id(), RING_F_SP_ENQ | RING_F_SC_DEQ);
        if (lcore_queue_conf[0].tx_queues[portid_list[0]][0] == NULL)
            rte_exit(EXIT_FAILURE, "Cannot create ring for TX port 0\n");
    } else {
        for (rx_lcore_id = 0; rx_lcore_id < nb_queues; rx_lcore_id++) {
            lcore_queue_conf[rx_lcore_id].n_rx_port = 1;
            lcore_queue_conf[rx_lcore_id].rx_port_list[0] =
                portid_list[rx_lcore_id];
            lcore_queue_conf[rx_lcore_id].rx_queues[0] =
                rte_ring_create(
                    "rx_port", RX_RING_SIZE, rte_socket_id(),
                    RING_F_SP_ENQ | RING_F_SC_DEQ);
            if (lcore_queue_conf[rx_lcore_id].rx_queues[0] == NULL)
                rte_exit(EXIT_FAILURE,
                        "Cannot create ring for RX port %u\n", portid);

            for (queueid = 0; queueid < nb_queues; queueid++) {
                if (rx_lcore_id == queueid)
                    continue;

                lcore_queue_conf[rx_lcore_id].tx_port_id[portid_list[queueid]] =
                    portid_list[queueid];
                lcore_queue_conf[rx_lcore_id].tx_queues[portid_list[queueid]][0] =
                    rte_ring_create(
                        "tx_port", TX_RING_SIZE, rte_socket_id(),
                        RING_F_SP_ENQ | RING_F_SC_DEQ);
                if (lcore_queue_conf[rx_lcore_id].tx_queues[portid_list[queueid]][0] == NULL)
                    rte_exit(EXIT_FAILURE,
                            "Cannot create ring for TX port %u\n",
                            portid_list[queueid]);
            }
        }
    }

    nb_lcores = rte_lcore_count();
    RTE_LCORE_FOREACH(lcore_id) {
        if (lcore_id >= nb_queues)
            break;

        if (lcore_id >= nb_lcores)
            break;

        printf("Initializing rx/tx queues on lcore %u... ", lcore_id);
        fflush(stdout);

        ret = lcore_queue_init(lcore_id);
        if (ret) {
            printf("Cannot initialize rx/tx queues on lcore %u\n",
                lcore_id);
            return -1;
        }
    }

    if (signal(SIGINT, signal_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");

    if (signal(SIGTERM, signal_handler) == SIG_ERR)
        printf("\ncan't catch SIGTERM\n");

    printf("\n\n");
    RTE_LCORE_FOREACH_WORKER(lcore_id) {
        if (lcore_id >= nb_queues)
            break;

        rte_eal_remote_launch(lcore_main, NULL, lcore_id);
    }

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    printf("entering main loop\n");

    for (;;) {
        sleep(1);
        fflush(stdout);
        if (force_quit)
            break;
    }

    RTE_LCORE_FOREACH_WORKER(lcore_id) {
        if (lcore_id >= nb_queues)
            break;

        rte_eal_wait_lcore(lcore_id);
    }

    RTE_LCORE_FOREACH(rx_lcore_id) {
        if (rx_lcore_id >= nb_queues)
            break;

        rte_ring_free(lcore_queue_conf[rx_lcore_id].rx_queues[0]);

        for (queueid = 0; queueid < nb_queues; queueid++) {
            if (rx_lcore_id == queueid)
                continue;

            rte_ring_free(lcore_queue_conf[rx_lcore_id].tx_queues[portid_list[queueid]][0]);
        }
    }

    for (portid = 0; portid < nb_ports; portid++) {
        if (!rte_eth_dev_is_valid_port(portid))
            continue;

        rte_eth_dev_stop(portid);
        rte_eth_dev_close(portid);
    }

    printf("Bye...\n");

    return 0;
}