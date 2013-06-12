import java.util.*;
import java.io.*;

public class ascii_rs implements Runnable {
	private BufferedReader in;
	private PrintWriter out;
	
	private void solve() throws IOException {
		StringTokenizer st = new StringTokenizer(in.readLine());
		int h = Integer.parseInt(st.nextToken());
		int w = Integer.parseInt(st.nextToken());
		int answer = 0;
		for (int i = 0; i < h; i++) {
			String line = in.readLine();
			boolean inside = false;
			for (int j = 0; j < w; j++) {
				if (line.charAt(j) == '/' ||line.charAt(j) == '\\') {
					inside = !inside;
				}
				if (inside) {
					answer++;
				}
			}
		}
		out.println(answer);
	}
	
	public static void main(String[] args) {
		new Thread(new ascii_rs()).start();
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
