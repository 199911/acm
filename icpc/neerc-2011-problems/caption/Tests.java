import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

/**
 * Tests generator for NEERC'2011 Problem C: Caption
 * @author Roman Elizarov
 */
class Tests {
	static int TEST_COUNTER = 0;
	static final File TESTS_DIR = new File("tests");
	static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");

	static final int MAX_M = 30;
	static final int MAX_N = 2000;
	static final int MAX_K = 30;
	static final int MAX_S = 30;
	static final int MAX_LEN = 30;

	static final Random RND = new Random(20111119);

	static class Glyph {
		char a[][];

		Glyph(int m, int k, char ch) {
			a = new char[m][k];
			for (int i = 0; i < m; i++)
				Arrays.fill(a[i], ch);
		}

		Glyph(int m, int k, String d) {
			this(m, k, '.');
			assert d.length() == m * k;
			for (int i = 0; i < m; i++)
				for (int j = 0; j < k; j++)
					a[i][j] = d.charAt(i * k + j);
		}
	}

	static class Font {
		int m;
		int k;

		Font(int m, int k) {
			this.m = m;
			this.k = k;
		}

		Map<Character, Glyph> f = new LinkedHashMap<Character, Glyph>();

		Font put(char c, String d) {
			return put(c, new Glyph(m, k, d));
		}

		Font put(char c, Glyph g) {
			f.put(c, g);
			return this;
		}
	}

	static final Font SAMPLE_5X5 = new Font(5, 5)
		.put('A',
			"..*.." +
			".*.*." +
			"*...*" +
			"*****" +
			"*...*")
		.put('B',
			"****." +
			"*...*" +
			"****." +
			"*...*" +
			"****.")
		.put('C',
			".****" +
			"*...." +
			"*...." +
			"*...." +
			".****")
		.put('D',
			"****." +
			"*...*" +
			"*...*" +
			"*...*" +
			"****.")
		.put('E',
			"*****" +
			"*...." +
			"***.." +
			"*...." +
			"*****")
		.put('F',
			"*****" +
			"*...." +
			"***.." +
			"*...." +
			"*....")
		.put('G',
			".****" +
			"*...." +
			"*..**" +
			"*...*" +
			".***.")
		.put('H',
			"*...*" +
			"*...*" +
			"*****" +
			"*...*" +
			"*...*")
		.put('I',
			"..*.." +
			"..*.." +
			"..*.." +
			"..*.." +
			"..*..")
		.put('J',
			"..*.." +
			"..*.." +
			"..*.." +
			"*.*.." +
			".*...")
		.put('K',
			"*...*" +
			"*..*." +
			"***.." +
			"*..*." +
			"*...*")
		.put('L',
			"*...." +
			"*...." +
			"*...." +
			"*...." +
			"*****")
		.put('M',
			"*...*" +
			"**.**" +
			"*.*.*" +
			"*...*" +
			"*...*")
		.put('N',
			"*...*" +
			"**..*" +
			"*.*.*" +
			"*..**" +
			"*...*")
		.put('O',
			".***." +
			"*...*" +
			"*...*" +
			"*...*" +
			".***.")
		.put('P',
			"****." +
			"*...*" +
			"****." +
			"*...." +
			"*....")
		.put('Q',
			".***." +
			"*...*" +
			"*.*.*" +
			"*..**" +
			".***.")
		.put('R',
			"****." +
			"*...*" +
			"****." +
			"*.*.." +
			"*..*.")
		.put('S',
			".****" +
			"*...." +
			".***." +
			"....*" +
			"****.")
		.put('T',
			"*****" +
			"..*.." +
			"..*.." +
			"..*.." +
			"..*..")
		.put('U',
			"*...*" +
			"*...*" +
			"*...*" +
			"*...*" +
			".***.")
		.put('V',
			"*...*" +
			"*...*" +
			"*...*" +
			".*.*." +
			"..*..")
		.put('W',
			"*...*" +
			"*...*" +
			"*...*" +
			"*.*.*" +
			".*.*.")
		.put('X',
			"*...*" +
			".*.*." +
			"..*.." +
			".*.*." +
			"*...*")
		.put('Y',
			"*...*" +
			".*.*." +
			"..*.." +
			"..*.." +
			"..*..")
		.put('Z',
			"*****" +
			"...*." +
			"..*.." +
			".*..." +
			"*****");

