import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * @author Dmitry Paraschenko
 */
public class gcd_dp implements Runnable {
    private void solve() throws Exception {
        int n = nextInt();
        boolean[] a = new boolean[n + 1];
        for (int i = 2; i <= n; i++) {
            if (a[i]) {
                continue;
            }
            for (int j = 2 * i; j <= n; j += i) {
                a[j] = true;
            }
        }
        int answer = 0;
        for (int i = n; i >= 2; i--) {
            if (a[i]) {
                continue;
            }
            a[i] = true;
            int cur = i;
            for (int j = i - 1; j >= 2; j--) {
                if (a[j]) {
                    continue;
                }
                if (cur * 2 > n) {
                    break;
                }
                if (cur * j <= n) {
                    a[j] = true;
                    cur *= j;
                }
            }
            answer++;
        }
//      for (int i = 2; i <= n; i++) {
//          if (a[i]) {
//              continue;
//          }
//          for (int j = n / i; j > i; j--) {
//              if (a[j]) {
//                  continue;
//              }
//              answer++;
//              a[i] = true;
//              a[j] = true;
//          }
//          if (!a[i]) {
//              answer++;
//          }
//      }
        out.println(answer);
    }

    //========================================
    private BufferedReader in;
    private StringTokenizer st;
    private PrintWriter out;

    public gcd_dp(String file) {
        try {
            in = new BufferedReader(new FileReader(file + ".in"));
            st = new StringTokenizer("");
            out = new PrintWriter(file + ".out");
        } catch (FileNotFoundException e) {
            halt(e);
        }
    }

    public void run() {
        try {
            solve();
        } catch (Throwable e) {
            halt(e);
        } finally {
            out.close();
        }
    }
    
    private String nextToken() throws IOException {
        while (!st.hasMoreTokens()) {
            String line = in.readLine();
            if (line == null) {
                return null;
            }
            st = new StringTokenizer(line);
        }
        return st.nextToken();
    }

    private int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }
    
    private long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    private void halt(Throwable e) {
        System.exit(239);
    }

    public static void main(String[] args) {
        new Thread(new gcd_dp("gcd")).start();
    }
}
