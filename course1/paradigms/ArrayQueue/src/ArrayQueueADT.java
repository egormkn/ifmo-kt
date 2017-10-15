// INV: FIFO (First in - first out)
//      size >= 0
//      queue[head]..queue[tail] - queue
public class ArrayQueueADT {
    private int head = 0;
    private int size = 0;
    private Object[] elements = new Object[16];

    // PRE:  newSize >= 0
    //       queue - not null
    // POST: elements.length > newSize
    //       elements.length < 4 * newSize
    //       queue - immutable
    private static void ensureCapacity(ArrayQueueADT queue, int newSize) {
        if (newSize == queue.elements.length || (newSize > 3 && newSize == queue.elements.length / 4)) {
            newSize = (newSize == queue.elements.length ? queue.elements.length * 2 : queue.elements.length / 2);
            Object[] newElements = new Object[newSize];
            if (queue.head + size(queue) < queue.elements.length) {
                System.arraycopy(queue.elements, queue.head, newElements, 0, size(queue));
            } else {
                System.arraycopy(queue.elements, queue.head, newElements, 0, queue.elements.length - queue.head);
                System.arraycopy(queue.elements, 0, newElements, queue.elements.length - queue.head, (queue.head + size(queue)) % queue.elements.length);
            }
            queue.head = 0;
            queue.elements = newElements;
        }
    }

    // PRE:  queue - not nullable
    // POST: queue[tail] = element
    //       size' = size + 1
    //       queue[head]..queue[tail-1] - immutable
    public static void enqueue(ArrayQueueADT queue, Object element) {
        ensureCapacity(queue, size(queue) + 1);
        queue.elements[(queue.head + size(queue)) % queue.elements.length] = element;
        queue.size++;
    }

    // PRE:  size > 0
    //       queue - not nullable
    // POST: R = queue[head]
    //       queue - immutable
    public static Object element(ArrayQueueADT queue) {
        return queue.elements[queue.head];
    }

    // PRE:  size > 0
    //       queue - not nullable
    // POST: R = queue[head]
    //       queue[head] = queue[head+1]
    //       size' = size - 1
    //       queue[head+1]..queue[tail] - immutable
    public static Object dequeue(ArrayQueueADT queue) {
        assert queue.size > 0;
        ensureCapacity(queue, size(queue) - 1);
        Object r = queue.elements[queue.head];
        queue.elements[queue.head] = null;
        queue.head = (queue.head + 1) % queue.elements.length;
        queue.size--;
        return r;
    }

    // PRE:  queue - not nullable
    // POST: R = size
    //       queue - immutable
    public static int size(ArrayQueueADT queue) {
        return queue.size;
    }

    // PRE:  queue - not nullable
    // POST: queue - immutable
    //       R = (size == 0)
    public static boolean isEmpty(ArrayQueueADT queue) {
        return queue.size == 0;
    }

    // PRE:  queue - not nullable
    // POST: size == 0
    public static void clear(ArrayQueueADT queue) {
        while (queue.size > 0) {
            dequeue(queue);
        }
    }

    // PRE:  queue - not nullable
    // POST: Array[size]
    //       0 <= i < size: Array[i] = queue[head + i]
    //       R = Array
    //       queue - immutable
    public static Object[] toArray(ArrayQueueADT queue) {
        Object[] array = new Object[queue.size];
        for (int i = 0; i < queue.size; i++) {
            array[i] = dequeue(queue);
            enqueue(queue, array[i]);
        }
        return array;
    }

    // PRE:  queue - not nullable
    // POST: queue[head] = element
    //       size' = size + 1
    //       queue[head + 1]..queue[tail] - immutable
    public static void push(ArrayQueueADT queue, Object element) {
        ensureCapacity(queue, size(queue) + 1);
        queue.head = queue.head == 0 ? queue.elements.length - 1 : queue.head - 1;
        queue.elements[queue.head] = element;
        queue.size++;
    }

    // PRE:  size > 0
    //       queue - not nullable
    // POST: R = queue[tail]
    //       queue - immutable
    public static Object peek(ArrayQueueADT queue) {
        assert queue.size > 0;
        int tail = (queue.head + queue.size) % queue.elements.length;
        return queue.elements[tail == 0 ? queue.elements.length - 1 : tail - 1];
    }

    // PRE:  size > 0
    //       queue - not nullable
    // POST: R = queue[tail]
    //       queue[tail] = queue[tail - 1]
    //       size' = size - 1
    //       queue[head]..queue[tail - 1] - immutable
    public static Object remove(ArrayQueueADT queue) {
        assert queue.size > 0;

        ensureCapacity(queue, size(queue) - 1);
        int tail = (queue.head + size(queue)) % queue.elements.length;
        tail = tail == 0 ? queue.elements.length - 1 : tail - 1;
        Object r = queue.elements[tail];
        queue.elements[tail] = null;
        queue.size--;
        return r;
    }
}
