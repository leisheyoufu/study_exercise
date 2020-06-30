kubectl create ns loch
kubectl create -f redis-master-deploy.yml
kubectl create -f redis-master-service.yml
kubectl create -f redis-slave-deploy.yml
kubectl create -f redis-slave-service.yml
kubectl create -f redis-frontend-deploy.yml
kubectl create -f redis-frontend-service.yml

root@vbox:~/study_exercise/k8s/service# kubectl get svc -n loch
NAME           TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)        AGE
frontend       NodePort    10.43.240.243   <none>        80:31926/TCP   8m47s
redis-master   ClusterIP   10.43.177.33    <none>        6379/TCP       10m
redis-slave    ClusterIP   10.43.95.250    <none>        6379/TCP       10m

curl http://10.43.240.243:31926/
```
<html ng-app="redis">
  <head>
    <title>Guestbook</title>
    <link rel="stylesheet" href="//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.2.12/angular.min.js"></script>
    <script src="controllers.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/angular-ui-bootstrap/0.13.0/ui-bootstrap-tpls.js"></script>
  </head>
  <body ng-controller="RedisCtrl">
    <div style="width: 50%; margin-left: 20px">
      <h2>Guestbook</h2>
    <form>
    <fieldset>
    <input ng-model="msg" placeholder="Messages" class="form-control" type="text" name="input"><br>
    <button type="button" class="btn btn-primary" ng-click="controller.onRedis()">Submit</button>
    </fieldset>
    </form>
    <div>
      <div ng-repeat="msg in messages track by $index">
        {{msg}}
      </div>
    </div>
    </div>
  </body>
</html>
```

## Reference
https://kubernetes.io/docs/tutorials/stateless-application/guestbook/