在 C++ 中，memory_order 是一个枚举类型，用于定义原子操作的内存排序模型。它有以下几种类型：

memory_order_relaxed: 这是一种最低限度的内存排序，它仅保证原子操作的有序性，但不保证与其他线程的有序性。在 memory_order_relaxed 下，编译器和处理器可以对指令进行重排序，只要不影响单线程的执行结果。这种内存排序通常用于实现无锁数据结构，如原子计数器等。

memory_order_consume: 这种内存排序用于表示某种方法的修改结果仅在依赖数据的其他操作中消耗。它需要保证原子操作之间的有序性，但允许其他非原子操作被重排序。memory_order_consume 通常用于优化读操作，避免不必要的内存栅栏。

memory_order_acquire: 这种内存排序用于表示原子操作将获取（或加载）一个值。在 memory_order_acquire 下，原子操作会在读取值之前，对所有在当前线程中对应的原子操作进行同步。这种内存排序通常用于实现互斥或信号量等同步原语。

memory_order_release: 这种内存排序用于表示原子操作将释放（或存储）一个值。在 memory_order_release 下，原子操作会在写入值之后，对所有在当前线程中对应的原子操作进行同步。这种内存排序通常用于实现互斥或信号量等同步原语。

memory_order_acq_rel: 这种内存排序是 memory_order_acquire 和 memory_order_release 的组合。它用于表示原子操作既将获取一个值，又将释放一个值。这种内存排序通常用于实现互斥或信号量等同步原语。

memory_order_seq_cst: 这是一种顺序一致性内存排序，它保证所有线程中的原子操作都按照顺序执行。在 memory_order_seq_cst 下，原子操作会在所有线程中按照顺序执行，就像在单线程环境中一样。这种内存排序通常用于实现简单的同步原语，如互斥锁等。


在这个示例中，我们使用 memory_order_relaxed 和 memory_order_release 对 counter 和 ready 原子变量进行操作。increase_counter 函数将计数器值递增，并将 ready 标志设置为 true。print_counter 函数使用 memory_order_acquire 加载 ready 变量，以确保在读取 counter 之前，所有依赖于 ready 的操作都已完成。

总之，memory_order_relaxed、memory_order_consume、memory_order_acquire、memory_order_release、memory_order_acq_rel 和 memory_order_seq_cst 是 C++ 标准库中的不同内存排序模型，它们用于定义原子操作的有序性要求。这些内存排序模型可以帮助您优化多线程程序的性能，避免不必要的内存栅栏和同步开销。