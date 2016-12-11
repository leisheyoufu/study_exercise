package lei.exercise;

import java.util.HashMap;
import java.util.Map;

public class LFUCache {
    private int capacity;
    private int size = 0;
    private class Cache {
        public Cache(int key, int value) {
            this.key = key;
            this.value = value;
        }
        public int key;
        public int value;
        public Cache next;
        public Cache prev;
    }
    Map<Integer, Cache> nodes = new HashMap();
    private Cache head;


    public LFUCache(int capacity) {
        this.capacity = capacity;
    }

    public int get(int key) {
        Cache node;
        if(size == 0) {
            return -1;
        }
        if((node = nodes.get(key)) == null) {
            return -1;
        }
        move(node);
        return node.value;
    }

    public void set(int key, int value) {
        Cache node;
        if(( node = nodes.get(key)) !=null) {
            node.value = value;
        } else {
            if (size >= capacity) {
                remove();
            }
            node = new Cache(key, value);
            if(size == 0) {
                node.prev = node;
                node.next = node;
                head = node;
            } else {
                node.prev = head;
                node.next = head.next;
            }
            size++;
            nodes.put(key, node);
        }
        move(node);
    }
    private void move(Cache node) {
        Cache tail = head.prev;
        if (node == head)
            return;
        if(node != tail) {
            node.prev.next = node.next;
            node.next.prev = node.prev;
            node.prev = tail;
            node.next = head;
            head.prev = node;
        }
        head = node;
    }

    private void remove() {
        if (size == 0 ) {
            return;
        }
        Cache tail = head.prev;
        head.prev = tail.prev;
        tail.prev.next = head;
        nodes.remove(tail.key);
        size --;
    }

    public static void main(String[] args) {
        LFUCache cache = new LFUCache( 3 /* capacity */ );

        cache.set(2, 2);
        cache.set(1, 1);
        System.out.println(cache.get(2));       // returns 1
        //cache.set(3, 3);    // evicts key 2
        System.out.println(cache.get(1));       // returns -1 (not found)
        System.out.println(cache.get(2));       // returns 3.
        cache.set(3,3);
        cache.set(4, 4);    // evicts key 1.
        System.out.println(cache.get(3));       // returns -1 (not found)
        System.out.println(cache.get(2));       // returns 3
        System.out.println(cache.get(1));
        System.out.println(cache.get(4));       // returns 4
    }
}
