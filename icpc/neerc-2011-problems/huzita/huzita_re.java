import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2011 Problem H: Huzita Axiom 6
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class huzita_re {
	private static final double EPS = 1e-10;

	public static void main(String[] args) throws Exception {
		new huzita_re().go();
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	static int readCoordinate(Scanner in) {
		int c = in.nextInt();
		assert Math.abs(c) <= 10;
		return c;
	}

	static class Pt {
		final int x;
		final int y;

		public Pt(Scanner in) {
			x = readCoordinate(in);
			y = readCoordinate(in);
		}

		@Override
		public boolean equals(Object o) {
			if (this == o) return true;
			if (!(o instanceof Pt)) return false;
			Pt pt = (Pt) o;
			return x == pt.x && y == pt.y;
		}

		@Override
		public int hashCode() {
			return 31 * x + y;
		}
	}

	static double sqr(double x) {
		return x * x;
	}

	static double cube(double x) {
		return x * x * x;
	}

	static double cbrt(double x) {
		return Math.pow(Math.abs(x), 1.0 / 3) * Math.signum(x);
	}

	static double len(double x, double y) {
		return Math.sqrt(sqr(x) + sqr(y));
	}

	static class Ln {
		final Pt q1;
		final Pt q2;

		// a * x + b * y = c
		final double a;
		final double b;
		final double c;

		public Ln(Scanner in) {
			q1 = new Pt(in);
			q2 = new Pt(in);
			assert !q1.equals(q2);
			double a = q1.y - q2.y;
			double b = q2.x - q1.x;
			double d = len(a, b);
			a /= d;
			b /= d;
			this.a = a;
			this.b = b;
			this.c = q1.x * a + q1.y * b;
		}

		public boolean contains(Pt p) {
			return Math.abs(a * p.x + b * p.y - c) < EPS;
		}
	}

	static class Case {
		final Ln l1;
		final Pt p1;
		final Ln l2;
		final Pt p2;

		public Case(Scanner in) {
			l1 = new Ln(in);
			in.nextLine();
			p1 = new Pt(in);
			in.nextLine();
			l2 = new Ln(in);
			in.nextLine();
			p2 = new Pt(in);
			in.nextLine();
			assert !l1.contains(p1) && !l2.contains(p2);
		}
	}

	static class C implements Comparable<C> {
		int p1;
		int p2;
		double c;
		int o;

		C(int p1, int p2, double c, int o) {
			this.p1 = p1;
			this.p2 = p2;
			this.c = c;
			this.o = o;
		}

		public int compareTo(C o) {
			int r = p1 - o.p1;
			if (r != 0)
					return r;
			return p2 - o.p2;
		}

		@Override
		public String toString() {
			return String.format(Locale.US, "%d%d*%.6f(%d)", p1, p2, c, o);
		}
	}

	static void add(List<C> res, int p1, int p2, double c, int o) {
		for (int i = 0, n = res.size(); i < n; i++) {
			C rc = res.get(i);
			if (rc.p1 == p1 && rc.p2 == p2) {
				rc.c += c;
				rc.o = Math.max(rc.o, o);
				return;
			}
		}
		res.add(new C(p1, p2, c, o));
	}

	static C[] result(List<C> res) {
		Collections.sort(res);
		return res.toArray(new C[res.size()]);
	}

	static C[] mul(C[] a, C[] b) {
		List<C> res = new ArrayList<C>();
		for (C ca : a) {
			for (C cb : b) {
				add(res, ca.p1 + cb.p1, ca.p2 + cb.p2, ca.c * cb.c, ca.o + cb.o);
			}
		}
		return result(res);
	}

	static C[] add(C[] a, C[] b) {
		List<C> res = new ArrayList<C>(Arrays.asList(a));
		for (C cb : b) {
			add(res, cb.p1, cb.p2, cb.c, cb.o);
		}
		return result(res);
	}

	static C[] sub(C[] a, C[] b) {
		List<C> res = new ArrayList<C>(Arrays.asList(a));
		for (C cb : b) {
			add(res, cb.p1, cb.p2, -cb.c, cb.o);
		}
		return result(res);
	}

	static C[] eliminate2(C[] a, int p2) {
		List<C> res = new ArrayList<C>();
		for (C ca : a) {
			if (ca.p2 == p2) {
				add(res, ca.p1, 0, ca.c, ca.o);
			}
		}
		return result(res);
	}

	static class Family {
		// Equation:
		// a * x + b * y = c, where
		// a = a0 + a1 * t
		// b = b0 + b1 * t
		// c = c0 + c1 * t + c2 * t^2
		final double a0;
		final double a1;
		final double b0;
		final double b1;
		final double c0;
		final double c1;
		final double c2;

		// Representative point:
		// x' = f0 + f1 * t
		// y' = g0 + g1 * t
		final double f0;
		final double f1;
		final double g0;
		final double g1;

		Family(Ln l, Pt p) {
			a0 = l.q1.x - p.x;     // O1
			a1 = l.q2.x - l.q1.x;  // O1
			b0 = l.q1.y - p.y;     // O1
			b1 = l.q2.y - l.q1.y;  // O1

			double c = l.q1.x + p.x; // O1
			double d = l.q1.y + p.y; // O1

			c0 = (a0 * c + b0 * d) / 2; // O2
			c1 = (a1 * c + a0 * a1 + b1 * d + b0 * b1) / 2; // O2
			c2 = (sqr(a1) + sqr(b1)) / 2; // O2

			f0 = c / 2;  // O1
			f1 = a1 / 2; // O1
			g0 = d / 2;  // O1
			g1 = b1 / 2; // O1
		}

		C[] a(int p1, int p2) {
			return new C[] { new C(0, 0, a0, 1), new C(p1, p2, a1, 1)};
		}

		C[] b(int p1, int p2) {
			return new C[] { new C(0, 0, b0, 1), new C(p1, p2, b1, 1)};
		}

		C[] c(int p1, int p2) {
			return new C[] { new C(0, 0, c0, 2), new C(p1, p2, c1, 2), new C(p1 * 2, p2 * 2, c2, 2)};
		}

		C[] x(int p1, int p2) {
			return new C[] { new C(0, 0, f0, 1), new C(p1, p2, f1, 1)} ;
		}

		C[] y(int p1, int p2) {
			return new C[] { new C(0, 0, g0, 1), new C(p1, p2, g1, 1)} ;
		}

		double a(double t) {
			return a0 + a1 * t;
		}

		double b(double t) {
			return b0 + b1 * t;
		}

		double x(double t) {
			return f0 + f1 * t;
		}

		double y(double t) {
			return g0 + g1 * t;
		}
	}

	static class Solution {
		double x1;
		double y1;
		double x2;
		double y2;

		Solution(double x1, double y1, double x2, double y2) {
			this.x1 = x1;
			this.y1 = y1;
			this.x2 = x2;
			this.y2 = y2;
		}
	}

	int t;
	Case[] c;
	Solution[] s;

	void read() throws Exception {
		Scanner in = new Scanner(new File("huzita.in"));
		in.useLocale(Locale.US);
		t = in.nextInt();
		in.nextLine();
		assert t >= 0 && t <= 20000;
		c = new Case[t];
		for (int i = 0; i < t; i++)
			c[i] = new Case(in);
		in.close();
	}

	static void print(C[] e) {
		for (C c : e) {
			System.out.print(" " + c);
		}
	}

	// a1 * x + a0 = 0
	static double solve1(double a0, double a1) {
		return Math.abs(a1) < EPS ? Double.NaN : -a0 / a1;
	}

	// x^2 + a1 * x + a0 = 0
	static double solve2(double a0, double a1) {
  		double d = sqr(a1 / 2) - a0;
		if (d < -EPS)
			return Double.NaN;
		if (d < EPS)
			return -a1 / 2;
		double d2 = Math.sqrt(d);
		return d2 - a1 / 2;
	}

	// a2 * x^2 + a1 * x + a0 = 0
	static double solve2(double a0, double a1, double a2) {
		return Math.abs(a2) < EPS ? solve1(a0, a1) : solve2(a0 / a2, a1 / a2);
	}

	// x^3 + a2 * x^2 + a1 * x + a0 = 0
	static double solve3(double a0, double a1, double a2) {
		double x1 = -1;
		while (compute3(x1, a0, a1, a2) > 0)
			x1 *= 2;
		double x2 = 1;
		while (compute3(x2, a0, a1, a2) < 0)
			x2 *= 2;
		while (x2 - x1 > EPS) {
			double x = (x1 + x2) / 2;
			double z = compute3(x, a0, a1, a2);
			if (z < 0)
				x1 = x;
			else
				x2 = x;
		}
		return (x1 + x2) / 2;
	}

	static double compute3(double x, double a0, double a1, double a2) {
		return ((x + a2) * x + a1) * x + a0;
	}

	// a3 * x^3 + a2 * x^2 + a1 * x + a0 = 0
	static double solve3(double a0, double a1, double a2, double a3) {
		return Math.abs(a3) < EPS ? solve2(a0, a1, a2) : solve3(a0 / a3, a1 / a3, a2 / a3);
	}

	static Solution solve(Case c) {
		Family f1 = new Family(c.l1, c.p1);
		Family f2 = new Family(c.l2, c.p2);

		C[] p = sub(mul(f1.a(1, 0), f2.b(0, 1)), mul(f1.b(1, 0), f2.a(0, 1)));
		C[] q = sub(add(mul(f1.a(1, 0), f2.x(0, 1)), mul(f1.b(1, 0), f2.y(0, 1))), f1.c(1, 0));

		C[] p0 = eliminate2(p, 0);
		C[] p1 = eliminate2(p, 1);
		C[] q0 = eliminate2(q, 0);
		C[] q1 = eliminate2(q, 1);

		C[] e = sub(mul(q0, p1), mul(q1, p0));
		assert e.length == 4;

		double t = solve3(e[0].c, e[1].c, e[2].c, e[3].c);

//		print(e);
//		System.out.println(" -> " + t);

		if (Double.isNaN(t))
			return null;
		double x1 = f1.x(t);
		double y1 = f1.y(t);
		double x2 = x1 + f1.b(t);
		double y2 = y1 - f1.a(t);
		return new Solution(x1, y1, x2, y2);
	}

	void solve() {
		s = new Solution[t];
		for (int i = 0; i < t; i++)
			s[i] = solve(c[i]);
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("huzita.out");
		for (int i = 0; i < t; i++) {
			Solution sol = s[i];
			if (sol == null) {
				out.println("0 0 0 0");
			} else {
				out.println(sol.x1 + " " + sol.y1 + " " + sol.x2 + " " + sol.y2);
			}
		}
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
