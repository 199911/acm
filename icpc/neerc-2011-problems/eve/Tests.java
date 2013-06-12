import java.io.*;
import java.util.*;

public class Tests {
	private static File dir = new File("tests");
	private int curTest = 1;
	private static boolean verbose = true;

	private String testName;
	private PrintWriter out;
	private Random r = new Random(4523560356087435L);
	final static int MAX = 100000;
	
	public void run() {
		t("4\nM\nF\nM\nF\n12\n3 4 F\n1 2 M\n1 2 M\n3 4 F\n-3\n-2\n-4\n-1\n6 5 M\n7 5 F\n-7\n-6\n0");
		t("3\nF\nF\nM\n3\n3 2 M\n3 1 F\n-3\n2\n4 100500\n5 100500");
		t("3\nM\nF\nM\n2\n1 2 M\n3 2 F\n0");
		t("2\nM\nF\n2\n1 2 M\n-2\n2\n1 2011\n2 2012");
		t(2, 2, 6, 0, 1, 4, true, 0, 8);
		t(1, 2, 2, 0, 2, 4, true, 2, 8);
		t(2, 1, 2, 2, 1, 5, true, 0, 8);
		t(1, 1, 1, 1, 1, 2, false, 2, 8);
		t(1, 1, 8, 0, 1, 5, false, 0, -1);
		for (int n : new int[]{10, 566, MAX}) {
			for (int c = 0; c <= 1; c++) {
				t(n / 4, n / 4, n / 2, n / 8, n / 8, n / 2, true, n / 8 * 2 - c, -1);
				t(n / 3, n / 3, n / 3, 0, 1 + c, n / 3 + 1, false, 0, 7);
				t(n / 3, 2 * n / 3, 0, n / 6, n / 3, n / 6 + n / 3, true, n / 6 + n / 3 - c * (r.nextInt(n / 10) + 1), -1);
				t(n / 4, n / 4, n / 2, n / 8, n / 8, n / 2, false, c, -1);
				t(n - 1, 1, n, n - 1, 1, 2 * n, false, 1 + c, -1);
				t(1, n - 1, n, 1, n - 1, 2 * n, false, c * n / 10, -1);
			}
			t(n / 3, n / 3, n - n / 3 * 2, 1, 1, n / 3 + 1, false, n / 2, 3);
		}
		t(0, MAX, 0, 0, 1, 1, false, MAX, 7);
		t(0, MAX, 0, 0, 2, 2, false, 1, 7);
		t(0, MAX, 0, 0, 2, 2, false, MAX, 7);
		t(MAX, 0, 0, 1, 0, 1, true, MAX, 7);
		t(MAX, 0, 0, 2, 0, 2, true, 1, 7);
	}

