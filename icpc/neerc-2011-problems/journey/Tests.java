import java.io.*;
import java.util.*;

public class Tests {
    private static int TEST_COUNTER = 0;
    private static final File TESTS_DIR = new File("tests");
    private static final File TESTS_LST = new File(TESTS_DIR, "tests.lst");
    private static final Random RND = new Random(2378135);

    private static final int MAX_COMMANDS_PER_FUNCTION = 100;
    private static final int MAX_FUNCTIONS = 100;
    
    private final PrintWriter out;
    
    private static class Function {
        private final String[] commands;
        
        public Function(String[] commands) {
            this.commands = commands;
        }
    }
    
    private List<Function> functions;

    private Tests(String description) throws IOException {
        String tn = String.format("%02d", ++TEST_COUNTER);
        File tests = new File("tests");
        tests.mkdir();
        PrintWriter lst = new PrintWriter(new FileWriter(TESTS_LST, true));
        lst.println(tn + " " + description);
        lst.close();
        out = new PrintWriter(new FileWriter(new File(tests, tn)));
        functions = new ArrayList<Function>();
    }
    
    private Tests addFunction(String[] commands) {
        functions.add(new Function(commands));
        return this;
    }
    
    private Tests addFunction(String commands) {
        return addFunction(commands.split(" "));
    }
    
    private void shuffleFunctions() {
        int n = functions.size();
        int[] p = new int[n];
        for (int i = 1; i < n; i++) {
            int t = 1 + RND.nextInt(i);
            p[i] = p[t];
            p[t] = i;
        }
        Function[] newFunctions = new Function[n];
        for (int i = 0; i < n; i++) {
            newFunctions[p[i]] = functions.get(i);
        }
        for (int i = 0; i < n; i++) {
            String[] commands = newFunctions[i].commands; 
            for (int j = 0; j < commands.length; j++) {
                if (commands[j].charAt(0) == 'F') {
                    int num = Integer.parseInt(commands[j].substring(1));
                    commands[j] = "F" + (1 + p[num - 1]);
                }
            }
        }
        functions = Arrays.asList(newFunctions);
    }
    
    private void write() {
        out.println(functions.size());
        for (Function f: functions) {
            String[] commands = f.commands;
            out.print(commands.length);
            for (int i = 0; i < commands.length; i++) {
                out.print(" " + commands[i].toUpperCase());
            }
            out.println();
        }
        out.close();
    }
    
    private static void writeSampleTests() throws IOException {
        new Tests("First sample from the problem statement.").
            addFunction("GO F2 GO F2 GO F2").
            addFunction("F3 F3 F3 F3").
            addFunction("GO LEFT").
            write();
    
        new Tests("Second sample from the problem statement.").addFunction("GO F1").write();
    
        new Tests("Third sample from the problem statement.").
            addFunction("GO F2").
            addFunction("LEFT GO GO GO F3 LEFT F4").
            addFunction("GO F4 RIGHT F2 RIGHT").
            addFunction("GO GO LEFT LEFT GO LEFT GO").
            write();
    }
    
    private static void writeSmallTests() throws IOException {
        new Tests("A small test, three finite functions.").
            addFunction("F3 LEFT F2 GO F3 RIGHT GO").
            addFunction("F3 F3").
            addFunction("GO RIGHT GO").
            write();

        new Tests("A small infinite test, finite answer.").
            addFunction("GO RIGHT F2 F2 F1").
            addFunction("GO GO").
            write();

        new Tests("A small infinite test, infinite answer.").
            addFunction("GO GO RIGHT GO GO RIGHT GO RIGHT GO RIGHT F1").
            write();

        new Tests("One infinite empty function.").
            addFunction("F1").
            write();

        new Tests("One infinite function, no movement.").
            addFunction("LEFT F1").
            write();

        new Tests("Move a bit and then infinite empty loop, finite answer.").
            addFunction("GO GO LEFT GO GO GO GO GO F2 GO GO GO GO").
            addFunction("F2 F2 F2").
            write();

        new Tests("Unused functions.").
            addFunction("LEFT LEFT GO").
            addFunction("RIGHT GO GO LEFT LEFT GO GO GO GO GO").
            addFunction("GO GO LEFT GO GO RIGHT GO").
            addFunction("F5").
            addFunction("F4").
            write();

        new Tests("Move a bit and then loop, finite answer.").
            addFunction("LEFT LEFT GO F2").
            addFunction("GO F3").
            addFunction("RIGHT F2").
            write();

        new Tests("A small test, four functions, finite answer.").
            addFunction("GO GO RIGHT GO LEFT GO F4 GO LEFT GO RIGHT GO LEFT GO LEFT GO GO GO LEFT F3").
            addFunction("GO GO GO GO GO").
            addFunction("F2 LEFT F2 GO GO").
            addFunction("RIGHT GO RIGHT GO LEFT GO GO").
            write();
    }

