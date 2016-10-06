package lei.study;

import org.jboss.netty.bootstrap.ClientBootstrap;
import org.jboss.netty.buffer.ChannelBuffer;
import org.jboss.netty.buffer.ChannelBuffers;
import org.jboss.netty.channel.*;
import org.jboss.netty.channel.socket.nio.NioClientSocketChannelFactory;
import org.jboss.netty.handler.codec.serialization.ObjectEncoder;

import java.lang.management.ManagementFactory;
import java.lang.management.RuntimeMXBean;
import java.net.InetSocketAddress;
import java.nio.charset.Charset;
import java.util.concurrent.Executors;

public class MessageClient {

    public static void main(String args[]) {
        ClientBootstrap bootstrap = new ClientBootstrap(
                new NioClientSocketChannelFactory(
                        Executors.newCachedThreadPool(),
                        Executors.newCachedThreadPool()));
        bootstrap.setPipelineFactory(new ChannelPipelineFactory() {
            @Override
            public ChannelPipeline getPipeline() throws Exception {
                return Channels.pipeline(new ObjectEncoder(),
                        new ObjectClientHandler());
            }
        });
        bootstrap.connect(new InetSocketAddress("127.0.0.1", 8000));
    }

    public static class ObjectClientHandler extends SimpleChannelHandler {

        public void channelConnected(ChannelHandlerContext ctx, ChannelStateEvent e) {
            sendObject(e.getChannel());
        }

        private void sendObject(Channel channel) {
            Command command = new Command();
            command.setActionName("Hello Action");
            channel.write(command);
        }

    }

}