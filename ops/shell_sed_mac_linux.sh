#!/bin/bash -e

CURR_DIR=$(
    cd "$(dirname $0)"
    pwd
)

BIN_DIR=${CURR_DIR}/bin
TASK_IMAGE=$(cat $BIN_DIR/task_version.txt)
MONITOR_IMAGE=$(cat $BIN_DIR/monitor_version.txt)
TEMPLATE_VERSION=$(cat $BIN_DIR/template_version.txt)


cd ${CURR_DIR}
mkdir -p ${BIN_DIR}/template
cp -r ${CURR_DIR}/template ${BIN_DIR}
echo $BIN_DIR/template/
ls $BIN_DIR/template/

case "$(uname -s)" in
   Darwin)
     sed -i '' "s|{{ task_image }}|$TASK_IMAGE|g" $(grep '{{ task_image }}' -rl $BIN_DIR/template/*.yaml)
     sed -i '' "s|{{ monitor_image }}|$MONITOR_IMAGE|g" $(grep '{{ monitor_image }}' -rl $BIN_DIR/template/*.yaml)
     sed -i '' "s|{{ template_version }}|$TEMPLATE_VERSION|g" $(grep '{{ template_version }}' -rl bin/template/*.yaml)
     ;;

   Linux)
     sed -i "s|{{ task_image }}|$TASK_IMAGE|g" $(grep '{{ task_image }}' -rl $BIN_DIR/template/*.yaml)
     sed -i "s|{{ monitor_image }}|$MONITOR_IMAGE|g" $(grep '{{ monitor_image }}' -rl $BIN_DIR/template/*.yaml)
     sed -i "s|{{ template_version }}|$TEMPLATE_VERSION|g" $(grep '{{ template_version }}' -rl bin/template/*.yaml)
     ;;
esac

cd $BIN_DIR
tar -cf $BIN_DIR/template.tar template