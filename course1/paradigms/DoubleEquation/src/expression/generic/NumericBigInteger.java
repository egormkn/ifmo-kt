package expression.generic;

import java.math.BigInteger;

public class NumericBigInteger extends Numeric<BigInteger> {
    public NumericBigInteger(BigInteger value) {
        super(value);
    }

    @Override
    public NumericBigInteger add(Numeric<BigInteger> numeric) {
        return new NumericBigInteger(getValue().add(numeric.getValue()));
    }

    @Override
    public NumericBigInteger subtract(Numeric<BigInteger> numeric) {
        return new NumericBigInteger(getValue().subtract(numeric.getValue()));
    }

    @Override
    public NumericBigInteger multiply(Numeric<BigInteger> numeric) {
        return new NumericBigInteger(getValue().multiply(numeric.getValue()));
    }

    @Override
    public NumericBigInteger divide(Numeric<BigInteger> numeric) {
        return new NumericBigInteger(getValue().divide(numeric.getValue()));
    }

    @Override
    public NumericBigInteger getMinValue() {
        return new NumericBigInteger(BigInteger.valueOf(Long.MIN_VALUE));
    }

    @Override
    public NumericBigInteger getMaxValue() {
        return new NumericBigInteger(BigInteger.valueOf(Long.MAX_VALUE));
    }

    @Override
    public NumericBigInteger parse(String value) throws NumberFormatException {
        return new NumericBigInteger(new BigInteger(value));
    }
}