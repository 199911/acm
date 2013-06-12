import java.math.BigInteger;
import java.util.*;
import java.io.*;

public class journey_rs implements Runnable {
    private static final int[] DIR_DX = { 1, 0, -1, 0, 1 };
    private static final int[] DIR_DY = { 0, 1, 0, -1, 0 };

    private static final int[] R_DX = { 1, -1, -1, 1, 1 };
    private static final int[] R_DY = { 1, 1, -1, -1, 1 };
    
    private static final int COMMAND_GO = 0;
    private static final int COMMAND_LEFT = -1;
    private static final int COMMAND_RIGHT = -2;
    
    private static final int MAX_COMMANDS_PER_FUNCTION = 100;
    private static final int MAX_FUNCTIONS = 100;
      
    private static class Function {
        public final int[] commands;

        public boolean isFinite;
        public WalkSummary walkSummary;
        public int firstInfinite = -1;

        public Function(String line) {
            StringTokenizer st = new StringTokenizer(line);
            int n = Integer.parseInt(st.nextToken());
            if (n < 0 || n > MAX_COMMANDS_PER_FUNCTION) {
                throw new Error("Invalid commands number: " + n);
            }
            commands = new int[n];
            for (int i = 0; i < n; i++) {
                String cur = st.nextToken();
                if (cur.equals("GO")) {
                    commands[i] = COMMAND_GO;
                } else if (cur.equals("LEFT")) {
                    commands[i] = COMMAND_LEFT;
                } else if (cur.equals("RIGHT")) {
                    commands[i] = COMMAND_RIGHT;
                } else {
                    if (cur.charAt(0) != 'F') {
                        throw new Error("Unknown command: " + cur);
                    }
                    commands[i] = Integer.parseInt(cur.substring(1));
                    if (commands[i] <= 0) {
                        throw new Error("F" + i + " invokes F" + commands[i]);
                    }
                }
            }
        }
    }

    private static class WalkSummary {
        BigInteger[] maxDist;
        BigInteger dx;
        BigInteger dy;
        int dirChange;
        
        public WalkSummary() {
            maxDist = new BigInteger[4];
            Arrays.fill(maxDist, BigInteger.ZERO);
            dx = dy = BigInteger.ZERO;
            dirChange = 0;
        }
        
        public WalkSummary(WalkSummary walk) {
            maxDist = new BigInteger[4];
            for (int i = 0; i < 4; i++) {
                maxDist[i] = walk.maxDist[i];
            }
            dx = walk.dx;
            dy = walk.dy;
            dirChange = walk.dirChange;
        }

        public void append(WalkSummary walk) {
            for (int i = 0; i < 4; i++) {
                int dir = (i - dirChange + 4) % 4;
                BigInteger cur = add(add(walk.maxDist[dir], dx, R_DX[i]), dy, R_DY[i]);
                maxDist[i] = max(maxDist[i], cur);
            }
            dx = add(add(dx, walk.dx, DIR_DX[dirChange]), walk.dy, DIR_DX[dirChange + 1]);
            dy = add(add(dy, walk.dx, DIR_DY[dirChange]), walk.dy, DIR_DY[dirChange + 1]);
            dirChange = (dirChange + walk.dirChange) % 4;
        }
        
        public void append(int command) {
            switch (command) {
            case COMMAND_GO:
                dx = add(dx, BigInteger.ONE, DIR_DX[dirChange]);
                dy = add(dy, BigInteger.ONE, DIR_DY[dirChange]);
                for (int i = 0; i < 4; i++) {
                    BigInteger cur = add(add(BigInteger.ZERO, dx, R_DX[i]), dy, R_DY[i]);
                    maxDist[i] = max(maxDist[i], cur);
                }
                break;
            case COMMAND_LEFT:
                dirChange = (dirChange + 1) % 4;
                break;
            case COMMAND_RIGHT:
                dirChange = (dirChange + 3) % 4;
                break;
            default:
                throw new IllegalArgumentException("Unknown command: " + command);
            }
        }
        
        public BigInteger getMaxDistance() {
            BigInteger answer = maxDist[0];
            for (int i = 1; i < 4; i++) {
                answer = max(answer, maxDist[i]);
            }
            return answer;
        }
        
        private static BigInteger add(BigInteger value, BigInteger a, int coef) {
            if (coef == 0) {
                return value;
            } else if (coef == 1) {
                return value.add(a);
            } else if (coef == -1) {
                return value.subtract(a);
            } else {
                throw new Error("Not implemented");
            }
        }
        
        @Override
        public String toString() {
            String result = "";
            result += "dx        = " + dx + "\n";
            result += "dy        = " + dy + "\n";
            result += "dirChange = " + dirChange + "\n";
            result += "max of  x + y = " + maxDist[0] + "\n";
            result += "max of -x + y = " + maxDist[1] + "\n";
            result += "max of -x - y = " + maxDist[2] + "\n";
            result += "max of  x - y = " + maxDist[3] + "\n";
            return result;
        }
    }
    
    private String getAnswer(WalkSummary prePeriod, WalkSummary period) {
        if (period.dirChange == 0) {
            if (!period.dx.equals(BigInteger.ZERO) || !period.dy.equals(BigInteger.ZERO)) {
                return "Infinity";
            }
        }
        
        WalkSummary walk = new WalkSummary(prePeriod);
        BigInteger answer = walk.getMaxDistance();
        for (int i = 0; i < 4; i++) {
            walk.append(period);
            answer = max(answer, walk.getMaxDistance());
        }
        return answer.toString();
    }
    
