## Reference

http://www.cnblogs.com/xz1024/p/5862998.html

## Setup enviroment

Setup nodejs from (nodejs)[https://nodejs.org/en/download/]
`npm` has been integrated with nodejs.

Setup gulp and webpack
```
npm install webpack -g
npm install webpack-cli -g
npm install gulp -g

```
## Build target
Run the following steps
```
gulp run
open -a "Google Chrome" build/html/login.html # this command would open the html in Chrome

# Run webpack-dev-server
npm run devServer
# open Chrome, type http://127.0.0.1:9090/html/login.html
# open Chrome, http://127.0.0.1:9000/webpack-dev-server to see the map file
```
