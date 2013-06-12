import java.io.IOException;
import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.Set;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Random;
import java.io.Writer;
import java.math.BigInteger;
import java.util.HashSet;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 * @author Egor Kulikov (egor@egork.net)
 */
public class interactive_egor {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		OutputWriter out = new OutputWriter(outputStream);
		Interactive solver = new Interactive();
		solver.solve(1, in, out);
		out.close();
	}
}

class Interactive {
	public void solve(int testNumber, InputReader in, OutputWriter out) {
		int size = in.readInt();
		int[] permutation = new int[size];
		for (int i = 0; i < size; i++)
			permutation[i] = i + 1;
		print(out, permutation);
		int current = in.readInt();
		Random rand = new Random(239);
		Set<Integer> set = new HashSet<Integer>();
		Set<Integer> forbidden = new HashSet<Integer>();
		while (current != size) {
			int first = rand.nextInt(size);
			while (forbidden.contains(first))
				first = rand.nextInt(size);
			int second = rand.nextInt(size);
			int key = first * size + second;
			while (first == second || set.contains(key)) {
				second = rand.nextInt(size);
				key = first * size + second;
			}
			set.add(key);
			int[] newPermutation = Arrays.copyOf(permutation, size);
			if (second > first) {
				System.arraycopy(permutation, first + 1, newPermutation, first, second - first);
				newPermutation[second] = permutation[first];
			} else {
				System.arraycopy(permutation, second, newPermutation, second + 1, first - second);
				newPermutation[second] = permutation[first];
			}
			print(out, newPermutation);
			int next = in.readInt();
			if (next < current)
				forbidden.add(first);
			else if (next == current)
				set.add(key);
			else {
				permutation = newPermutation;
				current = next;
				set.clear();
				forbidden.clear();
			}
		}
	}

	private void print(OutputWriter out, int[] permutation) {
		out.print(permutation[0]);
		for (int i = 1; i < permutation.length; i++)
			out.print("", permutation[i]);
		out.printLine();
		out.flush();
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

	public void flush() {
		writer.flush();
	}
}

