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
public class kingdom_dp_wa implements Runnable {
	private int n;
	private List<Set<Integer>> edges;
	private ArrayList<int[]> answer;

	private void solve() throws Exception {
		answer = new ArrayList<int[]>();
		n = nextInt();
		edges = new ArrayList<Set<Integer>>();
		for (int i = 0; i < n; i++) {
			edges.add(new HashSet<Integer>());
		}
		for (int i = 1; i < n; i++) {
			int v1 = nextInt();
			int v2 = nextInt();
			v1--;
			v2--;
			edges.get(v1).add(v2);
			edges.get(v2).add(v1);
		}
		int[] result = solve(-1, 0);
		if (result.length == 2) {
			connect(result[0], result[1]);
		} else if (result.length == 1) {
			connect(result[0], result[0] + 1);
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
					connect(pair1[1], pair2[1]);
					pairs.clear();
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

	//========================================
	private BufferedReader in;
	private StringTokenizer st;
	private PrintWriter out;

	public kingdom_dp_wa(String file) {
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
		} catch (Exception e) {
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
	
	private void halt(Exception e) {
		System.exit(239);
	}

	public static void main(String[] args) {
		new Thread(new kingdom_dp_wa("kingdom")).start();
	}
}
