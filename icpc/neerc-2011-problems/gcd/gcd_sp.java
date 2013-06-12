import java.io.*;
import java.util.*;
import java.math.*;

public class gcd_sp {
	public static void main(String[] args) {
		new gcd_sp().run();
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

	String FNAME = "gcd";

	private void solve() throws IOException {
//		for (int n = 2; n <= 10000; n++) {
		int n = nextInt();
//			System.err.println(n);
		int ans = 0;
		ArrayList<Integer> primes = new ArrayList<Integer>();
		for (int i = 2; i <= n; i++) {
			if (BigInteger.valueOf(i).isProbablePrime(100)) {
				ans++;
				primes.add(i);
			}
		}
		int m = primes.size();
		boolean[] u = new boolean[m];
		for (int i = 0; i < primes.size(); i++) {
			if (!u[i]) {
				for (int j = m - 1; j > i; j--) {
					if (!u[j] && primes.get(i) * primes.get(j) <= n) {
						u[i] = true;
						u[j] = true;
						ans--;
						break;
					}
				}
			}
		}
		out.println(ans);
	}}
//}
