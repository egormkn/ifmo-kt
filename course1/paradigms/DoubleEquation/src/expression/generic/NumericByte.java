package expression.generic;

public class NumericByte extends Numeric<Byte> {
    public NumericByte(byte value) {
        super(value);
    }

    @Override
    public NumericByte add(Numeric<Byte> numeric) {
        return new NumericByte((byte) (getValue() + numeric.getValue()));
    }

    @Override
    public NumericByte subtract(Numeric<Byte> numeric) {
        return new NumericByte((byte) (getValue() - numeric.getValue()));
    }

    @Override
    public NumericByte multiply(Numeric<Byte> numeric) {
        return new NumericByte((byte) (getValue() * numeric.getValue()));
    }

    @Override
    public NumericByte divide(Numeric<Byte> numeric) {
        return new NumericByte((byte) (getValue() / numeric.getValue()));
    }

    @Override
    public NumericByte getMinValue() {
        return new NumericByte(Byte.MIN_VALUE);
    }

    @Override
    public NumericByte getMaxValue() {
        return new NumericByte(Byte.MAX_VALUE);
    }

    @Override
    public NumericByte parse(String value) throws NumberFormatException {
        return new NumericByte(Byte.parseByte(value));
    }
}