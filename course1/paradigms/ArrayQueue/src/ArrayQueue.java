public class ArrayQueue extends AbstractQueue {
    private int head = 0;
    private Object[] elements = new Object[16];

    // PRE:  newSize >= 0
    // POST: elements.length > newSize
    //       elements.length < 4 * newSize
    //       queue - immutable
    private void ensureCapacity(int newSize) {
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

    protected void doEnqueue(Object element) {
        ensureCapacity(size() + 1);
        elements[(head + size()) % elements.length] = element;
    }

    protected Object doDequeue() {
        ensureCapacity(size() - 1);
        Object r = elements[head];
        elements[head] = null;
        head = (head + 1) % elements.length;
        return r;
    }

    protected void doPush(Object element) {
        ensureCapacity(size() + 1);
        head = head == 0 ? elements.length - 1 : head - 1;
        elements[head] = element;
    }

    protected Object doRemove() {
        ensureCapacity(size() - 1);
        int tail = (head + size()) % elements.length;
        tail = tail == 0 ? elements.length - 1 : tail - 1;
        Object r = elements[tail];
        elements[tail] = null;
        return r;
    }

    protected Queue sameTypeQueue() {
        return new ArrayQueue();
    }
}
