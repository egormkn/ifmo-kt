package common;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Triple<F, S, T> {
    public final F first;
    public final S second;
    public final T third;

    public Triple(final F first, final S second, final T third) {
        this.first = first;
        this.second = second;
        this.third = third;
    }

    public F first() {
        return first;
    }

    public S second() {
        return second;
    }

    public T third() {
        return third;
    }

    public static <F, S, T> Triple<F, S, T> of(final F first, final S second, final T third) {
        return new Triple<>(first, second, third);
    }
}
