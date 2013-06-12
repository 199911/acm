import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2011 Problem K: Kingdom Roadmap
 * This solution checks correctness of the input.
 * @author Roman Elizarov
 */
public class kingdom_re implements Runnable {

	public static void main(String[] args) throws Exception {
		new Thread(new kingdom_re()).start(); // need deep stack
	}

	public void run() {
		try {
			go();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	void go() throws Exception {
		read();
		solve();
		write();
	}

	class City {
		final int i;
		final List<City> adj = new ArrayList<City>();
		final List<City> children = new ArrayList<City>();
		boolean inQueue;

		City(int i) {
			this.i = i;
		}

		@Override
		public String toString() {
			return Integer.toString(i);
		}
	}

	class Road {
		final City a;
		final City b;

		Road(City a, City b) {
			this.a = a;
			this.b = b;
		}
	}

	int n;
	City[] cities;

	void read() throws Exception {
		Scanner in = new Scanner(new File("kingdom.in"));
		n = in.nextInt();
		in.nextLine();
		assert n >= 2 && n <= 100000;
		cities = new City[n + 1];
		for (int i = 1; i <= n; i++)
			cities[i] = new City(i);
		for (int i = 1; i < n; i++) {
			int u = in.nextInt();
			int v = in.nextInt();
			in.nextLine();
			assert u >= 1 && u <= n;
			assert v >= 1 && v <= n;
			assert u != v;
			cities[u].adj.add(cities[v]);
			cities[v].adj.add(cities[u]);
		}
		in.close();
	}

	List<Road> roads = new ArrayList<Road>();

	void solve() {
		if (n == 2) {
			roads.add(new Road(cities[1], cities[2]));
			return;
		}
		City root = findNonLeaf();
		buildTree(root);
		List<City> rem = connect(root);
		switch (rem.size()) {
		case 1:
			roads.add(new Road(root, rem.get(0)));
			break;
		case 2:
			roads.add(new Road(rem.get(0), rem.get(1)));
			break;
		default:
			assert false;
		}
	}

	City findNonLeaf() {
		for (int i = 1; i <= n; i++) {
			City city = cities[i];
			if (city.adj.size() > 1)
				return city;
		}
		throw new AssertionError("should have non-leaf root");
	}

	void buildTree(City root) {
		List<City> queue = new ArrayList<City>(n);
		root.inQueue = true;
		queue.add(root);
		for (int i = 0; i < queue.size(); i++) {
			City c = queue.get(i);
			for (City cc : c.adj)
				if (!cc.inQueue) {
					cc.inQueue = true;
					queue.add(cc);
					c.children.add(cc);
				}
		}
		assert queue.size() == n;
	}

	private List<City> connect(City node) {
		if (node.children.isEmpty())
			return new ArrayList<City>(Collections.singletonList(node));
		List<City> res = new ArrayList<City>();
		for (City c : node.children) {
			List<City> rem = connect(c);
			if (res.size() + rem.size() > 2) {
				City a = res.remove(res.size() - 1);
				City b = rem.remove(rem.size() - 1);
				roads.add(new Road(a, b));
			}
			res.addAll(rem);
		}
		return res;
	}

	void write() throws Exception {
		PrintWriter out = new PrintWriter("kingdom.out");
		out.println(roads.size());
		for (Road road : roads) {
			out.println(road.a.i + " " + road.b.i);
		}
		out.close();
	}

//----------------- just for validation ------------------

	/**
	 * Strict scanner to verify 100% correspondence between input files and input file format specification.
	 * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a solution source
	 * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
	 */
	public class Scanner {
		private final BufferedReader in;
		private String line = "";
		private int pos;
		private int lineNo;

		public Scanner(File source) throws FileNotFoundException {
			in = new BufferedReader(new FileReader(source));
			nextLine();
		}

		public void close() {
			assert line == null : "Extra data at the end of file";
			try {
				in.close();
			} catch (IOException e) {
				throw new AssertionError("Failed to close with " + e);
			}
		}

		public void nextLine() {
			assert line != null : "EOF";
			assert pos == line.length() : "Extra characters on line " + lineNo;
			try {
				line = in.readLine();
			} catch (IOException e) {
				throw new AssertionError("Failed to read line with " + e);
			}
			pos = 0;
			lineNo++;
		}

		public String next() {
			assert line != null : "EOF";
			assert line.length() > 0 : "Empty line " + lineNo;
			if (pos == 0)
				assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
			else {
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
				pos++;
				assert pos < line.length() : "Line " + lineNo + " is over";
				assert line.charAt(pos) > ' ' : "Line " + lineNo + " has double whitespace";
			}
			StringBuilder sb = new StringBuilder();
			while (pos < line.length() && line.charAt(pos) > ' ')
				sb.append(line.charAt(pos++));
			return sb.toString();
		}

		public int nextInt() {
			String s = next();
			assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
			assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
			try {
				return Integer.parseInt(s);
			} catch (NumberFormatException e) {
				throw new AssertionError("Malformed number " + s + " on line " + lineNo);
			}
		}
	}
}
