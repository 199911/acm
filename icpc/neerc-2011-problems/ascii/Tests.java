import java.awt.*;
import java.io.*;
import java.util.*;

public class Tests {
    static class Testcase {
        final int h, w;
        final char[][] a;

        Testcase(String[] ss) {
            h = ss.length + 1;
            w = ss[0].length() + 1;
            myAssert(h <= MAX_N && w <= MAX_N);
            a = new char[h][w];
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    a[i][j] = '.';

                    char c1 = (i > 0 && j > 0) ? ss[i - 1].charAt(j - 1) : '.';
                    char c2 = (i < h - 1 && j < w - 1) ? ss[i].charAt(j) : '.';
                    if (c1 != c2) a[i][j] = '/';
                    c1 = (i > 0 && j < w - 1) ? ss[i - 1].charAt(j) : '.';
                    c2 = (i < h - 1 && j > 0) ? ss[i].charAt(j - 1) : '.';
                    if (c1 != c2) a[i][j] = '\\';
                }
            }
        }

    }

    private static void myAssert(boolean b) {
        if (!b) throw new RuntimeException();
    }

    Random random = new Random(43543915431L);
    private static final int MAX_N = 100;

    public static void main(String[] args) throws IOException {
        new File("tests").mkdir();
        new Tests().run();
    }

    private void run() {
        outputTest(new Testcase(new String[]{
                "*.*",
                ".*.",
                "..*"
        }));
        outputTest(new Testcase(new String[]{
                "*"
        }));
        outputTest(new Testcase(new String[]{
                "*.",
                ".*"
        }));
        outputTest(new Testcase(new String[]{
                "*.*",
                ".*."
        }));
        outputTest(new Testcase(new String[]{
                ".*.",
                "*.*",
                ".*."
        }));
        outputTest(new Testcase(new String[]{
                "*.*",
                ".*.",
                "*.*"
        }));
        for (int i = 0; i < 5; i++) {
            outputTest(generateTree(5 + random.nextInt(5), 5 + random.nextInt(5)));
        }
        outputTest(generateSpiral(20, 20));

        for (int i = 0; i < 5; i++) {
            outputTest(generateTree(MAX_N - random.nextInt(5), MAX_N - random.nextInt(5)));
            outputTest(generateCircle(MAX_N - random.nextInt(5), MAX_N - random.nextInt(5)));
            outputTest(generateFull(MAX_N - random.nextInt(5), MAX_N - random.nextInt(5)));
        }
        outputTest(generateSpiral(MAX_N, MAX_N));
        outputTest(generateTree(MAX_N, MAX_N));
        outputTest(generateCircle(MAX_N, MAX_N));
        outputTest(generateFull(MAX_N, MAX_N));
    }

    private Testcase generateSpiral(int h, int w) {
        h = h - 1;
        w = w - 1;
        char[][] a = new char[h][w];
        for (char[] chars : a) {
            Arrays.fill(chars, '.');
        }
        int x = h / 2;
        int y = w / 2;
        a[x][y] = '*';
        int d = 0;
        int dx = 1;
        int dy = 1;
        while (x >= 0 && x < h && y >= 0 && y < w) {
            d++;
            for (int i = 0; i < d; i++) {
                x += dx;
                y += dy;
                if (x < 0 || x >= h || y < 0 || y >= w) break;
                a[x][y] = '*';
            }
            int ndx = dy;
            int ndy = -dx;
            dx = ndx;
            dy = ndy;
        }
        String[] ss = new String[h];
        for (int i = 0; i < h; i++) {
            ss[i] = String.valueOf(a[i]);
        }
        return new Testcase(ss);
    }

    private Testcase generateFull(int h, int w) {
        h = h - 1;
        w = w - 1;
        char[][] a = new char[h][w];
        for (char[] chars : a) {
            Arrays.fill(chars, '.');
        }
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if ((i + j) % 2 == 0) {
                    a[i][j] = '*';
                }
            }
        }
        String[] ss = new String[h];
        for (int i = 0; i < h; i++) {
            ss[i] = String.valueOf(a[i]);
        }
        return new Testcase(ss);
    }

    private Testcase generateTree(int h, int w) {
        h = h - 1;
        w = w - 1;
        char[][] a = new char[h][w];
        for (char[] chars : a) {
            Arrays.fill(chars, '.');
        }
        a[0][0] = '*';
        Set<Point> candidates = new HashSet<Point>();
        candidates.add(new Point(1, 1));
        while (true) {
            int ii = -1;
            int jj = -1;
            int k = 0;
            Set<Point> newCandidates = new HashSet<Point>();
            for (Point point : candidates) {
                int i = point.x;
                int j = point.y;
                if (a[i][j] == '.') {
                    char[] z = new char[8];
                    z[0] = bounds(a, i - 1, j - 1, '.');
                    z[1] = bounds(a, i - 2, j, '.');
                    z[2] = bounds(a, i - 1, j + 1, '.');
                    z[3] = bounds(a, i, j + 2, '.');
                    z[4] = bounds(a, i + 1, j + 1, '.');
                    z[5] = bounds(a, i + 2, j, '.');
                    z[6] = bounds(a, i + 1, j - 1, '.');
                    z[7] = bounds(a, i, j - 2, '.');

                    boolean ok = false;
                    for (int r = 0; r < 8; r += 2) {
                        if (z[r] == '*') {
                            ok = true;
                            for (int c = 2; c <= 6; c++) {
                                if (z[(r + c) % 8] == '*') {
                                    ok = false;
                                    break;
                                }
                            }
                            if (ok) break;
                        }
                    }

                    if (ok) {
                        newCandidates.add(point);
                        if (i > 0 && j > 0) newCandidates.add(new Point(i - 1, j - 1));
                        if (i > 0 && j < w - 1) newCandidates.add(new Point(i - 1, j + 1));
                        if (i < h - 1 && j > 0) newCandidates.add(new Point(i + 1, j - 1));
                        if (i < h - 1 && j < w - 1) newCandidates.add(new Point(i + 1, j + 1));
                        k++;
                        if (random.nextDouble() < 1.0 / k) {
                            ii = i;
                            jj = j;
                        }
                    }
                }
            }
            if (ii == -1) break;
            a[ii][jj] = '*';
            candidates = newCandidates;
        }
        String[] ss = new String[h];
        for (int i = 0; i < h; i++) {
            ss[i] = String.valueOf(a[i]);
        }
        return new Testcase(ss);
    }

    private Testcase generateCircle(int h, int w) {
        h = h - 1;
        w = w - 1;
        char[][] a = new char[h][w];
        for (char[] chars : a) {
            Arrays.fill(chars, '.');
        }
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                a[i][j] = '.';
                if ((i + j) % 2 == 0) {
                    double dx = (i + .5) / (h * .5) - 1;
                    double dy = (j + .5) / (w * .5) - 1;
                    if (Math.hypot(dx, dy) < 1) {
                        a[i][j] = '*';
                    }
                }
            }
        }
        String[] ss = new String[h];
        for (int i = 0; i < h; i++) {
            ss[i] = String.valueOf(a[i]);
        }
        return new Testcase(ss);
    }

    private char bounds(char[][] a, int i, int j, char c) {
        if (i < 0 || i >= a.length || j < 0 || j >= a[i].length) return c;
        else return a[i][j];
    }

    private int testNumber = 0;

    private void outputTest(Testcase testcase) {
        String name = "" + ++testNumber;
        while (name.length() < 2) name = "0" + name;
        PrintWriter writer;
        try {
            writer = new PrintWriter("tests/" + name);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        writer.println("" + testcase.h + " " + testcase.w);
        for (int i = 0; i < testcase.h; i++) {
            for (int j = 0; j < testcase.w; j++) {
                writer.print(testcase.a[i][j]);
            }
            writer.println();
        }
        writer.close();
        System.out.println("Test " + testNumber + " done");
    }
}
