package expression.generic;

public class NumericDouble extends Numeric<Double> {
    public NumericDouble(double value) {
        super(value);
    }

    @Override
    public NumericDouble add(Numeric<Double> numeric) {
        return new NumericDouble(getValue() + numeric.getValue());
    }

    @Override
    public NumericDouble subtract(Numeric<Double> numeric) {
        return new NumericDouble(getValue() - numeric.getValue());
    }

    @Override
    public NumericDouble multiply(Numeric<Double> numeric) {
        return new NumericDouble(getValue() * numeric.getValue());
    }

    @Override
    public NumericDouble divide(Numeric<Double> numeric) {
        return new NumericDouble(getValue() / numeric.getValue());
    }

    @Override
    public NumericDouble getMinValue() {
        return new NumericDouble(Double.MIN_VALUE);
    }

    @Override
    public NumericDouble getMaxValue() {
        return new NumericDouble(Double.MAX_VALUE);
    }

    @Override
    public NumericDouble parse(String value) throws NumberFormatException {
        return new NumericDouble(Double.parseDouble(value));
    }
}