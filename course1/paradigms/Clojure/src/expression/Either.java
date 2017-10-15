package expression;

import java.util.function.Function;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public interface Either<L, R> {
    <NR> Either<L, NR> mapRight(final Function<? super R, ? extends NR> f);
    <NR> Either<L, NR> flatMapRight(final Function<? super R, ? extends Either<L, NR>> f);

    boolean isLeft();

    L getLeft();
    R getRight();

    public static <L, R> Either<L, R> right(final R value) {
        return new Right<>(value);
    }

    static <L, R> Either<L, R> left(final L value) {
        return new Left<>(value);
    }

    public class Left<L, R> implements Either<L, R> {
        private final L value;

        public Left(final L value) {
            this.value = value;
        }

        @Override
        public <NR> Either<L, NR> mapRight(final  Function<? super R, ? extends NR> f) {
            return new Left<>(value);
        }

        @Override
        public <NR> Either<L, NR> flatMapRight(final Function<? super R, ? extends Either<L, NR>> f) {
            return new Left<>(value);
        }

        @Override
        public boolean isLeft() {
            return true;
        }

        @Override
        public L getLeft() {
            return value;
        }

        @Override
        public R getRight() {
            return null;
        }
    }

    public class Right<L, R> implements Either<L, R> {
        private final R value;

        public Right(final R value) {
            this.value = value;
        }

        @Override
        public <NR> Either<L, NR> mapRight(final  Function<? super R, ? extends NR> f) {
            return new Right<>(f.apply(value));
        }

        @Override
        public <NR> Either<L, NR> flatMapRight(final Function<? super R, ? extends Either<L, NR>> f) {
            return f.apply(value);
        }

        @Override
        public boolean isLeft() {
            return false;
        }

        @Override
        public L getLeft() {
            return null;
        }

        @Override
        public R getRight() {
            return value;
        }
    }
}
