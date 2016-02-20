import java.util.stream.Stream;

public class BinarySearch {

    // PRE: i < j => a[i] >= a[j]
    // POST: ℝ = i  ∧  a[i] <= x < a[i-1]
    public static int iterativeBinarySearch(int x, int a[]) {
        int l = 0, r = a.length, m;
        while (l < r) {
            m = (l + r) >>> 1;
            if (x == a[m]) {
                return m;
            } else if (x > a[m]) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return r;
    }

    public static int recursiveBinarySearch(int x, int a[]) {
        return recursiveBinarySearch(x, a, 0, a.length);
    }

    // PRE: i < j => a[i] >= a[j]
    // POST: ℝ = i  ∧  a[i] <= x < a[i-1]
    public static int recursiveBinarySearch(int x, int a[], int l, int r) {
        if (l == r) {
            return r;
        }
        int m = (l + r) >>> 1;
        if (x == a[m]) {
            return m;
        } else if (x > a[m]) {
            return recursiveBinarySearch(x, a, l, m);
        } else {
            return recursiveBinarySearch(x, a, m + 1, r);
        }
    }

    public static void main(String[] args) {
        int x = Integer.parseInt(args[0]);
        int a[] = Stream.of(args).skip(1).mapToInt(Integer::parseInt).toArray();
        int iterativeResult = iterativeBinarySearch(x, a);
        int recursiveResult = recursiveBinarySearch(x, a);
        System.out.println(iterativeResult == recursiveResult ? iterativeResult : "Error");
    }
}
