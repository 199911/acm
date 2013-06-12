import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * Checker for NEERC'2011 Problem C: Caption
 * @author Roman Elizarov
 */
public class Check implements Checker {
	private static final int DEBUG_PRINT_LAYOUT = 100;

	private static final char ON = '*';
	private static final char OFF = '.';

	static class Rec {
		char[][] a;

		Rec(int nr, int nc) {
			a = new char[nr][nc];
			for (int i = 0; i < nr; i++)
				Arrays.fill(a[i], OFF);
		}

		@Override
		public String toString() {
			StringBuilder sb = new StringBuilder();
			for (int i = 0; i < a.length; i++) {
				if (i > 0)
					sb.append('\n');
				for (int j = 0; j < a[i].length; j++)
					sb.append(a[i][j]);
			}
			return sb.toString();
		}
	}

	int m;
	int n;
	int k;
	int smin;
	int smax;

	Map<Character, Rec> font;

	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		m = inf.nextInt();
		n = inf.nextInt();
		k = inf.nextInt();
		smin = inf.nextInt();
		smax = inf.nextInt();
		inf.skipLine(); // skip rest of line
		font = readFont(inf);
		String cur_str = inf.nextLine();
		Rec cur_rec = readLayout(cur_str, inf, false);
		inf.skipLine(); // skip rest of line
		String new_str = inf.nextLine();
		Rec ans_rec = readLayout(new_str, ans, true);
		Rec ouf_rec = readLayout(new_str, ouf, true);
		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.PE, "extra information in the output file");

		int ans_n = countFlips(cur_rec, ans_rec);
		int ouf_n = countFlips(cur_rec, ouf_rec);

		if (n <= DEBUG_PRINT_LAYOUT) {
			System.out.println(cur_rec);
			System.out.println();
			System.out.println(ouf_rec);
		}

		if (ouf_n > ans_n)
			throw new Outcome(Outcome.Type.WA, String.format("Not optimal: %d flips instead of %d", ouf_n, ans_n));
		if (ouf_n < ans_n)
			throw new Outcome(Outcome.Type.FAIL, String.format("More optimal: %d flips instead of %d", ouf_n, ans_n));
		return new Outcome(Outcome.Type.OK, String.format("%d flips", ouf_n));
	}

	private Map<Character, Rec> readFont(InStream inf) {
		HashMap<Character, Rec> font = new HashMap<Character, Rec>();
		String[] line = new String[m];
		for (int i = 0; i < m; i++)
			line[i] = inf.nextLine();
		int w = k + 3;
		int t = (line[0].length() + 1) / w;
		for (int p = 0; p < t; p++) {
			char c = line[0].charAt(p * w);
			Rec rec = new Rec(m, k);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < k; j++)
					rec.a[i][j] = line[i].charAt(p * w + 2 + j);
			font.put(c, rec);
		}
		font.put(' ', new Rec(m, k));
		return font;
	}

	private Rec readLayout(String s, InStream in, boolean obeysMinMax) {
		Rec rec = new Rec(m, n);
		int ofs = 0;
		for (int p = 0; p < s.length(); p++) {
			int spacing = in.nextInt();
			if (spacing < 0)
				throw new Outcome(Outcome.Type.WA, String.format("Negative spacing #%d: %d", p + 1, spacing));
			if (obeysMinMax) {
				if (p > 0 && (spacing < smin || spacing > smax))
					throw new Outcome(Outcome.Type.WA, String.format("Spacing #%d is out of range: %d", p + 1, spacing));
			}
			ofs += spacing;
			if (ofs + k > n)
				throw new Outcome(Outcome.Type.WA, String.format("Character #%d does not fit", p + 1));
			char c = s.charAt(p);
			Rec glyph = font.get(c);
			if (glyph == null)
				throw new Outcome(Outcome.Type.FAIL, String.format("Letter %c is not in font", c));
			for (int i = 0; i < m; i++)
				System.arraycopy(glyph.a[i], 0, rec.a[i], ofs, k);
			ofs += k;
		}
		return rec;
	}

	private int countFlips(Rec r1, Rec r2) {
		int cnt = 0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (r1.a[i][j] != r2.a[i][j])
					cnt++;
		return cnt;
	}
}
 