	static Glyph constGlyph(int m, int k, char ch) {
		return new Glyph(m, k, ch);
	}

	static Font constFont(int m, int k, char ch) {
		Font font = new Font(m, k);
		for (char c = 'A'; c <= 'Z'; c++)
			font.put(c, constGlyph(m, k, ch));
		return font;
	}

	static Glyph randomGlyph(int m, int k) {
		Glyph g = new Glyph(m, k, '.');
		for (int i = 0; i < m; i++)
			for (int j = 0; j < k; j++)
				if (RND.nextBoolean())
					g.a[i][j] = '*';
		return g;
	}

	static Font randomFont(int m, int k) {
		Font font = new Font(m, k);
		for (char c = 'A'; c <= 'Z'; c++)
			font.put(c, randomGlyph(m, k));
		return font;
	}

	static String randomText(int len) {
		StringBuilder sb = new StringBuilder(len);
		for (int i = 0; i < len; i++) {
			int r = RND.nextInt((i == 0 || i == len - 1) ? 26 : 27);
			sb.append(r == 26 ? ' ' : (char)('A' + r));
		}
		return sb.toString();
	}

	final String tn;

	int m;
	int n;
	int k;
	int smin;
	int smax;
	Font font;
	List<Character> chars;
	boolean orderChars;
	String curText;
	int[] curLayout;
	String newText;

	Tests(String description) throws IOException {
		tn = String.format("%02d", ++TEST_COUNTER);
		System.out.println(tn + " - " + description);
		PrintWriter lst = new PrintWriter(new FileWriter(TESTS_LST, true));
		lst.println(tn + " " + description);
		lst.close();
	}

	Tests width(int n) {
		this.n = n;
		return this;
	}

	Tests limits(int smin, int smax) {
		this.smin = smin;
		this.smax = smax;
		return this;
	}

	Tests font(Font font) {
		this.font = font;
		this.m = font.m;
		this.k = font.k;
		return this;
	}

	Tests curText(String curText) {
		this.curText = curText;
		return this;
	}

	int curLayoutWidth() {
		int w = curLayout.length * k;
		for (int i = 1; i < curLayout.length; i++)
			w += curLayout[i];
		return w;
	}

	Tests curLayout(int... curLayout) {
		int curLen = curText.length();
		this.curLayout = Arrays.copyOf(curLayout, curLen);
		int i = curLayout.length;
		if (i > 1)
			while (i < curLen) {
				System.arraycopy(curLayout, 1, this.curLayout, i, Math.min(curLen - i, curLayout.length - 1));
				i += curLayout.length - 1;
			}
		assert curLayout[0] + curLayoutWidth() <= n;
		return this;
	}

	Tests curLayoutRandom(int min, int max) {
		int curLen = curText.length();
		curLayout = new int[curLen];
		do {
			for (int i = 1; i < curLen; i++)
				curLayout[i] = min + RND.nextInt(max - min + 1);
		} while (curLayoutWidth() > n);
		curLayout[0] = RND.nextInt(n - curLayoutWidth() + 1);
		return this;
	}

	Tests newText(String newText) {
		this.newText = newText;
		return this;
	}

	Tests orderChars() {
		this.orderChars = true;
		return this;
	}

	Tests allChars() {
		chars = new ArrayList<Character>();
		for (char c = 'A'; c <= 'Z'; c++)
			chars.add(c);
		return this;
	}

	void usedChars() {
		chars = new ArrayList<Character>();
		Set<Character> used = new HashSet<Character>();
		chars(used, curText);
		chars(used, newText);
		for (Character c : font.f.keySet())
			if (used.contains(c))
				chars.add(c);
	}

	void chars(Set<Character> used, String text) {
		for (int i = 0; i < text.length(); i++) {
			char c = text.charAt(i);
			if (c != ' ')
				used.add(c);
		}
	}
	
	void shuffleChars() {
		Collections.shuffle(chars, RND);
	}

	void write() throws IOException {
		if (chars == null)
			usedChars();
		if (!orderChars)
			shuffleChars();
		PrintWriter out = new PrintWriter(new FileWriter(new File(TESTS_DIR, tn)));
		out.println(m + " " + n + " " + k + " " + smin + " " + smax);
		for (int i = 0; i < m; i++) {
			boolean first = true;
			for (Character c : chars) {
				if (first)
					first = false;
				else
					out.print(' ');
				out.print(i == 0 ? c : ' ');
				out.print(' ');
				Glyph g = font.f.get(c);
				for (int j = 0; j < k; j++)
					out.print(g.a[i][j]);
			}
			out.println();
		}
		out.println(curText);
		for (int i = 0; i < curLayout.length; i++) {
			if (i > 0)
				out.print(' ');
			out.print(curLayout[i]);
		}
		out.println();
		out.println(newText);
		out.close();
	}


