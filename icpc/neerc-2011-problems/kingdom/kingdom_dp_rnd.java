import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.StringTokenizer;

/**
 * @author Dmitry Paraschenko
 */
public class kingdom_dp_rnd implements Runnable {
    private static final int INF = 100000000;

    private static final Random RANDOM = new Random(20111121);
    
    private int n;
    private List<List<Integer>> edges;
    private int[] enter;
    private int time;

    private ArrayList<List<Integer>> saved_edges;

    private ArrayList<int[]> answer;
    private ArrayList<Integer> leaves;

    private void solve() throws Exception {
        n = nextInt();
        edges = new ArrayList<List<Integer>>();
        saved_edges = new ArrayList<List<Integer>>();
        for (int i = 0; i < n; i++) {
            edges.add(new ArrayList<Integer>());
            saved_edges.add(new ArrayList<Integer>());
        }
        for (int i = 1; i < n; i++) {
            int v1 = nextInt();
            int v2 = nextInt();
            addEdge(v1, v2);
        }
        answer = new ArrayList<int[]>();
        leaves = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) {
            if (saved_edges.get(i).size() == 1) {
                leaves.add(i);
            }
        }
        enter = new int[n];
        while (true) {
            for (int i = 0; i < n; i++) {
                edges.get(i).clear();
                edges.get(i).addAll(saved_edges.get(i));
            }
            for (int i = 0; i < leaves.size(); i++) {
                int p = RANDOM.nextInt(i + 1);
                if (p != i) {
                    int tmp = leaves.get(p);
                    leaves.set(p, leaves.get(i));
                    leaves.set(i, tmp);
                }
            }
            answer.clear();
            for (int i = 0; i < leaves.size(); i += 2) {
                int l1 = leaves.get(i);
                int l2 = leaves.get((i + 1) % leaves.size());
                edges.get(l1).add(l2);
                edges.get(l2).add(l1);
                answer.add(new int[] {l1, l2});
            }
            Arrays.fill(enter, 0);
            time = 0;
            if (dfs(-1, 0) != INF) {
                out.println(answer.size());
                for (int[] a : answer) {
                    out.printf("%d %d\n", a[0] + 1, a[1] + 1);
                }
                break;
            }
        }
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
                    return INF;
                }
                result = Math.min(result, res);
            }
        }
        return result;
    }

    private void addEdge(int v1, int v2) {
        v1--;
        v2--;
        saved_edges.get(v1).add(v2);
        saved_edges.get(v2).add(v1);
    }

//    ========================================
    private BufferedReader in;
    private StringTokenizer st;
    private PrintWriter out;

    public kingdom_dp_rnd(String file) {
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
    
    private long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    private void halt(Throwable e) {
        System.exit(239);
    }

    public static void main(String[] args) {
        new Thread(new kingdom_dp_rnd("kingdom")).start();
    }
}
