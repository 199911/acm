import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

/**
 * Tests generator for NEERC'2011 Problem L: Lanes
 * @author Roman Elizarov
 */
public class Tests {
	private static int TEST_COUNTER = 0;
	private static final File TESTS_DIR = new File("tests");
	private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");

	private static final Random RND = new Random(20111118);
	private static final int MAX_M = 100000;

	private final PrintWriter out;

	private final int m;
	private final int[] lr;
	private final int[] rl;

	private Tests(String description, int n1, int n2, int m, int r) throws IOException {
		this.m = m ;
		this.lr = new int[m];
		this.rl = new int[m];

		String tn = String.format("%02d", ++TEST_COUNTER);
		System.out.println(tn + " - " + description);
		PrintWriter lst = new PrintWriter(new FileWriter(TESTS_LST, true));
		lst.println(tn + " " + description);
		lst.close();
		out = new PrintWriter(new FileWriter(new File(TESTS_DIR, tn)));
		out.println(n1 + " " + n2 + " " + m + " " + r);
	}

	private Tests lr(int... a) {
		System.arraycopy(a, 0, lr, 0, a.length);
		return this;
	}

	private Tests rl(int... a) {
		System.arraycopy(a, 0, rl, 0, a.length);
		return this;
	}

	private void write() {
		for (int i = 0; i < m; i++) {
			out.println(lr[i] + " " + rl[i]);
		}
		out.close();
	}

	private interface Gen {
		int[] gen(int m);
	}

	private static class Rnd implements Gen {
		final int max;

		private Rnd(int max) {
			this.max = max;
		}

		public int[] gen(int m) {
			int[] a = new int[m];
			for (int i = 0; i < m; i++)
				a[i] = RND.nextInt(max + 1);
			return a;
		}

		public String toString() {
			return "Rnd(" + max + ")";
		}
	}

	private static class RndD implements Gen {
		final int max;

		private RndD(int max) {
			this.max = max;
		}

		public int[] gen(int m) {
			int[] a = new int[m];
			for (int i = 0; i < m; i++)
				a[i] = RND.nextInt(2 + max * (m - 1 - i) / m);
			return a;
		}

		public String toString() {
			return "RndD(" + max + ")";
		}
	}

	private static class RndU implements Gen {
		final int max;

		private RndU(int max) {
			this.max = max;
		}

		public int[] gen(int m) {
			int[] a = new int[m];
			for (int i = 0; i < m; i++)
				a[i] = RND.nextInt(2 + max * i / m);
			return a;
		}

		public String toString() {
			return "RndU(" + max + ")";
		}
	}

	private static class Const implements Gen {
		final int max;

		private Const(int max) {
			this.max = max;
		}

		public int[] gen(int m) {
			int[] a = new int[m];
			for (int i = 0; i < m; i++)
				a[i] = max;
			return a;
		}

		public String toString() {
			return "Const(" + max + ")";
		}
	}

	private static final void randomTest(int n1, int n2, int m, int r, Gen lr, Gen rl) throws IOException {
		new Tests("Random " + n1 + " " + n2 + " " + m + " "  + r + " " + lr + " " + rl, n1, n2, m, r).
				lr(lr.gen(m)).rl(rl.gen(m)).write();

	}

