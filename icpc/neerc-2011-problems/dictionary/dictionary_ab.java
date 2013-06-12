import java.io.*;
import java.util.*;

public class dictionary_ab {
	public static void main(String[] args) {
		new dictionary_ab().run();
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

	String FNAME = "dictionary";

	int[][] go = new int[500000][26];
	
	int free = 1;
	
	void addString(String s) {
		int p = 0;
		for (int i = 0; i < s.length(); ++i) {
			int c = s.charAt(i) - 'a';
			if (go[p][c] == 0) {
				go[p][c] = free;
				++free;
			}
			p = go[p][c];
		}
	}
	
	Random rand = new Random();
	
	String randString(int m) {
		StringBuilder ans = new StringBuilder();
		for (int i =0; i < m; ++i) {
			ans.append((char)('a' + rand.nextInt(26)));
		}
		return ans.toString();
	}
	
	HashSet<String>[] ep;
	
	private void solve() throws IOException {
		Long tm = System.currentTimeMillis();
		HashSet<String> b = new HashSet<String>();
		ep = new HashSet[26];
		for (int i = 0; i < ep.length; ++i) {
			ep[i] = new HashSet<String>();
		}
		
		int n = nextInt();
		String[] s = new String[n];
		for (int i = 0; i < n; ++i) {
			s[i] = nextToken();
//			s[i] = randString(40);
			addString(s[i]);
			for (int j = 0; j < s[i].length(); ++j) {
				String t = s[i].substring(j);
				ep[t.charAt(0) - 'a'].add(t);
			}
			for (int j = 1; j <= s[i].length(); ++j) {
				b.add(s[i].substring(0, j));
			}
		}
		
		System.out.println(System.currentTimeMillis() - tm);
		
		sc = new boolean[ep.length];
		for (int i = 0; i < sc.length; ++i) {
			sc[i] = ep[i].contains("" + (char)(i + 'a'));
		}
		
//		long ans = 0;
//					
//		
//		for (String t : b) {
//			for (char c = 'a'; c <= 'z'; ++c) {
//				boolean q = b.contains(t + c);
//				if (!q) {
//					ans += ep[c - 'a'].size();
//				}
//				if (q && sc[c - 'a']) {
//					++ans;
//				}
//			}
//		}
		
		long ans = dfs(0);
		
		System.out.println(System.currentTimeMillis() - tm);
		
		boolean[] ff = new boolean[26];
		
		for (String w : s) {
			if (w.length() == 1 && !ff[w.charAt(0) - 'a']) {
				++ans;
				ff[w.charAt(0) - 'a'] = true;
			}
		}
					
		out.println(ans);
		
		System.out.println(System.currentTimeMillis() - tm);
	}
	
	boolean[] sc;
	
	long dfs(int p) {
		long ans = 0;
		for (int i = 0; i < go[p].length; ++i) {
			if (go[p][i] == 0) {
				if (p != 0) {
					ans += ep[i].size();
				}
			} else {
				ans += dfs(go[p][i]);
				if (p != 0 && sc[i]) {
					++ans;
				}
			}
		}
		return ans;
	}
	
}
