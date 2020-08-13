# reference https://unix.stackexchange.com/questions/82598/how-do-i-write-a-retry-logic-in-script-to-keep-retrying-to-run-it-upto-5-times
function fail {
  echo $1 >&2
  exit 1
}

function retry {
  local n=1
  local max=3
  local delay=1
  while true; do
    "$@" && break || {
      if [[ $n -lt $max ]]; then
        ((n++))
        echo "Command failed. Attempt $n/$max:"
        sleep $delay;
      else
        fail "The command has failed after $n attempts."
      fi
    }
  done
}
# useage
retry sh build.sh build

# Retry timeout

mysql_cmd='mysql -u$DB_USER -p$DB_PASSWORD -h$DB_HOST -P$DB_PORT -e "source /tmp/db/db.sql;"'
if ! timeout 10 /bin/bash -c "while ! $mysql_cmd; do sleep 2; done"; then
    echo "ERROR: Failed to init mysql db"
    exit 1
fi

# nc command -w 3 : timeout 3
nc_cmd="nc -w 3 -v $DB_HOST 3306 < /dev/null >> /tmp/nc.txt"


## Function 2
NEXT_WAIT_TIME=0
until [ $NEXT_WAIT_TIME -eq 5 ] || command; do
    sleep $(( NEXT_WAIT_TIME++ ))
done
[ $NEXT_WAIT_TIME -lt 5 ]