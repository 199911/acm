import java.io.*;
import java.util.*;

public class kingdom_rs implements Runnable {
	private BufferedReader in;
	private PrintWriter out;

	private List<Integer>[] edges;
	private boolean[] mark;
	private int[] unpaired;
	private int unpairedCount;

	private void printEdge(int u, int v) {
		out.println((u + 1) + " " + (v + 1));
	}

	private void dfs(int u) {
		mark[u] = true;
		for (int v : edges[u]) {
			if (mark[v]) {
				continue;
			}
			dfs(v);
			if (unpairedCount > 2) {
				printEdge(unpaired[0], unpaired[unpairedCount - 1]);
				unpaired[0] = unpaired[1];
				unpaired[1] = unpaired[2];
				unpairedCount -= 2;
			}
		}
		if (u > 0 && edges[u].size() == 1) {
			unpaired[unpairedCount++] = u;
		}
	}

	@SuppressWarnings("unchecked")
	private void solve() throws IOException {
		int n = Integer.parseInt(in.readLine());
		edges = new ArrayList[n];
		for (int i = 0; i < n; i++) {
			edges[i] = new ArrayList<Integer>();
		}
		for (int i = 0; i < n - 1; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int u = Integer.parseInt(st.nextToken()) - 1;
			int v = Integer.parseInt(st.nextToken()) - 1;
			edges[u].add(v);
			edges[v].add(u);
		}
		int answer = 0;
		for (int i = 0; i < n; i++) {
			if (edges[i].size() == 1) {
				answer++;
			}
		}
		unpaired = new int[4];
		unpairedCount = 0;
		mark = new boolean[n];
		out.println((answer + 1) / 2);
		dfs(0);
		if (unpairedCount == 2) {
			if (edges[0].size() == 1) {
				printEdge(0, unpaired[0]);
				printEdge(0, unpaired[1]);
			} else {
				printEdge(unpaired[0], unpaired[1]);
			}
			return;
		}
		printEdge(0, unpaired[0]);
	}

	public static void main(String[] args) {
		new Thread(new kingdom_rs()).start();
	}

	@Override
	public void run() {
		try {
			String problemName = getClass().getName().split("_")[0];
			in = new BufferedReader(new FileReader(
					new File(problemName + ".in")));
			out = new PrintWriter(new File(problemName + ".out"));
			solve();
			in.close();
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}