    private static void writeMaxTest() throws IOException {
        Tests test = new Tests("Test with the almost maximum answer.");
        for (int i = 0; i < MAX_FUNCTIONS - 1; i++) {
            String[] commands = new String[MAX_COMMANDS_PER_FUNCTION];
            for (int j = 0; j < commands.length; j++) {
                commands[j] = "F" + (i + 2);
            }
            test = test.addFunction(commands);
        }
        String[] commands = new String[MAX_COMMANDS_PER_FUNCTION];
        for (int j = 0; j < commands.length; j++) {
            commands[j] = "GO";
        }
        test = test.addFunction(commands);
        test.shuffleFunctions();
        test.write();
    }
    
    private static void writeMaxTest2() throws IOException {
        Tests test = new Tests("Test with the maximum answer.");
        for (int i = 0; i < MAX_FUNCTIONS - 1; i++) {
            String[] commands = new String[MAX_COMMANDS_PER_FUNCTION];
            for (int j = 0; j < commands.length; j++) {
                commands[j] = "F" + (i + 2);
            }
            if (i == 0) {
                commands[commands.length - 2] = "RIGHT";
                commands[commands.length - 1] = "F1";
            }
            test = test.addFunction(commands);
        }
        String[] commands = new String[MAX_COMMANDS_PER_FUNCTION];
        for (int j = 0; j < commands.length; j++) {
            commands[j] = "GO";
        }
        test = test.addFunction(commands);
        test.shuffleFunctions();
        test.write();
    }
    
    private static void writeBigPeriodTest() throws IOException {
        Tests test = new Tests("Test with a big period.");
        for (int i = 0; i < MAX_FUNCTIONS - 1; i++) {
            String[] commands = new String[MAX_COMMANDS_PER_FUNCTION];
            for (int j = 0; j < commands.length; j++) {
                commands[j] = "F" + (i + 2);
            }
            test = test.addFunction(commands);
        }
        String[] commands = new String[MAX_COMMANDS_PER_FUNCTION];
        for (int j = 0; j < commands.length - 2; j++) {
            commands[j] = "GO";
        }
        commands[commands.length - 2] = "LEFT";
        commands[commands.length - 1] = "F1";
        test = test.addFunction(commands);
        test.shuffleFunctions();
        test.write();
    }
    
    private static void writeMaxInfinityTest() throws IOException {
        Tests test = new Tests("Test with the maximum period.");
        for (int i = 0; i < MAX_FUNCTIONS - 1; i++) {
            String[] commands = new String[MAX_COMMANDS_PER_FUNCTION];
            for (int j = 0; j < commands.length; j++) {
                commands[j] = "F" + (i + 2);
            }
            test = test.addFunction(commands);
        }
        String[] commands = new String[MAX_COMMANDS_PER_FUNCTION];
        for (int j = 0; j < commands.length - 1; j++) {
            commands[j] = "GO";
        }
        commands[commands.length - 1] = "F1";
        test = test.addFunction(commands);
        test.shuffleFunctions();
        test.write();
    }
    
    private static void writeRandomFiniteTest(int functions) throws IOException {
        Tests test = new Tests("Random finite test, number of functions is " + functions + ".");
        
        for (int i = 0; i < functions; i++) {
            String[] commands = new String[MAX_COMMANDS_PER_FUNCTION];
            for (int j = 0; j < commands.length; j++) {
                int percent = RND.nextInt(100);
                if (percent < 10) {
                    commands[j] = "LEFT";
                } else if (percent < 20) {
                    commands[j] = "RIGHT";
                } else if (percent < 40) {
                    commands[j] = "GO";
                } else {
                    if (i == functions - 1) {
                        commands[j] = "GO";
                    } else {
                        int f = i + 1 + RND.nextInt(functions - i - 1);
                        commands[j] = "F" + (f + 1);
                    }
                }
            }
            test = test.addFunction(commands);
        }
        test.shuffleFunctions();
        test.write();
    }
    
