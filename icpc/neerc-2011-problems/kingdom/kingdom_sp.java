import java.io.*;
import java.util.*;

public class kingdom_sp {
	public static void main(String[] args) {
		new kingdom_sp().run();
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

	String FNAME = "kingdom";
	
	void dfs(int i, int par) {
		if (G[i].size() == 1) {
			leafs.add(i + 1);
		}
		for (int j : G[i]) {
			if (j != par) {
				dfs(j, i);
			}
		}
	}
	
	ArrayList<Integer> leafs = new ArrayList<Integer>();
	
	ArrayList<Integer>[] G;

	private void solve() throws IOException {
		int n = nextInt();
		G = new ArrayList[n];
		for (int i = 0; i < n; i++) {
			G[i] = new ArrayList<Integer>();
		}
		for (int i = 0; i < n - 1; i++) {
			int a = nextInt() - 1;
			int b = nextInt() - 1;
			G[a].add(b);
			G[b].add(a);
		}
		if (n == 2) {
			out.println(1);
			out.println("1 2");
			return;
		}
		for (int i = 0; i < n; i++) {
			if (G[i].size() > 1) {
				dfs(i, -1);
				break;
			}
		}
		int m = leafs.size() / 2;
		out.println(m + leafs.size() % 2);
		for (int i = 0; i < m ; i++) {
			out.println(leafs.get(i) + " " + leafs.get(i + m));
		}
		if (leafs.size() % 2 == 1) {
			out.println(leafs.get(0) + " " + leafs.get(leafs.size() - 1));
		}
	}
}
