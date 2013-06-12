import java.io.*;
import java.util.*;

public class Interact {
	private static String fileName = "interactive";
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";

	final BufferedReader stdin;
	final Scanner fin;
	final PrintWriter fout;

	int n;
	int[] p;
	int[][] a;

	Interact() throws IOException {
		stdin = new BufferedReader(new InputStreamReader(System.in));
		fin = new Scanner(new FileReader(inputFileName));
		fout = new PrintWriter(new FileWriter(outputFileName), true);
	}

	void close() {
		fin.close();
		fout.close();
	}

	static class PresentationException extends Exception {
		PresentationException(String message) {
			super(message);
		}
	}

	void go() {
		try {
			fout.println(interact());
		} catch (PresentationException e) {
			fout.println("PE " + e.getMessage());
		} catch (IOException e) {
			fout.println("FAIL " + e.getMessage());
		}
	}

	String interact() throws IOException, PresentationException {
		n = fin.nextInt();
		int maxQueries = 5 * n * n;
		p = new int[n];
		a = new int[n + 1][n + 1];
		for (int i = 0; i < n; i++)
			p[i] = fin.nextInt();
		writeLine("" + n);
		for (int queries = 0; queries < maxQueries; queries++) {
			int[] q;
			q = readPermutation(n);
			int r = result(q);
			writeLine("" + r);
			if (r == n)
				return "OK " + (queries + 1) + " queries";
		}
		return "WA queries limit reached";
	}

	private int[] readPermutation(int n) throws PresentationException, IOException {
		int[] a = new int[n];
		boolean[] used = new boolean[n + 1];
		String s = readLine();
		StringTokenizer st = new StringTokenizer(s);
		for (int i = 0; i < n; i++) {
			if (!st.hasMoreTokens())
				throw new PresentationException("not enough tokens on a line");
			String token = st.nextToken();
			try {
				a[i] = Integer.parseInt(token);
			} catch (NumberFormatException e) {
				throw new PresentationException("token is not a number");
			}
			if (a[i] < 1 || a[i] > n)
				throw new PresentationException("number out of range");
			if (used[a[i]])
				throw new PresentationException("not a permutation");
			used[a[i]] = true;
		}
		if (st.hasMoreTokens())
			throw new PresentationException("too many tokens on a line");
		return a;
	}

	int result(int[] q) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (p[i] == q[j]) {
					a[i + 1][j + 1] = a[i][j] + 1;
				} else {
					a[i + 1][j + 1] = Math.max(a[i][j + 1], a[i + 1][j]);
				}
			}
		}
		return a[n][n];
	}

	private String readLine() throws IOException {
		String s = stdin.readLine();
		fout.print("INP ");
		fout.println(s);
		return s;
	}

	private void writeLine(String s) {
		fout.print("OUT ");
		fout.println(s);
		System.out.println(s);
	}

	public static void main(String[] args) throws IOException {
		Interact instance = new Interact();
		instance.go();
		instance.close();
	}
}
 
import java.io.*;
import java.util.*;

public class Interact {
	private static String fileName = "interactive";
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";

	final BufferedReader stdin;
	final Scanner fin;
	final PrintWriter fout;

	int n;
	int[] p;
	int[][] a;

	Interact() throws IOException {
		stdin = new BufferedReader(new InputStreamReader(System.in));
		fin = new Scanner(new FileReader(inputFileName));
		fout = new PrintWriter(new FileWriter(outputFileName), true);
	}

	void close() {
		fin.close();
		fout.close();
	}

	static class PresentationException extends Exception {
		PresentationException(String message) {
			super(message);
		}
	}

	void go() {
		try {
			fout.println(interact());
		} catch (PresentationException e) {
			fout.println("PE " + e.getMessage());
		} catch (IOException e) {
			fout.println("FAIL " + e.getMessage());
		}
	}

	String interact() throws IOException, PresentationException {
		n = fin.nextInt();
		int maxQueries = 5 * n * n;
		p = new int[n];
		a = new int[n + 1][n + 1];
		for (int i = 0; i < n; i++)
			p[i] = fin.nextInt();
		writeLine("" + n);
		for (int queries = 0; queries < maxQueries; queries++) {
			int[] q;
			q = readPermutation(n);
			int r = result(q);
			writeLine("" + r);
			if (r == n)
				return "OK " + (queries + 1) + " queries";
		}
		return "WA queries limit reached";
	}

	private int[] readPermutation(int n) throws PresentationException, IOException {
		int[] a = new int[n];
		boolean[] used = new boolean[n + 1];
		String s = readLine();
		StringTokenizer st = new StringTokenizer(s);
		for (int i = 0; i < n; i++) {
			if (!st.hasMoreTokens())
				throw new PresentationException("not enough tokens on a line");
			String token = st.nextToken();
			try {
				a[i] = Integer.parseInt(token);
			} catch (NumberFormatException e) {
				throw new PresentationException("token is not a number");
			}
			if (a[i] < 1 || a[i] > n)
				throw new PresentationException("number out of range");
			if (used[a[i]])
				throw new PresentationException("not a permutation");
			used[a[i]] = true;
		}
		if (st.hasMoreTokens())
			throw new PresentationException("too many tokens on a line");
		return a;
	}

	int result(int[] q) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (p[i] == q[j]) {
					a[i + 1][j + 1] = a[i][j] + 1;
				} else {
					a[i + 1][j + 1] = Math.max(a[i][j + 1], a[i + 1][j]);
				}
			}
		}
		return a[n][n];
	}

	private String readLine() throws IOException {
		String s = stdin.readLine();
		fout.print("INP ");
		fout.println(s);
		return s;
	}

	private void writeLine(String s) {
		fout.print("OUT ");
		fout.println(s);
		System.out.println(s);
	}

	public static void main(String[] args) throws IOException {
		Interact instance = new Interact();
		instance.go();
		instance.close();
	}
}