import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * Checker for NEERC'2011 Problem C: Caption
 * @author Roman Elizarov
 */
public class Check implements Checker {
	private static final int DEBUG_PRINT_LAYOUT = 100;

	private static final char ON = '*';
	private static final char OFF = '.';

	static class Rec {
		char[][] a;

		Rec(int nr, int nc) {
			a = new char[nr][nc];
			for (int i = 0; i < nr; i++)
				Arrays.fill(a[i], OFF);
		}

		@Override
		public String toString() {
			StringBuilder sb = new StringBuilder();
			for (int i = 0; i < a.length; i++) {
				if (i > 0)
					sb.append('\n');
				for (int j = 0; j < a[i].length; j++)
					sb.append(a[i][j]);
			}
			return sb.toString();
		}
	}

	int m;
	int n;
	int k;
	int smin;
	int smax;

	Map<Character, Rec> font;

	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		m = inf.nextInt();
		n = inf.nextInt();
		k = inf.nextInt();
		smin = inf.nextInt();
		smax = inf.nextInt();
		inf.skipLine(); // skip rest of line
		font = readFont(inf);
		String cur_str = inf.nextLine();
		Rec cur_rec = readLayout(cur_str, inf, false);
		inf.skipLine(); // skip rest of line
		String new_str = inf.nextLine();
		Rec ans_rec = readLayout(new_str, ans, true);
		Rec ouf_rec = readLayout(new_str, ouf, true);
		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.PE, "extra information in the output file");

		int ans_n = countFlips(cur_rec, ans_rec);
		int ouf_n = countFlips(cur_rec, ouf_rec);

		if (n <= DEBUG_PRINT_LAYOUT) {
			System.out.println(cur_rec);
			System.out.println();
			System.out.println(ouf_rec);
		}

		if (ouf_n > ans_n)
			throw new Outcome(Outcome.Type.WA, String.format("Not optimal: %d flips instead of %d", ouf_n, ans_n));
		if (ouf_n < ans_n)
			throw new Outcome(Outcome.Type.FAIL, String.format("More optimal: %d flips instead of %d", ouf_n, ans_n));
		return new Outcome(Outcome.Type.OK, String.format("%d flips", ouf_n));
	}

	private Map<Character, Rec> readFont(InStream inf) {
		HashMap<Character, Rec> font = new HashMap<Character, Rec>();
		String[] line = new String[m];
		for (int i = 0; i < m; i++)
			line[i] = inf.nextLine();
		int w = k + 3;
		int t = (line[0].length() + 1) / w;
		for (int p = 0; p < t; p++) {
			char c = line[0].charAt(p * w);
			Rec rec = new Rec(m, k);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < k; j++)
					rec.a[i][j] = line[i].charAt(p * w + 2 + j);
			font.put(c, rec);
		}
		font.put(' ', new Rec(m, k));
		return font;
	}

	private Rec readLayout(String s, InStream in, boolean obeysMinMax) {
		Rec rec = new Rec(m, n);
		int ofs = 0;
		for (int p = 0; p < s.length(); p++) {
			int spacing = in.nextInt();
			if (spacing < 0)
				throw new Outcome(Outcome.Type.WA, String.format("Negative spacing #%d: %d", p + 1, spacing));
			if (obeysMinMax) {
				if (p > 0 && (spacing < smin || spacing > smax))
					throw new Outcome(Outcome.Type.WA, String.format("Spacing #%d is out of range: %d", p + 1, spacing));
			}
			ofs += spacing;
			if (ofs + k > n)
				throw new Outcome(Outcome.Type.WA, String.format("Character #%d does not fit", p + 1));
			char c = s.charAt(p);
			Rec glyph = font.get(c);
			if (glyph == null)
				throw new Outcome(Outcome.Type.FAIL, String.format("Letter %c is not in font", c));
			for (int i = 0; i < m; i++)
				System.arraycopy(glyph.a[i], 0, rec.a[i], ofs, k);
			ofs += k;
		}
		return rec;
	}

	private int countFlips(Rec r1, Rec r2) {
		int cnt = 0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (r1.a[i][j] != r2.a[i][j])
					cnt++;
		return cnt;
	}
}
