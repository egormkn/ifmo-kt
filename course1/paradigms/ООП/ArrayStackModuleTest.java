public class ArrayStackModuleTest {
    public static void fill() {
        for (int i = 0; i < 10; i++) {
            ArrayStackModule.push(i);
        }
    }

    public static void dump() {
        while (!ArrayStackModule.isEmpty()) {
            System.out.println(
                ArrayStackModule.size() + " " +
                ArrayStackModule.peek() + " " +
                ArrayStackModule.pop()
            );
        }
    }

    public static void main(String[] args) {
        fill();
        dump();
    }
}
