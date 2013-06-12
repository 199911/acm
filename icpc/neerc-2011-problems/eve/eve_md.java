import java.io.*;
import java.util.*;

public class eve_md {
	private static String fileName = eve_md.class.getSimpleName().replaceFirst("_.*", "").toLowerCase();
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;

	public void run() {
		int n = in.nextInt();
		int origin = n;
		boolean[] female = new boolean[n];
		for (int i = 0; i < n; i++) {
			female[i] = in.next().equals("F");
		}
		int m = in.nextInt();
		female = Arrays.copyOf(female, n + m);
		boolean[] alive = new boolean[n + m];
		int[] grandmother = new int[n + m];
		for (int i = 0; i < n; i++) {
			grandmother[i] = i;
		}
		Arrays.fill(alive, true);
		for (int i = 0; i < m; i++) {
			int id = in.nextInt();
			if (id < 0) {
				alive[- id - 1] = false;
			} else {
				id = in.nextInt() - 1;
				female[n] = in.next().equals("F");
				grandmother[n] = grandmother[id];
				n++;
			}
		}
		boolean[] hasAncestors = new boolean[origin];
		for (int i = 0; i < n; i++) {
			if (alive[i]) {
				hasAncestors[grandmother[i]] = true;
			}
		}
		int[] dna = new int[origin];
		final int UNKNOWN = Integer.MIN_VALUE;
		Arrays.fill(dna, UNKNOWN);
		for (int i = 0, k = in.nextInt(); i < k; i++) {
			int x = in.nextInt() - 1;
			int uid = in.nextInt();
			dna[grandmother[x]] = uid;
		}
		int commonDna = UNKNOWN;
		boolean haveUnknown = false;
		boolean haveDifferent = false;
		int eve = 0;
		for (int i = 0; i < origin; i++) {
			if (!hasAncestors[i]) {
				continue;
			}
			eve++;
			if (dna[i] == UNKNOWN) {
				haveUnknown = true;
				continue;
			}
			if (commonDna == UNKNOWN) {
				commonDna = dna[i];
			} else if (commonDna != dna[i]) {
				haveDifferent = true;
			}
		}
		if (haveDifferent) {
			out.println("NO");
		} else if (eve > 1 && haveUnknown) {
			out.println("POSSIBLY");
		} else {
			out.println("YES");
		}
	}
	
	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new FileReader(inputFileName));
		out = new PrintWriter(outputFileName);
		new eve_md().run();
		in.close();
		out.close();
	}
}