	public static void main(String[] args) throws IOException {
		TESTS_LST.delete();
		TESTS_DIR.mkdir();

		new Tests("Sample")
			.font(SAMPLE_5X5)
			.width(53)
			.limits(1, 2)
			.curText("ACM ICPC")
			.curLayout(3, 1)
			.newText("NEERC")
			.orderChars()
			.write();

		new Tests("Sample Q->Q smallest")
			.font(SAMPLE_5X5)
			.width(5)
			.limits(1, 2)
			.curText("Q")
			.curLayout(0)
			.newText("Q")
			.write();

		new Tests("Sample W->W left on n=6")
			.font(SAMPLE_5X5)
			.width(6)
			.limits(1, 2)
			.curText("W")
			.curLayout(0)
			.newText("W")
			.write();

		new Tests("Sample V->V right on n=6")
			.font(SAMPLE_5X5)
			.width(6)
			.limits(1, 2)
			.curText("W")
			.curLayout(1)
			.newText("W")
			.write();

		new Tests("Sample Q->Q on n=20")
			.font(SAMPLE_5X5)
			.width(20)
			.limits(1, 2)
			.curText("Q")
			.curLayout(7)
			.newText("Q")
			.write();

		new Tests("Sample F->I on n=20")
			.font(SAMPLE_5X5)
			.width(20)
			.limits(1, 2)
			.curText("F")
			.curLayout(7)
			.newText("I")
			.write();

		new Tests("Sample ABC->CAB on n=30, shift")
			.font(SAMPLE_5X5)
			.width(30)
			.limits(1, 2)
			.curText("ABC")
			.curLayout(8, 1)
			.newText("CAB")
			.write();

		new Tests("Sample OIEO->OHO on n=30")
			.font(SAMPLE_5X5)
			.width(30)
			.limits(0, 10)
			.curText("OIEO")
			.curLayout(5, 0, 1, 0)
			.newText("OHO")
			.write();


		new Tests("Sample X->AXIS on n=30, fix spacing 1")
			.font(SAMPLE_5X5)
			.width(30)
			.limits(1, 1)
			.curText("X")
			.curLayout(8)
			.newText("AXIS")
			.write();

		new Tests("Sample A->HABA on n=30, fix spacing 3")
			.font(SAMPLE_5X5)
			.width(30)
			.limits(3, 3)
			.curText("A")
			.curLayout(8)
			.newText("HABA")
			.write();

		new Tests("Sample THIS IS A TEST->HELLO WORLD on n=100")
			.font(SAMPLE_5X5)
			.width(100)
			.limits(1, 5)
			.curText("THIS IS A TEST")
			.curLayout(3, 2)
			.newText("HELLO WORLD")
			.write();

		new Tests("Sample CONTEST STATS->CONTEST ENDS on n=100")
			.font(SAMPLE_5X5)
			.width(100)
			.limits(0, 3)
			.curText("CONTEST STARTS")
			.curLayoutRandom(1, 2)
			.newText("CONTEST ENDS")
			.write();

		new Tests("Empty min")
			.font(constFont(5, 5, '.'))
			.width(5)
			.limits(0, 0)
			.curText("A")
			.curLayout(0)
			.newText("A")
			.write();

		new Tests("Empty font text n=100")
			.font(constFont(5, 5, '.'))
			.width(100)
			.limits(0, 30)
			.curText("TEST TEXT")
			.curLayoutRandom(0, 5)
			.newText("QUICK FOX")
			.write();

		new Tests("Full font HABA HABA->LAZY ROAD n=100")
			.font(constFont(5, 5, '*'))
			.width(100)
			.limits(0, 30)
			.curText("HABA HABA")
			.curLayoutRandom(0, 10)
			.newText("LAZY ROAD")
			.write();

		new Tests("Random font & text, n=100")
			.font(randomFont(5, 5))
			.width(100)
			.limits(0, 30)
			.curText(randomText(10))
			.curLayoutRandom(1, 9)
			.newText(randomText(10))
			.write();

		new Tests("Random font & text dense, n=100")
			.font(randomFont(5, 5))
			.width(100)
			.limits(1, 30)
			.curText(randomText(15))
			.curLayoutRandom(0, 1)
			.newText(randomText(15))
			.write();

		new Tests("Random font & text + all chars, n=100")
			.font(randomFont(5, 5))
			.width(100)
			.limits(0, 1)
			.curText(randomText(16))
			.curLayoutRandom(0, 1)
			.newText(randomText(16))
			.allChars()
			.write();

		new Tests("Sample font XZ->XYYZ, wide cur layout, n=100")
			.font(SAMPLE_5X5)
			.width(100)
			.limits(20, 30)
			.curText("XZ")
			.curLayout(0, 90)
			.newText("XYYZ")
			.write();

		new Tests("Sample on n=1000, random layout, exact match")
			.font(SAMPLE_5X5)
			.width(1000)
			.limits(1, 10)
			.curText("ABCDEFGHIJKLKMNOPRQSTUVWXYZ")
			.curLayoutRandom(1, 10)
			.newText("ABCDEFGHIJKLKMNOPRQSTUVWXYZ")
			.orderChars()
			.write();

		new Tests("Sample on n=1000, random layout, non-exact match")
			.font(SAMPLE_5X5)
			.width(1000)
			.limits(1, 10)
			.curText("ABCDEFGHIJKLKMNOPQRSTUVWXYZ")
			.curLayoutRandom(0, 15)
			.newText("ABCDEFGHIJKLKMNOPQRSTUVWXYZ")
			.orderChars()
			.write();

		new Tests("Max on empty font")
			.font(constFont(MAX_M, MAX_K, '.'))
			.width(MAX_N)
			.limits(0, MAX_S)
			.curText(randomText(MAX_LEN))
			.curLayoutRandom(0, MAX_S)
			.newText(randomText(MAX_LEN))
			.write();

		new Tests("Max on full font")
			.font(constFont(MAX_M, MAX_K, '*'))
			.width(MAX_N)
			.limits(0, MAX_S)
			.curText(randomText(MAX_LEN))
			.curLayoutRandom(0, MAX_S)
			.newText(randomText(MAX_LEN))
			.write();

		new Tests("Max on random font")
			.font(randomFont(MAX_M, MAX_K))
			.width(MAX_N)
			.limits(0, MAX_S)
			.curText(randomText(MAX_LEN))
			.curLayoutRandom(0, MAX_S)
			.newText(randomText(MAX_LEN))
			.write();

		new Tests("Max on random font fix layout 0-0")
			.font(randomFont(MAX_M, MAX_K))
			.width(MAX_N)
			.limits(0, 0)
			.curText(randomText(MAX_LEN))
			.curLayoutRandom(0, MAX_S)
			.newText(randomText(MAX_LEN))
			.write();

		new Tests("Max on random font fix layout 20-20")
			.font(randomFont(MAX_M, MAX_K))
			.width(MAX_N)
			.limits(20, 20)
			.curText(randomText(MAX_LEN))
			.curLayoutRandom(0, MAX_S)
			.newText(randomText(MAX_LEN))
			.write();

		new Tests("Max on random font 0-30 to 0-10")
			.font(randomFont(MAX_M, MAX_K))
			.width(MAX_N)
			.limits(0, 10)
			.curText(randomText(MAX_LEN))
			.curLayoutRandom(0, 30)
			.newText(randomText(MAX_LEN))
			.write();

		new Tests("Max on random font 0-10 to 0-30")
			.font(randomFont(MAX_M, MAX_K))
			.width(MAX_N)
			.limits(0, 30)
			.curText(randomText(MAX_LEN))
			.curLayoutRandom(0, 10)
			.newText(randomText(MAX_LEN))
			.write();

		new Tests("Max on random font 0-10 to 20-30")
			.font(randomFont(MAX_M, MAX_K))
			.width(MAX_N)
			.limits(20, 30)
			.curText(randomText(MAX_LEN))
			.curLayoutRandom(0, 10)
			.newText(randomText(MAX_LEN))
			.write();

		new Tests("Max on random font 10-25 to 0-10")
			.font(randomFont(MAX_M, MAX_K))
			.width(MAX_N)
			.limits(0, 10)
			.curText(randomText(MAX_LEN))
			.curLayoutRandom(10, 25)
			.newText(randomText(MAX_LEN))
			.write();
	}
}
