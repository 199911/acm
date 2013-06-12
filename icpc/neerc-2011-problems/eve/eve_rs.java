import java.io.*;
import java.util.*;

public class eve_rs implements Runnable {
	private BufferedReader in;
	private PrintWriter out;

	private static class Graph {
		private List<Integer>[] edges;

		private int[] components;
		private int curComponent;

		@SuppressWarnings("unchecked")
		public Graph(int n) {
			edges = new List[n];
			for (int i = 0; i < n; i++) {
				edges[i] = new ArrayList<Integer>();
			}
			components = new int[n];
			Arrays.fill(components, -1);
			curComponent = 0;
		}

		public void addEdge(int u, int v) {
			edges[u].add(v);
			edges[v].add(u);
		}

		public int getComponentId(int u) {
			if (components[u] != -1) {
				return components[u];
			}
			dfs(u, curComponent++);
			return components[u];
		}

		private void dfs(int u, int c) {
			components[u] = c;
			for (int v : edges[u]) {
				if (components[v] == -1) {
					dfs(v, c);
				}
			}
		}
	}

	private void solve() throws IOException {
		int n = Integer.parseInt(in.readLine());
		boolean[] isMale = new boolean[n];
		for (int i = 0; i < n; i++) {
			isMale[i] = in.readLine().equals("M");
		}
		int m = Integer.parseInt(in.readLine());
		isMale = Arrays.copyOf(isMale, n + m);
		int curId = n;
		Graph g = new Graph(n + m);
		boolean[] isDead = new boolean[n + m];
		for (int i = 0; i < m; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int id1 = Integer.parseInt(st.nextToken());
			if (id1 > 0) {
				int mother = Integer.parseInt(st.nextToken()) - 1;
				int child = curId++;
				isMale[child] = st.nextToken().equals("M");
				g.addEdge(mother, child);
			} else {
				isDead[-id1 - 1] = true;
			}
		}
		Set<Integer> aliveComponents = new HashSet<Integer>();
		for (int i = 0; i < curId; i++) {
			if (!isDead[i]) {
				aliveComponents.add(g.getComponentId(i));
			}
		}

		Map<Integer, Integer> dna = new HashMap<Integer, Integer>();
		int k = Integer.parseInt(in.readLine());
		for (int i = 0; i < k; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int u = Integer.parseInt(st.nextToken()) - 1;
			int v = Integer.parseInt(st.nextToken());
			dna.put(g.getComponentId(u), v);
		}

		if (aliveComponents.size() == 1) {
			out.println("YES");
			return;
		}

		int dType = -1;
		boolean hasUnknown = false;
		for (int u : aliveComponents) {
			if (dna.containsKey(u)) {
				int d = dna.get(u);
				if (dType == -1 || dType == d) {
					dType = d;
				} else {
					out.println("NO");
					return;
				}
			} else {
				hasUnknown = true;
			}
		}
		if (!hasUnknown) {
			out.println("YES");
		} else {
			out.println("POSSIBLY");
		}
	}

	public static void main(String[] args) {
		new Thread(new eve_rs()).start();
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
