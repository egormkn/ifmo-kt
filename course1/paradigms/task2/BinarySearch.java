import java.util.stream.Stream;

public class BinarySearch {

    //  PRE: i < j => a[i] >= a[j]
    // POST: ℝ = i  ∧  a[i-1] > x >= a[i]
    public static int iterativeBinarySearch(int x, int a[]) {
        int l = 0, r = a.length;
        // INV: a[-1]..a[l-1] > x >= a[r]..a[a.length]
        while (l < r) {
            // INV  ∧  l < r
            int m = (l + r) >>> 1;
            // l <= m < r

            if (x >= a[m]) {
                // INV  ∧  x >= a[m]
                r = m;
                // a[-1]..a[l-1] > x >= a[m]..a[a.length]
            } else {
                // INV  ∧  x < a[m]
                l = m + 1;
                // a[-1]..a[m] > x >= a[r]..a[a.length]
            }
        }
        // POST: INV  ∧  l >= r
        //       => a[l-1] > x >= a[r]  ∧  l-1 >= r-1
        //       => a[r-1] > x >= a[r]
        //       => ℝ = r
        return r;
    }

    public static int recursiveBinarySearch(int x, int a[]) {
        return recursiveBinarySearch(x, a, 0, a.length);
    }

    //  PRE: i < j => a[i] >= a[j]
    // POST: ℝ = i  ∧  a[i-1] > x >= a[i]
    //  INV: a[-1]..a[l-1] > x >= a[r]..a[a.length]
    public static int recursiveBinarySearch(int x, int a[], int l, int r) {
        if (l >= r) {
            //  INV  ∧  l >= r
            //  => a[l-1] > x >= a[r]  ∧  l-1 >= r-1
            //  => a[r-1] > x >= a[r]
            //  => ℝ = r
            return r;
        }
        // INV  ∧  l < r
        int m = (l + r) >>> 1;
        // l <= m < r

        if (x >= a[m]) {
            // INV  ∧  x >= a[m]
            // a[-1]..a[l-1] > x >= a[m]..a[a.length]
            return recursiveBinarySearch(x, a, l, m);
        } else {
            // INV  ∧  x < a[m]
            // a[-1]..a[m] > x >= a[r]..a[a.length]
            return recursiveBinarySearch(x, a, m + 1, r);
        }
    }

    public static void main(String[] args) {
        int x = Integer.parseInt(args[0]);
        int a[] = Stream.of(args).skip(1).mapToInt(Integer::parseInt).toArray();

        assert iterativeBinarySearch(1, new int[]{10, 10, 6, 4, 2}) == 5;
        assert iterativeBinarySearch(2, new int[]{10, 10, 6, 4, 2}) == 4;
        assert iterativeBinarySearch(3, new int[]{10, 10, 6, 4, 2}) == 4;
        assert iterativeBinarySearch(4, new int[]{10, 10, 6, 4, 2}) == 3;
        assert iterativeBinarySearch(5, new int[]{10, 10, 6, 4, 2}) == 3;
        assert iterativeBinarySearch(6, new int[]{10, 10, 6, 4, 2}) == 2;
        assert iterativeBinarySearch(7, new int[]{10, 10, 6, 4, 2}) == 2;
        assert iterativeBinarySearch(8, new int[]{10, 10, 6, 4, 2}) == 2;
        assert iterativeBinarySearch(9, new int[]{10, 10, 6, 4, 2}) == 2;
        assert iterativeBinarySearch(10, new int[]{10, 10, 6, 4, 2}) == 0;
        assert iterativeBinarySearch(11, new int[]{10, 10, 6, 4, 2}) == 0;

        assert recursiveBinarySearch(1, new int[]{10, 10, 6, 4, 2}) == 5;
        assert recursiveBinarySearch(2, new int[]{10, 10, 6, 4, 2}) == 4;
        assert recursiveBinarySearch(3, new int[]{10, 10, 6, 4, 2}) == 4;
        assert recursiveBinarySearch(4, new int[]{10, 10, 6, 4, 2}) == 3;
        assert recursiveBinarySearch(5, new int[]{10, 10, 6, 4, 2}) == 3;
        assert recursiveBinarySearch(6, new int[]{10, 10, 6, 4, 2}) == 2;
        assert recursiveBinarySearch(7, new int[]{10, 10, 6, 4, 2}) == 2;
        assert recursiveBinarySearch(8, new int[]{10, 10, 6, 4, 2}) == 2;
        assert recursiveBinarySearch(9, new int[]{10, 10, 6, 4, 2}) == 2;
        assert recursiveBinarySearch(10, new int[]{10, 10, 6, 4, 2}) == 0;
        assert recursiveBinarySearch(11, new int[]{10, 10, 6, 4, 2}) == 0;

        int iterativeResult = iterativeBinarySearch(x, a);
        int recursiveResult = recursiveBinarySearch(x, a);
        System.out.println(iterativeResult == recursiveResult ? iterativeResult : "Error");
    }
}
