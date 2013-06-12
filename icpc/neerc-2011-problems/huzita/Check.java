import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import java.util.*;
import java.math.*;

/**
    Checker for NEERC'2011 Problem H: Huzita.
    (C) Andrey Lopatin
*/
public class Check implements Checker {
    private static final double PRECISION = 1e-4;
    private static final double MAX_ABS = 1e9;
    private static final BigDecimal TWO = BigDecimal.valueOf (2);
    
    MathContext mc = MathContext.DECIMAL128;//new MathContext (30, RoundingMode.HALF_EVEN);

    BigDecimal je = BigDecimal.ZERO, ce = BigDecimal.ZERO;

    BigDecimal vectd (BigDecimal x1, BigDecimal y1, BigDecimal x2, BigDecimal y2) {
	return x1.multiply(y2).subtract(x2.multiply(y1));
    }
    
    BigDecimal mse = BigDecimal.ZERO;
    
    BigDecimal mySqrt (BigDecimal a) {
	/*
	BigDecimal l = BigDecimal.ZERO, r = a.add (TWO);
	for (int i = 0; i < 120; i++) {
	    BigDecimal x = l.add(r).multiply (BigDecimal.valueOf (0.5), mc);
	    if (x.multiply(x).compareTo(a) > 0) r = x; else l = x;
	}
	return l.add(r).multiply (BigDecimal.valueOf (0.5), mc);*/
	BigDecimal x = BigDecimal.valueOf (Math.sqrt (a.doubleValue ())), se = BigDecimal.ZERO;
	for (int j = 0; j < 10; j++) {
	    for (int i = 0; i < 3; i++) {
		x = x.add (a.divide (x, mc)).multiply (BigDecimal.valueOf (0.5), mc);
	    }
	    se = x.multiply (x).subtract (a).abs ();
	    if (se.abs ().compareTo (BigDecimal.valueOf (1e-20)) < 0) {
	      break;
	    }
	}
	mse = mse.max (se);
	    
	//System.out.println ("Error = " + se);
	//mse = mse.max ();
	return x;
	//return BigDecimal.valueOf (Math.sqrt (a.doubleValue ()));
    }
    
    
    boolean isZero (BigDecimal a) {
	return a.compareTo (BigDecimal.ZERO) == 0;
    }
    
    
    boolean isSmall (BigDecimal a) {
	return a.abs ().compareTo (BigDecimal.valueOf (PRECISION)) < 0;
    }
    
    
    boolean isLarge (BigDecimal a) {
	return a.abs ().compareTo (BigDecimal.valueOf (MAX_ABS)) > 0;
    }
    
    
    BigDecimal getC (BigDecimal A, BigDecimal B, BigDecimal x1, BigDecimal y1) {
	return A.multiply (x1).add(B.multiply (y1));
    }
    
    
    BigDecimal getD (BigDecimal A, BigDecimal B) {
	return mySqrt (A.multiply(A).add(B.multiply (B)));
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
	int tn = inf.nextInt();
	for (int tc = 0; tc < tn; tc++) {
	    //if ((tc & 63) == 63) System.out.println (tc);
	    int x1 = inf.nextInt ();
	    int y1 = inf.nextInt ();
	    int dx1 = inf.nextInt () - x1;
	    int dy1 = inf.nextInt () - y1;
	    BigDecimal LA1 = BigDecimal.valueOf (dy1), LB1 = BigDecimal.valueOf (-dx1);
	    BigDecimal LC1 = getC (LA1, LB1, BigDecimal.valueOf (x1), BigDecimal.valueOf(y1));
	    BigDecimal LD1 = getD (LA1, LB1);
	    LA1 = LA1.divide (LD1, mc);
	    LB1 = LB1.divide (LD1, mc);
	    LC1 = LC1.divide (LD1, mc);
	    //System.out.println (LA1 + " " + LB1 + " " + LC1);
	    BigDecimal px1 = BigDecimal.valueOf (inf.nextInt ());
	    BigDecimal py1 = BigDecimal.valueOf (inf.nextInt ());
	    int x2 = inf.nextInt ();
	    int y2 = inf.nextInt ();
	    int dx2 = inf.nextInt () - x2;
	    int dy2 = inf.nextInt () - y2;
	    BigDecimal LA2 = BigDecimal.valueOf (dy2), LB2 = BigDecimal.valueOf (-dx2);
	    BigDecimal LC2 = getC (LA2, LB2, BigDecimal.valueOf (x2), BigDecimal.valueOf(y2));
	    BigDecimal LD2 = getD (LA2, LB2);
	    LA2 = LA2.divide (LD2, mc);
	    LB2 = LB2.divide (LD2, mc);
	    LC2 = LC2.divide (LD2, mc);
	    BigDecimal px2 = BigDecimal.valueOf (inf.nextInt ());
	    BigDecimal py2 = BigDecimal.valueOf (inf.nextInt ());


	    BigDecimal cx1 = BigDecimal.valueOf (ouf.nextDouble ());
	    BigDecimal cy1 = BigDecimal.valueOf (ouf.nextDouble ());
	    BigDecimal cx2 = BigDecimal.valueOf (ouf.nextDouble ());
	    BigDecimal cy2 = BigDecimal.valueOf (ouf.nextDouble ());
	    boolean csol = false;
	    if (!isZero (cx1) || !isZero (cy1) || !isZero (cx2) || !isZero (cy2)) {
		BigDecimal F1, F2, qqx, qqy, cq;
		if (isSmall (cx2.subtract(cx1).abs ()) && isSmall (cy2.subtract (cy1).abs ()))
			throw new Outcome(Outcome.Type.WA, "contestant has degenerate line");
                if (isLarge (cx1) || isLarge (cy1) || isLarge (cx2) || isLarge (cy2))
			throw new Outcome(Outcome.Type.WA, "contestant coordinates are too large");

		BigDecimal CA = cy2.subtract (cy1), CB = cx1.subtract (cx2);
		BigDecimal CC = getC (CA, CB, cx1, cy1);
		BigDecimal CD = getD (CA, CB);
		CA = CA.divide (CD, mc);
		CB = CB.divide (CD, mc);
		CC = CC.divide (CD, mc);

		F1 = getC (CA, CB, px1, py1);
		qqx = px1.subtract(CA.multiply (TWO).multiply (F1.subtract (CC)));
		qqy = py1.subtract(CB.multiply (TWO).multiply (F1.subtract (CC)));
		cq = getC (LA1, LB1, qqx, qqy).subtract (LC1).abs();
		if (!isSmall (cq)) throw new Outcome(Outcome.Type.WA, "contestant's answer does not fit line 1 in case " + (tc + 1) + ", error = " + cq.doubleValue ());
		ce = ce.max (cq);

		F2 = getC (CA, CB, px2, py2);
		qqx = px2.subtract(CA.multiply (TWO).multiply (F2.subtract (CC)));
		qqy = py2.subtract(CB.multiply (TWO).multiply (F2.subtract (CC)));
		cq = getC (LA2, LB2, qqx, qqy).subtract (LC2).abs();
		if (!isSmall (cq)) throw new Outcome(Outcome.Type.WA, "contestant's answer does not fit line 2 in case " + (tc + 1) + ", error = " + cq.doubleValue ());
		ce = ce.max (cq);

		csol = true;
	    }


	    BigDecimal jx1 = BigDecimal.valueOf (ans.nextDouble ());
	    BigDecimal jy1 = BigDecimal.valueOf (ans.nextDouble ());
	    BigDecimal jx2 = BigDecimal.valueOf (ans.nextDouble ());
	    BigDecimal jy2 = BigDecimal.valueOf (ans.nextDouble ());
	    boolean jsol = false;
	    if (!isZero (jx1) || !isZero (jy1) || !isZero (jx2) || !isZero (jy2)) {
		/*BigDecimal F1, F2, qqx, qqy, jq;
		if (isSmall (jx2.subtract(jx1).abs ().add (jy2.subtract (jy1).abs ()))) 
			throw new Outcome(Outcome.Type.FAIL, "jury has degenerate line");
                if (isLarge (jx1) || isLarge (jy1) || isLarge (jx2) || isLarge (jy2))
			throw new Outcome(Outcome.Type.FAIL, "jury coordinates are too large");
		BigDecimal JA = jy2.subtract (jy1), JB = jx1.subtract (jx2);
		BigDecimal JC = getC (JA, JB, jx1, jy1);
		BigDecimal JD = getD (JA, JB);
		JA = JA.divide (JD, mc);
		JB = JB.divide (JD, mc);
		JC = JC.divide (JD, mc);
		F1 = getC (JA, JB, px1, py1);
		qqx = px1.subtract(JA.multiply (TWO).multiply (F1.subtract (JC)));
		qqy = py1.subtract(JB.multiply (TWO).multiply (F1.subtract (JC)));
		jq = getC (LA1, LB1, qqx, qqy).subtract (LC1).abs();
		if (!isSmall (jq)) throw new Outcome(Outcome.Type.FAIL, "jury answer does not fit line 1 in case " + (tc + 1) + ", error = " + jq.doubleValue ());
		je = je.max (jq);


		F2 = getC (JA, JB, px2, py2);
		qqx = px2.subtract(JA.multiply (TWO).multiply (F2.subtract (JC)));
		qqy = py2.subtract(JB.multiply (TWO).multiply (F2.subtract (JC)));
		jq = getC (LA2, LB2, qqx, qqy).subtract (LC2).abs();
		if (!isSmall (jq)) throw new Outcome(Outcome.Type.FAIL, "jury answer does not fit line 2 in case " + (tc + 1) + ", error = " + jq.doubleValue ());
		je = je.max (jq);*/

		jsol = true;
	    }


	    if (jsol && !csol) throw new Outcome(Outcome.Type.WA, "Contestant has not found solution in case " + (tc + 1));
	    if (csol && !jsol) throw new Outcome(Outcome.Type.WA, "There is no solution in case " + (tc + 1));
	}

	//System.out.println ("Max sqrt error = " + mse.doubleValue ());
	return new Outcome(Outcome.Type.OK, tn + " cases, contesant max error = " + ce.doubleValue ());
    }
}

 
import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import java.util.*;
import java.math.*;

