public class LinkedStack implements Stack, Copiable {
    private int size;
    private Node head;

    public void push(Object element) {
        assert element != null;

        size++;
        head = new Node(element, head);
    }

    public Object pop() {
        assert size > 0;

        size--;
        Object result = head.value;
        head = head.next;
        return result;
    }

    public Object peek() {
        assert size > 0;

        return head.value;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public LinkedStack makeCopy() {
        final LinkedStack copy = new LinkedStack();
        copy.size = size;
        copy.head = head;
        return copy;
    }
}
