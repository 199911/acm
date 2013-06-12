import java.io.IOException;
import java.util.PriorityQueue;
import java.util.InputMismatchException;
import java.util.Comparator;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.FileInputStream;
import java.io.Writer;
import java.util.Queue;
import java.math.BigInteger;
import java.util.Collection;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 * @author Egor Kulikov (egor@egork.net)
 */
public class kingdom_egor {
	public static void main(String[] args) {
		InputStream inputStream;
		try {
			inputStream = new FileInputStream("kingdom.in");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		OutputStream outputStream;
		try {
			outputStream = new FileOutputStream("kingdom.out");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		InputReader in = new InputReader(inputStream);
		OutputWriter out = new OutputWriter(outputStream);
		Kingdom solver = new Kingdom();
		solver.solve(1, in, out);
		out.close();
	}
}

class Kingdom {
	public void solve(int testNumber, InputReader in, OutputWriter out) {
		int size = in.readInt();
		if (size == 2) {
			out.printLine(1);
			out.printLine(1, 2);
			return;
		}
		int[] from = new int[size - 1];
		int[] to = new int[size - 1];
		for (int i = 0; i < size - 1; i++) {
			from[i] = in.readInt() - 1;
			to[i] = in.readInt() - 1;
		}
		int[] degree = new int[size];
		for (int i = 0; i < size - 1; i++) {
			degree[from[i]]++;
			degree[to[i]]++;
		}
		int[][] graph = new int[size][];
		for (int i = 0; i < size; i++)
			graph[i] = new int[degree[i]];
		for (int i = 0; i < size - 1; i++) {
			graph[from[i]][--degree[from[i]]] = to[i];
			graph[to[i]][--degree[to[i]]] = from[i];
		}
		int start = -1;
		for (int i = 0; i < size; i++) {
			if (graph[i].length != 1) {
				start = i;
				break;
			}
		}
		if (start == -1)
			throw new RuntimeException();
		int[] singeCount = new int[size];
		int totalSingles = go(start, -1, singeCount, graph);
		int maxIndex;
		while (true) {
			int sum = 0;
			int max = 0;
			maxIndex = -1;
			for (int i : graph[start]) {
				sum += singeCount[i];
				if (singeCount[i] > max) {
					max = singeCount[i];
					maxIndex = i;
				}
			}
			if (sum + 1 >= 2 * max)
				break;
			singeCount[start] = sum - max;
			start = maxIndex;
		}
		final int[] color = new int[size];
		for (int i : graph[start])
			color(i, start, i, graph, color);
		final int[] perColor = new int[size];
		for (int i = 0; i < size; i++) {
			if (graph[i].length == 1)
				perColor[color[i]]++;
		}
		final int[][] perColorList = new int[size][];
		for (int i = 0; i < size; i++)
			perColorList[i] = new int[perColor[i]];
		for (int i = 0; i < size; i++) {
			if (graph[i].length == 1) {
				perColorList[color[i]][--perColor[color[i]]] = i;
			}
		}
		Queue<Integer> queue = new PriorityQueue<Integer>(graph[start].length, new Comparator<Integer>() {
			public int compare(Integer o1, Integer o2) {
				return -(perColorList[o1].length - perColor[o1]) + (perColorList[o2].length - perColor[o2]);
			}
		});
		out.printLine((totalSingles + 1) / 2);
		for (int i = 0; i < size; i++) {
			if (perColorList[i].length != 0)
				queue.add(i);
		}
		while (queue.size() > 1) {
			int first = queue.poll();
			int second = queue.poll();
			out.printLine(perColorList[first][perColor[first]++] + 1, perColorList[second][perColor[second]++] + 1);
			if (perColor[first] != perColorList[first].length)
				queue.add(first);
			if (perColor[second] != perColorList[second].length)
				queue.add(second);
		}
		if (queue.size() == 1) {
			int first = queue.poll();
			out.printLine(perColorList[first][perColor[first]++] + 1, start + 1);
		}
	}

	private void color(int vertex, int last, int currentColor, int[][] graph, int[] color) {
		color[vertex] = currentColor;
		for (int i : graph[vertex]) {
			if (i != last)
				color(i, vertex, currentColor, graph, color);
		}
	}

	private int go(int vertex, int last, int[] singeCount, int[][] graph) {
		if (graph[vertex].length == 1) {
			singeCount[vertex] = 1;
			return 1;
		}
		for (int i : graph[vertex]) {
			if (i != last)
				singeCount[vertex] += go(i, vertex, singeCount, graph);
		}
		return singeCount[vertex];
	}
}

class InputReader {

	private InputStream stream;
	private byte[] buf = new byte[1024];
	private int curChar;
	private int numChars;

	public InputReader(InputStream stream) {
		this.stream = stream;
	}

	public int read() {
		if (numChars == -1)
			throw new InputMismatchException();
		if (curChar >= numChars) {
			curChar = 0;
			try {
				numChars = stream.read(buf);
			} catch (IOException e) {
				throw new InputMismatchException();
			}
			if (numChars <= 0)
				return -1;
		}
		return buf[curChar++];
	}

	public int readInt() {
		int c = read();
		while (isSpaceChar(c))
			c = read();
		int sgn = 1;
		if (c == '-') {
			sgn = -1;
			c = read();
		}
		int res = 0;
		do {
			if (c < '0' || c > '9')
				throw new InputMismatchException();
			res *= 10;
			res += c - '0';
			c = read();
		} while (!isSpaceChar(c));
		return res * sgn;
	}

	public static boolean isSpaceChar(int c) {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
	}

	}

class OutputWriter {
	private final PrintWriter writer;

	public OutputWriter(OutputStream outputStream) {
		writer = new PrintWriter(outputStream);
	}

	public OutputWriter(Writer writer) {
		this.writer = new PrintWriter(writer);
	}

	public void print(Object...objects) {
		for (int i = 0; i < objects.length; i++) {
			if (i != 0)
				writer.print(' ');
			writer.print(objects[i]);
		}
	}

	public void printLine(Object...objects) {
		print(objects);
		writer.println();
	}

	public void close() {
		writer.close();
	}
}

