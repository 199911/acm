import java.io.*;
import java.util.*;
import java.math.*;

public class journey_sp {
	public static void main(String[] args) {
		new journey_sp().run();
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

	String FNAME = "journey";
	
	int[] dx = new int[]{1, 0, -1, 0};
	int[] dy = new int[]{0, -1, 0, 1};
	BigInteger[] startx, starty, shiftx, shifty;
	int[] startdir, shiftdir;
	boolean finita = false;
	
	boolean move(int func, BigInteger sx, BigInteger sy, int sdir) {
//		System.err.println(func + " " + sx + " " + sy + " " + sdir);
		if (color[func] == 2) {
			return false;
		}
		if (color[func] == 0) {
			color[func] = 1;
			startx[func] = sx;
			starty[func] = sy;
			startdir[func] = sdir;
		} else if (color[func] == 1) {
			if (startdir[func] == sdir) {
				finita = true;
				if (!sx.equals(startx[func]) || !sy.equals(starty[func])) {
					return true;
				} else {
					return false;
				}
			}
		}
		BigInteger x = BigInteger.ZERO;
		BigInteger y = BigInteger.ZERO;
		int dir = 0;
		for (int j = 0; j < commands[func].length; j++) {
			if (commands[func][j] == -1) {
				x = x.add(BigInteger.valueOf(dx[dir]));
				y = y.add(BigInteger.valueOf(dy[dir]));
				relax(func, x, y);
			} else if (commands[func][j] == -2) {
				dir = (dir + 3) % 4;
			} else if (commands[func][j] == -3) {
				dir = (dir + 1) % 4;
			} else {
				int i = commands[func][j];
				if (sdir == 0) {
					if (move(i, sx.add(x), sy.add(y), (sdir + dir) % 4)) {
						return true;
					}
				} else if (sdir == 1) {
					if (move(i, sx.add(y), sy.subtract(x), (sdir + dir) % 4)) {
						return true;
					}
				} else if (sdir == 2) {
					if (move(i, sx.subtract(x), sy.subtract(y), (sdir + dir) % 4)) {
						return true;
					}
				} else if (sdir == 3) {
					if (move(i, sx.subtract(y), sy.add(x), (sdir + dir) % 4)) {
						return true;
					}
				}
 				for (int k = 0; k < 4; k++) {
					if (dir == 0) {
						relax(func, x.add(bestx[i][k]), y.add(besty[i][k]));
					} else if (dir == 1) {
						relax(func, x.add(besty[i][k]), y.subtract(bestx[i][k]));
					} else if (dir == 2) {
						relax(func, x.subtract(bestx[i][k]), y.subtract(besty[i][k]));
					} else if (dir == 3) {
						relax(func, x.subtract(besty[i][k]), y.add(bestx[i][k]));
					}
				}
				if (dir == 0) {
					x = x.add(shiftx[i]);
					y = y.add(shifty[i]);
				} else if (dir == 1) {
					x = x.add(shifty[i]);
					y = y.subtract(shiftx[i]);
				} else if (dir == 2) {
					x = x.subtract(shiftx[i]);
					y = y.subtract(shifty[i]);
				} else if (dir == 3) {
					x = x.subtract(shifty[i]);
					y = y.add(shiftx[i]);
				}
				dir = (dir + shiftdir[i]) % 4;
				if (finita) {
					return false;
				}
			}
		}
		color[func] = 2;
		shiftx[func] = x;
		shifty[func] = y;
		shiftdir[func] = dir;
		return false;
	}
	
	void relax(int f, BigInteger x, BigInteger y) {
		if (bestx[f][0].add(besty[f][0]).compareTo(x.add(y)) < 0) {
			bestx[f][0] = x;
			besty[f][0] = y;
		}
		if (bestx[f][1].subtract(besty[f][1]).compareTo(x.subtract(y)) < 0) {
			bestx[f][1] = x;
			besty[f][1] = y;
		}
		if (bestx[f][2].add(besty[f][2]).compareTo(x.add(y)) > 0) {
			bestx[f][2] = x;
			besty[f][2] = y;
		}
		if (bestx[f][3].subtract(besty[f][3]).compareTo(x.subtract(y)) > 0) {
			bestx[f][3] = x;
			besty[f][3] = y;
		}
	}
	
	BigInteger[][] bestx, besty;
	
	int[][] commands;
	int[] color;

	private void solve() throws IOException {
		int n = nextInt();
		commands = new int[n][];
		for (int i = 0; i < n; i++) {
			int m = nextInt();
			commands[i] = new int[m];
			for (int j = 0; j < m; j++) {
				String s = nextToken();
				if ("GO".equals(s)) {
					commands[i][j] = -1;
				} else if ("LEFT".equals(s)) {
					commands[i][j] = -2;
				} else if ("RIGHT".equals(s)) {
					commands[i][j] = -3;
				} else {
					commands[i][j] = Integer.parseInt(s.substring(1)) - 1;
				}
			}
		}
		bestx = new BigInteger[n][4];
		besty = new BigInteger[n][4];
		for (int i = 0; i < n; i++) {
			Arrays.fill(bestx[i], BigInteger.ZERO);
			Arrays.fill(besty[i], BigInteger.ZERO);
		}
		color = new int[n];
		startx = new BigInteger[n];
		starty = new BigInteger[n];
		startdir = new int[n];
		shiftx = new BigInteger[n];
		shifty = new BigInteger[n];
		Arrays.fill(shiftx, BigInteger.ZERO);
		Arrays.fill(shifty, BigInteger.ZERO);
		shiftdir = new int[n];
		if (move(0, BigInteger.ZERO, BigInteger.ZERO, 0)) {
			out.println("Infinity");
		} else {
			BigInteger ans = BigInteger.ZERO;
			for (int i = 0; i < 4; i++) {
				if (ans.compareTo((bestx[0][i].abs()).add(besty[0][i].abs())) < 0) {
					ans = (bestx[0][i].abs()).add(besty[0][i].abs());
				}
			}
			out.println(ans);
		}
	}
}
