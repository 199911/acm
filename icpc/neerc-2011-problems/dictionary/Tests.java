import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Arrays;

/**
 * Tests generator for NEERC'2011 Problem D: Dictionary Size
 * @author Alexander Klenin
 */
public class Tests {
    private static int TEST_COUNTER = 0;
    private static final File TESTS_DIR = new File("tests");
    private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");

    private static final Random RND = new Random(92832345);
    private static final int MAX_N = 10000;
    private static final int MAX_L = 40;

    private final PrintWriter out;

    private String[] dict;

    private Tests(String description) throws IOException {
        dict = new String[0];
        String tn = String.format("%02d", ++TEST_COUNTER);
        System.out.println(tn + " - " + description);
        PrintWriter lst = new PrintWriter(new FileWriter(TESTS_LST, true));
        lst.println(tn + " " + description);
        lst.close();
        out = new PrintWriter(new FileWriter(new File(TESTS_DIR, tn)));
    }

    private void write() {
        out.println(dict.length);
        for (String w: dict) out.println(w);
        out.close();
    }

    private Tests g(String... a) {
        dict = a;
        return this;
    }

    private void inc(char[] s) {
        for (int i = s.length - 1; i >= 0; --i)
            if (s[i] == 'z')
                s[i] = 'a';
            else {
                ++s[i];
                break;
            }
    }

    private Tests genInc(int n, int len) {
        char[] s = new char[len];
        Arrays.fill(s, 0, s.length, 'a');
        dict = new String[n];

        for (int i = 0; i < n; ++i, inc(s))
            dict[i] = new String(s);
        return this;
    }

    private String randomWord(int len, int alpha_size) {
        final String alpha = "abcdefghijklmnopqrstuvwxyz";
        char[] s = new char[len];
        for (int i = 0; i < len; ++i)
            s[i] = alpha.charAt(RND.nextInt(alpha_size));
        return new String(s);
    }

    private String randomRotate(String s) {
        int p = RND.nextInt(s.length());
        return s.substring(p) + s.substring(0, p);
    }

    private Tests genRandom(int n, int len, int alpha_size) {
        dict = new String[n];
        for (int i = 0; i < n; ++i)
            dict[i] = randomWord(len, alpha_size);
        return this;
    }

    private Tests genRandomLen(int n, int len) {
        dict = new String[n];
        for (int i = 0; i < n; ++i)
            dict[i] = randomWord(RND.nextInt(len) + 1, 26);
        return this;
    }

    private Tests genIncMax(int n) {
        char [][] a = {
            { 'a', 'a', 'a' }, { 'b', 'c', 'd' }, { 'e', 'a', 'a' }, { 'd', 'k', 'z' },
            { 'p', 'q', 'r' }, { 'a', 's', 'k' }, { 'x', 'y', 'z' }, 
            { 'z', 'a', 'a' }, { 'y', 'c', 'd' }, { 'w', 'a', 'a' }, { 'v', 'k', 'z' },
            { 'x', 'q', 'r' }, { 'u', 's', 'k' }, { 'x', 'y', 'z' } };
        int [] step = { 1, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 27, 41, 43 };
        dict = new String[n];
        for (int i = 0; i < n; ++i) {
            dict[i] = "";
            for (int j = 0; j < a.length; ++j) {
                for (int k = 0; k < step[j]; ++k) inc(a[j]);
                dict[i] += new String(a[j]);
            }
            if (dict[i].length() > MAX_L) 
                dict[i] = dict[i].substring(0, MAX_L);
        }
        return this;
    }

    private Tests shuffle() {
        for (int i = dict.length; i > 0; --i) {
            int j = RND.nextInt(i);
            String t = dict[i - 1];
            dict[i - 1] = dict[j];
            dict[j] = t;
        }
        return this;
    }
    
    private Tests rotate() {
        for (int i = 0; i < dict.length; ++i)
            dict[i] = randomRotate(dict[i]);
        return this;
    }

    public static void main(String[] args) throws IOException {
        TESTS_LST.delete();
        TESTS_DIR.mkdir();

        new Tests("Sample").g("abc", "def", "abef").write();
        new Tests("Minimal 1").g("a").write();
        new Tests("Minimal 2").g("a", "b").write();
        new Tests("Max len single line").g(new String(new char[MAX_L]).replace("\0", "z")).write();
        new Tests("Chars").genInc(26, 1).write();
        new Tests("Manual 1").g("ab", "ac", "bd", "cd").write();
        new Tests("Manual 2").g("a", "aa", "aaa", "b", "bb", "bbb").write();
        new Tests("Duplicates").g("ab", "ab", "ab").write();
        new Tests("Small inc").genInc(234, 8).shuffle().write();
        new Tests("Small random").genRandom(321, 9, 5).write();
        new Tests("Medium inc").genInc(1000, 10).shuffle().write();
        new Tests("Medium random 1").genRandom(1000, 10, 20).write();
        new Tests("Medium random 2").genRandom(1000, 12, 26).write();
        new Tests("Medium random length").genRandomLen(999, 11).write();
        new Tests("Medium max").genIncMax(1000).rotate().write();
        new Tests("Large inc").genInc(MAX_N, MAX_L).shuffle().write();
        new Tests("Large small alphabet 1").genRandom(MAX_N, MAX_L, 2).write();
        new Tests("Large small alphabet 2").genRandom(MAX_N, MAX_L, 4).write();
        new Tests("Large random").genRandom(MAX_N, MAX_L, 26).write();
        new Tests("Large random length").genRandomLen(MAX_N, MAX_L).write();
        new Tests("Large rotated").genInc(MAX_N, MAX_L).rotate().write();
        new Tests("Large max").genIncMax(MAX_N).rotate().write();
    }

}
