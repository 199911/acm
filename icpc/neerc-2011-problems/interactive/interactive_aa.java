import java.io.PrintWriter;
import java.util.Scanner;

public class interactive_aa {
	public static void main(String[] args) {
		new interactive_aa().run();
	}

	Scanner in = new Scanner(System.in);
	PrintWriter out = new PrintWriter(System.out);

	private void run() {
		int n = in.nextInt();
		int[] p = new int[n];
		for (int i = 0; i < p.length; i++) {
			p[i] = i + 1;
		}
		int same = 0;
		loop: while (same < n) {
			for (int num = 0; same < n && num < p.length; num++) {
				int[] a = p.clone();
				int numPos = -1;
				for (int i = 0; i < a.length; i++) {
					if (a[i] == num + 1) {
						numPos = i;
					}
				}
				for (int i = numPos; i > 0; i--) {
					a[i] = a[i - 1];
				}
				a[0] = num + 1;
				int max = -1;
				int maxpos = -1;
				for (int i = 0; same < n && i < a.length; i++) {
					print(a);
					same = in.nextInt();
					if (max < same) {
						max = same;
						maxpos = i;
					}
					if (i + 1 < a.length) {
						int tmp = a[i];
						a[i] = a[i + 1];
						a[i + 1] = tmp;
					}
				}
				same = max;
				a = p.clone();
				for (int i = numPos; i > 0; i--) {
					a[i] = a[i - 1];
				}
				a[0] = num + 1;
				for (int i = 0; i < maxpos; i++) {
					int tmp = a[i];
					a[i] = a[i + 1];
					a[i + 1] = tmp;
				}
				p = a;
			}
		}
	}

	private void print(int[] p) {
		for (int i = 0; i < p.length; i++) {
			if (i > 0) {
				out.print(" ");
			}
			out.print(p[i]);
		}
		out.println();
		out.flush();
	}

}
