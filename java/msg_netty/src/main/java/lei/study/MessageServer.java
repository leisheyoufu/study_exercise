package lei.study;

import org.jboss.netty.bootstrap.ServerBootstrap;
import org.jboss.netty.buffer.ChannelBuffer;
import org.jboss.netty.channel.*;
import org.jboss.netty.channel.socket.nio.NioServerSocketChannelFactory;

import java.net.InetSocketAddress;
import java.nio.charset.Charset;
import java.util.concurrent.Executors;

public class MessageServer {

    public static void main(String args[]) {
        ServerBootstrap bootstrap = new ServerBootstrap(
                new NioServerSocketChannelFactory(
                        Executors.newCachedThreadPool(),
                        Executors.newCachedThreadPool()));
        bootstrap.setPipelineFactory(new ChannelPipelineFactory() {
            @Override
            public ChannelPipeline getPipeline() throws Exception {
                return Channels.pipeline(new MessageServerHandler());
            }
        });
        bootstrap.bind(new InetSocketAddress(8000));
    }

    private static class MessageServerHandler extends SimpleChannelHandler {

        @Override
        public void messageReceived(ChannelHandlerContext ctx, MessageEvent e) {
            ChannelBuffer buffer = (ChannelBuffer) e.getMessage();
            System.out.println(buffer.toString(Charset.defaultCharset()));
            String msg = "Hello, I'm server.";
            buffer.clear();
            buffer.writeBytes(msg.getBytes());
            e.getChannel().write(buffer);
        }

        @Override
        public void channelOpen(ChannelHandlerContext ctx, ChannelStateEvent e) throws Exception {
            System.out.println("Hello, server is started.");
        }
    }
}