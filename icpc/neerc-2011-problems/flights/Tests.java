import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

public class Tests {
	private static int TEST_COUNTER = 0;
	private static final File TESTS_DIR = new File("tests");
	private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");
	private static final Random RND = new Random(84);

	private final PrintWriter out;
	private int n;
	private int m;
	private int[][] ps;
	private int[][] qs;
	
	final static int MAXLEN = 50000;
	final static int MAXH = 50;

	final static int MAXM = 20000;

	private Tests(String description) throws IOException {
		String tn = String.format("%02d", ++TEST_COUNTER);
		File tests = new File("tests");
		tests.mkdir();
		PrintWriter lst = new PrintWriter(new FileWriter(TESTS_LST, true));
		lst.println(tn + " " + description);
		lst.close();
		out = new PrintWriter(new FileWriter(new File(tests, tn)));
	}

	private void write() {
		out.println(n);
		for (int i = 0; i < n; i++) {
			out.println(ps[i][0] + " " + ps[i][1] + " " + ps[i][2]);
		}
		out.println(m);
		for (int i = 0; i < m; i++) {
			out.println(qs[i][0] + " " + qs[i][1] + " " + qs[i][2] + " " + qs[i][3]);
		}
		out.close();
	}

	private void hand(int n, int[][] ps, int m, int[][] qs) {
		this.n = n;
		this.ps = ps;
		this.m = m;
		this.qs = qs;
		write();
	}

	private void randomPoints(int n, int len, int h) {
		this.generateRandomParabols(n, len, 1, h);
		this.generatePoints(len);
		write();
	}

	private void randomIntervals(int n, int len, int h, int m) {
		this.generateRandomParabols(n, len, 1, h);
		this.generateRandomQueries(m, len, len);
		write();
	}

	private void randomIntervalsSmall(int n, int len, int h, int m) {
		this.generateRandomParabols(n, len, 1, h);
		this.generateRandomQueries(m, len, len / 100);
		write();
	}

	private void linearMaxTime(int n, int len, int h, int m) {
		this.generateLinearParabols(n, len, h, false);
		this.m = m;
		qs = new int[m][4];
		for (int i = 0; i < m; i++) {
			qs[i][0] = RND.nextInt(10) + 1;
			qs[i][1] = RND.nextInt(10) + n - 9;
			qs[i][2] = RND.nextInt(1000);
			qs[i][3] = RND.nextInt(1000) + len - 999;
		}
		write();
	}

	private void linearRandom(int n, int len, int h, int m) {
		this.generateLinearParabols(n, len, h, true);
		this.generateRandomQueries(m, len, len);
		write();
	}

	private void antiCheat(int n, int len, int h, int m) {
		this.generateRandomParabols(n, len, h - 1, h);
		this.m = m;
		qs = new int[m][4];
		for (int i = 0; i < m; i++) {
			qs[i][0] = 1;
			qs[i][1] = n;
			qs[i][2] = len - 2;
			qs[i][3] = len;
		}
		write();
	}

	private void antiCheat2(int n, int len, int h, int m) {
		this.n = n;
		ps = new int[n][3];
		int w = len / 2 - 1;
		for (int i = 0; i < n; i++) {
			ps[i][0] = RND.nextInt(2);
			ps[i][1] = ps[i][0] + w;
			ps[i][2] = RND.nextInt(3) + h - 2;
		}

		this.m = m;
		qs = new int[m][4];
		for (int i = 0; i < m; i++) {
			qs[i][0] = 1;
			qs[i][1] = n;
			qs[i][2] = 0;
			qs[i][3] = 1;
		}
		write();
	}

	private double sqr(double x) {
		return x * x;
	}

	private void myAssert(boolean f) {
		if (!f)
			throw new RuntimeException("botva");
	}

	private int rndInt(Random r, int L, int R) {
		return L + r.nextInt(R - L + 1);
	}

