public class LinkedQueue extends AbstractQueue {
    private Node head = null;
    private Node tail = null;

    protected void doEnqueue(Object element) {
        Node n = new Node(element);
        if (size() == 0) {
            head = n;
            tail = n;
        } else {
            tail.next = n;
            tail.next.prev = tail;
            tail = tail.next;
        }
    }

    protected Object doDequeue() {
        Object r = head.value;
        if (size() == 1) {
            head = null;
            tail = null;
        } else {
            head = head.next;
            head.prev = null;
        }
        return r;
    }

    protected void doPush(Object element) {
        Node n = new Node(element);
        if (size() == 0) {
            head = n;
            tail = n;
        } else {
            head.prev = n;
            head.prev.next = head;
            head = head.prev;
        }
    }

    protected Object doRemove() {
        Object r = tail.value;
        if (size() == 1) {
            head = null;
            tail = null;
        } else {
            tail = tail.prev;
            tail.next = null;
        }
        return r;
    }

    protected Queue sameTypeQueue() {
        return new LinkedQueue();
    }
}