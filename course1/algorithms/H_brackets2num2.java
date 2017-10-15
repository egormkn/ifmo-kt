import java.io.*;
import java.util.Stack;

/**
 * Created by Влад on 26.04.2016.
 */
public class H2 {
    private static BufferedReader in;
    private static BufferedWriter out;
    private static String brackets;
    private static long[][] d;
    private static long number;
    private static int n;


    private static void getInputInformation() throws IOException {
        brackets = in.readLine();
    }

    private static void getNumber() {
        Stack<Character> stack = new Stack<>();
        int depth = 0;
        long cur = 0;
        for (int i = 0; i < 2 * n; i++) {
            if (depth + 1 <= n) {
                cur = d[2 * n - i - 1][depth + 1] << ((2 * n - i - depth - 2) / 2);
            } else {
                cur = 0;
            }
            if (brackets.charAt(i) == '(') {
                stack.push('(');
                depth++;
                continue;
            }
            number += cur;

            if (stack.size() > 0 && stack.peek() == '(' && depth - 1 >= 0) {
                cur = d[2 * n - i - 1][depth - 1] << ((2 * n - i - depth) / 2);
            } else {
                cur = 0;
            }
            if (brackets.charAt(i) == ')') {
                stack.pop();
                depth--;
                continue;
            }
            number += cur;

            if (depth + 1 <= n) {
                cur = d[2 * n - i - 1][depth + 1] << ((2 * n - i - depth - 2) / 2);
            } else {
                cur = 0;
            }
            if (brackets.charAt(i) == '[') {
                stack.push('[');
                depth++;
                continue;
            }
            number += cur;
            stack.pop();
            depth--;
        }
    }


    public static void main(String[] args) throws IOException {
        in = new BufferedReader(new FileReader("brackets2num2.in"));
        out = new BufferedWriter(new FileWriter("brackets2num2.out"));
        getInputInformation();
        n = brackets.length() / 2;
        d = new long[2 * n + 1][n + 1];
        d[0][0] = 1;
        for (int i = 0; i < 2 * n; i++) {
            for (int j = 0; j <= n; j++) {
                if (j > 0) {
                    d[i + 1][j - 1] = d[i + 1][j - 1] + d[i][j];
                }
                if (j + 1 <= n) {
                    d[i + 1][j + 1] = d[i + 1][j + 1] + d[i][j];
                }
            }
        }
        getNumber();
        out.write(Long.toString(number));
        out.close();
    }
}
