import java.io.*;

public class binary_rs implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	
	private void solve() throws IOException {
		int m = Integer.parseInt(in.readLine());
		int n = 0;
		while ((1 << n) < m) {
			n++;
		}
		int left = (1 << n);
		for (int i = 0; m > 0; i++, left -= 2, m--) {
			String cur;
			if (left - 1 >= m) {
				cur = binary(i, n).substring(0, n - 1);
				i++;
			} else {
				cur = binary(i, n);
			}
			out.println(cur);
		}
		
	}
	
	private String binary(int number, int n) {
		StringBuilder sb = new StringBuilder();
		for (int k = 0; k < n; k++) {
			if (number % 2 == 0) {
				sb.append('0');
			} else {
				sb.append('1');
			}
			number = number >> 1;
		}
		return sb.reverse().toString();
	}

	public static void main(String[] args) {
		new Thread(new binary_rs()).start();
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