    private static void writeRandomTest(int functions, int finiteFunctions, boolean isFirstFinite, int leftProb, int rightProb) throws IOException {
        Tests test = new Tests("Random test, number of functions is " + functions + " (" + finiteFunctions + " finite). The first function is " + (isFirstFinite ? "finite" : "infinite") + ".");
        
        int firstFinite, lastFinite;
        if (isFirstFinite) {
            firstFinite = 0;
            lastFinite = finiteFunctions - 1;
        } else {
            firstFinite = 1;
            lastFinite = finiteFunctions;
        }
        
        for (int i = 0; i < functions; i++) {
            String[] commands = new String[MAX_COMMANDS_PER_FUNCTION];
            for (int j = 0; j < commands.length; j++) {
                int percent = RND.nextInt(100);
                if (percent < leftProb) {
                    commands[j] = "LEFT";
                } else if (percent < leftProb + rightProb) {
                    commands[j] = "RIGHT";
                } else {
                    commands[j] = "GO";
                }
            }
            if (i < firstFinite || i > lastFinite) {
                for (int j = 0; j < commands.length; j++) {
                    if (RND.nextInt(100) >= 30) {
                        continue;
                    }
                    int f = RND.nextInt(functions);
                    commands[j] = "F" + (f + 1);
                }
                int f = RND.nextInt(functions - finiteFunctions);
                if (f >= firstFinite) {
                    f += lastFinite - firstFinite + 1;
                }
                commands[RND.nextInt(commands.length)] = "F" + (f + 1);
            } else {
                for (int j = 0; j < commands.length; j++) {
                    if (RND.nextInt(100) >= 30) {
                        continue;
                    }
                    if (i == lastFinite) {
                        continue;
                    }
                    int f = i + 1 + RND.nextInt(lastFinite - i);
                    commands[j] = "F" + (f + 1);
                }
            }
            
            test = test.addFunction(commands);
        }
        
        test.shuffleFunctions();
        test.write();
    }
    
    private static void writeBigTest() throws IOException {
        Tests test = new Tests("Test with a big answer.");
        for (int i = 0; i < MAX_FUNCTIONS; i++) {
            String[] commands = new String[Math.min(MAX_FUNCTIONS - i, MAX_COMMANDS_PER_FUNCTION)];
            for (int j = 0; j < commands.length - 1; j++) {
                commands[j] = "F" + (i + j + 2);
            }
            commands[commands.length - 1] = "GO";
            test = test.addFunction(commands);
        }
        test.shuffleFunctions();
        test.write();
    }
    
    public static void main(String[] args) throws IOException {
        TESTS_LST.delete();
        writeSampleTests();
        writeSmallTests();
        writeRandomFiniteTest(MAX_FUNCTIONS / 4);
        writeRandomFiniteTest(MAX_FUNCTIONS / 2);
        for (int i = 0; i < 4; i++) {
            writeRandomFiniteTest(MAX_FUNCTIONS);
        }
        
        RND.setSeed(2734583);
        writeRandomTest(MAX_FUNCTIONS, MAX_FUNCTIONS / 2, true, 10, 10);
        RND.setSeed(58629694);
        writeRandomTest(MAX_FUNCTIONS, MAX_FUNCTIONS / 2, false, 10, 10);
        RND.setSeed(84718543);
        writeRandomTest(MAX_FUNCTIONS, MAX_FUNCTIONS / 3, false, 10, 10);
        RND.setSeed(47204350);
        writeRandomTest(MAX_FUNCTIONS, MAX_FUNCTIONS - 10, true, 10, 10);
        
        RND.setSeed(352958934);
        for (int i = 0; i < 5; i++) {
            writeRandomTest(MAX_FUNCTIONS, MAX_FUNCTIONS - 2 * i, true, 1, 1);
        }
        
        RND.setSeed(123589);
        writeRandomTest(MAX_FUNCTIONS, 0, false, 30, 30);
        writeRandomTest(MAX_FUNCTIONS, MAX_FUNCTIONS, true, 30, 30);

        RND.setSeed(777285195);
        writeRandomTest(MAX_FUNCTIONS, 10, false, 40, 40);
        writeRandomTest(MAX_FUNCTIONS, MAX_FUNCTIONS, true, 30, 30);
        
        RND.setSeed(736174183);
        writeRandomTest(MAX_FUNCTIONS, MAX_FUNCTIONS - 5, true, 10, 20);
        
        writeBigTest();
        writeMaxTest();

        writeMaxInfinityTest();
        writeBigPeriodTest();
        writeMaxTest2();
    }
}
