import java.io.*;
import java.util.*;

public class interactive_md_wa {
	private static BufferedReader in;

	public void run() throws IOException {
		int n = Integer.parseInt(in.readLine());
		ArrayList<Integer> a = new ArrayList<Integer>();
		for (int i = 0; i < n; i++) {
			a.add(i);
		}
		int s = 0;
		int lcs = query(a);
		main:
		while (lcs < n) {
			for (int i = s + 1; i < n; i++) {
				ArrayList<Integer> save = new ArrayList<Integer>(a);
				Integer t = a.remove(i);
				a.add(s, t);
				int query = query(a);
				if (query == n) {
					break main;
				}
				if (query > lcs) {
					lcs = query;
					continue main;
				}
				a = save;
			}
			for (;;) {
				ArrayList<Integer> save = new ArrayList<Integer>(a);
				Integer t = a.remove(s);
				a.add(t);
				int query = query(a);
				if (query == n) {
					break main;
				}
				if (query < lcs) {
					a = save;
					s++;
					continue main;
				}
			}
		}
	}
	
	int query(Iterable<Integer> a) throws IOException {
		boolean first = true;
		for (Integer i : a) {
			if (!first) {
				System.out.print(" ");
			}
			first = false;
			System.out.print(i + 1);
		}
		System.out.println();
		return Integer.parseInt(in.readLine());
	}
	
	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new BufferedReader(new InputStreamReader(System.in));
		new interactive_md_wa().run();
		in.close();
	}
}
