import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2011 Problem E: Eve
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class eve_re {
	private static final int MAX_M = 100000;
	private static final int MAX_N = 100000;
	private static final int MAX_SEQ = 1000000000;

	public static void main(String[] args) throws Exception {
		new eve_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	static class Family {
		int seq;

		@Override
		public String toString() {
			return Integer.toString(seq);
		}
	}

	static class Individual {
		int id;
		Individual mi;
		Individual fi;
		char sex;
		int seq;
		boolean dead;
		Family family;

		Individual(int id, char sex) {
			this.id = id;
			this.sex = sex;
		}

		Individual(int id, Individual mi, Individual fi, char sex) {
			this.id = id;
			this.mi = mi;
			this.fi = fi;
			this.sex = sex;
		}

		void initFamily() {
			if (family != null)
				return;
			Individual q = this;
			for (Individual p = fi; p != null; p = p.fi) {
				q = p;
				if (p.family != null)
					break;
			}
			if (q.family == null)
				q.family = new Family();
			for (Individual p = this; p != null && p.family == null; p = p.fi)
				p.family = q.family;
		}

		void initFamilySeq() {
			if (seq != 0) {
				assert family.seq == 0 || family.seq == seq;
				family.seq = seq;
			}
		}

		@Override
		public String toString() {
			return id + " " + sex + " " + seq + " {" + family + "}";
		}

	}

	int n;
	int m;
	int k;
	Map<Integer, Individual> ind = new HashMap<Integer, Individual>();

	void read() throws Exception {
		Scanner in = new Scanner(new File("eve.in"));
		n = in.nextInt();
		in.nextLine();
		assert 1 <= n && n <= MAX_N;
		for (int i = 1; i <= n; i++) {
			char sex = readSex(in);
			in.nextLine();
			ind.put(i, new Individual(i, sex));
		}
		int lastId = n;
		m = in.nextInt();
		in.nextLine();
		assert 0 <= m && m <= MAX_M;
		for (int i = 0; i < m; i++) {
			int mid = in.nextInt();
			if (mid < 0) {
				// death
				Individual mi = ind.get(-mid);
				assert !mi.dead;
				mi.dead = true;
			} else {
				// birth
				int fid = in.nextInt();
				char sex = readSex(in);
				Individual mi = ind.get(mid);
				Individual fi = ind.get(fid);
				assert mi.sex == 'M' && !mi.dead;
				assert fi.sex == 'F' && !fi.dead;
				lastId++;
				ind.put(lastId, new Individual(lastId, mi, fi, sex));
			}
			in.nextLine();
		}
		k = in.nextInt();
		in.nextLine();
		assert 0 <= k && k <= n + m;
		for (int i = 0; i < k; i++) {
			int sid = in.nextInt();
			int seq = in.nextInt();
			in.nextLine();
			assert 1 <= seq && seq <= MAX_SEQ;
			Individual si = ind.get(sid);
			assert si.seq == 0;
			si.seq = seq;
		}
		in.close();
	}

	private char readSex(Scanner in) {
		String sex = in.next();
		assert sex.equals("M") || sex.equals("F");
		return sex.charAt(0);
	}

	enum Result { YES, NO, POSSIBLY }

	Result result;

	void solve() {
		for (Individual ci : ind.values())
			ci.initFamily();
		for (Individual ci : ind.values())
			ci.initFamilySeq();
		int lastNewSeq = 0;
		for (Individual ci : ind.values())
			if (ci.family.seq == 0)
				ci.family.seq = --lastNewSeq;

		int aliveCount = 0;
		SortedSet<Integer> seqs = new TreeSet<Integer>();
		for (Individual ci : ind.values()) {
			if (!ci.dead) {
				aliveCount++;
				seqs.add(ci.family.seq);
				//System.out.println(ci);
			}
		}
		assert aliveCount > 0;
		if (seqs.tailSet(0).size() > 1)
			result = Result.NO;
		else if (seqs.size() == 1)
			result = Result.YES;
		else
			result = Result.POSSIBLY;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("eve.out");
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
