package expression.exceptions;

public class CheckedLog extends CheckedBinaryOperation {

    public CheckedLog(TripleExpression left, TripleExpression right) {
        super(left, right);
    }

    @Override
    protected int count(int left, int right) throws OverflowException, CountException {
        if(left <= 0 || right <= 0 || right == 1){
            throw new CountException(left + " // " + right);
        }
        int r = 0;
        while (left >= right) {
            left /= right;
            r++;
        }
        return r;
    }
}
