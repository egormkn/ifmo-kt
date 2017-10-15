package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class PostfixParserTest extends ModifiedPrefixParserTest {
    public static final Dialect POSTFIX = dialect(
            "%s",
            "%s",
            (op, args) -> "(" + String.join(" ", args) + " " + op + ")"
    );
    protected PostfixParserTest(final boolean hard) {
        super(hard, new AdvancedLanguage(OBJECT, POSTFIX, OPS), "postfix");
    }

    @Override
    protected void test() {
        super.test();

        printParsingError("Empty input", "");
        printParsingError("Unknown variable", "a");
        printParsingError("Invalid number", "-a");
        printParsingError("Missing )", "(z (x y +) *");
        printParsingError("Unknown operation", "( x y @@)");
        printParsingError("Excessive info", "(x y +) x");
        printParsingError("Invalid unary (0 args)", "(negate)");
        printParsingError("Invalid unary (2 args)", "(x y negate)");
        printParsingError("Invalid binary (0 args)", "(+)");
        printParsingError("Invalid binary (1 args)", "(x +)");
        printParsingError("Invalid binary (3 args)", "(x y z +)");
    }

    @Override
    protected String parse(final String expression) {
        return "parsePostfix('" + expression + "')";
    }

    private void printParsingError(final String description, final String input) {
        final String message = assertParsingError(input, "", "");
        final int index = message.lastIndexOf("in <eval>");
        System.out.format("%-25s: %s\n", description, message.substring(0, index > 0 ? index : message.length()));
    }

    public static void main(final String[] args) {
        final int mode = mode(args, PostfixParserTest.class, "easy", "hard");
        new PostfixParserTest(mode >= 1).test();
    }
}
