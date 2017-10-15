package expression.exceptions;

public class ParserException extends Exception {
    public ParserException(String message) {
        super("Error while parsing: " + message);
    }
}
