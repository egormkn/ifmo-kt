package expression.generic;

public class NumericFloat extends Numeric<Float> {
    public NumericFloat(float value) {
        super(value);
    }

    @Override
    public NumericFloat add(Numeric<Float> numeric) {
        return new NumericFloat(getValue() + numeric.getValue());
    }

    @Override
    public NumericFloat subtract(Numeric<Float> numeric) {
        return new NumericFloat(getValue() - numeric.getValue());
    }

    @Override
    public NumericFloat multiply(Numeric<Float> numeric) {
        return new NumericFloat(getValue() * numeric.getValue());
    }

    @Override
    public NumericFloat divide(Numeric<Float> numeric) {
        return new NumericFloat(getValue() / numeric.getValue());
    }

    @Override
    public NumericFloat getMinValue() {
        return new NumericFloat(Float.MIN_VALUE);
    }

    @Override
    public NumericFloat getMaxValue() {
        return new NumericFloat(Float.MAX_VALUE);
    }

    @Override
    public NumericFloat parse(String value) throws NumberFormatException {
        return new NumericFloat(Float.parseFloat(value));
    }
}