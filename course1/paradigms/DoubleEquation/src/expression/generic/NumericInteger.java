package expression.generic;

public class NumericInteger extends Numeric<Integer> {
    public NumericInteger(int value) {
        super(value);
    }

    @Override
    public NumericInteger add(Numeric<Integer> numeric) {
        return new NumericInteger(getValue() + numeric.getValue());
    }

    @Override
    public NumericInteger subtract(Numeric<Integer> numeric) {
        return new NumericInteger(getValue() - numeric.getValue());
    }

    @Override
    public NumericInteger multiply(Numeric<Integer> numeric) {
        return new NumericInteger(getValue() * numeric.getValue());
    }

    @Override
    public NumericInteger divide(Numeric<Integer> numeric) {
        return new NumericInteger(getValue() / numeric.getValue());
    }

    @Override
    public NumericInteger getMinValue() {
        return new NumericInteger(Integer.MIN_VALUE);
    }

    @Override
    public NumericInteger getMaxValue() {
        return new NumericInteger(Integer.MAX_VALUE);
    }

    @Override
    public NumericInteger parse(String value) throws NumberFormatException {
        return new NumericInteger(Integer.parseInt(value));
    }
}