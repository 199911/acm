import com.sun.servicetag.SystemEnvironment;

import java.io.*;
import java.util.Arrays;
import java.util.Locale;
import java.util.Map;
import java.util.TreeMap;

/**
 * Solution for NEERC'2011 Problem C: Caption
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class caption_re {

	public static void main(String[] args) throws Exception {
		new caption_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}


	class CharDef {
		final int[] rows;

		CharDef(int m) {
			this.rows = new int[m];
		}

		CharDef(int m, int k, String[] s, int offset) {
			this(m);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < k; j++)
					switch (s[i].charAt(offset + j)) {
					case '.':
						break;
					case '*':
						rows[i] |= 1 << (k - 1 - j);
						break;
					default:
						throw new AssertionError("Invalid char in grid");
					}
		}
	}

	int m;
	int n;
	int k;
	int s_min;
	int s_max;
	Map<Character, CharDef> cd = new TreeMap<Character, CharDef>();
	char[] cur_str;
	int[] cur_space;
	int[] cur_pos;
	char[] new_str;

	void read() throws Exception {
		Scanner in = new Scanner(new File("caption.in"));
		in.useLocale(Locale.US);
		m = in.nextInt();
		assert m >= 5 && m <= 30;
		n = in.nextInt();
		assert n >= 5 && n <= 2000;
		k = in.nextInt();
		assert k >= 5 && k <= 30;
		s_min = in.nextInt();
		s_max = in.nextInt();
		assert s_min >= 0 && s_min <= s_max && s_max <= 30;
		String remainder = in.nextLine();
		assert remainder.length() == 0 : "extra characters on line";
		String[] s = new String[m];
		for (int i = 0; i < m; i++)
			s[i] = in.nextLine();
		int t = (s[0].length() + 1) / (k + 3);
		assert t >= 1 && t <= 26;
		for (int i = 0; i < m; i++)
			assert s[i].length() == t * (k + 3) - 1 : "should have t * (k + 3) - 1 chars";
		assert countSpaces(s[0]) == 2 * t - 1 : "should have 2 * t - 1 spaces";
		for (int i = 1; i < m; i++)
			assert countSpaces(s[i]) == 3 * t - 1 : "should have 3 * t - 1 spaces";
		for (int i = 0; i < t; i++) {
			char c = s[0].charAt(i * (k + 3));
			assert c >= 'A' && c <= 'Z' : "letter is out of range";
			assert !cd.containsKey(c) : "duped definition of " + c;
			cd.put(c, new CharDef(m, k, s, i * (k + 3) + 2));
		}
		cd.put(' ', new CharDef(m));
		cur_str = in.nextLine().toCharArray();
		checkString(cur_str);
		cur_space = new int[cur_str.length];
		cur_pos = new int[cur_str.length];
		for (int i = 0; i < cur_str.length; i++) {
			cur_space[i] = in.nextInt();
			assert cur_space[i] >= 0;
			cur_pos[i] = (i > 0 ? cur_pos[i - 1] + k : 0) + cur_space[i];
			assert cur_pos[i] + k <= n;
		}
		remainder = in.nextLine();
		assert remainder.length() == 0 : "extra characters on line";
		new_str = in.nextLine().toCharArray();
		checkString(new_str);
		in.close();
	}

	private void checkString(char[] s) {
		int len = s.length;
		assert len >= 1 && len <= 30;
		for (int i = 0; i < len; i++)
			assert cd.containsKey(s[i]) : "undefined letter";
		assert s[0] != ' ' && s[len - 1] != ' ' : "no leading or trailing spaces";
	}

	private static int countSpaces(String s) {
		int sum = 0;
		for (int i = 0, n = s.length(); i < n; i++)
			if (s.charAt(i) == ' ')
				sum++;
		return sum;
	}

	int cc;
	char[] c;
	CharDef[] d;
	int[][] free_cost;
	int[][][] cross_cost;
	int[][] letter_cost;
	int[][] sol;
	int[][] space;
	int[] new_pos;
	int[] new_space;

	long time;

	void time(String s) {
		long nano = System.nanoTime();
		System.out.printf(Locale.US, "%s: %,d ns%n", s, nano - time);
		time = nano;
	}

	void solve() {
		time = System.nanoTime();
		initDefinedChars();
		time("initDefinedChars");
		initFreeCost();
		time("initFreeCost");
		initCrossCost();
		time("initCrossCost");
		initLetterCost();
		time("initLetterCost");
		sol = new int[new_str.length][n];
		space = new int[new_str.length][n];
		for (int j = 0; j < n; j++)
			sol[0][j] = free_cost[0][j] + letter_cost[0][j];
		for (int i = 1; i < new_str.length; i++) {
			for (int j = 0; j < n; j++) {
				int best_cost = Integer.MAX_VALUE / 2;
				int best_space = -1;
				int to = Math.min(s_max, j - k);
				for (int s = s_min; s <= to; s++) {
					int tc = sol[i - 1][j - s - k] + free_cost[j - s][j] + letter_cost[i][j];
					if (tc < best_cost) {
						best_cost = tc;
						best_space = s;
					}
				}
				sol[i][j] = best_cost;
				space[i][j] = best_space;
			}
		}
		time("sol");
		int best_sol = Integer.MAX_VALUE;
		int best_pos = -1;
		for (int j = 0; j <= n - k; j++) {
			int tc = sol[new_str.length - 1][j] + free_cost[j + k][n];
			if (tc < best_sol) {
				best_sol = tc;
				best_pos = j;
			}
		}
		assert best_pos >= 0 : "solution exists";
		new_pos = new int[new_str.length];
		new_pos[new_str.length - 1] = best_pos;
		for (int i = new_str.length - 1; i > 0; i--) {
			new_pos[i - 1] = new_pos[i] - k - space[i][new_pos[i]];
		}
		new_space = new int[new_str.length];
		new_space[0] = new_pos[0];
		for (int i = 1; i < new_str.length; i++)
			new_space[i] = new_pos[i] - new_pos[i - 1] - k;
		time("path");
	}

	private void initDefinedChars() {
		cc = cd.size();
		c = new char[cc];
		d = new CharDef[cc];
		int i = 0;
		for (Map.Entry<Character, CharDef> entry : cd.entrySet()) {
			c[i] = entry.getKey();
			d[i] = entry.getValue();
			i++;
		}
	}

	private void initFreeCost() {
		int[] vc = new int[n];
		for (int i = 0; i < cur_str.length; i++) {
			int c1 = Arrays.binarySearch(c, cur_str[i]);
			for (int ofs = 0; ofs < k; ofs++) {
				int p = cur_pos[i] + ofs;
				if (p < n)
				vc[p] += freeLineCost(c1, ofs);
			}
		}
		free_cost = new int[n + 1][n + 1];
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j <= n; j++)
				free_cost[i][j] = free_cost[i][j - 1] + vc[j - 1];
		}
	}

	private void initCrossCost() {
		cross_cost = new int[c.length][c.length][k];
		for (int i = 0; i < c.length; i++)
			for (int j = 0; j < c.length; j++)
				for (int ofs = 0; ofs < k; ofs++)
					cross_cost[i][j][ofs] = crossCost(i, j, ofs);
	}

	int[] letterIdx(char[] s) {
		int[] idx = new int[s.length];
		for (int i = 0; i < s.length; i++)
			idx[i] = Arrays.binarySearch(c, s[i]);
		return idx;
	}

	private void initLetterCost() {
		letter_cost = new int[new_str.length][n];
		int[] cur_idx = letterIdx(cur_str);
		int[] new_idx = letterIdx(new_str);
		// char to char cross letter_cost
		for (int i = 0; i < cur_str.length; i++) {
			int c1 = cur_idx[i];
			for (int j = 0; j < new_str.length; j++) {
				int c2 = new_idx[j];
				for (int ofs = 0; ofs < k; ofs++) {
					int p = cur_pos[i] + ofs;
					if (p < n)
						letter_cost[j][p] += cross_cost[c1][c2][ofs];
				}
				for (int ofs = 1; ofs < k; ofs++) {
					int p = cur_pos[i] - ofs;
					if (p >= 0)
						letter_cost[j][p] += cross_cost[c2][c1][ofs];
				}
			}
		}
		// free space cross letter_cost
		for (int i = 0; i <= cur_str.length; i++) {
			int from = i == 0 ? 0 : cur_pos[i - 1] + k;
			int to = i < cur_str.length ? cur_pos[i] : n;
			for (int j = 0; j < new_str.length; j++) {
				int c2 = Arrays.binarySearch(c, new_str[j]);
				for (int p = Math.max(0, from - k + 1); p < to; p++)
					letter_cost[j][p] += spaceCost(c2, Math.max(0, from - p), Math.min(k, to - p));
			}
		}
	}

	private int freeLineCost(int c1, int ofs) {
		int sum = 0;
		int mask = 1 << (k - ofs - 1);
		for (int i = 0; i < m; i++)
			if ((d[c1].rows[i] & mask) != 0)
				sum++;
		return sum;
	}

	private int crossCost(int c1, int c2, int ofs) {
		int sum = 0;
		int mask = ((1 << k) - 1) - ((1 << ofs) - 1);
		for (int i = 0; i < m; i++)
			sum += Integer.bitCount(((d[c1].rows[i] << ofs) ^ d[c2].rows[i]) & mask);
		return sum;
	}

	private int spaceCost(int c2, int from_pos, int to_pos) {
		int sum = 0;
		int mask = ((1 << (k - from_pos)) - 1) - ((1 << (k - to_pos)) - 1);
		for (int i = 0; i < m; i++)
			sum += Integer.bitCount(d[c2].rows[i] & mask);
		return sum;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("caption.out");
		for (int i = 0; i < new_str.length; i++) {
			if (i > 0)
				out.print(' ');
			out.print(new_space[i]);
		}
		out.println();
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

		public String nextLine() {
			assert line != null : "EOF";
			String result = line.substring(pos);
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
			return result;
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
