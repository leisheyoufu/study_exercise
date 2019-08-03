#Let's ask the API Server for the API Groups it knows about.
kubectl api-resources | more

#A list of the objects available in that API Group
kubectl api-resources --api-group=apps

#We can use explain to dig further into a specific API Object 
#Check out KIND and VERSION, we'll see the API Group in the from group/version 
#Which is extensions/v1beta1 and that's deprecated.
kubectl explain deployment | head

#Follow the version specified in the deprecation warning. That's deprecated too!
kubectl explain deployment --api-version apps/v1beta2 | head

#Follow the version specified in THAT deprecation warning. Ah...the one we should use.
kubectl explain deployment --api-version apps/v1 | head

#Print the supported API versions on the API server again in the form group/version.
#Here we see apps/v1,apps/v1beta1 and apps/v1beta2
kubectl api-versions | sort | more

#Now, we're in a transition period of where Deployments are moving from v1beta1, to v1beta2 to apps/v1
#Deployment went GA under apps/v1 in version 1.9, as of 1.13 it's still a work in progress.
#Follow the issue on GitHub - https://github.com/kubernetes/kubernetes/issues/43214
kubectl apply -f deployment.yaml

#Our 1.13 API Server converts apiVersion to v1beta1
#let's look at a Deployment
kubectl get deployment hello-world -o yaml | head

#Let's clean up after this demo
kubectl delete deployment hello-world