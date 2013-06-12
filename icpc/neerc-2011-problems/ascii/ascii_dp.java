import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;

/**
 * @author Dmitry Paraschenko
 */
public class ascii_dp implements Runnable {
    private void solve() throws Exception {
        int h = nextInt();
        int w = nextInt();
        if (1 > h || h > 100 || 1 > w || w > 100) {
            throw new AssertionError();
        }
        int answer = 0;
        for (int r = 0; r < h; r++) {
            String line = nextToken();
            if (w != line.length()) {
                throw new AssertionError();
            }
            boolean inside = false;
            for (int c = 0; c < w; c++) {
                char ch = line.charAt(c);
                if (ch == '/' || ch == '\\') {
                    inside = !inside;
                    answer++;
                } else if (ch == '.') {
                    if (inside) {
                        answer += 2;
                    }
                } else {
                    throw new AssertionError();
                }
                        
            }
        }
        out.println(answer / 2);
    }

    //========================================
    private BufferedReader in;
    private StringTokenizer st;
    private PrintWriter out;

    public ascii_dp(String file) {
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
    
    private void halt(Throwable e) {
        System.exit(239);
    }

    public static void main(String[] args) {
        new Thread(new ascii_dp("ascii")).start();
    }
}
