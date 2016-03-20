// INV: FIFO
//      head < tail:  elements[head]..elements[tail] - queue
//      head >= tail: elements[head]..elements[size()-1],
//                    elements[0]..elements[tail] - queue
public class ArrayQueueModule {
    private static int head = 0;
    private static int tail = 0;
    private static Object[] elements = new Object[16];

    // PRE:  size = new size of array
    // POST: elements.length > size
    //       elements.length < 4 * size
    //       queue - immutable
    private static void ensureCapacity(int size) {
        if (size == elements.length || (size > 3 && size == elements.length / 4)) {
            Object[] newElements;
            if (size == elements.length) {
                newElements = new Object[elements.length * 2];
            } else {
                newElements = new Object[elements.length / 2];
            }
            if (head <= tail) {
                System.arraycopy(elements, head, newElements, 0, size());
            } else {
                System.arraycopy(elements, head, newElements, 0, elements.length - head);
                System.arraycopy(elements, 0, newElements, elements.length - head, tail);
            }
            tail = size();
            head = 0;
            elements = newElements;
        }
    }

    // PRE:  None
    // POST: last element of queue = element,
    //       previous elements are immutable
    public static void enqueue(Object element) {
        ensureCapacity(size() + 1);
        elements[tail] = element;

        tail = (tail + 1) % elements.length;
    }

    // PRE:  !isEmpty
    // POST: queue - immutable
    //       R = first element of queue
    public static Object element() {
        assert !isEmpty();

        return elements[head];
    }

    // PRE:  !isEmpty
    // POST: R = first element of queue
    //       first element of queue = next element
    //       other elements are immutable
    public static Object dequeue() {
        assert !isEmpty();
        ensureCapacity(size() - 1);

        Object r = elements[head];
        elements[head] = null;
        head = (head + 1) % elements.length;
        return r;
    }

    // PRE:  None
    // POST: queue - immutable
    //       R = size of queue
    public static int size() {
        return tail - head + (head > tail ? elements.length : 0);
    }

    // PRE:  None
    // POST: queue - immutable
    //       R = (size() == 0)
    public static boolean isEmpty() {
        return size() == 0;
    }

    // PRE:  None
    // POST: isEmpty
    public static void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // PRE:  None
    // POST: R = array of queue elements
    //       from first to last element
    //       queue - immutable
    public static Object[] toArray() {
        Object array[] = new Object[size()];
        for (int i = 0; i < array.length; i++) {
            array[i] = elements[(head + i) % elements.length];
        }
        return array;
    }

    // PRE:  None
    // POST: first element of queue = element
    //       other elements are immutable
    public static void push(Object element) {
        ensureCapacity(size() + 1);
        head = head == 0 ? elements.length - 1 : head - 1;
        elements[head] = element;
    }

    // PRE:  !isEmpty
    // POST: R = last element of queue
    //       queue - immutable
    public static Object peek() {
        assert !isEmpty();
        return elements[tail == 0 ? elements.length - 1 : tail - 1];
    }

    // PRE:  !isEmpty
    // POST: R = last element of queue
    //       last element of queue = previous element
    //       other elements are immutable
    public static Object remove() {
        assert !isEmpty();
        ensureCapacity(size() - 1);

        tail = tail == 0 ? elements.length - 1 : tail - 1;
        Object r = elements[tail];
        elements[tail] = null;
        return r;
    }

}
