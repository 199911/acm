import java.awt.datatransfer.FlavorMap;
import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2011 Problem L: Lanes
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class lanes_re {
	public static void main(String[] args) throws Exception {
		new lanes_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	int[] n = new int[2];
	int m;
	int r;
	int[][] a;

	void read() throws Exception {
		Scanner in = new Scanner(new File("lanes.in"));
		in.useLocale(Locale.US);
		for	(int i = 0; i < 2; i++) {
			n[i] = in.nextInt();
			assert n[i] >= 1 && n[i] <= 10;
		}
		m = in.nextInt();
		assert m >= 1 && m <= 100000;
		r = in.nextInt();
		assert r >= 1 && r <= m;
		in.nextLine();
		a = new int[2][m];
		for (int i = 0; i < m; i++) {
			a[0][i] = nextCars(in);
			a[1][i] = nextCars(in);
			in.nextLine();
		}
		in.close();
	}

	private int nextCars(Scanner in) {
		int a = in.nextInt();
		assert a >= 0 && a <= 100;
		return a;
	}

	long[][] cost;
	int best;

	void solve() {
		cost = new long[2][];
		cost[0] = new Model(n[0], a[0]).computeLRCost();
		cost[1] = new Model(n[1], a[1]).computeRLCost();
		best = -1;
		long best_cost = Long.MAX_VALUE;
		for (int t = 0; t < m; t++) {
			long c = cost[0][t] + cost[1][t + r - 1];
			//System.out.printf("cost[%d] = %d = %d + %d%n", t + 1, c, cost[0][t], cost[1][t + r - 1]);
			if (c < best_cost) {
				best_cost = c;
				best = t;
			}
		}
		System.out.printf("cost[%d] = %d = %d + %d%n", best + 1, best_cost, cost[0][best], cost[1][best + r - 1]);
	}

	class Model {
		final int n;
		final int[] a;

		Model(int n, int[] a) {
			this.n = n;
			this.a = a;
		}

		int[] f;
		long total_wait;
		int last_time;

		private void build(int cap1, int cap2) {
			f = new int[m + 1];  // free capacity at time i, f[mid] == free cap at last instant
			total_wait = 0;
			int queue = 0;
			// model with cap1 capacity
			for (int t = 0; t < m; t++) {
				total_wait += queue;
				queue += a[t];
				int leave = Math.min(queue, cap1);
				f[t] = cap1 - leave;
				queue -= leave;
			}
			// model the tail at time moment mid and after it with cap2 capacity
			last_time = m;
			while (true) {
				f[m] = cap2;
				if (queue == 0)
					break;
				total_wait += queue;
				int leave = Math.min(queue, cap2);
				f[m] = cap2 - leave;
				queue -= leave;
				if (f[m] > 0)
					break;
				last_time++;
			}
		}

		private long[] computeLRCost() {
			// model with assumption that central lane closes for LR traffic at t == mid
			build(n + 1, n);
			// compute costs -- close bridge earlier -- from t = mid-1 downto 0
			long[] cost = new long[m];
			int[] nf = new int[m]; // next free (free :== f[i] > 0)
			int curf = m;
			for (int t = m - 1; t >= 0; t--) {
				if (f[t] > 0) {
					f[t]--;
					if (f[t] > 0) {
						nf[t] = curf;
						curf = t;
					}
				} else {
					total_wait += (curf == m ? last_time : curf) - t;
					if (--f[curf] == 0) {
						if (curf < m)
							curf = nf[curf];
						else {
							last_time++;
							f[m] = n;
						}
					}
				}
				cost[t] = total_wait;
			}
			return cost;
		}

		private long[] computeRLCost() {
			// model with assumption that central lane is always open for RL traffic
			build(n + 1, n + 1);
			// compute costs -- close from t = 0 to mid+r-1
			long[] cost = new long[m + r];
			int curf = 0;
			for (int t = 0; t < m + r; t++) {
				if (f(t) == 0) {
					curf = Math.max(curf, t + 1);
					while (f(curf) == 0)
						curf++;
					total_wait += curf - t;
					decf(curf);
				}
				cost[t] = total_wait;
			}
			return cost;
		}

		private int f(int t) {
			return (t < m) ? f[t] : (t < last_time) ? 0 : (t == last_time) ? f[m] : n + 1;
		}

		private void decf(int t) {
			if (t < m)
				f[t]--;
			else if (t < last_time)
				assert false;
			else if (t == last_time) {
				if (--f[m] == 0) {
					last_time++;
					f[m] = n + 1;
				}
			} else {
				last_time = t;
				f[m] = n;
			}
		}
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("lanes.out");
		out.println(best + 1);
		out.close();
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to verify 100% correspondence between input files and input file format specification.
	 * It is q1 drop-in replacement for {@link java.util.Scanner} that could be added to q1 solution source
	 * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public class Scanner {
		private final BufferedReader in;
		private String line = "";
		private int pos;
		private int lineNo;
		private boolean localeset;

		public Scanner(File source) throws FileNotFoundException {
			in = new BufferedReader(new FileReader(source));
			nextLine();
		}

		public void close() {
			assert line == null : "Extra data at the end of file";
			try {
				in.close();
			} catch (IOException e) {
				throw new AssertionError("Failed to close with " + e);
			}
		}

		public void nextLine() {
			assert line != null : "EOF";
			assert pos == line.length() : "Extra characters on line " + lineNo;
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
		}

		public String next() {
			assert line != null : "EOF";
			assert line.length() > 0 : "Empty line " + lineNo;
			if (pos == 0)
				assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
			else {
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
				pos++;
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(pos) > ' ' : "Line " + lineNo + " has double whitespace";
			}
			StringBuilder sb = new StringBuilder();
			while (pos < line.length() && line.charAt(pos) > ' ')
				sb.append(line.charAt(pos++));
			return sb.toString();
		}

		public int nextInt() {
			String s = next();
			assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Integer.parseInt(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}

		public double nextDouble() {
			assert localeset : "Locale must be set with useLocale(Locale.US)";
			String s = next();
			assert s.length() == 1 || s.startsWith("0.") || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Double.parseDouble(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}

		public void useLocale(Locale locale) {
			assert locale == Locale.US;
			localeset = true;
		}
	}
}
