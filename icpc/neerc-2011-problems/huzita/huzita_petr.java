import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class huzita_petr {
    public static void main(String[] args) throws IOException {
        new huzita_petr().run();
    }

    static class Point {
        final double x;
        final double y;

        Point(double x, double y) {
            this.x = x;
            this.y = y;
        }

        static Point read(String line) {
            String[] parts = line.split(" ", -1);
            if (parts.length != 2) throw new RuntimeException();
            return new Point(Double.parseDouble(parts[0]), Double.parseDouble(parts[1]));
        }
    }

    static class Line {
        final double a;
        final double b;
        final double c;

        Line(double a, double b, double c) {
            this.a = a;
            this.b = b;
            this.c = c;
        }

        static Line byPoints(Point p1, Point p2) {
            double a = p1.y - p2.y;
            double b = p2.x - p1.x;
            double z = Math.sqrt(a * a + b * b);
            a /= z;
            b /= z;
            return new Line(a, b, -a * p1.x - b * p1.y);
        }

        static Line read(String line) {
            String[] parts = line.split(" ", -1);
            if (parts.length != 4) throw new RuntimeException();
            return byPoints(new Point(Double.parseDouble(parts[0]), Double.parseDouble(parts[1])), new Point(Double.parseDouble(parts[2]), Double.parseDouble(parts[3])));
        }

        public String forOutput() {
            if (Math.abs(a) > Math.abs(b)) {
                Point[] points = getTwoPoints(a, b, c);
                return points[0].x + " " + points[0].y + " " + points[1].x + " " + points[1].y;
            } else {
                Point[] points = getTwoPoints(b, a, c);
                return points[0].y + " " + points[0].x + " " + points[1].y + " " + points[1].x;
            }
        }

        private static Point[] getTwoPoints(double a, double b, double c) {
            return new Point[]{
                    new Point(-c / a, 0),
                    new Point((-c - b) / a, 1)};
        }
    }

    static class Equation {
        double a2;
        double b2;
        double c2;
        double ab;
        double bc;
        double ac;
    }

    private Line solve(Line l1, Point p1, Line l2, Point p2) {
        if (l1.c != 0) {
            double dx = -l1.a * l1.c;
            double dy = -l1.b * l1.c;
            Line line = solve(
                    new Line(l1.a, l1.b, 0.0),
                    new Point(p1.x - dx, p1.y - dy),
                    new Line(l2.a, l2.b, l2.c + l2.a * dx + l2.b * dy),
                    new Point(p2.x - dx, p2.y - dy));
            if (line == null) return null;
            return new Line(line.a, line.b, line.c - line.a * dx - line.b * dy);
        }

        if (l1.a != 0 || l1.b != 1) {
            Line line = solve(
                    new Line(0.0, 1.0, 0.0),
                    new Point(l1.b * p1.x - l1.a * p1.y, l1.a * p1.x + l1.b * p1.y),
                    new Line(l1.b * l2.a - l1.a * l2.b, l1.a * l2.a + l1.b * l2.b, l2.c),
                    new Point(l1.b * p2.x - l1.a * p2.y, l1.a * p2.x + l1.b * p2.y));
            if (line == null) return null;
            return new Line(l1.b * line.a + l1.a * line.b, -l1.a * line.a + l1.b * line.b, line.c);
        }

        if (p1.x != 0) {
            double dx = p1.x;
            double dy = 0.0;
            Line line = solve(
                    new Line(0.0, 1.0, 0.0),
                    new Point(0.0, p1.y - dy),
                    new Line(l2.a, l2.b, l2.c + l2.a * dx + l2.b * dy),
                    new Point(p2.x - dx, p2.y - dy));
            if (line == null) return null;
            return new Line(line.a, line.b, line.c - line.a * dx - line.b * dy);
        }

        if (p1.y != 1) {
            double koef = 1.0 / p1.y;
            Line line = solve(
                    new Line(0.0, 1.0, 0.0),
                    new Point(0.0, 1.0),
                    new Line(l2.a, l2.b, l2.c * koef),
                    new Point(p2.x * koef, p2.y * koef));
            if (line == null) return null;
            return new Line(line.a, line.b, line.c / koef);
        }

        Equation eq = findEquation(l2, p2);

        double[] koef = new double[5];
        koef[2] += eq.a2;
        koef[0] += eq.b2;
        koef[1] += eq.ab;
        koef[3] += eq.ac / 2;
        koef[1] -= eq.ac / 2;
        koef[2] += eq.bc / 2;
        koef[0] -= eq.bc / 2;
        koef[4] += eq.c2 / 4;
        koef[2] -= eq.c2 / 2;
        koef[0] += eq.c2 / 4;
        List<Double> roots = solveEquation(koef);
        if (roots.isEmpty())
            return null;
        double u = roots.get(0);
        double a = u;
        double b = 1;
        double c = (u * u - 1) / 2;
        double z = Math.sqrt(a * a + b * b);
        a /= z;
        b /= z;
        c /= z;
        return new Line(a, b, c);
    }

    static final double EPS = 1e-9;

    private List<Double> solveEquation(double[] koef) {
        double z = 0;
        for (double x : koef)
            z += x * x;
        z = Math.sqrt(z);
        for (int i = 0; i < koef.length; ++i)
            koef[i] /= z;
        if (Math.abs(koef[koef.length - 1]) < EPS) {
            double[] nkoef = new double[koef.length - 1];
            System.arraycopy(koef, 0, nkoef, 0, koef.length - 1);
            return solveEquation(nkoef);
        }
        List<Double> res = new ArrayList<Double>();
        if (koef.length == 0) {
            throw new RuntimeException();
        }
        if (koef.length == 1) {
            return res;
        }
        if (koef.length == 2) {
            res.add(-koef[0] / koef[1]);
            return res;
        }
        if (koef.length == 3) {
            double d = (koef[1] * koef[1] - 4 * koef[0] * koef[2]);
            if (d < 0 && d > -EPS)
                d = 0;
            if (d < 0)
                return res;
            d = Math.sqrt(d);
            res.add((-koef[1] + d) / (2 * koef[2]));
            return res;
        }
        if (koef.length == 4) {
            if (koef[3] < 0) {
                for (int i = 0; i < koef.length; ++i) koef[i] = -koef[i];
            }
            double left = -1e10;
            double right = 1e10;
            for (int j = 0; j < 200; ++j) {
                double middle = (left + right) / 2;
                if (eval(koef, middle) < 0)
                    left = middle;
                else
                    right = middle;
            }
            res.add(left);
            return res;
        }
        throw new RuntimeException();
    }

/*    private List<Double> solveEquation(double[] koef) {
        double z = 0;
        for (double x : koef)
            z += x * x;
        z = Math.sqrt(z);
        for (int i = 0; i < koef.length; ++i)
            koef[i] /= z;
        if (Math.abs(koef[koef.length - 1]) < EPS) {
            double[] nkoef = new double[koef.length - 1];
            System.arraycopy(koef, 0, nkoef, 0, koef.length - 1);
            return solveEquation(nkoef);
        }
        List<Double> res = new ArrayList<Double>();
        if (koef.length == 0) {
            throw new RuntimeException();
        }
        if (koef.length == 1) {
            return res;
        }
        if (koef.length == 2) {
            res.add(-koef[0] / koef[1]);
            return res;
        }
        double[] deriv = new double[koef.length - 1];
        for (int i = 1; i < koef.length; ++i) {
            deriv[i - 1] = i * koef[i];
        }
        List<Double> derivRoots = solveEquation(deriv);
        double left = -1e10;
        if (!derivRoots.isEmpty()) {
            left = Math.min(left, derivRoots.get(0) * 2);
        }
        int needSignLeft = sign(koef[koef.length - 1]);
        if ((koef.length - 1) % 2 != 0)
            needSignLeft = -needSignLeft;
        while (sign(eval(koef, left)) != needSignLeft)
            left = left * 2;
        double right = 1e10;
        if (!derivRoots.isEmpty()) {
            right = Math.max(right, derivRoots.get(derivRoots.size() - 1) * 2);
        }
        int needSignRight = sign(koef[koef.length - 1]);
        while (sign(eval(koef, right)) != needSignRight)
            right = right * 2;
        derivRoots.add(right);
        derivRoots.add(0, left);
        for (int i = 0; i + 1 < derivRoots.size(); ++i) {
            left = derivRoots.get(i);
            right = derivRoots.get(i + 1);
            int leftSign = sign(eval(koef, left));
            int rightSign = sign(eval(koef, right));
            if (leftSign * rightSign > 0) continue;
            while (leftSign * rightSign != 0) {
                double middle = (left + right) / 2;
                int middleSign = sign(eval(koef, middle));
                if (middleSign * leftSign <= 0) {
                    right = middle;
                    rightSign = middleSign;
                } else {
                    left = middle;
                    leftSign = middleSign;
                }
            }
            if (leftSign == 0) {
                if (res.isEmpty() || res.get(res.size() - 1) < left - EPS)
                    res.add(left);
            }
            if (rightSign == 0) {
                if (res.isEmpty() || res.get(res.size() - 1) < right - EPS)
                    res.add(right);
            }
        }
        return res;
    }*/

    private int sign(double v) {
        if (Math.abs(v) < EPS)
            return 0;
        if (v > 0)
            return 1;
        return -1;
    }

    private double eval(double[] koef, double x) {
        double res = 0;
        for (int i = koef.length - 1; i >= 0; --i) {
            res = res * x + koef[i];
        }
        return res;
    }

    private Equation findEquation(Line l1, Point p1) {
        if (l1.c != 0) {
            double dx = -l1.a * l1.c;
            double dy = -l1.b * l1.c;
            Equation eq = findEquation(
                    new Line(l1.a, l1.b, 0.0),
                    new Point(p1.x - dx, p1.y - dy));
            Equation res = new Equation();
            res.a2 += eq.a2;
            res.b2 += eq.b2;
            res.ab += eq.ab;
            res.ac += eq.ac;
            res.a2 += eq.ac * dx;
            res.ab += eq.ac * dy;
            res.bc += eq.bc;
            res.ab += eq.bc * dx;
            res.b2 += eq.bc * dy;
            res.c2 += eq.c2;
            res.a2 += eq.c2 * dx * dx;
            res.b2 += eq.c2 * dy * dy;
            res.ab += eq.c2 * 2 * dx * dy;
            res.ac += eq.c2 * 2 * dx;
            res.bc += eq.c2 * 2 * dy;
            return res;
        }

        if (l1.a != 0.0 || l1.b != 1.0) {
            Equation eq = findEquation(
                    new Line(0.0, 1.0, 0.0),
                    new Point(l1.b * p1.x - l1.a * p1.y, l1.a * p1.x + l1.b * p1.y));
            Equation res = new Equation();
            double b = l1.b;
            double a = l1.a;
            res.a2 += eq.a2 * b * b;
            res.ab -= eq.a2 * 2 * a * b;
            res.b2 += eq.a2 * a * a;
            res.b2 += eq.b2 * b * b;
            res.ab += eq.b2 * 2 * a * b;
            res.a2 += eq.b2 * a * a;
            res.a2 += eq.ab * a * b;
            res.ab += eq.ab * (b * b - a * a);
            res.b2 -= eq.ab * a * b;
            res.c2 += eq.c2;
            res.ac += eq.ac * b;
            res.bc -= eq.ac * a;
            res.ac += eq.bc * a;
            res.bc += eq.bc * b;
            return res;
        }

        if (p1.x != 0) {
            double dx = p1.x;
            double dy = 0.0;
            Equation eq = findEquation(
                    new Line(0.0, 1.0, 0.0),
                    new Point(0.0, p1.y - dy));
            Equation res = new Equation();
            res.a2 += eq.a2;
            res.b2 += eq.b2;
            res.ab += eq.ab;
            res.ac += eq.ac;
            res.a2 += eq.ac * dx;
            res.ab += eq.ac * dy;
            res.bc += eq.bc;
            res.ab += eq.bc * dx;
            res.b2 += eq.bc * dy;
            res.c2 += eq.c2;
            res.a2 += eq.c2 * dx * dx;
            res.b2 += eq.c2 * dy * dy;
            res.ab += eq.c2 * 2 * dx * dy;
            res.ac += eq.c2 * 2 * dx;
            res.bc += eq.c2 * 2 * dy;
            return res;
        }

        if (p1.y != 1) {
            double koef = 1.0 / p1.y;
            Equation eq = findEquation(
                    new Line(0.0, 1.0, 0.0),
                    new Point(0.0, 1.0));
            Equation res = new Equation();
            res.a2 += eq.a2;
            res.b2 += eq.b2;
            res.ab += eq.ab;
            res.ac += koef * eq.ac;
            res.bc += koef * eq.bc;
            res.c2 += koef * koef * eq.c2;
            return res;
        }

        Equation res = new Equation();
        res.a2 = 1;
        res.b2 = -1;
        res.bc = -2;
        return res;
    }

    private void run() throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader("huzita.in"));
        int numTests = Integer.parseInt(reader.readLine());
        PrintWriter writer = new PrintWriter("huzita.out");
        for (int testId = 0; testId < numTests; ++testId) {
            Line l1 = Line.read(reader.readLine());
            Point p1 = Point.read(reader.readLine());
            Line l2 = Line.read(reader.readLine());
            Point p2 = Point.read(reader.readLine());
            Line res = solve(l1, p1, l2, p2);
            if (res == null)
                writer.println("0 0 0 0");
            else
                writer.println(res.forOutput());
        }
        writer.close();
    }
}