/**
    Checker for NEERC'2011 Problem H: Huzita.
    (C) Andrey Lopatin
*/
public class Check implements Checker {
    private static final double PRECISION = 1e-4;
    private static final double MAX_ABS = 1e9;
    private static final BigDecimal TWO = BigDecimal.valueOf (2);
    
    MathContext mc = MathContext.DECIMAL128;//new MathContext (30, RoundingMode.HALF_EVEN);

    BigDecimal je = BigDecimal.ZERO, ce = BigDecimal.ZERO;

    BigDecimal vectd (BigDecimal x1, BigDecimal y1, BigDecimal x2, BigDecimal y2) {
	return x1.multiply(y2).subtract(x2.multiply(y1));
    }
    
    BigDecimal mse = BigDecimal.ZERO;
    
    BigDecimal mySqrt (BigDecimal a) {
	/*
	BigDecimal l = BigDecimal.ZERO, r = a.add (TWO);
	for (int i = 0; i < 120; i++) {
	    BigDecimal x = l.add(r).multiply (BigDecimal.valueOf (0.5), mc);
	    if (x.multiply(x).compareTo(a) > 0) r = x; else l = x;
	}
	return l.add(r).multiply (BigDecimal.valueOf (0.5), mc);*/
	BigDecimal x = BigDecimal.valueOf (Math.sqrt (a.doubleValue ())), se = BigDecimal.ZERO;
	for (int j = 0; j < 10; j++) {
	    for (int i = 0; i < 3; i++) {
		x = x.add (a.divide (x, mc)).multiply (BigDecimal.valueOf (0.5), mc);
	    }
	    se = x.multiply (x).subtract (a).abs ();
	    if (se.abs ().compareTo (BigDecimal.valueOf (1e-20)) < 0) {
	      break;
	    }
	}
	mse = mse.max (se);
	    
	//System.out.println ("Error = " + se);
	//mse = mse.max ();
	return x;
	//return BigDecimal.valueOf (Math.sqrt (a.doubleValue ()));
    }
    
    
    boolean isZero (BigDecimal a) {
	return a.compareTo (BigDecimal.ZERO) == 0;
    }
    
    
    boolean isSmall (BigDecimal a) {
	return a.abs ().compareTo (BigDecimal.valueOf (PRECISION)) < 0;
    }
    
    
    boolean isLarge (BigDecimal a) {
	return a.abs ().compareTo (BigDecimal.valueOf (MAX_ABS)) > 0;
    }
    
    
    BigDecimal getC (BigDecimal A, BigDecimal B, BigDecimal x1, BigDecimal y1) {
	return A.multiply (x1).add(B.multiply (y1));
    }
    
    
    BigDecimal getD (BigDecimal A, BigDecimal B) {
	return mySqrt (A.multiply(A).add(B.multiply (B)));
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
	int tn = inf.nextInt();
	for (int tc = 0; tc < tn; tc++) {
	    //if ((tc & 63) == 63) System.out.println (tc);
	    int x1 = inf.nextInt ();
	    int y1 = inf.nextInt ();
	    int dx1 = inf.nextInt () - x1;
	    int dy1 = inf.nextInt () - y1;
	    BigDecimal LA1 = BigDecimal.valueOf (dy1), LB1 = BigDecimal.valueOf (-dx1);
	    BigDecimal LC1 = getC (LA1, LB1, BigDecimal.valueOf (x1), BigDecimal.valueOf(y1));
	    BigDecimal LD1 = getD (LA1, LB1);
	    LA1 = LA1.divide (LD1, mc);
	    LB1 = LB1.divide (LD1, mc);
	    LC1 = LC1.divide (LD1, mc);
	    //System.out.println (LA1 + " " + LB1 + " " + LC1);
	    BigDecimal px1 = BigDecimal.valueOf (inf.nextInt ());
	    BigDecimal py1 = BigDecimal.valueOf (inf.nextInt ());
	    int x2 = inf.nextInt ();
	    int y2 = inf.nextInt ();
	    int dx2 = inf.nextInt () - x2;
	    int dy2 = inf.nextInt () - y2;
	    BigDecimal LA2 = BigDecimal.valueOf (dy2), LB2 = BigDecimal.valueOf (-dx2);
	    BigDecimal LC2 = getC (LA2, LB2, BigDecimal.valueOf (x2), BigDecimal.valueOf(y2));
	    BigDecimal LD2 = getD (LA2, LB2);
	    LA2 = LA2.divide (LD2, mc);
	    LB2 = LB2.divide (LD2, mc);
	    LC2 = LC2.divide (LD2, mc);
	    BigDecimal px2 = BigDecimal.valueOf (inf.nextInt ());
	    BigDecimal py2 = BigDecimal.valueOf (inf.nextInt ());


	    BigDecimal cx1 = BigDecimal.valueOf (ouf.nextDouble ());
	    BigDecimal cy1 = BigDecimal.valueOf (ouf.nextDouble ());
	    BigDecimal cx2 = BigDecimal.valueOf (ouf.nextDouble ());
	    BigDecimal cy2 = BigDecimal.valueOf (ouf.nextDouble ());
	    boolean csol = false;
	    if (!isZero (cx1) || !isZero (cy1) || !isZero (cx2) || !isZero (cy2)) {
		BigDecimal F1, F2, qqx, qqy, cq;
		if (isSmall (cx2.subtract(cx1).abs ()) && isSmall (cy2.subtract (cy1).abs ()))
			throw new Outcome(Outcome.Type.WA, "contestant has degenerate line");
                if (isLarge (cx1) || isLarge (cy1) || isLarge (cx2) || isLarge (cy2))
			throw new Outcome(Outcome.Type.WA, "contestant coordinates are too large");

		BigDecimal CA = cy2.subtract (cy1), CB = cx1.subtract (cx2);
		BigDecimal CC = getC (CA, CB, cx1, cy1);
		BigDecimal CD = getD (CA, CB);
		CA = CA.divide (CD, mc);
		CB = CB.divide (CD, mc);
		CC = CC.divide (CD, mc);

		F1 = getC (CA, CB, px1, py1);
		qqx = px1.subtract(CA.multiply (TWO).multiply (F1.subtract (CC)));
		qqy = py1.subtract(CB.multiply (TWO).multiply (F1.subtract (CC)));
		cq = getC (LA1, LB1, qqx, qqy).subtract (LC1).abs();
		if (!isSmall (cq)) throw new Outcome(Outcome.Type.WA, "contestant's answer does not fit line 1 in case " + (tc + 1) + ", error = " + cq.doubleValue ());
		ce = ce.max (cq);

		F2 = getC (CA, CB, px2, py2);
		qqx = px2.subtract(CA.multiply (TWO).multiply (F2.subtract (CC)));
		qqy = py2.subtract(CB.multiply (TWO).multiply (F2.subtract (CC)));
		cq = getC (LA2, LB2, qqx, qqy).subtract (LC2).abs();
		if (!isSmall (cq)) throw new Outcome(Outcome.Type.WA, "contestant's answer does not fit line 2 in case " + (tc + 1) + ", error = " + cq.doubleValue ());
		ce = ce.max (cq);

		csol = true;
	    }


	    BigDecimal jx1 = BigDecimal.valueOf (ans.nextDouble ());
	    BigDecimal jy1 = BigDecimal.valueOf (ans.nextDouble ());
	    BigDecimal jx2 = BigDecimal.valueOf (ans.nextDouble ());
	    BigDecimal jy2 = BigDecimal.valueOf (ans.nextDouble ());
	    boolean jsol = false;
	    if (!isZero (jx1) || !isZero (jy1) || !isZero (jx2) || !isZero (jy2)) {
		/*BigDecimal F1, F2, qqx, qqy, jq;
		if (isSmall (jx2.subtract(jx1).abs ().add (jy2.subtract (jy1).abs ()))) 
			throw new Outcome(Outcome.Type.FAIL, "jury has degenerate line");
                if (isLarge (jx1) || isLarge (jy1) || isLarge (jx2) || isLarge (jy2))
			throw new Outcome(Outcome.Type.FAIL, "jury coordinates are too large");
		BigDecimal JA = jy2.subtract (jy1), JB = jx1.subtract (jx2);
		BigDecimal JC = getC (JA, JB, jx1, jy1);
		BigDecimal JD = getD (JA, JB);
		JA = JA.divide (JD, mc);
		JB = JB.divide (JD, mc);
		JC = JC.divide (JD, mc);
		F1 = getC (JA, JB, px1, py1);
		qqx = px1.subtract(JA.multiply (TWO).multiply (F1.subtract (JC)));
		qqy = py1.subtract(JB.multiply (TWO).multiply (F1.subtract (JC)));
		jq = getC (LA1, LB1, qqx, qqy).subtract (LC1).abs();
		if (!isSmall (jq)) throw new Outcome(Outcome.Type.FAIL, "jury answer does not fit line 1 in case " + (tc + 1) + ", error = " + jq.doubleValue ());
		je = je.max (jq);


		F2 = getC (JA, JB, px2, py2);
		qqx = px2.subtract(JA.multiply (TWO).multiply (F2.subtract (JC)));
		qqy = py2.subtract(JB.multiply (TWO).multiply (F2.subtract (JC)));
		jq = getC (LA2, LB2, qqx, qqy).subtract (LC2).abs();
		if (!isSmall (jq)) throw new Outcome(Outcome.Type.FAIL, "jury answer does not fit line 2 in case " + (tc + 1) + ", error = " + jq.doubleValue ());
		je = je.max (jq);*/

		jsol = true;
	    }


	    if (jsol && !csol) throw new Outcome(Outcome.Type.WA, "Contestant has not found solution in case " + (tc + 1));
	    if (csol && !jsol) throw new Outcome(Outcome.Type.WA, "There is no solution in case " + (tc + 1));
	}

	//System.out.println ("Max sqrt error = " + mse.doubleValue ());
	return new Outcome(Outcome.Type.OK, tn + " cases, contesant max error = " + ce.doubleValue ());
    }
}

