import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Reader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class flights_dg_naive implements Runnable {
	
	double eps = 1e-7;

	class Parabola {
		double a, b, c;
		double px, py;
		double lx, rx;
		
		public Parabola(double lx, double px, double py) {
			this.lx = lx;
			this.px = px;
			this.py = py;
			rx = 2 * px - lx;
			
			double d = det(lx * lx, lx, 1, rx * rx, rx, 1, px * px, px, 1);
			a = det(0, lx, 1, 0, rx, 1, py, px, 1) / d;
			b = det(lx * lx, 0, 1, rx * rx, 0, 1, px * px, py, 1) / d;
			c = det(lx * lx, lx, 0, rx * rx, rx, 0, px * px, px, py) / d;
			
			if (Math.abs(py - this.value(px)) > eps) {
				throw new AssertionError();
			}
			if (Math.abs(0 - this.value(lx)) > eps) {
				throw new AssertionError();
			}
			if (Math.abs(0 - this.value(rx)) > eps) {
				throw new AssertionError();
			}
		}

		public double query(double from, double to) {
			from = Math.max(from, lx);
			to = Math.min(to, rx);
			if (from > to + eps) {
				return 0;
			}
			return to <= px ? this.value(to) : (from >= px ? this.value(from) : py);
		}

		private double value(double x) {
			double result = a * x * x + b * x + c; 
			if (x < lx || x > rx || result < -eps || result > py + eps) {
				throw new AssertionError();
			}
			return result;
		}
	}
	
	int n;
	Parabola[] parabols;
	
	private void solve() throws IOException {
		n = in.nextInt();
		parabols = new Parabola[n];
		for (int i = 0; i < n; i++) {
			parabols[i] = new Parabola(in.nextDouble(), in.nextDouble(), in.nextDouble());
		}

		int m = in.nextInt();
		for (int i = 0; i < m; i++) {
			int lt = in.nextInt() - 1;
			int rt = in.nextInt() - 1;
			double lx = in.nextDouble();
			double rx = in.nextDouble();
			double result = 0;
			for (int j = lt; j <= rt; j++) {
				result = Math.max(result, parabols[j].query(lx, rx));
			}
			out.println(result);
		}
	}

	public double det(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
		return x1 * (y2 * z3 - y3 * z2) - y1 * (x2 * z3 - x3 * z2) + z1 * (x2 * y3 - x3 * y2);
	}

	public static void main(String[] args) {
		new Thread(new flights_dg_naive()).start();
	}

	public void run() {
		try {
			in = new FastScanner(new FileReader("flights.in"));
			out = new PrintWriter(new File("flights.out"));
			
			solve();
			
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	PrintWriter out;
	FastScanner in;
	
	class FastScanner {
		
		BufferedReader reader;
		StringTokenizer st;

		public FastScanner(Reader reader) {
			this.reader = new BufferedReader(reader);
			st = null;
		}
		
		String next() throws IOException {
			while (st == null || !st.hasMoreTokens()) {
				st = new StringTokenizer(reader.readLine());
			}
			return st.nextToken();
		}
		
		int nextInt() throws NumberFormatException, IOException {
			return Integer.parseInt(next());
		}

		long nextLong() throws NumberFormatException, IOException {
			return Long.parseLong(next());
		}
		
		double nextDouble() throws NumberFormatException, IOException {
			return Double.parseDouble(next());
		}

		String nextLine() throws IOException {
			st = null;
			return reader.readLine();
		}
	}

}
