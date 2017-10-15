public class LinkedStackTest {
    public static void fill(LinkedStack stack) {
        for (int i = 0; i < 10; i++) {
            stack.push(i);
        }
    }

    public static void dump(LinkedStack stack) {
        while (!stack.isEmpty()) {
            System.out.println(stack.size() + " " +
                stack.peek() + " " + stack.pop());
        }
    }

    public static void main(String[] args) {
        LinkedStack stack = new LinkedStack();
        fill(stack);
        dump(stack);
    }
}
