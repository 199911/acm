import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;

public class Analyze {
    public static void main(String[] args) {
        new Analyze().run();
    }

    static final int INF = 1000000;

    public int slowSolution(int n) {
        int[] best = new int[1 << n];
        Arrays.fill(best, INF);
        int[] mask = new int[n + 1];
        for (int set = 1; set < best.length; ++set) {
            if ((set & (set - 1)) == 0)
                best[set] = 0;
            else {
                for (int move = 1; move <= n; ++move) {
                    int nbest = 0;
                    Arrays.fill(mask, 0);
                    for (int i = 1; i <= n; ++i)
                        if ((set & (1 << (i - 1))) != 0) {
                            int g = gcd(i, move);
                            mask[g] |= 1 << (i - 1);
                        }
                    for (int i = 1; i <= n; ++i)
                        if (mask[i] != 0)
                            nbest = Math.max(nbest, 1 + best[mask[i]]);
                    best[set] = Math.min(best[set], nbest);
                }
            }
        }
        return best[best.length - 1];
    }

    private int gcd(int a, int b) {
        while (b > 0) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    int numPrimes;
    int[] primes;
    boolean[] used;
    boolean[] isPrime;
    int[] reqStart;
    int[] reqEnd;
    int[] req;
    int[] resReq;
    int[] resReqStart;
    int[] resReqEnd;
    int reqPtr;
    int res;
    int got;
    int n;
    int wrongMode;

    /**
     * @param wrongMode 0 means try all possible choices, 1 means always try the smallest possible number when
     *    multiplying an existing number, 2 means always try the largest possible number.
     */
    public int fastHeuristicSolution(int n, int wrongMode) {
        this.n = n;
        numPrimes = 0;
        for (int i = 0; i <= n; ++i) isPrime[i] = true;
        isPrime[0] = false;
        isPrime[1] = false;
        for (int i = 0; i <= n; ++i) if (isPrime[i]) {
            ++numPrimes;
            for (long j = (long) i * i; j <= n; j += i) {
                isPrime[(int) j] = false;
            }
        }
        numPrimes = 0;
        for (int i = 0; i <= n; ++i) if (isPrime[i]) primes[numPrimes++] = i;
        for (int i = 0; i < numPrimes; ++i) used[i] = false;
        res = INF;
        got = 0;
        this.wrongMode = wrongMode;
        numBranches = 0;
        rec(numPrimes - 1, 0, 1);
        return res;
    }

    private void rec(int last, int first, long curProd) {
        while (last >= 0 && used[last]) --last;
        while (first <= last && used[first]) ++first;
        if (curProd == 1) {
            if (first > last) {
                ++numBranches;
                if (got < res) {
                    res = got;
                    System.arraycopy(req, 0, resReq, 0, reqPtr);
                    System.arraycopy(reqStart, 0, resReqStart, 0, got);
                    System.arraycopy(reqEnd, 0, resReqEnd, 0, got);
                }
                return;
            }
            reqStart[got] = reqPtr;
        } else {
            if (first > last || curProd * primes[first] > n) {
                reqEnd[got] = reqPtr;
                ++got;
                rec(last, first, 1);
                --got;
                return;
            }
        }
        if (curProd == 1) {
            used[last] = true;
            req[reqPtr] = last;
            ++reqPtr;
            rec(last, first, primes[last]);
            --reqPtr;
            used[last] = false;
        } else {
            if (wrongMode == 2) {
                int maxi = -1;
                for (int i = first; i <= last; ++i) if (!used[i]) {
                    if (curProd * primes[i] <= n) {
                        maxi = i;
                    } else break;
                }
                {
                    int i = maxi;
                    used[i] = true;
                    req[reqPtr] = i;
                    ++reqPtr;
                    rec(last, first, curProd * primes[i]);
                    --reqPtr;
                    used[i] = false;
                }
            } else {
                for (int i = first; i <= last; ++i) if (!used[i]) {
                    if (curProd * primes[i] <= n) {
                        used[i] = true;
                        req[reqPtr] = i;
                        ++reqPtr;
                        rec(last, first, curProd * primes[i]);
                        --reqPtr;
                        used[i] = false;
                        if (wrongMode > 0) break;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    int[] answerFor;
    Integer[] perm;
    int numBranches;

    private void run() {
        PrintWriter writer;
        try {
            writer = new PrintWriter("tests.dat");
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        int maxn = 10000;
        answerFor = new int[maxn + 1];
        isPrime = new boolean[maxn + 1];
        primes = new int[maxn + 1];
        used = new boolean[maxn + 1];
        reqStart = new int[maxn + 1];
        reqEnd = new int[maxn + 1];
        req = new int[maxn + 1];
        resReqStart = new int[maxn + 1];
        resReqEnd = new int[maxn + 1];
        resReq = new int[maxn + 1];
        perm = new Integer[maxn + 1];
        Arrays.fill(answerFor, INF);
        final int SLOW_SOLUTION_LIMIT = 16;
        for (int i = 1; i <= maxn; ++i) {
            if (i % 10000 == 0) System.out.println("At " + i);
            int res = fastHeuristicSolution(i, 0);
            int curNumBranches = numBranches;
            int res1 = fastHeuristicSolution(i, 1);
            int res2 = fastHeuristicSolution(i, 2);
            int resSlow = -1;
            if (i <= SLOW_SOLUTION_LIMIT) {
                resSlow = slowSolution(i);
                if (res != resSlow) throw new RuntimeException();
            }
            if (res != res1 || res != res2) throw new RuntimeException();
            if (!provablyOptimal(res, resReq, resReqStart, resReqEnd, numPrimes, primes, i)) {
                if (resSlow == res) {
                    System.out.println(i + " proved by slow");
                } else {
                    throw new RuntimeException();
                }
            }
            answerFor[i] = res;
            writer.println(i + " " + res + " " + curNumBranches);
        }
        writer.close();
    }

    private boolean provablyOptimal(int cnt, final int[] req, int[] reqStart, final int[] reqEnd, int numPrimes, int[] primes, int n) {
        for (int i = 0; i < cnt; ++i)
            perm[i] = i;
        Arrays.sort(perm, 0, cnt, new Comparator<Integer>() {
            public int compare(Integer a, Integer b) {
                return req[reqEnd[a] - 1] - req[reqEnd[b] - 1];
            }
        });
        for (int i = 0; i < numPrimes; ++i)
            used[i] = false;
        int first = 0;
        for (int ii = 0; ii < cnt; ++ii) {
            int i = perm[ii];
            for (int j = reqStart[i]; j + 1 < reqEnd[i]; ++j) {
                if (req[j] < req[j + 1]) throw new RuntimeException();
            }
            int minGcd = primes[req[reqEnd[i] - 1]];
            if (answerFor[n / minGcd] > cnt - 1 - ii)
                return false;
            for (int j = reqStart[i]; j < reqEnd[i]; ++j) {
                if (used[req[j]]) throw new RuntimeException();
                used[req[j]] = true;
            }
            while (first < numPrimes && used[first]) ++first;
        }
        if (first != numPrimes) throw new RuntimeException();
        return true;
    }
}
