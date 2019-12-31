## Setup ironic with devstack
sudo useradd -s /bin/bash -d /opt/stack -m stack
echo "stack ALL=(ALL) NOPASSWD: ALL" | sudo tee /etc/sudoers.d/stack
sudo su - stack
git clone https://git.openstack.org/openstack-dev/devstack --branch stable/queens
vi local.conf
./stack.sh

## Service for ironic
systemctl restart devstack@ir-cond.service
journalctl -u devstack@ir-cond.service --since="2019-12-21 06:04:48" --until="2019-12-21 06:50:35" | grep agent

## Change deploy interface from iscsi to agent
openstack baremetal node create --driver ipmi --deploy-interface direct
openstack baremetal node set <NODE> --deploy-interface direct

## Deploy baremetal node
DEFAULT_IMAGE_NAME=cirros-0.4.0-x86_64-disk
PRIVATE_NETWORK_NAME=private
image=$(openstack image show $DEFAULT_IMAGE_NAME -f value -c id)
net_id=$(openstack network list | egrep "$PRIVATE_NETWORK_NAME"'[^-]' | awk '{ print $2 }')
openstack server create --flavor baremetal --nic net-id=$net_id --image $image --key-name default test

## agent deploy process
* http://<ironic_api>/v1/lookup   lookup node with node mac address, check the provision state for node, then return the results.
* agent post heartbeat to ironic api `POST /v1/heartbeat/3a249bd3-6fd9-4c75-ad67-1e4fc32dbf5d`, ironic check provision status for current node and call continue deploy method ironic 从deploy wait, fsm state was changed to `wait`
* conducter use agent client to prepare image for agent. `self._client.prepare_image(node, image_info)`  --> `post _command, methoc 'standby.prepare_image'`,   `extension_part, command_part = self.split_command(command_name)` , extension_part is class in agent/extensions and command_part is a method of this class.
* conductor receive heartbeat from agent and call `get_commands_status`   , agent return the result based on `result = ext.execute(command_part, **kwargs)` -->  `self.command_results[result.id] = result`
* conductor call `reboot_to_instance`  --> `check_deploy_success`
* conductor call `reboot_and_finish_deploy`

## Some useful commands for ovs
ip netns add ns1
ip netns add ns2
 
ovs-vsctl add-br br0
ovs-vsctl add-port br0 tap1 -- set Interface tap1 type=internal
 
ovs-vsctl set Port tap1  tag=10
 
ip link set tap1 netns ns1
ip netns exec ns1 ip link set dev tap1 up
 
ovs-vsctl add-port br0 tap2 -- set Interface tap2 type=internal
ovs-vsctl set Port tap2  tag=11
 
ip link set tap2 netns ns2
ip netns exec ns2 ip link set dev tap2 up
 
ip netns exec ns1 ip addr add 192.168.1.101/24 dev tap1
ip netns exec ns2 ip addr add 192.168.1.102/24 dev tap2
 
ip netns exec ns1 ip link set lo up
ip netns exec ns2 ip link set lo up
 
ovs-vsctl add-br br1
ovs-vsctl add-port br1 tap3 -- set Interface tap3 type=internal
 
ovs-vsctl add-port br0 trunk_br0 trunks=10,11  -- set Interface trunk_br0 type=patch options:peer=trunk_br1
ovs-vsctl add-port br1 trunk_br1 trunks=10,11 -- set Interface trunk_br1 type=patch options:peer=trunk_br0
 
ip netns add ns3
ip link set tap3 netns ns3
ip netns exec ns3 ip addr add 192.168.1.103/24 dev tap3
ip netns exec ns3 ip link set dev tap3 up
ovs-vsctl set Port tap3 tag=10
 
 
ip netns exec ns3 ping -c 4 192.168.1.101
ip netns exec ns3 ping -c 4 192.168.1.102