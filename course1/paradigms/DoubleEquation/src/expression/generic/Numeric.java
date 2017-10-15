package expression.generic;

public abstract class Numeric<T extends Comparable<T>> {

    private final T value;

    public Numeric(T value) {
        this.value = value;
    }

    public abstract Numeric<T> add(Numeric<T> numeric) throws OverflowException;

    public abstract Numeric<T> subtract(Numeric<T> numeric);

    public abstract Numeric<T> multiply(Numeric<T> numeric);

    public abstract Numeric<T> divide(Numeric<T> numeric);

    public abstract Numeric<T> getMinValue();

    public abstract Numeric<T> getMaxValue();

    public abstract Numeric<T> parse(String value)
            throws NumberFormatException;

    public T getValue() {
        return value;
    }

    @Override
    public String toString() {
        return getValue().toString();
    }

    public int compareTo(Numeric<T> numeric) {
        return getValue().compareTo(numeric.getValue());
    }
}