	private void t(int origM, int origF, int born, int adams, int eves, int alive, boolean allSame, int checks, int mode) {
		if (mode == -1) {
			mode = r.nextInt();
		}
		open();
		int orig = origM + origF;
		int n = orig + born;
		int id = orig;
		boolean[] female = new boolean[n + 1];
		int[] aliveAtEnd = new int[orig];
		int[] toBear = new int[orig];
		int[] toKill = new int[orig];
		Integer[] origIDs = new Integer[orig];
		@SuppressWarnings("unchecked")
		ArrayList<Integer>[] fs = new ArrayList[orig];
		@SuppressWarnings("unchecked")
		ArrayList<Integer>[] ms = new ArrayList[orig];
		@SuppressWarnings("unchecked")
		ArrayList<Integer>[] all = new ArrayList[orig];
		int mm = 0;
		for (int i = 0; i < orig; i++) {
			origIDs[i] = i + 1;
		}
		Collections.shuffle(Arrays.asList(origIDs), r);
		LottoSet<Integer> future = new LottoSet<Integer>();
		LottoSet<Integer> males = new LottoSet<Integer>();
		for (int i = 0; i < orig; i++) {
			fs[i] = new ArrayList<Integer>();
			ms[i] = new ArrayList<Integer>();
			all[i] = new ArrayList<Integer>();
			if (i < origF) {
				fs[i].add(origIDs[i]);
				female[origIDs[i]] = true;
			} else {
				ms[i].add(origIDs[i]);
				mm++;
				males.add(i);
			}
			all[i].add(origIDs[i]);
		}
		assert orig <= MAX;
		out.println(orig);
		for (int i = 1; i <= orig; i++) {
			out.println(female[i] ? "F" : "M");
		}
		for (int i = 0; i < eves; i++) {
			aliveAtEnd[i]++;
		}
		for (int i = 0; i < adams; i++) {
			aliveAtEnd[origF + i]++;
		}
		for (int i = 0; i < orig; i++) {
			toKill[i] = all[i].size() - aliveAtEnd[i];
		}
		assert alive >= adams + eves;
		assert alive <= born + adams + eves;
		for (int t = 0; t < born; t++) {
			if (t < alive - adams - eves) {
				int i = (mode & 8) > 0 ? t % eves : r.nextInt(eves);
				toBear[i]++;
				future.add(i);
				aliveAtEnd[i]++;
			} else {
				int i = (mode & 8) > 0 ? t % origF : r.nextInt(origF);
				toBear[i]++;
				future.add(i);
				toKill[i]++;
			}
		}
		int todoBirths = born;
		int todoDeaths = n - alive;
		assert todoBirths + todoDeaths <= MAX;
		out.println(todoBirths + todoDeaths);
		iteration:
		while (todoBirths + todoDeaths > 0) {
			if ((todoBirths + todoDeaths) % 2000 == 0) {
				System.out.print(".");
			}
			if (todoBirths == 0 || mm > 1 && r.nextInt(todoBirths + todoDeaths) < todoDeaths) {
				int i = -1;
				for (int t = 0; t < 100 * orig; t++) {
//				for (;;) {
					i = r.nextInt(orig);
					if (toKill[i] > 0 && (toBear[i] == 0 || fs[i].size() + ms[i].size() >= 2)) {
						break;
					}
					i = -1;
				}
				if (i >= 0) {
					int v;
					boolean killM = r.nextInt(ms[i].size() + fs[i].size()) < ms[i].size();
					if (toBear[i] > 0 && fs[i].size() == 1) {
						killM = true;
					}
					if (killM) {
						v = ms[i].get(r.nextInt(ms[i].size()));
						ms[i].remove((Integer) v);
						if (ms[i].size() == 0) {
							males.remove(i);
						}
						mm--;
					} else {
						v = fs[i].get(r.nextInt(fs[i].size()));
						fs[i].remove((Integer) v);
					}
					out.println(-v);
					todoDeaths--;
					toKill[i]--;
					continue iteration;
				}
			}
			if (todoBirths-- == 0) {
				throw new RuntimeException("todoBirths == 0");
			}
			int i = future.lotto(r);
			int j = males.lotto(r);
//			System.out.println("a");
//			for (;;) {
//				i = r.nextInt(origF);
//				if (toBear[i] > 0) {
//					if (fs[i].size() == 0) {
//						throw new RuntimeException("Where are the ladies?!");
//					}
//					break;
//				}
//			}
//			System.out.println("b");
//			for (;;) {
//				j = r.nextInt(orig);
//				if (ms[j].size() > 0) {
//					break;
//				}
//			}
			boolean sex = (mm > 1) && r.nextBoolean();
			out.println(ms[j].get(r.nextInt(ms[j].size())) + " " + fs[i].get(r.nextInt(fs[i].size())) + " " + (sex ? "F" : "M"));
			toBear[i]--;
			if (toBear[i] == 0) {
				future.remove(i);
			}
			id++;
			if (sex) {
				fs[i].add(id);
			} else {
				ms[i].add(id);
				males.add(i);
				mm++;
			}
			all[i].add(id);
		}
		
		ArrayList<String> mtDNA = new ArrayList<String>();
		int commonUid = rndUid();
		int m = adams + eves;
		for (int i = 0; i < orig; i++) {
			int uid;
			boolean doCheck;
			if (aliveAtEnd[i] == 0) {
				uid = ((mode & 1) > 0 || !allSame) ? rndUid() : commonUid;
				doCheck = (mode & 2) > 0;
				if (fs[i].size() > 0 || ms[i].size() > 0) {
					throw new RuntimeException("Zombies?!");
				}
			} else {
				doCheck = r.nextInt(m) < checks;
				if (doCheck) {
					checks--;
				}
				m--;
				uid = allSame ? commonUid : rndUid();
			}
			if (doCheck) {
				Collections.shuffle(all[i], r);
				int c = (mode & 4) > 0 ? (r.nextInt(all[i].size()) + 1) : 1;
				for (int j = 0; j < c; j++) {
					mtDNA.add(all[i].get(j) + " " + uid);
				}
			}
		}
		Collections.shuffle(mtDNA, r);
		assert mtDNA.size() <= MAX;
		out.println(mtDNA.size());
		for (String s : mtDNA) {
			out.println(s);
		}
		System.out.print(" (" + orig + ", " + (n - alive + born) + ", " + mtDNA.size() + ")");
		close();
		
	}

	int rndUid() {
		return r.nextInt(1000000000) + 1;
	}
	
	void t(String s) {
		open();
		out.println(s);
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
