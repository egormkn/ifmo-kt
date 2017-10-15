package hash;

import common.Triple;

import java.io.IOException;

/**
 * Test for homework 1.
 *
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class CalcMD5Test {
    public static void main(final String[] args) throws IOException {
        new HashChecker("CalcMD5").test(
                Triple.of("input.txt", "input.txt", "A8546347050ADC932FBEC189DC9FD50D"),
                Triple.of("__test_hello.txt", "hello", "5D41402ABC4B2A76B9719D911017C592"),
                Triple.of("__test_empty.txt", "", "D41D8CD98F00B204E9800998ECF8427E"),
                Triple.of("__test_hash.txt", "D41D8CD98F00B204E9800998ECF8427E", "80404D0C6D24E87F650FF7D1985CD762"),
                Triple.of("__test spaces txt", "this text contains spaces", "0AACC55D27AB04E26F3C7CCCAAC7B902"),
                "DB1FE12FBF369B59635FFCBA22007FF7",
                "664F95A728D5A0B117F3E5344B3B8ACE",
                "77FA15192315F12E6121B9EC6B04EB54",
                "DE1AF6F09647AB7B4E8821F0C7918195"
        ).printStatus();
    }
}
