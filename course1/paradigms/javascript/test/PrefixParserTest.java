package test;

import static expression.Util.randomInt;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class PrefixParserTest extends ObjectExpressionTest {

    public static final String INSERTIONS = "xyz()+*/@ABC";
    public static final Dialect PREFIX = dialect("%s", "%s", "(%s %s)", "(%s %s %s)");

    protected PrefixParserTest(final boolean hard) {
        this(hard, new ExpressionTest.ArithmeticLanguage(OBJECT, PREFIX, ObjectExpressionTest.OPS));
    }

    public PrefixParserTest(final boolean testParsing, final Language language) {
        super(testParsing, false, language);
        engine.toStringMethod = "prefix";
    }

    @Override
    protected String parse(final String expression) {
        return "parsePrefix('" + expression + "')";
    }

    @Override
    protected void test(final String parsed, final String unparsed) {
        super.test(parsed, unparsed);
        super.test(removeSpaces(parsed), unparsed);

        for (int i = 0; i < 1 + Math.min(10, 200 / unparsed.length()); i++) {
            final int index = randomInt(unparsed.length());
            final char c = unparsed.charAt(index);
            if (!Character.isDigit(c) && !Character.isWhitespace(c) && c != '-'){
                assertParsingError(unparsed.substring(0, index), "<SYMBOL REMOVED>", unparsed.substring(index + 1));
            }
            final char newC = INSERTIONS.charAt(randomInt(INSERTIONS.length()));
            assertParsingError(unparsed.substring(0, index), "<SYMBOL INSERTED -->", newC + unparsed.substring(index));
        }
    }

    private String removeSpaces(final String expression) {
        return expression.replace(" (", "(").replace(") ", ")");
    }

    protected String assertParsingError(final String prefix, final String comment, final String suffix) {
        try {
            engine.parse(parse(prefix + suffix));
            throw new AssertionError("Parsing error expected for " + prefix + comment + suffix);
        } catch (final EngineException e) {
            return e.getCause().getMessage();
        }
    }

    public static void main(final String[] args) {
        final int mode = mode(args, PrefixParserTest.class, "easy", "hard");
        new PrefixParserTest(mode >= 1).test();
    }
}
