job_list='job1 job2 job3'
pids=''
for j in `echo $job_list`;do
	run_job $j &
	pids="$pids $!"
done

for pid in $pids;do
	wait $pid || let "RES=1"
done

if [[ "$RES" -ne 0 ]]; then
	exit $RES
fi
