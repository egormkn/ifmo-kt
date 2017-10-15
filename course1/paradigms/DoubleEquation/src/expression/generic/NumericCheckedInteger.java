package expression.generic;

public class NumericCheckedInteger extends Numeric<Integer> {
    public NumericCheckedInteger(int value) {
        super(value);
    }

    @Override
    public NumericCheckedInteger add(Numeric<Integer> numeric) throws OverflowException {
        int left = getValue();
        int right = numeric.getValue();
        if ((left < 0 && right < Integer.MIN_VALUE - left)
                || (left > 0 && right > Integer.MAX_VALUE - left)) {
            throw new OverflowException(left + " + " + right);
        }
        return new NumericCheckedInteger(getValue() + numeric.getValue());
    }

    @Override
    public NumericCheckedInteger subtract(Numeric<Integer> numeric) {
        return new NumericCheckedInteger(getValue() - numeric.getValue());
    }

    @Override
    public NumericCheckedInteger multiply(Numeric<Integer> numeric) {
        return new NumericCheckedInteger(getValue() * numeric.getValue());
    }

    @Override
    public NumericCheckedInteger divide(Numeric<Integer> numeric) {
        return new NumericCheckedInteger(getValue() / numeric.getValue());
    }

    @Override
    public NumericCheckedInteger getMinValue() {
        return new NumericCheckedInteger(Integer.MIN_VALUE);
    }

    @Override
    public NumericCheckedInteger getMaxValue() {
        return new NumericCheckedInteger(Integer.MAX_VALUE);
    }

    @Override
    public NumericCheckedInteger parse(String value) throws NumberFormatException {
        return new NumericCheckedInteger(Integer.parseInt(value));
    }
}