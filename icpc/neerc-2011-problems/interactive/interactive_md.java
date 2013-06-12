import java.io.*;
import java.util.*;

public class interactive_md {
	private static BufferedReader in;

	public void run() throws IOException {
		int n = Integer.parseInt(in.readLine());
		ArrayList<Integer> a = new ArrayList<Integer>();
		for (int i = 0; i < n; i++) {
			a.add(i);
		}
		int best = query(a);
		main:
		for (int s = 0; best < n;) {
			for (int phase = 0; phase < 2; phase++) {
				for (int i = s + 1; i < n; i++) {
					ArrayList<Integer> save = new ArrayList<Integer>(a);
					if (phase == 0) {
						a.add(s, a.remove(i));
					} else {
						a.add(i, a.remove(s));
					}
					int query = query(a);
					if (query > best) {
						best = query;
						continue main;
					}
					a = save;
				}
			}
			s++;
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
		new interactive_md().run();
		in.close();
	}
}
