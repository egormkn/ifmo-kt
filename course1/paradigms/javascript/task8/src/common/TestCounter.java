package common;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class TestCounter {
    private int total = 0;
    private int passed = 0;

    public void nextTest() {
        total++;
    }

    public int getTest() {
        return total;
    }

    public void passed() {
        passed++;
    }

    public void printStatus() {
        System.err.println("===========================================");
        System.err.println(String.format("Test run: %d, passed; %d, failed: %d", total, passed, total - passed));
        if (total == passed) {
            System.err.println("OK");
        }
    }
}
