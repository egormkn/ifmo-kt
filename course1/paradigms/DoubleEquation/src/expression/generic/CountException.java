package expression.generic;

public class CountException extends Exception {
    public CountException(String message) {
        super("Error while trying to count: " + message);
    }
}
