import java.util.*;
import java.io.*;

public class huzita_al {
    static final int MaxT = (int)2e4;
    static final int MaxC = 10;
    static double err = 0;

    public static int rangeInt (String s, int a, int b) {
	int x = Integer.parseInt(s);
	if (x < a || x > b) throw new RuntimeException (x + " is not in " + a + ".." + b);
	return x;
    }

    public static int vect (int x1, int y1, int x2, int y2) {
	return x1 * y2 - x2 * y1;
    }

    public static double vectd (double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
    }

    public static void main (String args[]) throws Exception {
	BufferedReader in = new BufferedReader (new FileReader ("huzita.in"));
	PrintWriter out = new PrintWriter ("huzita.out");
	int tn = rangeInt (in.readLine (), 1, MaxT);
	for (int tc = 0; tc < tn; tc++) {
	    StringTokenizer t = new StringTokenizer (in.readLine ());
	    int x1 = rangeInt (t.nextToken (), -MaxC, MaxC);
	    int y1 = rangeInt (t.nextToken (), -MaxC, MaxC);
	    int dx1 = rangeInt (t.nextToken (), -MaxC, MaxC) - x1;
	    int dy1 = rangeInt (t.nextToken (), -MaxC, MaxC) - y1;
	    if (dx1 == 0 && dy1 == 0) throw new RuntimeException ("Line 1 is not allowed to be a point");
	    if (t.hasMoreTokens ()) throw new RuntimeException ("EOL expected");
	    t = new StringTokenizer (in.readLine ());
	    int px1 = rangeInt (t.nextToken (), -MaxC, MaxC);
	    int py1 = rangeInt (t.nextToken (), -MaxC, MaxC);
	    if (vect (px1 - x1, py1 - y1, dx1, dy1) == 0) throw new RuntimeException ("point 1 lies on line 1");
	    if (t.hasMoreTokens ()) throw new RuntimeException ("EOL expected");
	    t = new StringTokenizer (in.readLine ());
	    int x2 = rangeInt (t.nextToken (), -MaxC, MaxC);
	    int y2 = rangeInt (t.nextToken (), -MaxC, MaxC);
	    int dx2 = rangeInt (t.nextToken (), -MaxC, MaxC) - x2;
	    int dy2 = rangeInt (t.nextToken (), -MaxC, MaxC) - y2;
	    if (dx2 == 0 && dy2 == 0) throw new RuntimeException ("Line 2 is not allowed to be a point");
	    if (t.hasMoreTokens ()) throw new RuntimeException ("EOL expected");
	    t = new StringTokenizer (in.readLine ());
	    int px2 = rangeInt (t.nextToken (), -MaxC, MaxC);
	    int py2 = rangeInt (t.nextToken (), -MaxC, MaxC);
	    if (vect (px2 - x2, py2 - y2, dx2, dy2) == 0) throw new RuntimeException ("point 2 lies on line 2");
	    if (t.hasMoreTokens ()) throw new RuntimeException ("EOL expected");

	    if (vect (dx1, dy1, dx2, dy2) == 0 && vect (x2 - x1, y2 - y1, dx1, dy1) == 0) throw new RuntimeException ("lines are the same");

	    int a1 = px1 - x1;
	    int b1 = py1 - y1;
	    int a2 = px2 - x2;
	    int b2 = py2 - y2;
	    int c1 = px1 + x1 - px2 - x2; // up to MaxC * 4
	    int c2 = py1 + y1 - py2 - y2;
	    int A1 = -(dx1 * dy2 - dx2 * dy1); // up to MaxC^2 * 8
	    int B1 = -(a2 * dy1 - b2 * dx1);
	    int C1 = b1 * dx2 - a1 * dy2;
	    int D1 = a1 * b2 - a2 * b1;
	    if ((long)A1 * D1 == (long)B1 * C1) throw new RuntimeException ("Something went wrong (should be asserted in the input)");
	    int A2 = dx2 * dx2 + dy2 * dy2;
	    int B2 = -(dx1 * dx2 + dy1 * dy2);
	    int D2 = -(dx2 * (c1 + a2) + dy2 * (c2 + b2));
	    int E2 = dx1 * a2 + dy1 * b2;
	    int F2 = c1 * a2 + c2 * b2;

	    double A = (double)A1 * A2; // exact values
	    double B = (double)B1 * A2 + (double)C1 * B2 + (double)A1 * D2;
	    double C = (double)D1 * B2 + (double)B1 * D2 + (double)C1 * E2 + (double)A1 * F2;
	    double D = (double)D1 * E2 + (double)B1 * F2;
	    double t2 = -1e100;
	    if (A == 0) {
		if (dx1 * dy2 != dx2 * dy1) throw new RuntimeException ("Something went wrong in the formulae");
		if (B == 0) {
		    if (C == 0) {
			if (D == 0) throw new RuntimeException ("Something's definitely wrong - any solution fits"); else {
			    //System.out.println ("WARNING: Completely degenerate case");
			    out.println ("0 0 0 0");
			    continue;
			}
		    } else {
			t2 = - D / C;
			//System.out.println ("WARNING: LINEAR CASE");
		    }
		} else {
		    double G = C * C;
		    double H = 4 * B * D;
		    if (Math.abs (G - H) < 1e-14 * G) {
			t2 = - C / (2 * B);
			//System.out.println ("WARNING: QUADRATIC CASE, D = 0");
		    } else if (G < H) {
			out.println ("0 0 0 0");
			//System.out.println ("WARNING: QUADRATIC CASE, D < 0");
			continue;
		    } else {
			t2 = (- C + Math.sqrt (G - H)) / (2 * B);
			//System.out.println ("WARNING: QUADRATIC CASE, D > 0");
		    }
		}
	    } else {
		double QT = 2 * B * B * B - 9 * A * B * C + 27 * A * A * D;
		double QU = B * B - 3 * A * C;
		double Q2 = QT * QT - 4 * QU * QU * QU;
		if (Q2 < 0) {
		    double C2r = (2 * B * B * B - 9 * A * B * C + 27 * A * A * D) * 0.5;
		    double C2i = Math.sqrt (-Q2) * 0.5;
		    double C2m = Math.sqrt (C2r * C2r + C2i * C2i);
		    double C2a = Math.atan2 (C2i, C2r);
		    double Cm = Math.pow (C2m, 1.0 / 3);
		    double Ca = C2a / 3;
		    double CRe = Cm * Math.cos (Ca);
		    t2 = -(CRe * 2 + B) / (3 * A);
		    //System.out.println ("Complex case");
		} else {
		    double Q = Math.sqrt (Q2);
		    double C2 = 2 * B * B * B - 9 * A * B * C + 27 * A * A * D;
		    double CC1 = (C2 + Q) * 0.5;
		    double CV1 = (CC1 > 0) ? Math.pow (CC1, 1.0 / 3) : (CC1 < 0) ? -Math.pow (-CC1, 1.0 / 3) : 0;
		    double CC2 = (C2 - Q) * 0.5;
		    double CV2 = (CC2 > 0) ? Math.pow (CC2, 1.0 / 3) : (CC2 < 0) ? -Math.pow (-CC2, 1.0 / 3) : 0;
		    if (Math.abs (CV1) == 0 && Math.abs (CV2) == 0) {
			t2 = - (B + CV1 + CV2) / (3 * A);
		    } else
		    if (Math.abs (CC1) > Math.abs (CC2)) {
			t2 = - (B * CV1 + CV1 * CV1 + (B * B - 3 * A * C)) / (3 * A * CV1);
		    } else {
			t2 = - (B * CV2 + CV2 * CV2 + (B * B - 3 * A * C)) / (3 * A * CV2);
		    }
		    //System.out.println ("Real case " + Q + " " + C2 + " " + CC1 + " " + CV1 + " " + CC2 + " " + CV2);
		    //System.out.println (QT + " " + QU + " " + Q2 + " " + B + " " + CV1 + " " + CV2 + " " + t2);
		}
	    }
	    double cq = A * t2 * t2 * t2 + B * t2 * t2 + C * t2 + D;
	    if (Math.abs(cq) > 1e-4) throw new RuntimeException ("Cubic equation not solved: error = " + cq + " ( " + A + ", " + B + ", " + C + ", " + D + ")");
	    err = Math.max (cq, err);
	    double lx = x2 + t2 * dx2, ly = y2 + t2 * dy2;
	    double nx = (px2 + lx) * 0.5, ny = (py2 + ly) * 0.5;
	    double ndx = py2 - ly, ndy = lx - px2;
	    out.println (nx + " " + ny + " " + (nx + ndx) + " " + (ny + ndy));
	    double A3 = -ndy, B3 = ndx, C3 = A3 * nx + B3 * ny, D3 = Math.sqrt (A3 * A3 + B3 * B3);
	    A3 /= D3; 
	    B3 /= D3; 
	    C3 /= D3;
	    double F = A3 * px2 + B3 * py2;
	    double qqx = px2 - A3 * 2 * (F - C3), qqy = py2 - B3 * 2 * (F - C3);
	    cq = vectd (qqx - x2, qqy - y2, dx2, dy2);
	    err = Math.max (cq, err);
	    if (Math.abs(cq) > 1e-4) throw new RuntimeException ("Error in value for point 2 = " + cq);
	    double G = A3 * px1 + B3 * py1;
	    double ssx = px1 - A3 * 2 * (G - C3), ssy = py1 - B3 * 2 * (G - C3);
	    cq = vectd (ssx - x1, ssy - y1, dx1, dy1);
	    err = Math.max (cq, err);
	    if (Math.abs(cq) > 1e-4) throw new RuntimeException ("Error in value for point 1 = " + cq);
	    double t1 = (C1 * t2 + D1) / (A1 * t2 + B1);
	    cq = A2 * t2 * t2 + B2 * t1 * t2 + D2 * t2 + E2 * t1 + F2;
	    err = Math.max (cq, err);
	    if (Math.abs(cq) > 1e-4) throw new RuntimeException ("Error in value for equation 2 = " + cq);
	    cq = -A1 * t1 * t2 - B1 * t1 + C1 * t2 + D1;
	    err = Math.max (cq, err);
	    if (Math.abs(cq) > 1e-4) throw new RuntimeException ("Error in value for equation 1 = " + cq);
	    cq = vectd (px1 - x1 - t1 * dx1, py1 - y1 - t1 * dy1, px2 - x2 - t2 * dx2, py2 - y2 - t2 * dy2);
	    err = Math.max (cq, err);
	    if (Math.abs(cq) > 1e-4) throw new RuntimeException ("Error in checking t1 and t2 in other way = " + cq);
	    if (Double.isNaN (err)) throw new RuntimeException ("Something's wrong. Stop. " + t2 + " " + A + " " + B + " " + C + " " + D);
	}
	if (in.ready ()) throw new RuntimeException ("EOF expected");
	out.close ();
	System.out.println ("Max precision error: " + err);
    }
    
}