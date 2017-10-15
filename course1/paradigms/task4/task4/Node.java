public class Node {
    Object value;
    Node next;
    Node prev;

    public Node(Object value) {
        this.value = value;
        this.prev = null;
        this.next = null;
    }

    public Node(Object value, Node next) {
        this.value = value;
        this.prev = null;
        this.next = next;
    }

    public Node(Object value, Node prev, Node next) {
        this.value = value;
        this.prev = prev;
        this.next = next;
    }
}
