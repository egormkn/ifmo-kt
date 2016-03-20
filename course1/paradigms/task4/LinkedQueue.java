public class LinkedQueue extends AbstractQueue {
    private int size = 0;
    private Node head = null;
    private Node tail = null;

    public void enqueue(Object element) {
        Node n = new Node(element);
        if (head == null) {
            head = n;
            tail = n;
        } else {
            // n.prev = tail;
            tail.next = n;
            tail = tail.next;
        }
        size++;
    }

    public Object element() {
        return head.value;
    }

    public Object dequeue() {
        Node n = head;
        // head.next.prev = null;
        head = head.next;
        size--;
        return n.value;
    }

    public int size() {
        return size;
    }

    public void push(Object element) {
        // Not implemented
    }

    public Object peek() {
        assert !isEmpty();
        // Not implemented
        return null;
    }

    public Object remove() {
        assert !isEmpty();
        // Not implemented
        return null;
    }

    protected Queue sameTypeQueue() {
        return new LinkedQueue();
    }
}
