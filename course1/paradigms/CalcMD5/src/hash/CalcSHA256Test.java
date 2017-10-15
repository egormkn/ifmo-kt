package hash;

import common.Triple;

import java.io.IOException;

/**
 * Test for easy modification of homework 1.
 *
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class CalcSHA256Test {
    public static void main(final String[] args) throws IOException {
        new HashChecker("SHA256Sum").test(
                Triple.of("input.txt", "input.txt", "0E5523056AB6DBB2A3BFA672B305D76B003954FA5A1BCC8DE29528C2AD79B2ED"),
                Triple.of("__test_hello.txt", "hello", "2CF24DBA5FB0A30E26E83B2AC5B9E29E1B161E5C1FA7425E73043362938B9824"),
                Triple.of("__test_empty.txt", "", "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855"),
                Triple.of("__test_hash.txt", "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855", "F8BBB0CCB2491CA29A3DF03D6F92277A4F3574266507ACD77214D37ECA3F3082"),
                Triple.of("__test spaces txt", "this text contains spaces", "FCD2167D1975868261AAA54305D3206507C6D6BDEA182E3B2EF03871A5DA1167"),
                "1A5CF0FFEBECC32774A0BFAE298187C8FDD639EBC77A249A0DA1C465024DE5E7",
                "19EE99A01F375556EB427765798621E6C93FFF4A0DB30F7D1ED5C39AFE70C122",
                "EDCF6DD05775C7FFD0A4E5653573905DE965BAF29F1EB59D6FEB92E767E013EB",
                "1D8B7FEDBA5A7B2E1211E4E2E95E55DEA27F34B5E4A40A1E602220971446E141"
        ).printStatus();
    }
}
