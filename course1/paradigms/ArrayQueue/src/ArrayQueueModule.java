// INV: FIFO (First in - first out)
//      size >= 0
//      queue[head]..queue[tail] - queue
public class ArrayQueueModule {
    private static int head = 0;
    private static int size = 0;
    private static Object[] elements = new Object[16];

    // PRE:  newSize >= 0
    // POST: elements.length > newSize
    //       elements.length < 4 * newSize
    //       queue - immutable
    private static void ensureCapacity(int newSize) {
        if (newSize == elements.length || (newSize > 3 && newSize == elements.length / 4)) {
            newSize = (newSize == elements.length ? elements.length * 2 : elements.length / 2);
            Object[] newElements = new Object[newSize];
            if (head + size() < elements.length) {
                System.arraycopy(elements, head, newElements, 0, size());
            } else {
                System.arraycopy(elements, head, newElements, 0, elements.length - head);
                System.arraycopy(elements, 0, newElements, elements.length - head, (head + size()) % elements.length);
            }
            head = 0;
            elements = newElements;
        }
    }

    // PRE:  None
    // POST: queue[tail] = element
    //       size' = size + 1
    //       queue[head]..queue[tail-1] - immutable
    public static void enqueue(Object element) {
        ensureCapacity(size() + 1);
        elements[(head + size()) % elements.length] = element;
        size++;
    }

    // PRE:  size > 0
    // POST: R = queue[head]
    //       queue - immutable
    public static Object element() {
        return elements[head];
    }

    // PRE:  size > 0
    // POST: R = queue[head]
    //       queue[head] = queue[head+1]
    //       size' = size - 1
    //       queue[head+1]..queue[tail] - immutable
    public static Object dequeue() {
        assert size > 0;
        ensureCapacity(size() - 1);
        Object r = elements[head];
        elements[head] = null;
        head = (head + 1) % elements.length;
        size--;
        return r;
    }

    // PRE:  None
    // POST: R = size
    //       queue - immutable
    public static int size() {
        return size;
    }

    // PRE:  None
    // POST: queue - immutable
    //       R = (size == 0)
    public static boolean isEmpty() {
        return size == 0;
    }

    // PRE:  None
    // POST: size == 0
    public static void clear() {
        while (size > 0) {
            dequeue();
        }
    }

    // PRE:  None
    // POST: Array[size]
    //       0 <= i < size: Array[i] = queue[head + i]
    //       R = Array
    //       queue - immutable
    public static Object[] toArray() {
        Object[] array = new Object[size];
        for (int i = 0; i < size; i++) {
            array[i] = dequeue();
            enqueue(array[i]);
        }
        return array;
    }

    // PRE:  None
    // POST: queue[head] = element
    //       size' = size + 1
    //       queue[head + 1]..queue[tail] - immutable
    public static void push(Object element) {
        ensureCapacity(size() + 1);
        head = head == 0 ? elements.length - 1 : head - 1;
        elements[head] = element;
        size++;
    }

    // PRE:  size > 0
    // POST: R = queue[tail]
    //       queue - immutable
    public static Object peek() {
        assert size > 0;
        int tail = (head + size) % elements.length;
        return elements[tail == 0 ? elements.length - 1 : tail - 1];
    }

    // PRE:  size > 0
    // POST: R = queue[tail]
    //       queue[tail] = queue[tail - 1]
    //       size' = size - 1
    //       queue[head]..queue[tail - 1] - immutable
    public static Object remove() {
        assert size > 0;

        ensureCapacity(size() - 1);
        int tail = (head + size()) % elements.length;
        tail = tail == 0 ? elements.length - 1 : tail - 1;
        Object r = elements[tail];
        elements[tail] = null;
        size--;
        return r;
    }
}
