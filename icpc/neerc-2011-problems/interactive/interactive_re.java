import java.io.*;

/**
 * Solution for NEERC'2011 Problem T: 
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class interactive_re {

	public static void main(String[] args) throws Exception {
		new interactive_re().go();
	}

	void go() throws Exception {
		init();
		interact();
	}

	Scanner in;
	int n;

	void init() throws Exception {
		in = new Scanner(System.in);
		n = in.nextInt();
		assert n >= 1 && n <= 40;
	}

	void interact() {
		int[] a = new int[n];
		for (int i = 0; i < n; i++)
			a[i] = i + 1;
		int ck = ask(a);
		for (int i = 1; i <= n && ck < n; i++) {
			int cp = 0;
			while (a[cp] != i)
				cp++;
			move(a, cp, 0);
			int p = 0;
			while (true) {
				if (p != cp) {
					int k = ask(a);
					if (k > ck) {
						// better position found
						ck = k;
						break;
					}
					if (k < ck) {
						 // worse position found -- back to prev
						move(a, p, cp);
						break;
					}
				}
				swap(a, p, p + 1);
				p++;
			}
		}
		assert ck == n;
	}

	private void move(int[] a, int from, int to) {
		if (from < to)
			for (int i = from; i < to; i++)
				swap(a, i, i + 1);
		else if (from > to)
			for (int i = from; i > to; i--)
				swap(a, i, i - 1);
	}

	private void swap(int[] a, int i, int j) {
		int t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	private int ask(int[] a) {
		for (int i = 0; i < n; i++) {
			if (i > 0)
				System.out.print(" ");
			System.out.print(a[i]);
		}
		System.out.println();
		in.nextLine();
		int response = in.nextInt();
		assert response >= 1 && response <= n;
		return response;
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

		public Scanner(InputStream in) throws FileNotFoundException {
			this.in = new BufferedReader(new InputStreamReader(in));
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
	}
}
