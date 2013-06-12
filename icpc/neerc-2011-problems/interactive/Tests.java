import java.io.*;
import java.util.*;

public class Tests {
	private static File dir = new File("tests");
	private int curTest = 1;
	private static boolean verbose = true;

	private String testName;
	private PrintWriter out;
	private Random r = new Random(4523560355687435L);
	final static int MAX = 50;
	
	public void run() {
		t(2, 0, 1, 3);
		t(r(4));
		t(r(5));
		t(r(6));
		t(0, 1);
		t(1, 0);
		t(0);
		t(0, 1, 2);
		t(1, 0, 2);
		t(2, 1, 0);
		t(1, 3, 2, 0);
		for (int i = 0; i < 4; i++) {
			t(r(r.nextInt(5) + 5));
		}
		for (int i = 0; i < 4; i++) {
			t(r(r.nextInt(10) + 10));
		}
		for (int i = 12; i <= 40; i += 7) {
			t(r(i));
		}
		for (int i = 1; i <= 40; i++) {
			if (40 % i != 0) {
				continue;
			}
			for (int j = 0; j <= 1; j++) {
				t(f(z(i, 40 / i), 3 * j));
			}
		}
		for (int i = 1; i <= 11; i += 5) {
			t(f(z(40, 1), i));
			t(f(z(1, 40), i));
		}
		for (int i = 0; i < 4; i++) {
			t(r(40 - r.nextInt(1 + r.nextInt(5))));
		}
	}
	
	List<Integer> r(int n) {
		List<Integer> a = z(n, 1);
		Collections.shuffle(a, r);
		return a;
	}
	
	List<Integer> f(List<Integer> a, int changes) {
		while (changes-- > 0) {
			Collections.swap(a, r.nextInt(a.size()), r.nextInt(a.size()));
		}
        return a;
	}
	
	List<Integer> z(int n, int series) {
		List<Integer> a = new ArrayList<Integer>();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= series; j++) {
				a.add(i * series - j);
			}
		}
		return a;
	}
	
	void t(List<Integer> a) {
		t(a.toArray(new Integer[a.size()]));
	}
	
	void t(Integer... a) {
		open();
		out.println(a.length);
		for (int i = 0; i < a.length; i++) {
			if (i > 0) {
				out.print(" ");
			}
			out.print(a[i] + 1);
		}
		out.println();
		close();
	}
	
	private void open() {
		try {
			testName = "" + curTest / 10 + curTest % 10;
			out = new PrintWriter(new File(dir, testName));
			if (verbose) { 
				System.out.print("Generating " + testName + "...");
			}
		} catch (IOException e) {
			throw new RuntimeException("Unable to open " + testName + " for writing", e);
		}
	}

	private void close() {
		out.close();
		if (verbose) {
			System.out.println(" done.");
		}
		curTest++;
	}

	public static void main(String[] args) {
		Locale.setDefault(Locale.US);
		dir.mkdirs();
		new Tests().run();
	}
	
	class LottoSet<T> {
		List<T> list = new ArrayList<T>();
		Map<T, Integer> positions = new HashMap<T, Integer>();
		
		public void add(T v) {
			if (positions.containsKey(v)) {
				return;
			}
			positions.put(v, list.size());
			list.add(v);
		}

		public void remove(T v) {
			int p = positions.get(v);
			if (p == list.size() - 1) {
				list.remove(p);
				positions.remove(v);
				return;
			}
			T last = list.get(list.size() - 1);
			list.set(p, last);
			list.remove(list.size() - 1);
			positions.put(last, p);
			positions.remove(v);
			return;
		}
		
		public T lotto(Random r) {
			return list.get(r.nextInt(list.size()));
		}
	}
}