	public static void main(String[] args) throws IOException {
		TESTS_LST.delete();
		TESTS_DIR.mkdir();

		new Tests("Sample", 2, 2, 10, 2).
				lr(1, 2, 3, 4, 3, 2, 1, 0, 1, 0).
				rl(0, 1, 2, 2, 3, 3, 5, 3, 2, 1).
				write();
		new Tests("Minimal", 1, 1, 1, 1).
				write();
		new Tests("Minimal 1lr", 1, 1, 1, 1).
				lr(1).
				write();
		new Tests("Minimal 1rl", 1, 1, 1, 1).
				rl(1).
				write();
		new Tests("Minimal 1l+1r", 1, 1, 1, 1).
				lr(1).
				rl(1).
				write();
		new Tests("Minimal 100l+100r", 1, 1, 1, 1).
				lr(100).
				rl(100).
				write();
		new Tests("Minimal 100l+100r and m=100", 1, 1, 100, 1).
				lr(100).
				rl(100).
				write();
		new Tests("Sample in, but 1 lr lane", 1, 2, 10, 2).
				lr(1, 2, 3, 4, 3, 2, 1, 0, 1, 0).
				rl(0, 1, 2, 2, 3, 3, 5, 3, 2, 1).
				write();
		new Tests("Sample in, but 1 rl lane", 2, 1, 10, 2).
				lr(1, 2, 3, 4, 3, 2, 1, 0, 1, 0).
				rl(0, 1, 2, 2, 3, 3, 5, 3, 2, 1).
				write();
		new Tests("Sample in, but 5 rl lanes", 2, 5, 10, 2).
				lr(1, 2, 3, 4, 3, 2, 1, 0, 1, 0).
				rl(0, 1, 2, 2, 3, 3, 5, 3, 2, 1).
				write();
		new Tests("Sample in, but 1+5 lanes", 1, 5, 10, 2).
				lr(1, 2, 3, 4, 3, 2, 1, 0, 1, 0).
				rl(0, 1, 2, 2, 3, 3, 5, 3, 2, 1).
				write();
		new Tests("Sample in, but 10 lanes each way", 10, 10, 10, 2).
				lr(1, 2, 3, 4, 3, 2, 1, 0, 1, 0).
				rl(0, 1, 2, 2, 3, 3, 5, 3, 2, 1).
				write();

		randomTest(2, 3, 100, 10, new Rnd(4), new Rnd(5));
		randomTest(3, 3, 100, 10, new Rnd(6), new Rnd(7));
		randomTest(3, 3, 100, 10, new Rnd(8), new Rnd(7));
		randomTest(3, 3, 100, 10, new Rnd(10), new Rnd(10));
		randomTest(10, 10, 100, 10, new Rnd(10), new Rnd(10));
		randomTest(10, 10, 100, 50, new Rnd(10), new Rnd(10));

		randomTest(6, 6, 100, 5, new RndD(10), new RndU(10));
		randomTest(6, 7, 100, 5, new RndD(10), new RndU(10));
		randomTest(7, 6, 100, 5, new RndD(10), new RndU(10));

		// big rnd

		randomTest(8, 9, 88888, 88, new RndD(15), new RndU(15));

		// max sizes

		randomTest(10, 10, MAX_M, 1, new Rnd(100), new Rnd(100));
		randomTest(10, 10, MAX_M, 1, new RndD(100), new Rnd(100));
		randomTest(10, 10, MAX_M, 1, new Rnd(100), new RndU(100));
		randomTest(10, 10, MAX_M, 1, new RndD(100), new RndU(100));
		randomTest(10, 10, MAX_M, 1, new RndD(20), new RndU(20));
		randomTest(10, 10, MAX_M, 1, new RndD(100), new Const(100));
		randomTest(10, 10, MAX_M, 1, new Const(100), new RndU(100));
		randomTest(10, 10, MAX_M, 1, new Const(100), new Const(100));
		randomTest(10, 10, MAX_M, 1, new Const(11), new Const(11));
		randomTest(10, 10, MAX_M, 1, new Const(11), new Const(13));

		randomTest(10, 10, MAX_M, 1000, new Rnd(100), new Rnd(100));
		randomTest(10, 10, MAX_M, 1000, new RndD(100), new Rnd(100));
		randomTest(10, 10, MAX_M, 1000, new Rnd(100), new RndU(100));
		randomTest(10, 10, MAX_M, 1000, new RndD(100), new RndU(100));
		randomTest(10, 10, MAX_M, 1000, new RndD(20), new RndU(20));
		randomTest(10, 10, MAX_M, 1000, new RndD(100), new Const(100));
		randomTest(10, 10, MAX_M, 1000, new Const(100), new RndU(100));
		randomTest(10, 10, MAX_M, 1000, new Const(100), new Const(100));
		randomTest(10, 10, MAX_M, 1000, new Const(11), new Const(11));
		randomTest(10, 10, MAX_M, 1000, new Const(13), new Const(17));

		randomTest(10, 10, MAX_M, MAX_M, new Rnd(100), new Rnd(100));
		randomTest(10, 10, MAX_M, MAX_M, new RndD(100), new Rnd(100));
		randomTest(10, 10, MAX_M, MAX_M, new Rnd(100), new RndU(100));
		randomTest(10, 10, MAX_M, MAX_M, new RndD(100), new RndU(100));
		randomTest(10, 10, MAX_M, MAX_M, new RndD(20), new RndU(20));
		randomTest(10, 10, MAX_M, MAX_M, new RndD(100), new Const(100));
		randomTest(10, 10, MAX_M, MAX_M, new Const(100), new RndU(100));
		randomTest(10, 10, MAX_M, MAX_M, new Const(10), new Const(10));
		randomTest(10, 10, MAX_M, MAX_M, new Const(11), new Const(11));
		randomTest(10, 10, MAX_M, MAX_M, new Const(15), new Const(15));

		randomTest(1, 1, MAX_M, 1, new Rnd(100), new Rnd(100));
		randomTest(1, 1, MAX_M, 1, new RndD(100), new Rnd(100));
		randomTest(1, 1, MAX_M, 1, new Rnd(100), new RndU(100));
		randomTest(1, 1, MAX_M, 1, new RndD(100), new RndU(100));
		randomTest(1, 1, MAX_M, 1, new RndD(4), new RndU(4));
		randomTest(1, 1, MAX_M, 1, new RndD(5), new RndU(3));
		randomTest(1, 1, MAX_M, 1, new RndD(100), new Const(100));
		randomTest(1, 1, MAX_M, 1, new Const(100), new RndU(100));

		randomTest(1, 1, MAX_M, 1, new Const(100), new Const(100));
		randomTest(1, 1, MAX_M, 1, new Const(100), new Const(0));
		randomTest(1, 1, MAX_M, 1, new Const(0), new Const(100));
		randomTest(1, 1, MAX_M, 1, new Const(0), new Const(0));

		randomTest(1, 1, MAX_M, MAX_M, new Const(100), new Const(100));
		randomTest(1, 1, MAX_M, MAX_M, new Const(100), new Const(0));
		randomTest(1, 1, MAX_M, MAX_M, new Const(0), new Const(100));
		randomTest(1, 1, MAX_M, MAX_M, new Const(0), new Const(0));
	}
}
