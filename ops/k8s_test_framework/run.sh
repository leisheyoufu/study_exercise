#!/bin/bash
export NAMESPACE=${NAMESPACE:-"k8s"}

K8S=(k8sservice)
FUNCTIONAL=(hello)
CURRENT_PATH=$(cd "$(dirname $0)";pwd)
TEST_CASE=""
hello_pod=""
declare -a SUPPORTED_CASES

function run_pod_cmd()
{
    kubectl exec -it $hello_pod -n $NAMESPACE -- $@
}

function init_test()
{
    echo "Start checking service status"
    bash $CURRENT_PATH/k8sservice/run.sh
    if [[ "$?" -ne "0" ]]; then
        echo "Service is not available"
        exit 1
    fi
    kubectl get po -n $NAMESPACE

    ## copy testcase into pod
    export hello_pod=$(kubectl get po -l=app=hello -n $NAMESPACE -o jsonpath="{.items[0].metadata.name}")
    cd $CURRENT_PATH
    rm -rf /tmp/testcases.tar.gz
    tar cfz /tmp/testcases.tar.gz *
    cd -
    run_pod_cmd rm -rf /opt/tests
    run_pod_cmd mkdir -p /opt/tests
    kubectl cp /tmp/testcases.tar.gz $hello_pod:/opt/tests -n $NAMESPACE
    run_pod_cmd tar xfz /opt/tests/testcases.tar.gz -C /opt/tests
}

function k8s()
{
    local rc=0
    local total=1
    local passed=0
    for t in ${K8S[@]}
    do
        echo "Test case $t: started"
        bash $CURRENT_PATH/${t}/run.sh
        total=$(($total+1))
        if [[ "$?" -ne "0" ]]; then
            rc=1
            echo "Test case $t: fail"
        else
            passed=$(($passed+1))
            echo "Test case $t: pass"
        fi
    done
    echo "Result: $passed/$total"
    return $rc
}

function functional()
{
    init_test
    local rc=0
    local total=0
    local passed=0
    for t in ${FUNCTIONAL[@]}
    do
        echo "Test case $t: started"
        run_pod_cmd bash /opt/tests/$t/run.sh
        total=$(($total+1))
        if [[ "$?" -ne "0" ]]; then
            rc=1
            echo "Test case $t: fail"
        else
            passed=$(($passed+1))
            echo "Test case $t: pass"
        fi
    done
    echo "Result: $passed/$total"
    return $rc
}

function get_supported_cases()
{
    local i=1
    cd $CURRENT_PATH/
    for d in */
    do
        if [[ "${d%/}" != "bin" && "${d%/}" != "common" ]]; then
            SUPPORTED_CASES[i++]="${d%/}"
        fi
    done
    cd -
    echo $SUPPORTED_CASES
}

function single_case()
{
    get_supported_cases
    local rc=0
    local total=1
    local passed=0
    if [[ "${SUPPORTED_CASES[@]}" =~ "${TEST_CASE}" ]]; then
        init_test
        echo "Test case $t: started"
        if [[ "${FUNCTIONAL[@]}" =~ "${TEST_CASE}" ]]; then
            run_pod_cmd bash /opt/tests/$TEST_CASE/run.sh
        elif [[ "${K8S[@]}" =~ "${TEST_CASE}" ]]; then
            bash $CURRENT_PATH/${TEST_CASE}/run.sh
        fi
        
        if [[ "$rc" -ne "0" ]]; then
            echo "Test case ${TEST_CASE}: fail"
            rc=1
        else
            passed=$(($passed+1))
            echo "Test case ${TEST_CASE}: pass"
        fi
    else
        echo "Supported cases: ${SUPPORTED_CASES[@]}"
        rc=1
    fi
    echo "Result: $passed/$total"
    return $rc
}

function usage()
{
	local script="${0##*/}"
	while read -r ; do echo "${REPLY}" ; done <<-EOF
	Usage: ${script} [ACTION]
	Test Hello cases

	Actions:
      k8s                       test suit to check k8s status
      functional                functional test suit inside hello pod
      <other>                   test case directory basename

	Examples:
	  ${script}
	  ${script} k8s
	  ${script} functional
	  ${script} hello
	EOF
}

while [ "$#" -gt "0" ]
do
	case "$1" in
	"-h"|"--help")
		usage
		exit 0
		;;
    *)
        [ "$1" == "--" ] && shift
        TEST_CASE=$1
	esac
	shift
done

case "${TEST_CASE}" in
"k8s")
    k8s
    exit "$?"
    ;;
"func"|"functional")
    functional
    exit "$?"
    ;;
"")
    usage
    exit 1
    ;;
*)
    single_case
    exit "$?"
    ;;
esac
