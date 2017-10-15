public class ArrayStackTest {
    public static void fill(ArrayStack stack) {
        for (int i = 0; i < 10; i++) {
            stack.push(i);
        }
    }

    public static void dump(ArrayStack stack) {
        while (!stack.isEmpty()) {
            System.out.println(stack.size() + " " +
                stack.peek() + " " + stack.pop());
        }
    }

    public static void main(String[] args) {
        ArrayStack stack = new ArrayStack();
        fill(stack);
        dump(stack);
    }
}
