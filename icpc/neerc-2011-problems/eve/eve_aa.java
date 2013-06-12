import java.io.*;
import java.util.*;

public class eve_aa {
	public static void main(String[] args) {
		new eve_aa().run();
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

	String FNAME = "eve";

	private void solve() throws IOException {
		int mid = 0;
		int n = nextInt();
		HashMap<Integer, Indiv> hm = new HashMap<Integer, Indiv>();
		for (int i = 0; i < n; i++) {
			Indiv ind = new Indiv(i + 1, nextToken().charAt(0) == 'M' ? 1 : 0);
			hm.put(ind.id, ind);
		}
		mid = n;
		int m = nextInt();
		for (int i = 0; i < m; i++) {
			int x = nextInt();
			if (x > 0) {
				int y = nextInt();
				int sex = nextToken().charAt(0) == 'M' ? 1 : 0;
				Indiv mother = hm.get(y);
				Indiv child = new Indiv(++mid, sex);
				mother.edges.add(child);
				child.edges.add(mother);
				hm.put(child.id, child);
			} else {
				x = -x;
				hm.get(x).alive = false;
			}
		}
		int k = nextInt();
		for (int i = 0; i < k; i++) {
			int id = nextInt();
			int color = nextInt();
			Indiv ind = hm.get(id);
			if (ind.color == -1) {
				dfs(ind, color);
			}
		}
		int neg = 0;
		for (Indiv i : hm.values()) {
			if (i.alive && i.color == -1) {
				dfs(i, -++neg - 1);
			}
		}
		HashSet<Integer> livingColors = new HashSet<Integer>();
		for (Indiv i : hm.values()) {
			// System.out.println(i.id + " " + i.color);
			// for (Indiv j : i.edges) {
			// System.out.println("	" + j.id);
			// }
			if (i.alive) {
				livingColors.add(i.color);
			}
		}
		int pos = 0;
		neg = 0;
		for (int i : livingColors) {
			if (i > 0) {
				pos++;
			} else {
				neg++;
			}
		}
		if (pos == 1 && neg == 0 || neg == 1 && pos == 0) {
			out.println("YES");
		} else if (pos > 1) {
			out.println("NO");
		} else {
			out.println("POSSIBLY");
		}
	}

	private void dfs(Indiv x, int color) {
		x.color = color;
		for (Indiv i : x.edges) {
			if (i.color == -1) {
				dfs(i, color);
			}
		}
	}

	class Indiv {
		public Indiv(int i, int j) {
			id = i;
			sex = j;
			color = -1;
			alive = true;
			edges = new ArrayList<Indiv>();
		}

		int id;
		int sex;
		int color;
		boolean alive;

		ArrayList<Indiv> edges;
	}
}
