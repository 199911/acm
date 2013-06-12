import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Tests generator for NEERC'2011 Problem K: Kingdom Roadmap.
 * 
 * @author Dmitry Paraschenko
 */
public class Tests {
	private static int TEST_COUNTER = 0;
	private static final File TESTS_DIR = new File("tests");
	private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");
	private static final Random RANDOM = new Random(200111115); 
	
	private static final int MAXN = 100000;

	private final PrintWriter out;

	private final int n;
	private final List<int[]> edges;

	private Tests(int n, String description) throws IOException {
		this.n = n;
		edges = new ArrayList<int[]>();
		String tn = String.format("%02d", ++TEST_COUNTER);
		File tests = new File("tests");
		tests.mkdir();
		PrintWriter lst = new PrintWriter(new FileWriter(TESTS_LST, true));
		lst.println(tn + " n=" + n + " " + description);
		lst.close();
		out = new PrintWriter(new FileWriter(new File(tests, tn)));
	}

	private void addEdge(int v1, int v2) {
		edges.add(new int[] {v1, v2});
	}
	
	private void write() {
		out.println(n);
		for (int[] e : edges) {
			out.printf("%d %d\n", e[0] + 1, e[1] + 1);
		}
		out.close();
	}
	
	private Tests generate(int[] graph) {
		for (int i = 1; i < n; i++) {
			addEdge(graph[i], i);
		}
		return this;
	}

	private Tests generateStar() {
		int[] graph = new int[n];
		int count = n / 3;
		graph[0] = -1;
		int i = 0;
		while (i < count) {
			graph[++i] = 0;
		}
		int p = 1;
		while (i < n - 1) {
			graph[++i] = p;
			graph[++i] = p;
			p++;
		}
		generate(graph);
		return this;
	}

	private Tests generateSingleBranch() {
		for (int i = 1; i < n; i++) {
			addEdge(i - 1, i);
		}
		return this;
	}

	private Tests generateLongBranches(int count) {
		int length = (n - 1) / count;
		int last = 0;
		for (int c = 0; c < count; c++) {
			addEdge(0, ++last);
			for (int i = 2; i < length; i++) {
				addEdge(last, ++last);
			}
		}
		while (last < n - 1) {
			addEdge(last, ++last);
		}
		return this;
	}

	private Tests generateShortBranches(int max_length) {
		int last = 0;
		while (last < n - 1) {
			addEdge(0, ++last);
			int length = RANDOM.nextInt(max_length - 1) + 2;
			for (int i = 1; last < n - 1 && i < length; i++) {
				addEdge(last, ++last);
			}
		}
		return this;
	}

	private Tests generateRandom() {
		for (int i = 1; i < n; i++) {
			addEdge(RANDOM.nextInt(i), i);
		}
		return this;
	}

	private Tests generateAntiRandom() {
		ArrayList<Integer>[] branches = new ArrayList[5];
		for (int i = 0; i < branches.length; i++) {
			branches[i] = new ArrayList<Integer>();
			branches[i].add(i);
		}
		for (int i = branches.length; i < n; i++) {
			branches[RANDOM.nextInt(branches.length)].add(i);
		}
		for (ArrayList<Integer> branch : branches) {
			for (int i = 1; i < branch.size(); i++) {
				addEdge(branch.get(i - 1), branch.get(i));
			}
		}
		ArrayList<Integer> line = branches[4];
		int end1 = line.get(0);
		int end2 = line.get(line.size() - 1);
		addEdge(branches[0].get(0), end1);
		addEdge(branches[1].get(0), end1);
		addEdge(branches[2].get(0), end2);
		addEdge(branches[3].get(0), end2);
		return this;
	}

	private Tests shuffle() {
		int[] perm = new int[n];
		for (int i = 0; i < n; i++) {
			int p = RANDOM.nextInt(i + 1);
			perm[i] = perm[p];
			perm[p] = i;
		}
		for (int[] e : edges) {
			e[0] = perm[e[0]];
			e[1] = perm[e[1]];
		}
		return this;
	}
	
