public class ArrayQueue extends AbstractQueue {
    private int head = 0;
    private int tail = 0;
    private Object[] elements = new Object[16];

    private void ensureCapacity(int size) {
        if (size == elements.length || (size > 3 && size == elements.length / 4)) {
            Object[] newElements = new Object[size == elements.length ? elements.length * 2 : elements.length / 2];
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

    public void enqueue(Object element) {
        ensureCapacity(size() + 1);
        elements[tail] = element;
        tail = (tail + 1) % elements.length;
    }

    public Object element() {
        assert !isEmpty();

        return elements[head];
    }

    public Object dequeue() {
        assert !isEmpty();

        ensureCapacity(size() - 1);
        Object r = elements[head];
        elements[head] = null;
        head = (head + 1) % elements.length;
        return r;
    }

    public int size() {
        return tail - head + (head > tail ? elements.length : 0);
    }

    public void push(Object element) {
        ensureCapacity(size() + 1);
        head = head == 0 ? elements.length - 1 : head - 1;
        elements[head] = element;
    }

    public Object peek() {
        assert !isEmpty();

        return elements[tail == 0 ? elements.length - 1 : tail - 1];
    }

    public Object remove() {
        assert !isEmpty();

        ensureCapacity(size() - 1);
        tail = tail == 0 ? elements.length - 1 : tail - 1;
        Object r = elements[tail];
        elements[tail] = null;
        return r;
    }

    protected Queue sameTypeQueue() {
        return new ArrayQueue();
    }
}
