public class StackTest {
    public static void fill(Stack stack) {
        for (int i = 0; i < 3; i++) {
            stack.push(i);
        }
    }

    public static void dump(Stack stack) {
        while (!stack.isEmpty()) {
            System.out.println(stack.size() + " " +
                stack.peek() + " " + stack.pop());
        }
    }

    public static void test(Stack stack) {
        fill(stack);
        Stack copy = stack.makeCopy();

        dump(stack);
        System.out.println();

        dump(copy);
        System.out.println("-------");
    }

    public static void main(String[] args) {
        test(new ArrayStack());
        test(new LinkedStack());
    }
}
