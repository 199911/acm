import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.StringTokenizer;

/**
 * Wrong solution for NEERC'2011 Problem K: Kingdom Roadmap.
 * The solution misses some edges.
 * 
 * @author Dmitry Paraschenko
 */
public class kingdom_dp_wa5 implements Runnable {
	private static final int MAXN = 100000;
	private int n;
	private List<Set<Integer>> edges;
	private boolean[] visited;
	private ArrayList<int[]> answer;

	private void solve() throws Exception {
		answer = new ArrayList<int[]>();
		n = nextInt();
		if (n <= 1 || n > MAXN) {
			throw new AssertionError("illegal number of nodes");
		}
		edges = new ArrayList<Set<Integer>>();
		for (int i = 0; i < n; i++) {
			edges.add(new HashSet<Integer>());
		}
		for (int i = 1; i < n; i++) {
			int v1 = nextInt();
			int v2 = nextInt();
			if (v1 < 1 || v1 > n) {
				throw new AssertionError();
			}
			if (v2 < 1 || v2 > n) {
				throw new AssertionError();
			}
			v1--;
			v2--;
			if (!edges.get(v1).add(v2)) {
				throw new AssertionError("multiedges are not allowed");
			}
			if (!edges.get(v2).add(v1)) {
				throw new AssertionError("multiedges are not allowed");
			}
		}
		visited = new boolean[n];
		int count = 0;
		int root = -1; 
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				dfscheck(-1, i);
				count++;
			}
			if (edges.get(i).size() > 1) {
				root = i;
			}
		}
		if (count != 1) {
			throw new AssertionError("graph is not connected");
		}
		if (n == 2) {
			out.println("1");
			out.println("1 2");
			return;
		}
		if (root == -1) {
			throw new AssertionError();
		}
		int[] result = solve(-1, root);
		if (result.length == 2) {
			connect(result[0], result[1]);
		} else if (result.length == 1) {
			connect(result[0], answer.get(0)[0]);
		}
		out.println(answer.size());
		for (int[] e : answer) {
			out.printf("%d %d\n", e[0] + 1, e[1] + 1);
		}
	}

	private int[] solve(int p, int v) {
		ArrayList<int[]> pairs = new ArrayList<int[]>();
		ArrayList<Integer> singles = new ArrayList<Integer>();
		for (int u : edges.get(v)) {
			if (u == p) {
				continue;
			}
			int[] result = solve(v, u);
			if (result.length == 1) {
				if (singles.size() == 2) {
					int single1 = singles.get(0);
					int single2 = singles.get(1);
					connect(single1, single2);
					singles.clear();
				}
				singles.add(result[0]);
			} else if (result.length == 2) {
				if (pairs.size() == 2) {
					int[] pair1 = pairs.get(0);
					int[] pair2 = pairs.get(1);
					connect(pair1[0], pair2[0]);
					pairs.clear();
					pairs.add(new int[] {pair1[1], pair2[1]});
				}
				pairs.add(result);
			} else {
				throw new IllegalStateException();
			}
		}
		if (pairs.size() == 2) {
			int[] pair1 = pairs.get(0);
			int[] pair2 = pairs.get(1);
			connect(pair1[0], pair2[0]);
			singles.add(pair1[1]);
			singles.add(pair2[1]);
		} else if (pairs.size() == 1) {
			int[] pair1 = pairs.get(0);
			if (singles.size() == 0) {
				return pair1;
			}
			int single1 = singles.get(0);
			connect(single1, pair1[0]);
			singles.set(0, pair1[1]);
		}
		while (singles.size() > 2) {
			int single1 = singles.get(singles.size() - 1);
			singles.remove(singles.size() - 1);
			int single2 = singles.get(singles.size() - 1);
			singles.remove(singles.size() - 1);
			connect(single1, single2);
		}
		if (singles.size() == 2) {
			int single1 = singles.get(0);
			int single2 = singles.get(1);
			return new int[] {single1, single2};
		} else if (singles.size() == 1) {
			int single1 = singles.get(0);
			return new int[] {single1};
		}
		// the node is a leaf
		return new int[] {v};
	}

	private void connect(int v1, int v2) {
		v1 %= n;
		v2 %= n;
		answer.add(new int[] {v1, v2});
	}

	private void dfscheck(int p, int v) {
		if (visited[v]) {
			throw new AssertionError("the graph contains cycles");
		}
		visited[v] = true;
		int parents = 0;
		for (int u : edges.get(v)) {
			if (u == p) {
				if (parents > 0) {
					// this check is, in fact, irrelevant
					throw new AssertionError("the graph contains multiedges");
				}
				parents++;
				continue;
			}
			dfscheck(v, u);
		}
	}

	//========================================
	private BufferedReader in;
	private StringTokenizer st;
	private PrintWriter out;

	public kingdom_dp_wa5(String file) {
		try {
			in = new BufferedReader(new FileReader(file + ".in"));
			st = new StringTokenizer("");
			out = new PrintWriter(file + ".out");
		} catch (FileNotFoundException e) {
			halt(e);
		}
	}

	public void run() {
		try {
			solve();
		} catch (Throwable e) {
			halt(e);
		} finally {
			out.close();
		}
	}
	
	private String nextToken() throws IOException {
		while (!st.hasMoreTokens()) {
			String line = in.readLine();
			if (line == null) {
				return null;
			}
			st = new StringTokenizer(line);
		}
		return st.nextToken();
	}

	private int nextInt() throws IOException {
		return Integer.parseInt(nextToken());
	}
	
	private void halt(Throwable e) {
		System.exit(239);
	}

	public static void main(String[] args) {
		new Thread(new kingdom_dp_wa5("kingdom")).start();
	}
}
