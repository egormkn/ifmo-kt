package hash;

import common.Triple;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.Collections;
import java.util.stream.Collectors;

/**
 * Test for hard modification of homework 1.
 *
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class SHA256SumTest {
    private static final HashChecker CHECKER = new HashChecker("SHA256Sum") {
        @Override
        protected void testArray(final String input, final Triple<String, String, String>[] tests) throws IOException {
            writeFiles(tests);
            final String[] args = Arrays.stream(tests).map(Triple::first).toArray(String[]::new);
            checkEquals(Arrays.stream(tests).map(Triple::third).collect(Collectors.toList()), run(args));
        }
    };
    public static final String[] RANDOMS = new String[]{
            "4BA38ADCC5322341225195A3BB4C603C19E8475AF3BBD190E5EF14D5799CAFE6",
            "20AC9E98602E81931A73AD98330B741A9DD36F04991C464062AF142A64B1FDF3",
            "920AE6845B656C46333B449FC3B02FF9B1BD3BD54C640E52E33ED1D086EB288D",
            "912764A532BF9CAD5A64FAB8D2D51B59E7F82B103EEC3094A27DC9E956930B28"
    };

    private static void testStdin(final String contents, final String result) throws IOException {
        System.setIn(new ByteArrayInputStream(contents.getBytes("UTF-8")));
        CHECKER.checkEquals(Collections.singletonList(result), CHECKER.run());
    }

    public static void main(final String[] args) throws IOException {
        CHECKER.test(
                Triple.of("input.txt", "input.txt", "0E5523056AB6DBB2A3BFA672B305D76B003954FA5A1BCC8DE29528C2AD79B2ED *input.txt"),
                Triple.of("__test_hello.txt", "hello", "2CF24DBA5FB0A30E26E83B2AC5B9E29E1B161E5C1FA7425E73043362938B9824 *__test_hello.txt"),
                Triple.of("__test_empty.txt", "", "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855 *__test_empty.txt"),
                Triple.of("__test_hash.txt", "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855", "F8BBB0CCB2491CA29A3DF03D6F92277A4F3574266507ACD77214D37ECA3F3082 *__test_hash.txt"),
                Triple.of("__test spaces txt", "this text contains spaces", "FCD2167D1975868261AAA54305D3206507C6D6BDEA182E3B2EF03871A5DA1167 *__test spaces txt"),
                "1A5CF0FFEBECC32774A0BFAE298187C8FDD639EBC77A249A0DA1C465024DE5E7 *__test__random10",
                "19EE99A01F375556EB427765798621E6C93FFF4A0DB30F7D1ED5C39AFE70C122 *__test__random1000",
                "EDCF6DD05775C7FFD0A4E5653573905DE965BAF29F1EB59D6FEB92E767E013EB *__test__random100000",
                "1D8B7FEDBA5A7B2E1211E4E2E95E55DEA27F34B5E4A40A1E602220971446E141 *__test__random10000000"
        );
        testStdin("input.txt", "0E5523056AB6DBB2A3BFA672B305D76B003954FA5A1BCC8DE29528C2AD79B2ED *-");
        testStdin("E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855", "F8BBB0CCB2491CA29A3DF03D6F92277A4F3574266507ACD77214D37ECA3F3082 *-");
        for (int i = 10, j = 0; i <= 10_000_000; i *= 100, j++) {
            testStdin(CHECKER.randomString(i), RANDOMS[j] + " *-");
        }

        CHECKER.printStatus();
    }
}
