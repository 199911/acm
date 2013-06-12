import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

public class gcd_petr {
    public static void main(String[] args) throws IOException {
        new gcd_petr().run();
    }

    static final int INF = 1000000;
    int n;
    int numPrimes;
    int[] primes;
    boolean[] used;
    int res;

    public int solve() {
        numPrimes = 0;
        boolean[] isPrime = new boolean[n + 1];
        for (int i = 0; i <= n; ++i) isPrime[i] = true;
        isPrime[0] = false;
        isPrime[1] = false;
        for (int i = 0; i <= n; ++i) if (isPrime[i]) {
            ++numPrimes;
            for (long j = (long) i * i; j <= n; j += i) {
                isPrime[(int) j] = false;
            }
        }
        primes = new int[numPrimes];
        numPrimes = 0;
        for (int i = 0; i <= n; ++i) if (isPrime[i]) primes[numPrimes++] = i;
        used = new boolean[numPrimes];
        res = INF;
        rec(numPrimes - 1, 0, 1, 0);
        return res;
    }

    private void rec(int last, int first, long curProd, int got) {
        while (last >= 0 && used[last]) --last;
        while (first <= last && used[first]) ++first;
        if (curProd == 1) {
            if (first > last) {
                if (got < res) {
                    res = got;
                }
                return;
            }
        } else {
            if (first > last || curProd * primes[first] > n) {
                rec(last, first, 1, got + 1);
                return;
            }
        }
        if (curProd == 1) {
            used[last] = true;
            rec(last, first, primes[last], got);
            used[last] = false;
        } else {
            for (int i = first; i <= last; ++i) if (!used[i]) {
                if (curProd * primes[i] <= n) {
                    used[i] = true;
                    rec(last, first, curProd * primes[i], got);
                    used[i] = false;
                } else {
                    break;
                }
            }
        }
    }

    private void run() throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader("gcd.in"));
        n = Integer.parseInt(reader.readLine());
        solve();
        PrintWriter writer = new PrintWriter("gcd.out");
        writer.println(res);
        writer.close();
    }
}
