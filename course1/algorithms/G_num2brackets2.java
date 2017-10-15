import java.io.*;
import java.util.Stack;

/**
 * Created by Влад on 26.04.2016.
 */
public class G2 {
    private static BufferedReader in;
    private static BufferedWriter out;
    private static int n;
    private static long k;
    private static long[][] d;
    private static String answer;


    private static void getInputInformation() throws IOException {
        String inputString;
        String[] arrayOfArr;
        inputString = in.readLine();
        arrayOfArr = inputString.split(" ");
        n = Integer.parseInt(arrayOfArr[0]);
        k = Long.parseLong(arrayOfArr[1]);
    }

    private static void generate() {
        Stack<Character> stack = new Stack<>();
        int depth = 0;
        answer = "";
        long cur;
        for (int i = 2 * n - 1; i >= 0; i--) {
            if (depth + 1 <= n) {
                cur = d[i][depth + 1] << ((i - depth - 1) / 2);
            } else {
                cur = 0;
            }
            if (cur >= k) {
                answer += "(";
                stack.push('(');
                depth++;
                continue;
            }
            k -= cur;

            if (stack.size() > 0 && stack.get(stack.size() - 1) == '(' && depth - 1 >= 0)
                cur = d[i][depth - 1] << ((i - depth + 1) / 2);
            else
                cur = 0;
            if (cur >= k) {
                answer += ")";
                stack.pop();
                depth--;
                continue;
            }
            k -= cur;

            if (depth + 1 <= n)
                cur = d[i][depth + 1] << ((i - depth - 1) / 2);
            else
                cur = 0;
            if (cur >= k) {
                answer += "[";
                stack.push('[');
                depth++;
                continue;
            }
            k -= cur;

            answer += "]";
            stack.pop();
            depth--;
        }
    }


    public static void main(String[] args) throws IOException {
        in = new BufferedReader(new FileReader("num2brackets2.in"));
        out = new BufferedWriter(new FileWriter("num2brackets2.out"));
        getInputInformation();
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
        k++;
        generate();
        out.write(answer);
        out.close();
    }
}
