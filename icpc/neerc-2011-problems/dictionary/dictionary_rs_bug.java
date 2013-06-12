import java.util.*;
import java.io.*;

public class dictionary_rs_bug implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	
	private static class Trie {
		int[][] go;
		boolean[] term;
		int curSize;
		
		public Trie(int maxSize) {
			go = new int[maxSize][26];
			term = new boolean[maxSize];
			Arrays.fill(go[0], -1);
			curSize = 1;
		}
		
		public void addWord(String word) {
			int cur = 0;
			for (int i = 0; i < word.length(); i++) {
				int ch = word.charAt(i) - 'a';
				if (go[cur][ch] == -1) {
					go[cur][ch] = curSize;
					Arrays.fill(go[curSize], -1);
					curSize++;
				}
				cur = go[cur][ch];
			}
			term[cur] = true;
		}
	}
	
	private void solve() throws IOException {
		int n = Integer.parseInt(in.readLine());
		Set<String> words = new HashSet<String>();
		for (int i = 0; i < n; i++) {
			words.add(in.readLine());
		}
		Trie prefixTrie = new Trie(100 * n);
		@SuppressWarnings("unchecked")
		Set<String>[] suffixes = new Set[26];
		for (int i = 0; i < suffixes.length; i++) {
			suffixes[i] = new HashSet<String>();
		}
		for (String word: words) {
			prefixTrie.addWord(word);
			for (int j = 0; j < word.length(); j++) {
				int ch = word.charAt(j) - 'a';
				suffixes[ch].add(word.substring(j + 1));
			}
		}
		long answer = 0;
		for (int i = 1; i < prefixTrie.curSize; i++) {
			for (int ch = 0; ch < 26; ch++) {
				if (prefixTrie.go[i][ch] == -1) {
					answer += suffixes[ch].size();
				} else {
					int t = prefixTrie.go[i][ch];
					if (!prefixTrie.term[t] && suffixes[ch].size() > 0) {
						answer++;
					}
				}
			}
		}
		out.println(answer + words.size());
	}
	
	public static void main(String[] args) {
		new Thread(new dictionary_rs_bug()).start();
	}

	@Override
	public void run() {
		String problemName = getClass().getName().split("_")[0];
		try {
			in = new BufferedReader(new FileReader(new File(problemName + ".in")));
			out = new PrintWriter(new File(problemName + ".out"));
			solve();
			in.close();
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}
