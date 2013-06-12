import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import java.util.*;

/**
    Checker for NEERC'2011 Problem H: Huzita (in Doubles). It is not recommended to use on real contest because of
    1. Precision losses
    2. Fails in case of "infinite" solution
    (C) Andrey Lopatin
*/
public class CheckDouble implements Checker {
    private static final double MIN_DIST = 1e-4;
    private static final double MAX_ABS = 1e9;

    double je = 0, ce = 0;

    double vectd (double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
	int tn = inf.nextInt();
	for (int tc = 0; tc < tn; tc++) {
	    int x1 = inf.nextInt ();
	    int y1 = inf.nextInt ();
	    int dx1 = inf.nextInt () - x1;
	    int dy1 = inf.nextInt () - y1;
	    double LA1 = dy1, LB1 = -dx1, LC1 = LA1 * x1 + LB1 * y1, LD1 = Math.sqrt (LA1 * LA1 + LB1 * LB1);
	    LA1 /= LD1;
	    LB1 /= LD1;
	    LC1 /= LD1;
	    int px1 = inf.nextInt ();
	    int py1 = inf.nextInt ();
	    int x2 = inf.nextInt ();
	    int y2 = inf.nextInt ();
	    int dx2 = inf.nextInt () - x2;
	    int dy2 = inf.nextInt () - y2;
	    double LA2 = dy2, LB2 = -dx2, LC2 = LA2 * x2 + LB2 * y2, LD2 = Math.sqrt (LA2 * LA2 + LB2 * LB2);
	    LA2 /= LD2;
	    LB2 /= LD2;
	    LC2 /= LD2;
	    int px2 = inf.nextInt ();
	    int py2 = inf.nextInt ();

	    double F1, F2, qqx, qqy, cq;

	    double cx1 = ouf.nextDouble ();
	    double cy1 = ouf.nextDouble ();
	    double cx2 = ouf.nextDouble ();
	    double cy2 = ouf.nextDouble ();
	    boolean csol = false;
	    if (cx1 != 0 || cy1 != 0 || cx2 != 0 || cy2 != 0) {
		if (Math.abs (cx2 - cx1) < MIN_DIST && Math.abs (cy2 - cy1) < MIN_DIST) 
			throw new Outcome(Outcome.Type.WA, "contestant has degenerate line");
                if (Math.abs (cx1) > MAX_ABS || Math.abs (cy1) > MAX_ABS || Math.abs (cx2) > MAX_ABS || Math.abs(cy2) > MAX_ABS)
			throw new Outcome(Outcome.Type.WA, "contestant coordinates are too large");
		//System.out.println (Math.abs (cx2 - cx1));
		//System.out.println (Math.abs (cy2 - cy1));
		double CA = cy2 - cy1, CB = cx1 - cx2, CC = CA * cx1 + CB * cy1, CD = Math.sqrt (CA * CA + CB * CB);
		CA /= CD;
		CB /= CD;
		CC /= CD;
		F1 = CA * px1 + CB * py1;
		qqx = px1 - CA * 2 * (F1 - CC);
		qqy = py1 - CB * 2 * (F1 - CC);
		//cq = vectd (qqx - x1, qqy - y1, dx1, dy1);
		cq = Math.abs (LA1 * qqx + LB1 * qqy - LC1);
		if (Math.abs (cq) > 1e-4) throw new Outcome(Outcome.Type.WA, "contestant's answer does not fit line 1 in case " + (tc + 1) + ", error = " + cq);
		ce = Math.max (ce, cq);
		F2 = CA * px2 + CB * py2;
		qqx = px2 - CA * 2 * (F2 - CC);
		qqy = py2 - CB * 2 * (F2 - CC);
		//cq = vectd (qqx - x2, qqy - y2, dx2, dy2);
		cq = Math.abs (LA2 * qqx + LB2 * qqy - LC2);
		if (Math.abs (cq) > 1e-4) throw new Outcome(Outcome.Type.WA, "contestant's answer does not fit line 2 in case " + (tc + 1) + ", error = " + cq); 
		ce = Math.max (ce, cq);
		csol = true;
	    }


	    double jx1 = ans.nextDouble ();
	    double jy1 = ans.nextDouble ();
	    double jx2 = ans.nextDouble ();
	    double jy2 = ans.nextDouble ();
	    boolean jsol = false;
	    if (jx1 != 0 || jy1 != 0 || jx2 != 0 || jy2 != 0) {
		if (Math.abs (jx2 - jx1) < MIN_DIST && Math.abs (jy2 - jy1) < MIN_DIST) 
			throw new Outcome(Outcome.Type.FAIL, "jury has degenerate line");
                if (Math.abs (jx1) > MAX_ABS || Math.abs (jy1) > MAX_ABS || Math.abs (jx2) > MAX_ABS || Math.abs(jy2) > MAX_ABS)
			throw new Outcome(Outcome.Type.FAIL, "jury coordinates are too large");
		double JA = jy2 - jy1, JB = jx1 - jx2, JC = JA * jx1 + JB * jy1, JD = Math.sqrt (JA * JA + JB * JB);
		JA /= JD;
		JB /= JD;
		JC /= JD;
		F1 = JA * px1 + JB * py1;
		qqx = px1 - JA * 2 * (F1 - JC);
		qqy = py1 - JB * 2 * (F1 - JC);
		//cq = vectd (qqx - x1, qqy - y1, dx1, dy1);
		cq = Math.abs (LA1 * qqx + LB1 * qqy - LC1);
		if (Math.abs (cq) > 1e-4) throw new Outcome(Outcome.Type.FAIL, "jury answer does not fit line 1 in case " + (tc + 1) + ", error = " + cq);
		je = Math.max (je, cq);
		F2 = JA * px2 + JB * py2;
		qqx = px2 - JA * 2 * (F2 - JC);
		qqy = py2 - JB * 2 * (F2 - JC);
		//cq = vectd (qqx - x2, qqy - y2, dx2, dy2);
		cq = Math.abs (LA2 * qqx + LB2 * qqy - LC2);
		if (Math.abs (cq) > 1e-4) throw new Outcome(Outcome.Type.FAIL, "jury answer does not fit line 2 in case " + (tc + 1) + ", error = " + cq); 
		je = Math.max (je, cq);
		jsol = true;
	    }
	    if (jsol && !csol) throw new Outcome(Outcome.Type.WA, "Contestant has not found solution in case " + (tc + 1));
	    if (csol && !jsol) throw new Outcome(Outcome.Type.FAIL, "Jury has not found solution in case " + (tc + 1));
	}

	return new Outcome(Outcome.Type.OK, tn + " cases, jury max error = " + je + ", contesant max error = " + ce);
    }
}

