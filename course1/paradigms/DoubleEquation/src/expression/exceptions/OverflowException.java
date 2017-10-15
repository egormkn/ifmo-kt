package expression.exceptions;

public class OverflowException extends Exception {
    public OverflowException(String message) {
        super("Overflow while counting: " + message);
    }
}
