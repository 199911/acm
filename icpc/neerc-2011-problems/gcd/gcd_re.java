import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2011 Problem T: 
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class gcd_re {

	private static final int N_PRIMES = 1300;

	public static void main(String[] args) throws Exception {
		new gcd_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	int n;

	void read() throws Exception {
		Scanner in = new Scanner(new File("gcd.in"));
		in.useLocale(Locale.US);
		n = in.nextInt();
		in.nextLine();
		assert n >= 2 && n <= 10000;
		in.close();
	}

	int[] p = new int[N_PRIMES];
	int pc;

	void solve() {
		findPrimes();
		computeResult();
	}

	private void findPrimes() {
		p[0] = 2;
		pc = 1;
	search:
		for (int i = 3; i <= n; i += 2) {
			for (int j = 0; j < pc && p[j] * p[j] <= i; j++) {
				if (i % p[j] == 0)
					continue search;
			}
			p[pc++] = i;
		}
	}

	int result;
	boolean u[] = new boolean[N_PRIMES];

	private void computeResult() {
		result = 0;
		for (int i = 0; i < pc; i++) {
			if (!u[i]) {
				int g = p[i];
				for (int j = pc - 1; j > i; j--)
					if (!u[j] && g * p[j] <= n) {
						u[j] = true;
						break;
					}
				result++;
			}
		}
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("gcd.out");
		out.println(result);
		out.close();
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to verify 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a solution source
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
