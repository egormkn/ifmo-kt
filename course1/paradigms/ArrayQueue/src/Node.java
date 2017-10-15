public class Node {
    Object value;
    Node next;
    Node prev;

    public Node(Object value) {
        this(value, null, null);
    }

    public Node(Object value, Node next) {
        this(value, null, next);
    }

    public Node(Object value, Node next, Node prev) {
        this.value = value;
        this.prev = prev;
        this.next = next;
    }
}
