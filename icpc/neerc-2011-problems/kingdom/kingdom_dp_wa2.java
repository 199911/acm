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
public class kingdom_dp_wa2 implements Runnable {
	private int n;
	private List<Set<Integer>> edges;
	private ArrayList<int[]> answer;
	private ArrayList<Integer> leafs;

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
		leafs = new ArrayList<Integer>();
		for (int i = 0; i < n; i++) {
			if (edges.get(i).size() == 1) {
				leafs.add(i);
			}
		}
		for (int i = 0; i + 1 < leafs.size(); i += 2) {
			connect(leafs.get(i), leafs.get(i + 1));
		}
		if (leafs.size() % 2 == 1) {
			int v = leafs.get(leafs.size() - 1);
			connect(v, v + 1);
		}
		out.println(answer.size());
		for (int[] e : answer) {
			out.printf("%d %d\n", e[0] + 1, e[1] + 1);
		}
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

	public kingdom_dp_wa2(String file) {
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
		new Thread(new kingdom_dp_wa2("kingdom")).start();
	}
}
