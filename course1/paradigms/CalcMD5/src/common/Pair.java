package common;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Pair<F, S> {
    public final F first;
    public final S second;

    public Pair(final F first, final S second) {
        this.first = first;
        this.second = second;
    }

    public static <F, S> Pair<F, S> of(final F first, final S second) {
        return new Pair<>(first, second);
    }
}