	private void burunduk1(int N, int M) {
		Random RND = new Random(239); // I use my instance of Random, so the test does not depend on order of tests.

		final int X = 50000;
		final int P = X - (6 << 13);
		final int Y = 6 * 6;
		double a = Y / sqr(X - P);

		final int V = 4;
		final int X1 = X - (V << 13);
		final int Y1 = 6 * 6 - V * V;
		myAssert(Math.abs(Y - a * sqr(X1 - X) - Y1) < 1e-4);
		System.err.println("answer is " + Y1);

		int p[] = new int[N];
		int x[] = new int[N];
		int y[] = new int[N];

		p[N - 1] = P; x[N - 1] = X; y[N - 1] = Y;
		for (int i = 0; i < N - 1; i++) {
			int cx, cy, cp = -1;
			while (true) {
				cx = rndInt(RND, 0, 50000);
				cy = rndInt(RND, Y1 + 1, 50);
				if (cx == X1)
					continue;
				a = (cy - Y1) / sqr(cx - X1);
				myAssert(a > 0);
				double x0 = cx - Math.sqrt(cy / a);
				myAssert(Math.abs(cy - a * sqr(cx - x0)) < 1e-4);
				cp = (int)Math.ceil(x0);
				if (cp < 0)
					continue;
				myAssert(cp < cx);
				a = cy / sqr(cx - cp);
				double Y2 = cy - a * sqr(cx - X1);
				if (Y2 < Y1 - 3e-4) // 3e-4 > eps from statements
					break;
			}
    		x[i] = cx; y[i] = cy; p[i] = cp;
  		}
		
		int ind[] = new int[N];
		for (int i = 0; i < N; i++)
			ind[i] = i;
		for (int i = 0; i < N; i++) {
			int j = RND.nextInt(N);
			int xx = ind[j]; ind[j] = ind[i]; ind[i] = xx;
		}

		this.n = N;
		ps = new int[N][3];
		for (int j = 0; j < N; j++) {
			int i = ind[j];
			ps[j][0] = p[i];	
			ps[j][1] = x[i];	
			ps[j][2] = y[i];	
		}

		this.m = M;
		qs = new int[M][4];
		final int DT = (int)Math.sqrt(M);
		for (int i = 0; i < M; i++) {
			qs[i][0] = 1 + RND.nextInt(DT);
			qs[i][1] = N - RND.nextInt(DT);
			qs[i][2] = X1;
			qs[i][3] = X1;
		}

		write();
	}

	private void coinsidePoints(int mul, int inside, int linear, int big) {
		int len = this.generateCoinside(mul, inside, linear, big);
		this.generatePoints(len);
		write();
	}

	private void coinsideRandom(int mul, int inside, int linear, int big, int m) {
		int len = this.generateCoinside(mul, inside, linear, big);
		this.generateRandomQueries(m, len, len);
		write();
	}

	private int generateCoinside(int mul, int inside, int linear, int big) {
		ps = new int[mul * (inside + linear + big)][3];
		int[] p = this.generatePermutation(ps.length, true);
		n = 0;
		int len = 0;
		for (int i = 0; i < inside; i++) {
			for (int j = 0; j < mul; j++) {
				ps[p[n]][0] = len + i;
				ps[p[n]][1] = len + inside;
				ps[p[n]][2] = inside - i;
				n++;
			}
		}
		len += 2 * inside;
		
		for (int i = 0; i < linear; i++) {
			for (int j = 0; j < mul; j++) {
				ps[p[n]][0] = len + i;
				ps[p[n]][1] = len + i + 1;
				ps[p[n]][2] = 7;
				n++;
			}
		}
		len += linear + 1;
		
		int w = (big + 1) / 2;
		for (int i = 0; i < big; i++) {
			for (int j = 0; j < mul; j++) {
				ps[p[n]][0] = len + i;
				ps[p[n]][1] = len + i + w;
				ps[p[n]][2] = 17;
				n++;
			}
		}
		len += 2 * big - 1;

		return len;
	}

