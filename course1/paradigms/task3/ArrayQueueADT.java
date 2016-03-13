// INV: FIFO
//      head < tail:  elements[head]..elements[tail] - queue
//      head >= tail: elements[head]..elements[size()-1],
//                    elements[0]..elements[tail] - queue
public class ArrayQueueADT {
    private int head = 0;
    private int tail = 0;
    private Object[] elements = new Object[16];

    // PRE:  size = new size of array
    // POST: elements.length > size
    //       elements.length < 4 * size
    //       queue - immutable
    private static void ensureCapacity(ArrayQueueADT queue, int size) {
        if (size == queue.elements.length || (size > 3 && size == queue.elements.length / 4)) {
            Object[] newElements;
            if (size == queue.elements.length) {
                newElements = new Object[queue.elements.length * 2];
            } else {
                newElements = new Object[queue.elements.length / 2];
            }
            if (queue.head <= queue.tail) {
                System.arraycopy(queue.elements, queue.head, newElements, 0, size(queue));
            } else {
                System.arraycopy(queue.elements, queue.head, newElements, 0, queue.elements.length - queue.head);
                System.arraycopy(queue.elements, 0, newElements, queue.elements.length - queue.head, queue.tail);
            }
            queue.tail = size(queue);
            queue.head = 0;
            queue.elements = newElements;
        }
    }

    // PRE:  None
    // POST: last element of queue = element,
    //       previous elements are immutable
    public static void enqueue(ArrayQueueADT queue, Object element) {
        ensureCapacity(queue, size(queue) + 1);
        queue.elements[queue.tail] = element;

        queue.tail = (queue.tail + 1) % queue.elements.length;
    }

    // PRE:  !isEmpty
    // POST: queue - immutable
    //       R = first element of queue
    public static Object element(ArrayQueueADT queue) {
        assert !isEmpty(queue);

        return queue.elements[queue.head];
    }

    // PRE:  !isEmpty
    // POST: R = first element of queue
    //       first element of queue = next element
    //       other elements are immutable
    public static Object dequeue(ArrayQueueADT queue) {
        assert !isEmpty(queue);
        ensureCapacity(queue, size(queue) - 1);

        Object r = queue.elements[queue.head];
        queue.elements[queue.head] = null;
        queue.head = (queue.head + 1) % queue.elements.length;
        return r;
    }

    // PRE:  None
    // POST: queue - immutable
    //       R = size of queue
    public static int size(ArrayQueueADT queue) {
        return queue.tail - queue.head + (queue.head > queue.tail ? queue.elements.length : 0);
    }

    // PRE:  None
    // POST: queue - immutable
    //       R = (size() == 0)
    public static boolean isEmpty(ArrayQueueADT queue) {
        return size(queue) == 0;
    }

    // PRE:  None
    // POST: isEmpty
    public static void clear(ArrayQueueADT queue) {
        while (!isEmpty(queue)) {
            dequeue(queue);
        }
    }

    // PRE:  None
    // POST: R = array of queue elements
    //       from first to last element
    //       queue - immutable
    public static Object[] toArray(ArrayQueueADT queue) {
        Object array[] = new Object[size(queue)];
        for (int i = 0; i < array.length; i++) {
            array[i] = queue.elements[(queue.head + i) % queue.elements.length];
        }
        return array;
    }

    // PRE:  None
    // POST: first element of queue = element
    //       other elements are immutable
    public static void push(ArrayQueueADT queue, Object element) {
        ensureCapacity(queue, size(queue) + 1);
        queue.head = queue.head == 0 ? queue.elements.length - 1 : queue.head - 1;
        queue.elements[queue.head] = element;
    }

    // PRE:  !isEmpty
    // POST: R = last element of queue
    //       queue - immutable
    public static Object peek(ArrayQueueADT queue) {
        assert !isEmpty(queue);
        return queue.elements[queue.tail == 0 ? queue.elements.length - 1 : queue.tail - 1];
    }

    // PRE:  !isEmpty
    // POST: R = last element of queue
    //       last element of queue = previous element
    //       other elements are immutable
    public static Object remove(ArrayQueueADT queue) {
        assert !isEmpty(queue);
        ensureCapacity(queue, size(queue) - 1);

        queue.tail = queue.tail == 0 ? queue.elements.length - 1 : queue.tail - 1;
        Object r = queue.elements[queue.tail];
        queue.elements[queue.tail] = null;
        return r;
    }

}
