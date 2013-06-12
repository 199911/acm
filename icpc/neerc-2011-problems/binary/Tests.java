import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Tests generator for NEERC'2011 Problem B: Binary Encoding
 * @author Roman Elizarov
 */
public class Tests {
	private static int TEST_COUNTER = 0;
	private static final File TESTS_DIR = new File("tests");

	private static final void writeTest(int m) throws IOException {
		String tn = String.format("%02d", ++TEST_COUNTER);
		PrintWriter out = new PrintWriter(new FileWriter(new File(TESTS_DIR, tn)));
		out.println(m);
		out.close();
	}

	public static void main(String[] args) throws IOException {
		TESTS_DIR.mkdirs();
		writeTest(6);
		for (int i = 2; i <= 20; i++)
			if (i != 6)
				writeTest(i);
		for (int i = 32; i <= 10000; i *= 2)
			for (int k = -1; k <= 1; k++)
				writeTest(i + k);
		writeTest(8888);
		writeTest(9998);
		writeTest(9999);
		writeTest(10000);
	}
}
