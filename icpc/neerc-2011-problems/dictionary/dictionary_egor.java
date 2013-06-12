import java.util.Map;
import java.io.IOException;
import java.util.InputMismatchException;
import java.util.HashMap;
import java.util.Set;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.FileInputStream;
import java.io.Writer;
import java.math.BigInteger;
import java.util.Collection;
import java.util.HashSet;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 * @author Egor Kulikov (egor@egork.net)
 */
public class dictionary_egor {
	public static void main(String[] args) {
		InputStream inputStream;
		try {
			inputStream = new FileInputStream("dictionary.in");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		OutputStream outputStream;
		try {
			outputStream = new FileOutputStream("dictionary.out");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		InputReader in = new InputReader(inputStream);
		OutputWriter out = new OutputWriter(outputStream);
		Dictionary solver = new Dictionary();
		solver.solve(1, in, out);
		out.close();
	}
}

class Dictionary {
	public void solve(int testNumber, InputReader in, OutputWriter out) {
		int count = in.readInt();
		String[] words = new String[count];
		for (int i = 0; i < count; i++)
			words[i] = in.readString();
		Map<String, Integer> prefix = new HashMap<String, Integer>();
		Map<String, Integer> suffix = new HashMap<String, Integer>();
		for (String word : words) {
			for (int i = 1; i < word.length(); i++) {
				String current = word.substring(0, i);
				Integer value = prefix.get(current);
				if (value == null)
					value = 0;
				value |= 1 << (word.charAt(i) - 'a');
				prefix.put(current, value);
				current = word.substring(i);
				value = suffix.get(current);
				if (value == null)
					value = 0;
				value |= 1 << (word.charAt(i - 1) - 'a');
				suffix.put(current, value);
			}
			if (!prefix.containsKey(word))
				prefix.put(word, 0);
			if (!suffix.containsKey(word))
				suffix.put(word, 0);
		}
		int[] countPrefix = new int[26];
		int[] countSuffix = new int[26];
		for (int i : prefix.values()) {
			for (int j = 0; j < 26; j++) {
				if ((i >> j & 1) == 1)
					countPrefix[j]++;
			}
		}
		for (int i : suffix.values()) {
			for (int j = 0; j < 26; j++) {
				if ((i >> j & 1) == 1)
					countSuffix[j]++;
			}
		}
		long result = (long)prefix.size() * suffix.size();
		for (int i = 0; i < 26; i++)
			result -= (long)countPrefix[i] * countSuffix[i];
		Set<String> single = new HashSet<String>();
		for (String word : words) {
			if (word.length() == 1)
				single.add(word);
		}
		result += single.size();
		out.printLine(result);
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

	public String readString() {
		int c = read();
		while (isSpaceChar(c))
			c = read();
		StringBuffer res = new StringBuffer();
		do {
			res.appendCodePoint(c);
			c = read();
		} while (!isSpaceChar(c));
		return res.toString();
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

