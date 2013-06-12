import java.io.*;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Random;

public class Tests {
    static class Testcase {
        final int n;
        final int res;
        final int numBranches;
        final int randomValueForSorting;

        Testcase(int n, int res, int numBranches, Random random) {
            this.n = n;
            this.res = res;
            this.numBranches = numBranches;
            this.randomValueForSorting = random.nextInt(1000000);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader("tests.dat"));
        new File("tests").mkdir();
        Random random = new Random(43543915431L);
        int maxN = 10000;
        Testcase[] t = new Testcase[maxN + 1];
        for (int i = 1; i <= maxN; ++i) {
            String line = reader.readLine();
            String[] parts = line.split(" ", -1);
            int n = Integer.parseInt(parts[0]);
            int res = Integer.parseInt(parts[1]);
            int numBranches = Integer.parseInt(parts[2]);
            if (n != i) throw new RuntimeException();
            t[i] = new Testcase(n, res, numBranches, random);
        }
        Testcase[] byBranches = new Testcase[maxN];
        System.arraycopy(t, 1, byBranches, 0, maxN);
        Arrays.sort(byBranches, new Comparator<Testcase>() {
            public int compare(Testcase a, Testcase b) {
                int z = b.numBranches - a.numBranches;
                if (z == 0)
                    z = a.randomValueForSorting - b.randomValueForSorting;
                return z;
            }
        });
        boolean[] take = new boolean[maxN + 1];
        for (int i = 1; i <= 39; ++i)
            take[i] = true;
        take[maxN] = true;
        for (int i = 0; i < 5; ++i) {
            take[byBranches[i].n] = true;
        }
        int firstNonEqual;
        for (firstNonEqual = 0; byBranches[firstNonEqual].numBranches == byBranches[0].numBranches; ++firstNonEqual) {}
        for (int i = 0; i < 5; ++i) {
            take[byBranches[i + firstNonEqual].n] = true;
        }
        for (int i = 0; i < 29; ++i) {
            int x;
            do {
                x = random.nextInt(maxN) + 1;
                if (!take[x] && ((x == 1 || t[x].res != t[x - 1].res || x == maxN || t[x].res != t[x + 1].res)))
                    break;
            } while (true);
            take[x] = true;
        }
        for (int i = 0; i < 20; ++i) {
            int x;
            do {
                x = random.nextInt(maxN) + 1;
                if (!take[x])
                    break;
            } while (true);
            take[x] = true;
        }
        int SAMPLE_INPUT = 6;
        take[SAMPLE_INPUT] = false;
        outputTest(1, SAMPLE_INPUT);
        int lastTest = 1;
        // 1 is disallowed by the problem statement.
        take[1] = false;
        for (int i = 1; i < take.length; ++i) {
            if (take[i]) {
                outputTest(++lastTest, i);
            }
        }
    }

    private static void outputTest(int testId, int input) {
        String name = "" + testId;
        while (name.length() < 2) name = "0" + name;
        PrintWriter writer;
        try {
            writer = new PrintWriter("tests/" + name);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        writer.println(input);
        writer.close();
    }
}
