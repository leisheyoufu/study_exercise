## ssh authenticity of host
ssh-keyscan hostname.example.com >> $HOME/.ssh/known_hosts

if [ -z "$(ssh-keygen -F $IP)" ]; then
  ssh-keyscan -H $IP >> ~/.ssh/known_hosts
fi

scp -o RequestTTY=no -r


https://superuser.com/questions/1148390/scp-stalls-at-sending-command-v-t


## ssh config

Host <跳板机>
        ServerAliveInterval 30    // 定时心跳
        ControlMaster auto       // 配置会话共享
        ControlPath ~/.ssh/%r@%h:%p       //会话共享socket文件