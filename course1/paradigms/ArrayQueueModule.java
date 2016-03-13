// INV: head < tail: elements[head]..elements[tail] - queue
//      head >= tail: elements[head]..elements[size()-1],
//                    elements[0]..elements[tail] - queue
public class ArrayQueueModule {
    private static int head = 0;
    private static int tail = 0;
    private static Object[] elements = new Object[16];

    // PRE:  size = new size of array
    // POST: elements.length > size
    //       elements.length < 4 * size
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

    // PRE: None
    // POST: elements[tail-1] = element     (last element of queue = element)
    //       tail = (tail + 1) % elements.length;
    public static void enqueue(Object element) { // добавить элемент в очередь
        ensureCapacity(size() + 1);
        elements[tail] = element;

        tail = (tail + 1) % elements.length;
    }

    // PRE: !isEmpty
    // POST: queue - immutable
    //       R = elements[head]  (first element of queue)
    public static Object element() { // первый элемент в очереди
        assert !isEmpty();

        return elements[head];
    }

    // PRE:  !isEmpty
    // POST: R = elements[head]     (first element of queue)
    //       head = (head + 1) % elements.length;
    public static Object dequeue() {
        assert !isEmpty();
        ensureCapacity(size() - 1);

        Object r = elements[head];
        elements[head] = null;
        head = (head + 1) % elements.length;
        return r;
    }

    // PRE: None
    // POST: queue - immutable
    //       R = size
    public static int size() { // текущий размер очереди
        return tail - head + (head > tail ? elements.length : 0);
    }

    // PRE: None
    // POST: queue - immutable
    //       R = (head == tail)
    public static boolean isEmpty() { // является ли очередь пустой
        return head == tail;
    }

    // PRE: None
    // POST: isEmpty
    public static void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // PRE: None
    // POST: R = queue
    public static Object[] toArray() {
        Object array[] = new Object[size()];
        for (int i = 0; i < array.length; i++) {
            array[i] = elements[(head + i) % elements.length];
        }
        return array;
    }

    // PRE:  None
    // POST: elements[head] = element (first element of queue = element)
    public static void push(Object element) {
        ensureCapacity(size() + 1);
        head = head == 0 ? elements.length - 1 : head - 1;
        elements[head] = element;
    }

    // PRE:  !isEmpty
    // POST: R = elements[tail - 1] (last element of queue)
    public static Object peek() {
        assert !isEmpty();
        return elements[tail == 0 ? elements.length - 1 : tail - 1];
    }

    // PRE:  !isEmpty
    // POST: R = elements[tail] (last element of queue)
    public static Object remove() {
        assert !isEmpty();
        ensureCapacity(size() - 1);

        tail = tail == 0 ? elements.length - 1 : tail - 1;
        Object r = elements[tail];
        elements[tail] = null;
        return r;
    }

}
