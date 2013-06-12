import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Reader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class flights_dg_wa implements Runnable {
	
	/*
	 * Solution:
	 * 1. Create interval tree A on based on the time. Each node corresponds to parabols segment [i..j].
	 * 2. For each node, store the parabolic line - the union of all parabols and negative half-plane.
	 * 3. For each node except leafs, line is constructed by merging two child nodes' lines.
	 * 4. Inside each line, create interval tree B to find maximum height between consecutive parabol segments [i..j].
	 * 5. For each query, split time segment [min..max] to nodes of tree A.
	 * 6. Inside each node, binary search for x1 and x2 to find the corresponding parabol segment.
	 * 7. Query tree B for minimum on consecutive segments, and relax on the side (partial) ones.
	 */
	
	double eps = 1e-7;

	// Set to true to disable internal trees.
	final static boolean LINEAR = false;
	
	class Parabola {
		double a, b, c;
		double px, py;
		double lx, rx;
		boolean zero;
		
		public Parabola(double lx, double px, double py) {
			this.lx = lx;
			this.px = px;
			this.py = py;
			rx = 2 * px - lx;
			zero = false;
			
			double d = det(lx * lx, lx, 1, rx * rx, rx, 1, px * px, px, 1);
			a = det(0, lx, 1, 0, rx, 1, py, px, 1) / d;
			b = det(lx * lx, 0, 1, rx * rx, 0, 1, px * px, py, 1) / d;
			c = det(lx * lx, lx, 0, rx * rx, rx, 0, px * px, px, py) / d;
		}

		public Parabola() {
			lx = Double.NEGATIVE_INFINITY;
			rx = Double.POSITIVE_INFINITY;
			px = py = a = b = c = 0;
			zero = true;
		}

		public double query(double from, double to) {
			if (from < lx - eps || to > rx + eps || from > to + eps) {
				throw new AssertionError();
			}
			return to <= px ? this.value(to) : (from >= px ? this.value(from) : py);
		}

		private double value(double x) {
			double result = zero ? 0 : a * x * x + b * x + c;
			return result;
		}
		
		public double[] intersect(Parabola o) {
			double na = a - o.a;
			double nb = b - o.b;
			double nc = c - o.c;
			
			if (Math.abs(na) < eps) {
				if (Math.abs(nb) < eps) {
					return new double[] {};
				}
				return new double[] {-nc / nb};
			}
			
			double nd = nb * nb - 4 * na * nc;
			if (nd < 0) {
				return new double[] {};
			}
			nd = Math.sqrt(nd);
			double x1 = (-nb + nd) / (2 * na);
			double x2 = (-nb - nd) / (2 * na);
			
			return new double[] {x1, x2};
		}
	}
	
	class ParabolicLine {
		int count;
		double[] x;
		Parabola[] p;
		double[] max;
		
		public ParabolicLine(Parabola single) {
			count = 3;
			x = new double[4];
			x[0] = Double.NEGATIVE_INFINITY;
			x[1] = single.lx;
			x[2] = single.rx;
			x[3] = Double.POSITIVE_INFINITY;
			p = new Parabola[3];
			p[0] = ox;
			p[1] = single;
			p[2] = ox;
			makeTree();
		}
		
		public ParabolicLine(ParabolicLine pl1, ParabolicLine pl2) {
			ArrayList<Double> nx = new ArrayList<Double>();
			ArrayList<Parabola> np = new ArrayList<Parabola>();
			count = 0;
			
			double curx = Double.NEGATIVE_INFINITY;
			ParabolicLine[] pl = new ParabolicLine[2];
			pl[0] = pl1;
			pl[1] = pl2;
			int[] ind = new int[2];
			ind[0] = 0;
			ind[1] = 0;
			
			while (curx < Double.POSITIVE_INFINITY) {
				for (int i = 0; i < 2; i++) {
					while (pl[i].x[ind[i] + 1] < curx + eps) {
						ind[i]++;
					}
				}
				
				double value0 = pl[0].p[ind[0]].value(curx);
				double value1 = pl[1].p[ind[1]].value(curx);
				double value0e = pl[0].p[ind[0]].value(curx + 1e-3);
				double value1e = pl[1].p[ind[1]].value(curx + 1e-3);
				
				int up;
				if (Math.abs(value0 - value1) > eps) {
					// The upper one.
					up = value0 > value1 ? 0 : 1;
				} else if (Math.abs(value0e - value1e) > eps) {
					// Equal in curx, choose the more curve one.
					up = value0e > value1e ? 0 : 1;
				} else {
					// Coinside, choose the one with nearest intersection.
					up = pl[0].x[ind[0] + 1] > pl[1].x[ind[1] + 1] ? 1 : 0;
				}
				int down = 1 - up;
				
				nx.add(curx);
				np.add(pl[up].p[ind[up]]);
				count++;

				double nextx = Math.min(pl[up].x[ind[up] + 1], pl[down].x[ind[down] + 1]);
				double[] xx = pl[up].p[ind[up]].intersect(pl[down].p[ind[down]]);
				for (double x : xx) {
					if (x > curx + eps && x < nextx) {
						nextx = x;
					}
				}
				
				curx = nextx;
			}
			
			// Positive infinity.
			nx.add(curx);
			
			if (np.size() != count || nx.size() != count + 1) {
				throw new AssertionError();
			}
			
			p = new Parabola[count];
			for (int i = 0; i < count; i++) {
				p[i] = np.get(i);
			}
			x = new double[count + 1];
			for (int i = 0; i <= count; i++) {
				x[i] = nx.get(i);
			}
			makeTree();
		}

		private void makeTree() {
			if (LINEAR) {
				return;
			}
			max = new double[2 * count - 1];
			for (int i = 0; i < count; i++) {
				max[i + count - 1] = p[i].query(x[i], x[i + 1]);
			}
			for (int i = count - 2; i >= 0; i--) {
				max[i] = Math.max(max[2 * i + 1], max[2 * i + 2]);
			}
		}

		private double treeQuery(int i, int j) {
			double result = Double.NEGATIVE_INFINITY;
			i += count - 1;
			j += count - 1;
			while (i <= j) {
				result = Math.max(result, max[i]);
				result = Math.max(result, max[j]);
				i = i / 2;
				j = (j / 2) - 1;
			}
			return result;
		}

		public double query(double lx, double rx) {
			int left = Arrays.binarySearch(x, lx);
			if (left < 0) {
				left = -(left + 1);
			}
			left--;
			
			int right = Arrays.binarySearch(x, rx);
			if (right < 0) {
				right = -(right + 1);
			}
			right--;
			
			if (left == right) {
				return p[left].query(lx, rx);
			}

			double res = p[left].query(lx, x[left + 1]);
			if (LINEAR) {
				for (int i = left + 1; i < right; i++) {
					res = Math.max(res, p[i].query(x[i], x[i + 1]));
				}
			} else {
				res = Math.max(res, treeQuery(left + 1, right - 1));
			}
			res = Math.max(res, p[right].query(x[right], rx));
			
			return res;
		}
	}
	
	class Node {
		ParabolicLine line;
		Node nl;
		Node nr;
		int l;
		int r;
		
		public Node(int left, int right) {
			l = left;
			r = right;
			if (l == r) {
				line = new ParabolicLine(parabols[l]);
				nl = nr = null;
				return;
			}
			
			int mid = (l + r) / 2;
			nl = new Node(left, mid);
			nr = new Node(mid + 1, right);
			line = new ParabolicLine(nl.line, nr.line);
		}

		public double query(int left, int right, double lx, double rx) {
			if (right < this.l || left > this.r) {
				return Double.NEGATIVE_INFINITY;
			}
			
			if (left <= this.l && right >= this.r) {
				return this.line.query(lx, rx);
			}
			
			return Math.max(this.nl.query(left, right, lx, rx), this.nr.query(left, right, lx, rx));
		}
	}
	
	int n;
	Parabola[] parabols;
	Node root;
	Parabola ox;
	
	private void solve() throws IOException {
		n = in.nextInt();
		parabols = new Parabola[n];
		for (int i = 0; i < n; i++) {
			parabols[i] = new Parabola(in.nextDouble(), in.nextDouble(), in.nextDouble());
		}
		ox = new Parabola();
		
		root = new Node(0, n - 1);
		
		int m = in.nextInt();
		for (int i = 0; i < m; i++) {
			int lt = in.nextInt() - 1;
			int rt = in.nextInt() - 1;
			double lx = in.nextDouble();
			double rx = in.nextDouble();
			out.println(root.query(lt, rt, lx, rx));
		}
	}

	public double det(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
		return x1 * (y2 * z3 - y3 * z2) - y1 * (x2 * z3 - x3 * z2) + z1 * (x2 * y3 - x3 * y2);
	}

	public static void main(String[] args) {
		new Thread(new flights_dg_wa()).start();
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
