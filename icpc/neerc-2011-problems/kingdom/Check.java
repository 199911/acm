import java.util.ArrayList;
import java.util.List;

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

/**
 * Checker for NEERC'2011 Problem K: Kingdom Roadmap.
 * 
 * @author Dmitry Paraschenko
 */
public class Check implements Checker {
	private int n;
	private List<List<Integer>> edges;
	private int[] enter;
	private int time;
	
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		n = inf.nextInt();
		edges = new ArrayList<List<Integer>>();
		for (int i = 0; i < n; i++) {
			edges.add(new ArrayList<Integer>());
		}
		for (int i = 1; i < n; i++) {
			int v1 = inf.nextInt();
			int v2 = inf.nextInt();
			if (!addEdge(v1, v2)) {
				throw new Outcome(Outcome.Type.FAIL, String.format("wrong input file format: node must be between %d and %d", 1, n));
			}
		}
		final int pa = ouf.nextInt();
		for (int i = 0; i < pa; i++) {
			int v1 = ouf.nextInt();
			int v2 = ouf.nextInt();
			if (!addEdge(v1, v2)) {
				throw new Outcome(Outcome.Type.PE, String.format("node must be between %d and %d", 1, n));
			}
		}
		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.PE, "extra information in the output file");
		
		enter = new int[n];
		time = 0;
		dfs(-1, 0);
		if (time != n) {
			throw new Outcome(Outcome.Type.FAIL, "error in checker");
		}
		
		final int ja = ans.nextInt();
		if (pa > ja)
			throw new Outcome(Outcome.Type.WA, String.format("%d instead of %d", pa, ja));
		if (pa < ja)
			throw new Outcome(Outcome.Type.FAIL, String.format("participant has better answer: %d instead of %d", pa, ja));
		return new Outcome(Outcome.Type.OK, String.format("n=%d %d", n, pa));
	}

	private int dfs(int p, int v) {
		enter[v] = ++time;
		int parents = 0;
		int result = time;
		for (int u : edges.get(v)) {
			if (u == p) {
				if (parents > 0) {
					// multiedge p --- v
					result = Math.min(result, enter[u]);
				}
				parents++;
				continue;
			}
			if (enter[u] > 0) {
				// the 'u' is ancestor of 'v'
				result = Math.min(result, enter[u]);
			} else {
				int res = dfs(v, u);
				if (res > enter[v]) {
					throw new Outcome(Outcome.Type.WA, String.format("bridge was found: %d %d", v + 1, u + 1));
				}
				result = Math.min(result, res);
			}
		}
		return result;
	}

	private boolean addEdge(int v1, int v2) {
		if (v1 < 1 || v1 > n) {
			return false;
		}
		if (v2 < 1 || v2 > n) {
			return false;
		}
		v1--;
		v2--;
		edges.get(v1).add(v2);
		edges.get(v2).add(v1);
		return true;
	}
}
 
import java.util.ArrayList;
import java.util.List;

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

/**
 * Checker for NEERC'2011 Problem K: Kingdom Roadmap.
 * 
 * @author Dmitry Paraschenko
 */
public class Check implements Checker {
	private int n;
	private List<List<Integer>> edges;
	private int[] enter;
	private int time;
	
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		n = inf.nextInt();
		edges = new ArrayList<List<Integer>>();
		for (int i = 0; i < n; i++) {
			edges.add(new ArrayList<Integer>());
		}
		for (int i = 1; i < n; i++) {
			int v1 = inf.nextInt();
			int v2 = inf.nextInt();
			if (!addEdge(v1, v2)) {
				throw new Outcome(Outcome.Type.FAIL, String.format("wrong input file format: node must be between %d and %d", 1, n));
			}
		}
		final int pa = ouf.nextInt();
		for (int i = 0; i < pa; i++) {
			int v1 = ouf.nextInt();
			int v2 = ouf.nextInt();
			if (!addEdge(v1, v2)) {
				throw new Outcome(Outcome.Type.PE, String.format("node must be between %d and %d", 1, n));
			}
		}
		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.PE, "extra information in the output file");
		
		enter = new int[n];
		time = 0;
		dfs(-1, 0);
		if (time != n) {
			throw new Outcome(Outcome.Type.FAIL, "error in checker");
		}
		
		final int ja = ans.nextInt();
		if (pa > ja)
			throw new Outcome(Outcome.Type.WA, String.format("%d instead of %d", pa, ja));
		if (pa < ja)
			throw new Outcome(Outcome.Type.FAIL, String.format("participant has better answer: %d instead of %d", pa, ja));
		return new Outcome(Outcome.Type.OK, String.format("n=%d %d", n, pa));
	}

	private int dfs(int p, int v) {
		enter[v] = ++time;
		int parents = 0;
		int result = time;
		for (int u : edges.get(v)) {
			if (u == p) {
				if (parents > 0) {
					// multiedge p --- v
					result = Math.min(result, enter[u]);
				}
				parents++;
				continue;
			}
			if (enter[u] > 0) {
				// the 'u' is ancestor of 'v'
				result = Math.min(result, enter[u]);
			} else {
				int res = dfs(v, u);
				if (res > enter[v]) {
					throw new Outcome(Outcome.Type.WA, String.format("bridge was found: %d %d", v + 1, u + 1));
				}
				result = Math.min(result, res);
			}
		}
		return result;
	}

	private boolean addEdge(int v1, int v2) {
		if (v1 < 1 || v1 > n) {
			return false;
		}
		if (v2 < 1 || v2 > n) {
			return false;
		}
		v1--;
		v2--;
		edges.get(v1).add(v2);
		edges.get(v2).add(v1);
		return true;
	}
}
