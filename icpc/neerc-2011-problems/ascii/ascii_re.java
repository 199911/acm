import java.io.*;

/**
 * Solution for NEERC'2011 Problem A: ASCII Area
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class ascii_re {

	public static void main(String[] args) throws Exception {
		new ascii_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	int h;
	int w;
	char[][] pic;

	void read() throws Exception {
		Scanner in = new Scanner(new File("ascii.in"));
		h = in.nextInt();
		w = in.nextInt();
		in.nextLine();
		assert 2 <= h && h <= 100;
		assert 2 <= w && w <= 100;
		pic = new char[h][];
		for (int i = 0; i < h; i++) {
			String s = in.next();
			in.nextLine();
			assert s.length() == w;
			pic[i] = s.toCharArray();
			for (int j = 0; j < w; j++)
				assert pic[i][j] == '.' || pic[i][j] == '/' || pic[i][j] == '\\';
		}
		in.close();
	}

	void solve() {
		verify();

	}

	int[][] tc; // touches count
	boolean[][] v; // mark visited
	int rc; // number of regions

	int curCount;
	int innerCount;
	int borderCount;

	void verify() {
		computeTouchCounts();
		countTouchCounts();
		computeRegions();
		assert rc == 1;
	}

	void computeTouchCounts() {
		tc = new int[h + 1][w + 1];
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				switch (pic[i][j]) {
				case '/':
					tc[i][j + 1]++;
					tc[i + 1][j]++;
					break;
				case '\\':
					tc[i][j]++;
					tc[i + 1][j + 1]++;
					break;
				case '.':
					break;
				default:
					assert false;
				}
			}
		}
	}

	void countTouchCounts() {
		for (int i = 0; i <= h; i++)
			for (int j = 0; j <= w; j++) {
				assert tc[i][j] == 0 || tc[i][j] == 2;
				if (tc[i][j] > 0)
					borderCount++;
			}
	}

	static final int MARKED = 0;
	static final int INNER = 1;
	static final int OUTER = 2;

	void computeRegions() {
		v = new boolean[h + 1][w + 1];
		for (int i = 0; i <= h; i++)
			for (int j = 0; j <= w; j++) {
				curCount = 0;
				if (mark(i, j) == INNER) {
					rc++;
					innerCount += curCount;
				}
			}
	}

	int mark(int i, int j) {
		if (i < 0 || i > h || j < 0 || j > w)
			return OUTER;
		if (v[i][j] || tc[i][j] > 0)
			return MARKED;
		v[i][j] = true;
		curCount++;
		int result = INNER;
		result = Math.max(result, mark(i - 1, j));
		result = Math.max(result, mark(i + 1, j));
		result = Math.max(result, mark(i, j - 1));
		result = Math.max(result, mark(i, j + 1));
		if (i < h && j < w && pic[i][j] != '/')
			result = Math.max(result, mark(i + 1, j + 1));
		if (i < h && j > 0 && pic[i][j - 1] != '\\')
			result = Math.max(result, mark(i + 1, j - 1));
		if (i > 0 && j < w && pic[i - 1][j] != '\\')
			result = Math.max(result, mark(i - 1, j + 1));
		if (i > 0 && j > 0 && pic[i - 1][j - 1] != '/')
			result = Math.max(result, mark(i - 1, j - 1));
		return result;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("ascii.out");
		out.println(innerCount + borderCount / 2 - 1); // use Pick's theorem which we don't actually need here.
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
	}
}
