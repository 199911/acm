import java.io.*;
import java.util.*;

public class caption_aa {
	public static void main(String[] args) {
		new caption_aa().run();
	}

	BufferedReader br;
	StringTokenizer st;
	PrintWriter out;
	boolean eof = false;

	private void run() {
		Locale.setDefault(Locale.US);
		try {
			br = new BufferedReader(new FileReader(FNAME + ".in"));
			out = new PrintWriter(FNAME + ".out");
			solve();
			out.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(566);
		}
	}

	String nextToken() {
		while (st == null || !st.hasMoreTokens()) {
			try {
				st = new StringTokenizer(br.readLine());
			} catch (Exception e) {
				eof = true;
				return "0";
			}
		}
		return st.nextToken();
	}

	int nextInt() {
		return Integer.parseInt(nextToken());
	}

	String FNAME = "caption";

	int BASE = 50;

	private void solve() throws IOException {
		int m = nextInt();
		int n = nextInt();
		int k = nextInt();
		int smin = nextInt();
		int smax = nextInt();
		st = new StringTokenizer(br.readLine());
		int tokens = st.countTokens() / 2;
		font = new long[tokens + 1][k][2];
		int[] perm = new int[256];
		Arrays.fill(perm, -1);
		perm[' '] = tokens;
		char[] names = new char[tokens];
		for (int i = 0; i < names.length; i++) {
			names[i] = nextToken().charAt(0);
			perm[names[i]] = i;
			char[] s = nextToken().toCharArray();
			for (int j = 0; j < s.length; j++) {
				if (s[j] == '*') {
					font[i][j][0] ^= 1;
				}
			}
		}
		for (int j = 1; j < m; j++) {
			int j0 = j / BASE;
			int j1 = j % BASE;
			for (int i = 0; i < names.length; i++) {
				char[] s = nextToken().toCharArray();
				for (int l = 0; l < s.length; l++) {
					if (s[l] == '*') {
						font[i][l][j0] ^= 1L << j1;
					}
				}
			}
		}
		char[] text = br.readLine().toCharArray();
		board = new long[n][2];
		int shift = 0;
		for (int i = 0; i < text.length; i++) {
			shift += nextInt();
			fill(shift, font[perm[text[i]]]);
			shift += k;
		}
		int[][] diff = new int[font.length][n];
		for (int i = 0; i < diff.length; i++) {
			for (int j = 0; j + k - 1 < diff[i].length; j++) {
				diff[i][j] = diff(j, font[i]);
			}
		}
		int[] inColumn = new int[n];
		for (int i = 0; i < inColumn.length; i++) {
			for (int j = 0; j < board[i].length; j++) {
				inColumn[i] += Long.bitCount(board[i][j]);
			}
		}
		char[] newText = br.readLine().toCharArray();
		int[][] a = new int[newText.length][n];
		int[][] p = new int[newText.length][n];
		for (int i = 0; i < a.length; i++) {
			Arrays.fill(a[i], Integer.MAX_VALUE / 2);
			Arrays.fill(p[i], -1);
		}
		int sum = 0;
		for (int i = 0; i + k - 1 < a[0].length; i++) {
			a[0][i + k - 1] = sum + diff[perm[newText[0]]][i];
			p[0][i + k - 1] = i;
			sum += inColumn[i];
		}
		for (int i = 0; i + 1 < a.length; i++) {
			for (int j = 0; j < a[i].length; j++) {
				if (a[i][j] < Integer.MAX_VALUE / 2) {
					sum = 0;
					for (int q = 1; q < smin && j + q < inColumn.length; q++) {
						sum += inColumn[j + q];
					}
					for (int s = smin; s <= smax && j + s + k < a[i].length; s++) {
						if (s > 0) {
							sum += inColumn[j + s];
						}
						int price = a[i][j] + sum
								+ diff[perm[newText[i + 1]]][j + s + 1];
						if (a[i + 1][j + s + k] > price) {
							a[i + 1][j + s + k] = price;
							p[i + 1][j + s + k] = s;
						}

					}
				}
			}
		}
		int min = Integer.MAX_VALUE / 2;
		int besti = 0;
		for (int i = 0; i < a[newText.length - 1].length; i++) {
			int price = a[newText.length - 1][i];
			for (int j = i + 1; j < inColumn.length; j++) {
				price += inColumn[j];
			}
			if (min > price) {
				min = price;
				besti = i;
			}
		}
		int[] ans = new int[newText.length];
		int letter = newText.length - 1;
		while (letter >= 0) {
			ans[letter] = p[letter][besti];
			besti -= ans[letter] + k;
			letter--;
		}
		for (int i = 0; i < ans.length; i++) {
			if (i > 0) {
				out.print(" ");
			}
			out.print(ans[i]);
		}
		out.println();
		// for (int i = 0; i < board.length; i++) {
		// for (int j = 0; j < board[i].length; j++) {
		// System.out.print(board[i][j]);
		// }
		// System.out.println();
		// }
	}

	long[][] board;

	private int diff(int shift, long[][] f) {
		int ans = 0;
		for (int i = 0; i < f.length; i++) {
			for (int j = 0; j < f[i].length; j++) {
				ans += Long.bitCount(board[i + shift][j] ^ f[i][j]);
			}
		}
		return ans;
	}

	private void fill(int shift, long[][] f) {
		for (int i = 0; i < f.length; i++) {
			for (int j = 0; j < f[i].length; j++) {
				board[i + shift][j] ^= f[i][j];
			}
		}
	}

	long[][][] font;
}
