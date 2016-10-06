package lei.study;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.util.Iterator;

public class NioSelectorServer {

    public static void main(String[] args) throws IOException {
        Selector selector = Selector.open();
        ServerSocketChannel socketChannel = ServerSocketChannel.open();
        socketChannel.socket().bind(new InetSocketAddress(8000));
        socketChannel.configureBlocking(false);
        socketChannel.register(selector, SelectionKey.OP_ACCEPT);
        for (;;) {
            selector.select();
            for (Iterator<SelectionKey> keyIter = selector.selectedKeys()
                    .iterator(); keyIter.hasNext();) {
                SelectionKey key = keyIter.next();
                keyIter.remove();
                System.out.println(key.readyOps());
                if (key.isAcceptable()) {
                    System.out.println("Accept");
                    socketChannel.accept();
                }
            }
        }
    }
}