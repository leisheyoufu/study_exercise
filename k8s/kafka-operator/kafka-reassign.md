## Partition reassignment

Within a broker pod, the kafka-reassign-partitions.sh utility allows you to reassign partitions to different brokers.

It has three different modes:

--generate
Takes a set of topics and brokers and generates a reassignment JSON file which will result in the partitions of those topics being assigned to those brokers. Because this operates on whole topics, it cannot be used when you just need to reassign some of the partitions of some topics.

--execute
Takes a reassignment JSON file and applies it to the partitions and brokers in the cluster. Brokers that gain partitions as a result become followers of the partition leader. For a given partition, once the new broker has caught up and joined the ISR (in-sync replicas) the old broker will stop being a follower and will delete its replica.

--verify
Using the same reassignment JSON file as the --execute step, --verify checks whether all of the partitions in the file have been moved to their intended brokers. If the reassignment is complete, --verify also removes any throttles that are in effect. Unless removed, throttles will continue to affect the cluster even after the reassignment has finished.

### Reassignment JSON file
The reassignment JSON file has a specific structure:
```
{
  "version": 1,
  "partitions": [
    <PartitionObjects>
  ]
}
```
Where <PartitionObjects> is a comma-separated list of objects like:
```
{
  "topic": <TopicName>,
  "partition": <Partition>,
  "replicas": [ <AssignedBrokerIds> ]
}
```
The following is an example reassignment JSON file that assigns topic topic-a, partition 4 to brokers 2, 4 and 7, and topic topic-b partition 2 to brokers 1, 5 and 7:
```
{
  "version": 1,
  "partitions": [
    {
      "topic": "topic-a",
      "partition": 4,
      "replicas": [2,4,7]
    },
    {
      "topic": "topic-b",
      "partition": 2,
      "replicas": [1,5,7]
    }
  ]
}
```