	public static void main(String[] args) throws IOException {
		TESTS_LST.delete();
		new Tests(5, "sample 1").generate(new int[] {-1, 0, 1, 2, 2}).write();
		new Tests(4, "sample 2").generate(new int[] {-1, 0, 0, 0}).write();
		new Tests(10, "shuffled short single branch").generateSingleBranch().shuffle().write();
		new Tests(10, "3 + 3 + 3 star").generate(new int[] {-1, 0, 0, 0, 1, 1, 2, 2, 3, 3}).write();
		new Tests(13, "3 + 3 + 3 + 3 star").generate(new int[] {-1, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4}).write();
		new Tests(1 + 33333 * 3, "large 3 + ... + 3 star").generateStar().write();
		new Tests(1 + 33331 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(1 + 33329 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(1 + 3333 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(1 + 33331 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(1 + 33329 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(1 + 3333 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(1 + 33332 * 3, "large 3 + ... + 3 star").generateStar().write();
		new Tests(1 + 33320 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(1 + 5330 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(1 + 33330 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(1 + 33320 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(1 + 5330 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(1 + 33330 * 3, "large 3 + ... + 3 star").generateStar().shuffle().write();
		new Tests(6, "2 + 2").generate(new int[] {-1, 0, 1, 1, 3, 3}).write();
		new Tests(6, "2 + 2").generate(new int[] {-1, 0, 0, 0, 3, 3}).write();
		new Tests(9, "2 + 2 + 2").generate(new int[] {-1, 0, 1, 1, 3, 3, 3, 6, 6}).write();
		new Tests(9, "2 + 2 + 2").generate(new int[] {-1, 0, 0, 0, 3, 3, 3, 6, 6}).write();
		new Tests(9, "2 + 2 + 2").generate(new int[] {-1, 0, 1, 1, 3, 3, 1, 6, 6}).write();
		new Tests(9, "2 + 2 + 2").generate(new int[] {-1, 0, 0, 0, 3, 3, 0, 6, 6}).write();
		for (int i = 0; i < 5; i++) {
			new Tests(10, "shuffled small random tree").generateRandom().shuffle().write();
			new Tests(15, "shuffled small random tree").generateRandom().shuffle().write();
			new Tests(20, "shuffled small random tree").generateRandom().shuffle().write();
		}
		new Tests(MAXN, "long 2 + 2").generateAntiRandom().write();
		new Tests(MAXN, "shuffled long 2 + 2").generateAntiRandom().shuffle().write();
		new Tests(MAXN, "shuffled long 2 + 2").generateAntiRandom().shuffle().write();
		new Tests(MAXN, "shuffled long 2 + 2").generateAntiRandom().shuffle().write();
		new Tests(MAXN, "shuffled long 2 + 2").generateAntiRandom().shuffle().write();
		new Tests(MAXN, "shuffled long 2 + 2").generateAntiRandom().shuffle().write();
		new Tests(MAXN, "shuffled long 2 + 2").generateAntiRandom().shuffle().write();
		new Tests(MAXN, "shuffled long 2 + 2").generateAntiRandom().shuffle().write();
		new Tests(MAXN, "shuffled long 2 + 2").generateAntiRandom().shuffle().write();
		new Tests(MAXN, "long single branch").generateSingleBranch().write();
		new Tests(MAXN - 1, "long single branch").generateSingleBranch().write();
		new Tests(MAXN, "shuffled 2 long branches").generateLongBranches(2).shuffle().write();
		new Tests(MAXN, "3 long branches").generateLongBranches(3).write();
		new Tests(MAXN, "shuffled 4 long branches").generateLongBranches(4).shuffle().write();
		new Tests(MAXN, "10 long branches").generateLongBranches(10).write();
		new Tests(MAXN, "many long branches").generateLongBranches((int) Math.sqrt(MAXN)).write();
		new Tests(MAXN, "shuffled many long branches").generateLongBranches((int) Math.sqrt(MAXN) / 2).shuffle().write();
		new Tests(100, "few very short branches").generateShortBranches(5).write();
		new Tests(MAXN, "many very short branches").generateShortBranches(5).write();
		new Tests(MAXN, "many relatively short branches").generateShortBranches(100).write();
		new Tests(MAXN, "random tree").generateRandom().write();
		new Tests(MAXN, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(MAXN, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(MAXN, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		new Tests(RANDOM.nextInt(MAXN - 1) + 2, "shuffled random tree").generateRandom().shuffle().write();
		/**/
	}
}
