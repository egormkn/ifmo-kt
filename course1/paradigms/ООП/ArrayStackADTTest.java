public class ArrayStackADTTest {
    public static void fill(ArrayStackADT stack) {
        for (int i = 0; i < 10; i++) {
            ArrayStackADT.push(stack, i);
        }
    }

    public static void dump(ArrayStackADT stack) {
        while (!ArrayStackADT.isEmpty(stack)) {
            System.out.println(
                ArrayStackADT.size(stack) + " " +
                ArrayStackADT.peek(stack) + " " +
                ArrayStackADT.pop(stack)
            );
        }
    }

    public static void main(String[] args) {
        ArrayStackADT stack = new ArrayStackADT();
        fill(stack);
        dump(stack);
    }
}