	private void generatePoints(int len) {
		qs = new int[Math.min(MAXM, (len + 1) * n * (n + 1) / 2)][4];
		m = 0;
		for (int i = 0; i <= len; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = j; k <= n; k++) {
					qs[m][0] = j;
					qs[m][1] = k;
					qs[m][2] = i;
					qs[m][3] = i;
					m++;
					if (m >= MAXM)
						return;
				}
			}
		}
	}

	private void generateLinearParabols(int n, int len, int h, boolean shuffle) {
		this.n = n;
		ps = new int[n][3];
		
		int[] p = this.generatePermutation(n, shuffle);
		int maxW = len / n * 3;
		
		int cur = 0;
		for (int i = 0; i < n; i++) {
			int rem = (n - i - 1);
			// cur + 2 * d <= len - 2 * rem;
			int d = RND.nextInt( Math.min(maxW, (len - 2 * rem - cur) / 2) ) + 1;
			int num = p[i];
			ps[num][0] = cur;
			ps[num][1] = cur + d;
			ps[num][2] = RND.nextInt(h) + 1;
			cur = cur + 2 * d - 1;
		}
	}

	private int[] generatePermutation(int n, boolean shuffle) {
		int[] p = new int[n];
		for (int i = 0; i < n; i++) {
			int j = shuffle ? RND.nextInt(i + 1) : i;
			p[i] = p[j];
			p[j] = i;
		}
		return p;
	}

	private void generateRandomParabols(int n, int len, int minh, int maxh) {
		this.n = n;
		ps = new int[n][3];
		int h = maxh - minh + 1;
		for (int i = 0; i < n; i++) {
			int lx = RND.nextInt(len - 1);
			int w = RND.nextInt((len - lx) / 2) + 1;
			int px = lx + w;
			int tmp = (int) Math.floor(1e-6 + Math.sqrt(RND.nextInt(h * h) + 1)); // 1 .. h
			int py = minh + (h - tmp);
			ps[i][0] = lx;
			ps[i][1] = px;
			ps[i][2] = py;
		}
	}

	private void generateRandomQueries(int m, int len, int maxW) {
		this.m = m;
		qs = new int[m][4];
		for (int i = 0; i < m; i++) {
			int lt = RND.nextInt(n) + 1;
			int rt = RND.nextInt(n - lt + 1) + lt;
			int lx = RND.nextInt(len);
			int rx = RND.nextInt(Math.min(len - lx + 1, maxW + 1)) + lx;
			qs[i][0] = lt;
			qs[i][1] = rt;
			qs[i][2] = lx;
			qs[i][3] = rx;
		}
	}

	public static void main(String[] args) throws IOException {
		TESTS_LST.delete();

		new Tests("First sample").hand(
				2, new int[][] {{10, 30, 10}, {20, 30, 30}},
				4, new int[][] {
					{1, 2, 0, 11},
					{1, 2, 20, 25}, 
					{1, 2, 25, 35}, 
					{1, 2, 45, 100}, 
				});
		new Tests("Second sample").hand(
				2, new int[][] {{0, 10, 10}, {30, 40, 10}},
				6, new int[][] {{1, 2, 0, 32}, {1, 1, 19, 35}, {2, 2, 0, 32}, {1, 2, 15, 35}, {1, 2, 21, 27}, {1, 2, 2, 100}});
		new Tests("3 parabols, 3 intersections").hand(
				3, new int[][] {{10, 30, 40}, {0, 40, 20}, {30, 50, 40}},
				8, new int[][] {{2, 2, 30, 40}, {2, 3, 30, 40}, {2, 3, 30, 33}, {1, 3, 30, 33},
						        {1, 2, 42, 48}, {1, 3, 42, 48}, {1, 3, 40, 40}, {1, 3, 0, 80}});
		
		new Tests("Small random, all points checked").randomPoints(2, 10, 10);
		new Tests("Small random, all points checked").randomPoints(10, 10, 10);
		new Tests("Small random, all points checked").randomPoints(99, 5, 50);
		new Tests("Small random, all points checked").randomPoints(30, 50, 30);
		new Tests("Small random, all points checked").randomPoints(50, 20, 30);

		new Tests("Small random").randomIntervals(10, 10, 10, 100);
		new Tests("Small random").randomIntervals(100, 80, 37, 5000);
		new Tests("Big random in small area").randomIntervals(11111, 123, 12, 17777);
		new Tests("Big random in small area").randomIntervals(50000, 200, 13, 20000);
		new Tests("Big random in medium area").randomIntervals(50000, 10000, 30, 20000);
		new Tests("Big random in medium area").randomIntervals(50000, 10000, 30, 20000);

		new Tests("Big random in vertical area").randomIntervals(50000, 20, MAXH, 20000);
		new Tests("Big random in horizontal area").randomIntervals(50000, MAXLEN, 10, 20000);
		
		new Tests("Big random in large area").randomIntervals(50000, MAXLEN, MAXH, 20000);
		new Tests("Big random in large area").randomIntervals(50000, MAXLEN, MAXH, 20000);
		new Tests("Big random in large area").randomIntervals(50000, MAXLEN, MAXH, 20000);

		new Tests("Big random, small queries").randomIntervalsSmall(50000, MAXLEN, MAXH, 20000);
		new Tests("Big random, small queries").randomIntervalsSmall(50000, MAXLEN, MAXH, 20000);
		
		new Tests("Max time").linearMaxTime(20000, MAXLEN, MAXH, 20000);
		new Tests("Linear random").linearRandom(20000, MAXLEN, MAXH, 20000);
		new Tests("Linear random").linearRandom(19999, MAXLEN, MAXH, 19998);
		
		new Tests("Coinside, different configurations, all points").coinsidePoints(2, 5, 6, 6);
		new Tests("Coinside large").coinsideRandom(10, 45, 2000, 2200, 20000);
		new Tests("Big parabols").coinsideRandom(1, 0, 0, 22000, 20000);
		
		new Tests("Anti-cheat: a lot of queires with small answer").antiCheat(50000, MAXLEN, MAXH, 20000);
		new Tests("Anti-cheat v2").antiCheat2(50000, MAXLEN, MAXH, 20000);

		new Tests("Burunduk1's test: All f_i(x0) = y0 - eps_i").burunduk1(50000, 20000);

		new Tests("Same parabolas with different height 1").hand(
				2, new int[][] {{0, 2, 4}, {1, 2, 1}},
				1, new int[][] {{1, 2, 0, 4}});

		new Tests("Same parabolas with different height 2").hand(
				2, new int[][] {{1, 2, 1}, {0, 2, 4}},
				1, new int[][] {{1, 2, 0, 4}});
	}
}
