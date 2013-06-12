import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;

/**
 * @author Dmitry Paraschenko
 */
public class binary_dp implements Runnable {
    private void solve() throws Exception {
        int m = nextInt();
        if (2 > m || m > 10000) {
            throw new AssertionError();
        }
        int n = 0;
        int n2 = 1;
        while (n2 * 2 <= m) {
            n++;
            n2 *= 2;
        }
        int r = m - n2;
        for (int i = 0; i < n2; i++) {
            String line = "";
            int tmp = i;
            for (int j = 0; j < n; j++) {
                line = (tmp % 2) + line;
                tmp /= 2;
            }
            if (i + r >= n2) {
                out.println(line + "0");
                out.println(line + "1");
            } else {
                out.println(line);
            }
        }
    }

    //========================================
    private BufferedReader in;
    private StringTokenizer st;
    private PrintWriter out;

    public binary_dp(String file) {
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
        new Thread(new binary_dp("binary")).start();
    }
}
