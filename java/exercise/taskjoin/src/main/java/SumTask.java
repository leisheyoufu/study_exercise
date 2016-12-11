import java.util.Random;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;


public class SumTask extends RecursiveTask<Long> {
    private static final int THRESHOLD = 4;
    private int low;
    private int high;
    private long[] array;

    public SumTask(int low, int high, long[] array) {
        this.array = array;
        this.low = low;
        this.high = high;
    }

    public SumTask(int low, int high) {
        this.low = low;
        this.high = high;
        genArray();
    }

    private void genArray() {
        int size = this.high - this.low + 1;
        this.array = new long[size];
        for (int i=low; i<=high; i++) {
            array[i] = new Random().nextLong();
            //array[i] = 1;
        }
    }

    public static void main(String[] args) throws ExecutionException, InterruptedException {
        SumTask sumTask = new SumTask(0, 10);
        long begin = System.currentTimeMillis();
        // 2. create thread pool
        ForkJoinPool forkJoinPool = new ForkJoinPool();
        // 3. submit task
        forkJoinPool.submit(sumTask);
        // 4. get task result
        Long result = sumTask.get();
        long end = System.currentTimeMillis();
        System.out.println(String.format("result %s time elaspe %sms", result, end - begin));
    }

    protected Long compute() {
        long sum = 0;
        if (high == low) {
            sum = array[low];
        } else {
            if (high - low > THRESHOLD) {
                int mid = (low + high) / 2;
                SumTask left = new SumTask(low, mid, array);
                SumTask right = new SumTask(mid+1, high, array);
                left.fork();
                right.fork();
                sum = left.join() + right.join();
            } else {
                for (int i = low; i <= high; i++) {
                    sum += array[i];
                }
            }
        }
        return sum;
    }
}
