package lei.study;

import org.jboss.netty.bootstrap.ServerBootstrap;
import org.jboss.netty.channel.*;
import org.jboss.netty.channel.socket.nio.NioServerSocketChannelFactory;

import java.net.InetSocketAddress;
import java.util.concurrent.Executors;

public class HelloServer {

    public static void main(String args[]) {
        ServerBootstrap bootstrap = new ServerBootstrap(
                new NioServerSocketChannelFactory(
                        Executors.newCachedThreadPool(),
                        Executors.newCachedThreadPool()));
        bootstrap
                .setPipelineFactory(new ChannelPipelineFactory() {
                    @Override
                    public ChannelPipeline getPipeline()
                            throws Exception {
                        return Channels
                                .pipeline(new HelloServerHandler());
                    }
                });
        bootstrap.bind(new InetSocketAddress(8000));
    }

    private static class HelloServerHandler extends
            SimpleChannelHandler {

        @Override
        public void channelConnected(
                ChannelHandlerContext ctx,
                ChannelStateEvent e) {
            System.out.println("Hello world, I'm server.");
        }
    }
}

