import java.io.*;
import java.util.*;

public class lanes_ab {
	public static void main(String[] args) {
		new lanes_ab().run();
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
//		} catch (OutOfMemoryError e){
//			return;
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

	String FNAME = "lanes";

	private void solve() throws IOException {
		long tm = System.currentTimeMillis();
		int n1 = nextInt();
		int n2 = nextInt();
		int m = nextInt();
		int r = nextInt();
		final int SIZE = 100 * m + 100;
		int[] x = new int[m];
		int[] y = new int[m];
		for (int i = 0; i < m; i++) {
			x[i] = nextInt();
			y[i] = nextInt();			
//			x[i] = 100;
//			y[i] = 100;
		}

		long[] lans;
		int[] flow = new int[SIZE];
		long[] buf = new long[SIZE];
		
		{	
			Arrays.fill(flow, 0);
			long tw = 0;
			int pw = 0;
			for (int i = 0; i < SIZE; ++i) {
				int xi = i < m ? x[i] : 0;
				flow[i] = Math.min(pw + xi, n1 + 1);
				pw = Math.max(pw + xi - n1 - 1, 0);
				tw += pw;
			}
			
			System.out.println(tw);
	
			lans = buf;
			Arrays.fill(lans, 0);
						
			int[] st = new int[SIZE];
			int top = 0;
			
			for (int i = lans.length - 1; i >= 0; --i) {
				if (flow[i] == n1 + 1) {
					--top;
					if (top < 0) {
						top += st.length;
					}
//					top = (top + st.length - 1) % st.length;
					tw += st[top] - i;
					lans[i] = tw;
				} else {
					lans[i] = tw;
					for (int j = flow[i]; j < n1; ++j) {
						st[top] = i;
						++top;
						if (top == st.length) {
							top = 0;
						}
//						top = (top + 1) % st.length;
					}
				}
			}
			
			lans = new long[2 * m];
			System.arraycopy(buf, 0, lans, 0, 2 * m);			
		}

		long[] rans;
		{
			Arrays.fill(flow, 0);
			long tw = 0;
			int pw = 0;
			for (int i = 0; i < SIZE; ++i) {
				int yi = i < m ? y[i] : 0;
				flow[i] = Math.min(pw + yi, n2 + 1);
				pw = Math.max(pw + yi - n2 - 1, 0);
				tw += pw;
			}
						
			System.out.println(tw);			
			
			int free = 0;
			
			rans = buf;
			Arrays.fill(rans, 0);

			for (int i = 0; i < SIZE; ++i) {
				if (flow[i] == n2 + 1) {
					while (free <= i && free < flow.length || flow[free] == n2 + 1) {
						++free;
					}
					tw += free - i;
					if (free < flow.length) {
						++flow[free];
					}
				}
				rans[i] = tw;
			}
		}
		
		int ans = -1;
		long ansv = Long.MAX_VALUE;
		
		for (int i = 0; i < m; ++i) {
			if (lans[i] + rans[i + r - 1] < ansv) {
				ansv = lans[i] + rans[i + r - 1];
				ans = i;
			}
		}
//		System.out.println(Arrays.toString(lans));
//		System.out.println(Arrays.toString(rans));
		System.out.println(ansv);
//	
		out.println(ans + 1);
		System.out.println(System.currentTimeMillis() - tm);
	}
}
