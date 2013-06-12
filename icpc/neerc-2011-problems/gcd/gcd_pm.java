import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

/**
 * To be documented
 *
 * @author Pavel Mavrin
 */
public class gcd_pm {


    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("gcd.in"));
        PrintWriter out = new PrintWriter("gcd.out");

        int n = in.nextInt();
        boolean[] p = new boolean[n + 1];
        Arrays.fill(p, true);
        for (int i = 2; i <= n; i++) {
            if (p[i]) {
                for (int j = i * i; j <= n; j += i) {
                    p[j] = false;
                }
            }
        }

        int j = 2;
        int s = 0;
        for (int i = n; i > 1; i--) {
            if (i < j) break;
            if (p[i]) {
                while (!p[j]) j++;
                p[i] = false;
                if (i * j <= n) {
                    p[j] = false;
                }
                s++;
            }
        }

        out.println(s);
        out.close();
    }
}
