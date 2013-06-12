import java.io.*;
import java.util.*;

public class binary_sp {
	public static void main(String[] args) {
		new binary_sp().run();
	}

	BufferedReader br;
	StringTokenizer st;
	PrintWriter out;
	boolean eof = false;

	private void run() {
		Locale.setDefault(Locale.US);
		try {
			br = new BufferedReader(new FileReader(FNAME + ".in"));
			out = new PrintWriter(FNAME + ".out");
			solve();
			out.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(566);
		}
	}

	String nextToken() {
		while (st == null || !st.hasMoreTokens()) {
			try {
				st = new StringTokenizer(br.readLine());
			} catch (Exception e) {
				eof = true;
				return "0";
			}
		}
		return st.nextToken();
	}

	int nextInt() {
		return Integer.parseInt(nextToken());
	}

	String FNAME = "binary";

	private void solve() throws IOException {
		int m = nextInt();
		int n = 2;
		int t = 1;
		while (n < m) {
			n *= 2;
			t++;
		}
		for (int i = 0; i < n - m; i++) {
			String s = Integer.toBinaryString(i);
			while (s.length() < t - 1) {
				s = "0" + s;
			}
			out.println(s);
		}
		for (int i = n - m; i < m; i++) {
			String s = Integer.toBinaryString(i + n - m);
			while (s.length() < t) {
				s = "0" + s;
			}
			out.println(s);
		}
	}
}
