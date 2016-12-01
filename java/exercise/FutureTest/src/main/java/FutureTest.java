import java.util.concurrent.*;

public class FutureTest {
    public static void main(String[] args) {
        ExecutorService executor = Executors.newCachedThreadPool();
        Task task = new Task(40000);
        Future<Integer> result = executor.submit(task);
        executor.shutdown();
        try {
            System.out.println(Thread.currentThread().getName() + ": waiting task result.");
            System.out.println("task result "+result.get());
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
    }

    private static class Task implements Callable<Integer> {
        private int count = 0;
        public Task(int count) {
            this.count = count;
        }

        public Integer call() throws Exception {
            int sum=0;
            System.out.println(Thread.currentThread().getName() + ": start running.");
            for(int i=1; i< count; i++) {
                sum+=i;
            }
            return sum;
        }
    }
}
