import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2011 Problem F: Flights
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class flights_re {
	private static final boolean NAIVE_VALIDATE = false;

	private static final double X_EPS = 1e-9;  // x < 1e5
	private static final double Y_EPS = 1e-12; // y < 1e2
	private static final double A_EPS = 1e-12; // a < 1e2
	private static final double B_EPS = 1e-7; // b < 1e7

	public static void main(String[] args) throws Exception {
		new flights_re().go();
	}

	long time;

	void time(String s) {
		long nano = System.nanoTime();
		System.out.printf(Locale.US, "%s: %,d ns%n", s, nano - time);
		time = nano;
	}

	void go() throws Exception {
		time = System.nanoTime();
		read();
		solve();
		write();
	}

	static double sqr(double x) {
		return x * x;
	}

	// y = a*x^2 + b*x + c
	static class Missile {
		final int index;

		final int x;
		final int y;

		final int x1;
		final int x2;

		final double a; // max |a| ~ max |y| ~ 1e2
		final double b; // max |b| ~ max |x*y| ~ 1e7
		final double c;

		Missile() {
			index = 0;
			x = 0;
			y = 0;
			x1 = Integer.MIN_VALUE;
			x2 = Integer.MAX_VALUE;
			a = 0;
			b = 0;
			c = 0;
		}

		Missile(int index, int p, int x, int y) {
			this.index = index;
			this.x = x;
			this.y = y;
			x1 = p;
			x2 = 2 * x - p;
			double d = sqr(p - x);
			a = -y / d;
			b = 2 * y * x / d;
			c = (y * sqr(p - x) - y * sqr(x)) / d;
		}

		double at(double x) {
			return a * sqr(x) + b * x + c;
		}

		double max(double x1, double x2) {
			return x1 < x && x < x2 ? y : Math.max(at(x1), at(x2));
		}

		@Override
		public String toString() {
			return String.format(Locale.US, "#%d [%d,%d] {%.4f %.4f %.4f}", index, x1, x2, a, b, c);
		}
	}

	static class Flight {
		final int t1;
		final int t2;
		final int x1;
		final int x2;

		double answer;

		Flight(int t1, int t2, int x1, int x2) {
			this.t1 = t1;
			this.t2 = t2;
			this.x1 = x1;
			this.x2 = x2;
		}
	}

	static class Chunk {
		final Missile m;
		final double x;

		Chunk(Missile m) {
			this.m = m;
			this.x = m.x1;
		}

		Chunk(Missile m, double x) {
			this.m = m;
			this.x = x;
		}

		@Override
		public String toString() {
			return String.format(Locale.US, "%.4f %s", x, m);
		}
	}

	static final class ChunkTree {
		final Chunk mid;
		final double x1;
		final double x2;
		final double max;
		final ChunkTree c1;
		final ChunkTree c2;

		ChunkTree(int i1, int i2, Chunk[] a) {
			if (i1 == i2) {
				mid = a[i1];
				x1 = mid.x;
				x2 = i1 + 1 < a.length ? a[i1 + 1].x : mid.m.x2;
				max = mid.m.max(x1, x2);
				c1 = null;
				c2 = null;
			} else {
				int m = (i1 + i2 + 1) / 2;
				c1 = new ChunkTree(i1, m - 1, a);
				c2 = new ChunkTree(m, i2, a);
				max = Math.max(c1.max, c2.max);
				mid = a[m];
				x1 = c1.x1;
				x2 = c2.x2;
			}
		}

		double max(double x1, double x2) {
			if (x2 < this.x1 - X_EPS || x1 > this.x2 + X_EPS)
				return 0;
			if (x1 < this.x1 + X_EPS && x2 > this.x2 - X_EPS)
				return max;
			if (c1 == null)
				return mid.m.max(Math.max(x1, this.x1), Math.min(x2, this.x2));
			return Math.max(c1.max(x1, x2), c2.max(x1, x2));
		}
	}

	static final Chunk GUARD = new Chunk(new Missile());

	static class ChunkList {
		final ChunkList l1;
		final ChunkList l2;
		final int t1;
		final int t2;
		final Chunk[] a;
		final ChunkTree root;

		ChunkList(int t, Missile one) {
			l1 = null;
			l2 = null;
			t1 = t;
			t2 = t;
			a = new Chunk[] { new Chunk(one) };
			root = new ChunkTree(0, 0, a);
		}

		ChunkList(ChunkList l1, ChunkList l2) {
			this.l1 = l1;
			this.l2 = l2;
			this.t1 = l1.t1;
			this.t2 = l2.t2;
			int i1 = 0;
			int i2 = 0;
			List<Chunk> chunks = new ArrayList<Chunk>();
			Chunk m0 = GUARD;
			double x0 = m0.x;
			while (i1 <= l1.a.length || i2 <= l2.a.length) {
				double x1 = l1.getX(i1);
				double x2 = l2.getX(i2);
				double xn = Math.min(x1, x2);
				Chunk m1 = l1.getM(i1 - 1);
				Chunk m2 = l2.getM(i2 - 1);
				while (x0 < xn - X_EPS) {
					double next = next(m1.m, m2.m, x0, xn);
					if (m1.m != m0.m)
						next = next(m1.m, m0.m, x0, next);
					else if (m2.m != m0.m)
						next = next(m2.m, m0.m, x0, next);
					Missile m = best(m1.m, m2.m, (x0 + next) / 2);
					if (m0.m != m) {
					   if (m0 != GUARD)
						   chunks.add(m0);
					   m0 = new Chunk(m, x0);
					}
					x0 = next;
				}
				if (x1 <= x2 && i1 <= l1.a.length) {
					i1++;
				} else {
					i2++;
				}
			}
			if (m0 != GUARD)
				chunks.add(m0);
			a = chunks.toArray(new Chunk[chunks.size()]);
			root = new ChunkTree(0, a.length - 1, a);
		}

		Chunk getM(int i) {
			return i >= 0 && i < a.length ? a[i] : GUARD;
		}

		double getX(int i) {
			return i < a.length ? a[i].x :
				i == a.length ? a[a.length - 1].m.x2 : Double.POSITIVE_INFINITY;
		}

		double computeMax(int t1, int t2, int x1, int x2) {
			if (t1 == this.t1 && t2 == this.t2)
				return root.max(x1, x2);
			double max = 0;
			if (t1 <= l1.t2) {
				max = l1.computeMax(t1, Math.min(t2, l1.t2), x1, x2);
			}
			if (t2 >= l2.t1) {
				max = Math.max(max, l2.computeMax(Math.max(l2.t1, t1), t2, x1, x2));
			}
			return max;
		}

		public void print() {
			System.out.println("#" + (t1 + 1) + " - #" + (t2 + 1));
			for (Chunk m : a) {
				System.out.println(m);
			}
		}
	}

	static double next(Missile m1, Missile m2, double x1, double x2) {
		double a = m1.a - m2.a;
		double b = m1.b - m2.b;
		double c = m1.c - m2.c;
		if (Math.abs(a) < A_EPS) {
			if (Math.abs(b) < B_EPS)
				return x2;
			double x = -c / b;
			if (x < x1 + X_EPS)
				return x2;
			return Math.min(x, x2);
		}
		b /= 2 * a;
		c /= a;
		double d = sqr(b) - c;
		if (d < 0)
			return x2;
		d = Math.sqrt(d);
		double x = -b - d;
		if (x < x1 + X_EPS) {
			x = -b + d;
			if (x < x1 + X_EPS)
				return x2;
		}
		return Math.min(x, x2);
	}

	static Missile best(Missile m1, Missile m2, double x) {
		double y1 = m1.at(x);
		double y2 = m2.at(x);
		return y1 > y2 + Y_EPS ? m1 : m2;
	}

	int n;
	Missile[] missiles;
	int m;
	Flight[] flights;

	void read() throws Exception {
		Scanner in = new Scanner(new File("flights.in"));
		n = in.nextInt();
		in.nextLine();
		assert n >= 1 && n <= 50000;
		missiles = new Missile[n];
		for (int i = 0; i < n; i++) {
			int p = in.nextInt();
			int x = in.nextInt();
			int y = in.nextInt();
			in.nextLine();
			assert p >= 0 && p < x && x <= 50000 && y > 0 && y <= 50 : p + " " + x + " " + y;
			missiles[i] = new Missile(i + 1, p, x, y);
		}
		m = in.nextInt();
		in.nextLine();
		assert m >= 1 && m <= 20000;
		flights = new Flight[m];
		for (int i = 0; i < m; i++) {
			int t1 = in.nextInt();
			int t2 = in.nextInt();
			int x1 = in.nextInt();
			int x2 = in.nextInt();
			in.nextLine();
			assert 1 <= t1 && t1 <= t2 && t2 <= n;
			assert 0 <= x1 && x1 <= x2 && x2 <= 50000;
			flights[i] = new Flight(t1, t2, x1, x2);
		}
		in.close();
		time("read");
	}

	ChunkList build(int t1, int t2) {
		if (t1 == t2)
			return new ChunkList(t1, missiles[t1]);
		int m = (t1 + t2) / 2;
		return new ChunkList(build(t1, m), build(m + 1, t2));
	}

	double naive(int t1, int t2, int x1, int x2) {
		double max = 0;
		for (int i = t1; i <= t2; i++)
			max = Math.max(max, missiles[i].max(x1, x2));
		return max;
	}

	void solve() {
		ChunkList root = build(0, n - 1);
		time("build");
		for (Flight f : flights) {
			f.answer = root.computeMax(f.t1 - 1, f.t2 - 1, f.x1, f.x2);
		}
		time("process");
		if (NAIVE_VALIDATE) {
			for (int i = 0; i < m; i++) {
				Flight f = flights[i];
				double naive = naive(f.t1 - 1, f.t2 - 1, f.x1, f.x2);
				assert Math.abs(naive - f.answer) < 1e-10 : String.format(Locale.US, "#%d: %.10f vs %.10f", i + 1, naive, f.answer);
			}
			time("validate");
		}
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("flights.out");
		for (Flight f : flights) {
			out.println(f.answer);
		}
		out.close();
		time("write");
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
