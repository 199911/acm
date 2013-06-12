import java.util.Map;
import java.io.IOException;
import java.util.TreeMap;
import java.util.InputMismatchException;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.util.NavigableMap;
import java.io.PrintWriter;
import java.io.FileInputStream;
import java.io.Writer;
import java.math.BigInteger;
import java.util.SortedMap;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 * @author Egor Kulikov (egor@egork.net)
 */
public class lanes_egor {
	public static void main(String[] args) {
		InputStream inputStream;
		try {
			inputStream = new FileInputStream("lanes.in");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		OutputStream outputStream;
		try {
			outputStream = new FileOutputStream("lanes.out");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		InputReader in = new InputReader(inputStream);
		OutputWriter out = new OutputWriter(outputStream);
		Lanes solver = new Lanes();
		solver.solve(1, in, out);
		out.close();
	}
}

class Lanes {
	public void solve(int testNumber, InputReader in, OutputWriter out) {
		int leftToRight = in.readInt();
		int rightToLeft = in.readInt();
		int intervalCount = in.readInt();
		int downTime = in.readInt();
		int[] carLeft = new int[intervalCount];
		int[] carRight = new int[intervalCount];
		for (int i = 0; i < intervalCount; i++) {
			carLeft[i] = in.readInt();
			carRight[i] = in.readInt();
		}
		int rightWait = 0;
		MultiSet right = new MultiSet();
		int[] passRight = new int[intervalCount + downTime];
		long totalWait = 0;
		for (int i = 0; i < intervalCount + downTime; i++) {
			if (i < intervalCount)
				rightWait += carRight[i];
			passRight[i] = Math.min(rightWait, rightToLeft + 1);
			rightWait -= rightToLeft + 1;
			if (rightWait < 0) {
				right.add(i, -rightWait);
				rightWait = 0;
			} else
				totalWait += rightWait;
		}
		int time = intervalCount + downTime;
		int delta = rightWait / (rightToLeft + 1);
		totalWait += (long)delta * (delta - 1) / 2 * (rightToLeft + 1);
		time += delta;
		rightWait %= rightToLeft + 1;
		totalWait += (long)delta * rightWait;
		while (right.size() < intervalCount + downTime) {
			right.add(time++, rightToLeft + 1 - rightWait);
			rightWait = 0;
		}
		long[] rightWaitAfter = new long[intervalCount + downTime];
		rightWaitAfter[0] = totalWait;
		for (int i = 1; i < intervalCount + downTime; i++) {
			if (passRight[i - 1] != rightToLeft + 1) {
				rightWaitAfter[i] = rightWaitAfter[i - 1];
				right.remove(i - 1);
			} else {
				int index = right.poll();
				rightWaitAfter[i] = rightWaitAfter[i - 1] + index - i + 1;
				if (index < intervalCount + downTime)
					passRight[index]++;
			}
		}
		long[] leftWaitAfter = new long[intervalCount];
		int[] passLeft = new int[intervalCount];
		int leftWait = 0;
		long leftTotalWait = 0;
		for (int i = 0; i < intervalCount; i++) {
			leftWait += carLeft[i];
			passLeft[i] = Math.min(leftWait, leftToRight + 1);
			leftWait = Math.max(0, leftWait - leftToRight - 1);
			leftTotalWait += leftWait;
		}
		MultiSet left = new MultiSet();
		time = intervalCount;
		delta = leftWait / leftToRight;
		leftTotalWait += (long)delta * (delta - 1) / 2 * (leftToRight);
		time += delta;
		leftWait %= leftToRight;
		leftTotalWait += (long)delta * leftWait;
		while (left.size() < intervalCount) {
			left.add(time++, leftToRight - leftWait);
			leftWait = 0;
		}
		for (int i = intervalCount - 1; i >= 0; i--) {
			if (passLeft[i] == leftToRight + 1) {
				leftTotalWait += left.poll() - i;
			} else {
				passLeft[i]++;
				if (passLeft[i] != leftToRight + 1)
					left.add(i, leftToRight + 1 - passLeft[i]);
			}
			leftWaitAfter[i] = leftTotalWait;
		}
		long best = Long.MAX_VALUE;
		int index = -1;
		for (int i = 0; i < intervalCount; i++) {
			long current = leftWaitAfter[i] + rightWaitAfter[i + downTime];
			if (current < best) {
				best = current;
				index = i;
			}
		}
		out.printLine(index + 1);
//		System.err.println(best + " " + leftWaitAfter[index] + " " + rightWaitAfter[index + downTime]);
		long r = 0;
		long rd = 0;
		for (int i = 0; i < intervalCount || rd != 0; i++) {
			if (i < intervalCount)
				rd += carRight[i];
			if (i < index + downTime)
				rd -= rightToLeft;
			else
				rd -= rightToLeft + 1;
			rd = Math.max(rd, 0);
			r += rd;
		}
		if (r != rightWaitAfter[index + downTime])
			throw new RuntimeException();
		long l = 0;
		long ld = 0;
		for (int i = 0; i < intervalCount || ld != 0; i++) {
			if (i < intervalCount)
				ld += carLeft[i];
			if (i < index)
				ld -= leftToRight + 1;
			else
				ld -= leftToRight;
			ld = Math.max(ld, 0);
			l += ld;
		}
		if (l != leftWaitAfter[index])
			throw new RuntimeException();
	}
}

class MultiSet {
	NavigableMap<Integer, Integer> map = new TreeMap<Integer, Integer>();

	public void add(int number, int count) {
		map.put(number, count);
	}

	public int poll() {
		int result = map.firstKey();
		if (map.get(result) == 1)
			map.remove(result);
		else
			map.put(result, map.get(result) - 1);
		return result;
	}

	public int size() {
		return map.size();
	}

	public void remove(int i) {
		map.remove(i);
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

