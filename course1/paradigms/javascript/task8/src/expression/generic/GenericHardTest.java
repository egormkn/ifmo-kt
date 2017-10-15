package expression.generic;

import java.util.Arrays;

import static expression.Util.checkAssert;
import static expression.Util.op;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class GenericHardTest extends GenericTest {
    public GenericHardTest() {
        ifb(
                "10",
                (x, y, z) -> 10,
                (x, y, z) -> 10.0f,
                (x, y, z) -> b(10)
        );
        ifb(
                "x",
                (x, y, z) -> x,
                (x, y, z) -> (float) x,
                (x, y, z) -> b(x)
        );
        ifb(
                "y + 2",
                (x, y, z) -> y + 2,
                (x, y, z) -> y + 2.0f,
                (x, y, z) -> b(y + 2)
        );
        ifb(
                "z / 2",
                (x, y, z) -> z / 2,
                (x, y, z) -> z / 2.0f,
                (x, y, z) -> b(z / 2)
        );
        ifb(
                "y / z",
                (x, y, z) -> y / z,
                (x, y, z) -> y / (float) z,
                (x, y, z) -> b(y / z)
        );
        ifb(
                "100 * x * y * 100 + z",
                (x, y, z) -> i(100 * x * y * 100 + z),
                (x, y, z) -> 100 * x * y * 100.0f + z,
                (x, y, z) -> b(100 * x * y * 100 + z)
        );
        ifb(
                "x * y + (z - 1) / 10",
                (x, y, z) -> x * y + (z - 1) / 10,
                (x, y, z) -> x * y + (z - 1) / 10.0f,
                (x, y, z) -> b(x * y + (z - 1) / 10)
        );
        ifb(
                "1 + 5 mod 3",
                (x, y, z) -> 1 + 5 % 3,
                (x, y, z) -> 1 + 5 % 3.0f,
                (x, y, z) -> b(1 + 5 % 3)
        );
        ifb(
                "x + y mod (z + 1)",
                (x, y, z) -> x + y % (z + 1),
                (x, y, z) -> x + y % (z + 1.0f),
                (x, y, z) -> b(x + y % (z + 1))
        );
        ifb(
                "abs -5",
                (x, y, z) -> 5,
                (x, y, z) -> 5.0f,
                (x, y, z) -> b(5)
        );
        ifb(
                "abs (x - y) / z",
                (x, y, z) -> Math.abs(x - y) / z,
                (x, y, z) -> Math.abs(x - y) / (float) z,
                (x, y, z) -> b(Math.abs(x - y) / z)
        );
        ifb(
                "square -5",
                (x, y, z) -> 25,
                (x, y, z) -> 25.0f,
                (x, y, z) -> b(25)
        );
        ifb(
                "square x - y / z",
                (x, y, z) -> x * x - y / z,
                (x, y, z) -> x * x - y / (float) z,
                (x, y, z) -> b(x * x - y / z)
        );
    }

    private byte b(final int x) {
        return (byte) x;
    }

    protected void ifb(final String expression, final F<Integer> fi, final F<Float> ff, final F<Byte> fb) {
        tests.addAll(Arrays.asList(
                        op("u:" + expression, fi),
                        op("f:" + expression, ff),
                        op("b:" + expression, fb))
        );
    }


    public static void main(final String[] args) {
        checkAssert(GenericHardTest.class);
        new GenericHardTest().test();
    }
}
