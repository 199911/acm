import java.io.*;
import java.util.*;

public class ascii_ab {
	public static void main(String[] args) {
		new ascii_ab().run();
	}

	BufferedReader br;
	StringTokenizer st;
	PrintWriter out;
	boolean eof = false;

	private void run() {
		Locale.setDefault(Locale.US);
		try {
			br = new BufferedReader(new FileReader(FNAME + ".in"));
			out = new PrintWriter(FNAME + ".out");
			solve();
			out.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(566);
		}
	}

	String nextToken() {
		while (st == null || !st.hasMoreTokens()) {
			try {
				st = new StringTokenizer(br.readLine());
			} catch (Exception e) {
				eof = true;
				return "0";
			}
		}
		return st.nextToken();
	}

	int nextInt() {
		return Integer.parseInt(nextToken());
	}

	String FNAME = "ascii";

	private void solve() throws IOException {
		int n = nextInt();
		int m = nextInt();
		ArrayList<Point> b = new ArrayList<Point>();
		ArrayList<Point> e = new ArrayList<Point>();
		for (int i = 0; i < n; ++i) {
			String s = nextToken();
			for (int j = 0; j < s.length(); ++j) {
				char c = s.charAt(j);
				if (c == '\\') {
					b.add(new Point(i, j));
					e.add(new Point(i + 1, j + 1));
				} else if (c == '/') {
					b.add(new Point(i, j + 1));
					e.add(new Point(i + 1, j));
				}
			}
		}
		
		ArrayList<Point> poly = new ArrayList<Point>();
		boolean[] u = new boolean[b.size()];
		int ci = 0;
		u[ci] = true;
		poly.add(b.get(ci));
		poly.add(e.get(ci));
		loop:
		while (true) {
			for (int i = 0; i < b.size(); ++i) {
				if (!u[i] && b.get(i).equals(e.get(ci))) {
					ci = i;
					u[i] = true;
					poly.add(e.get(ci));
					continue loop;
				} else if (!u[i] && e.get(i).equals(e.get(ci))) {
					Point tb = b.get(i);
					Point te = e.get(i);
					b.set(i, te);
					e.set(i, tb);
					u[i] = true;
					ci = i;
					poly.add(e.get(ci));
					continue loop;
				}
			}
			break;
		}
		
		int ans = 0;
		
		for (int i = 0; i < poly.size() - 1; ++i) {
			int next = i + 1;
			Point a1 = poly.get(i);
			Point b1 = poly.get(next);
			ans += a1.x * b1.y - a1.y * b1.x;
//			System.out.println(a1.x + " "+ a1.y);
		}
		
		out.println(Math.abs(ans) / 2);
	}
	
	
	class Point {
		int x, y;
		
		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}

		@Override
		public boolean equals(Object o) {
			Point p = (Point)o;
			return p.x == x && p.y == y;
		}
		
	}

}
