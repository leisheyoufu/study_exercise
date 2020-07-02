docker network create service --subnet 172.16.0.0/16

In docker compose:
```
networks:
  default:
    external:
      name: service
```