    private static BigInteger max(BigInteger u, BigInteger v) {
        if (u.compareTo(v) > 0) {
            return u;
        } else {
            return v;
        }
    }
    
    private BufferedReader in;
    private PrintWriter out;
    private Function[] functions;

    private void solve() throws IOException {
        int n = Integer.parseInt(in.readLine());
        if (n < 0 || n > MAX_FUNCTIONS) {
            throw new Error("Invalid number of functions: " + n);
        }
        functions = new Function[n];
        for (int i = 0; i < n; i++) {
            functions[i] = new Function(in.readLine());
            for (int j = 0; j < functions[i].commands.length; j++) {
                if (functions[i].commands[j] > n) {
                    throw new Error("F" + i + " invokes F" + functions[i].commands[j]);
                }
            }
        }
        identifyInfiniteFunctions();
        if (functions[0].isFinite) {
            System.out.println(functions[0].walkSummary);
            out.println(functions[0].walkSummary.getMaxDistance());
            return;
        }
        calcAnswerForInfiniteCase();
    }

    @SuppressWarnings("unchecked")
    private void identifyInfiniteFunctions() {
        int n = functions.length;
        Set<Integer>[] uses = new Set[n];
        Set<Integer>[] used_by = new Set[n];
        for (int i = 0; i < n; i++) {
            uses[i] = new HashSet<Integer>();
            used_by[i] = new HashSet<Integer>();
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < functions[i].commands.length; j++) {
                int cmd = functions[i].commands[j] - 1;
                if (cmd < 0) {
                    continue;
                }
                uses[i].add(cmd);
                used_by[cmd].add(i);
            }
        }
        boolean[] isFinite = new boolean[n];
        while (true) {
            int newFinite = -1;
            for (int i = 0; i < n; i++) {
                if (!isFinite[i] && uses[i].size() == 0) {
                    newFinite = i;
                    break;
                }
            }
            if (newFinite == -1) {
                break;
            }
            isFinite[newFinite] = true;
            for (int u : used_by[newFinite]) {
                uses[u].remove(newFinite);
            }
            used_by[newFinite].clear();
        }
        for (int i = 0; i < n; i++) {
            functions[i].isFinite = isFinite[i];
            if (isFinite[i]) {
                System.out.println("Function #" + (i + 1) + " is finite.");
            }
        }
        for (int i = 0; i < n; i++) {
            if (functions[i].isFinite) {
                calcWalkSummaryForFiniteFunction(i);
                continue;
            }
            WalkSummary walkSummary = new WalkSummary();
            for (int j = 0; j < functions[i].commands.length; j++) {
                int cmd = functions[i].commands[j];
                if (cmd <= 0) {
                    walkSummary.append(cmd);
                } else if (functions[cmd - 1].isFinite) {
                    calcWalkSummaryForFiniteFunction(cmd - 1);
                    walkSummary.append(functions[cmd - 1].walkSummary);
                } else {
                    functions[i].firstInfinite = cmd - 1;
                    break;
                }
            }
            functions[i].walkSummary = walkSummary;
        }
    }
    
    private void calcWalkSummaryForFiniteFunction(int function) {
        if (!functions[function].isFinite) {
            throw new IllegalArgumentException("Function #" + function + " is not finite");
        }
        if (functions[function].walkSummary != null) {
            return;
        }
        WalkSummary walkSummary = new WalkSummary();
        for (int i = 0; i < functions[function].commands.length; i++) {
            int cmd = functions[function].commands[i];
            if (cmd <= 0) {
                walkSummary.append(cmd);
            } else {
                calcWalkSummaryForFiniteFunction(cmd - 1);
                walkSummary.append(functions[cmd - 1].walkSummary);
            }
        }
        functions[function].walkSummary = walkSummary;
    }

    private void calcAnswerForInfiniteCase() {
        boolean[] mark = new boolean[functions.length];
        int cur = 0;
        mark[cur] = true;
        while (true) {
            cur = functions[cur].firstInfinite;
            if (mark[cur]) {
                break;
            }
            mark[cur] = true;
        }

        int periodStartsAt = cur;
        WalkSummary prePeriod = new WalkSummary();
        cur = 0;
        while (true) {
            prePeriod.append(functions[cur].walkSummary);
            cur = functions[cur].firstInfinite;
            if (cur == periodStartsAt) {
                break;
            }
        }
        
        WalkSummary period = new WalkSummary();
        while (true) {
            period.append(functions[cur].walkSummary);
            cur = functions[cur].firstInfinite;
            if (cur == periodStartsAt) {
                break;
            }
        }
        System.out.println("F1 -> ... -> F" + (periodStartsAt + 1) + " -> ... -> F" + (periodStartsAt + 1));
        System.out.println(prePeriod);
        System.out.println(period);
        out.println(getAnswer(prePeriod, period));
    }

    public static void main(String[] args) {
        new Thread(new journey_rs()).start();
    }

    @Override
    public void run() {
        try {
            String problem_name = getClass().getName().split("_")[0];
            in = new BufferedReader(new FileReader(new File(problem_name + ".in")));
            out = new PrintWriter(new File(problem_name + ".out"));
            solve();
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
