import java.io.*;
import java.util.*;

public class Tests {
    static final int MaxC = 10;
    static final int MaxCases = (int)2e4;
    
    static class Point {
	int x, y;
	Point (int xx, int yy) {
	    x = xx;
	    y = yy;
	}
	public boolean check () {
	    return Math.abs (x) <= MaxC && Math.abs (y) <= MaxC;
	}
	public String toString () {
	    return x + " " + y;
	}
    }
    static class Line {
	Point pa, pb;
	Line (Point ppa, Point ppb) {
	    pa = ppa;
	    pb = ppb;
	}
	public boolean check () {
	    return pa.check () && pb.check () && (pa.x != pb.x || pa.y != pb.y);
	}
	public String toString () {
	    return pa + " " + pb;
	}
    }
    static class Testcase {
	final Line l1, l2;
	final Point p1, p2;
	Testcase (Line ll1, Point pp1, Line ll2, Point pp2) {
	    l1 = ll1;
	    p1 = pp1;
	    l2 = ll2;
	    p2 = pp2;
	}

	public boolean check () {
	    if (!l1.check () || !p1.check () || !l2.check () || !p2.check ()) return false;
	    int dx1 = l1.pb.x - l1.pa.x;
	    int dy1 = l1.pb.y - l1.pa.y;
	    if (dx1 * (p1.y - l1.pa.y) - dy1 * (p1.x - l1.pa.x) == 0) return false;
	    int dx2 = l2.pb.x - l2.pa.x;
	    int dy2 = l2.pb.y - l2.pa.y;
	    if (dx2 * (p2.y - l2.pa.y) - dy2 * (p2.x - l2.pa.x) == 0) return false;
	    if (dx1 * dy2 - dx2 * dy1 == 0 && dx1 * (l2.pa.y - l1.pa.y) == dy1 * (l2.pa.x - l1.pa.x)) return false;
	    return true;
	}
	public boolean isParallel () {
	    int dx1 = l1.pb.x - l1.pa.x;
	    int dy1 = l1.pb.y - l1.pa.y;
	    int dx2 = l2.pb.x - l2.pa.x;
	    int dy2 = l2.pb.y - l2.pa.y;
	    return dx1 * dy2 == dy1 * dx2;
	}
	public String toString () {
	    return l1 + "\n" + p1 + "\n" + l2 + "\n" + p2;
	}
    }

    static class Testset {
	ArrayList <Testcase> C;
	public void add (Testcase X) {
	    C.add(X);
	}
	public Testset () {
	    C = new ArrayList <Testcase> ();
	}
	public boolean check () {
	    if (C.size () == 0 || C.size () > MaxCases) return false;
	    for (Testcase X : C)
		if (!X.check ()) return false;
	    return true;
	}
	public String toString () {
	    StringBuffer res = new StringBuffer ().append (C.size() + "\n");
	    for (Testcase X : C)
		res = res.append (X + "\n");
	    return res.toString ();
	}
    }

    public static void main(String[] args) throws IOException {
        new File("tests").mkdir();
        Random R = new Random(54357435983475L);
	ArrayList <Testset> B = new ArrayList <Testset> ();
	Testcase S1 = new Testcase (new Line (new Point (0, 0), new Point (0, 1)),
				    new Point (2, 1),
				    new Line (new Point (0, 0), new Point (1, 0)),
				    new Point (1, 2));
	Testcase S2 = new Testcase (new Line (new Point (0, 0), new Point (0, 1)),
				    new Point (5, 0),
				    new Line (new Point (1, 0), new Point (1, 1)),
				    new Point (6, 0));
	Testset T = new Testset ();
	T.add (S1);
	T.add (S2);
	B.add (T);
	Testcase H1 = new Testcase (new Line (new Point (0, 0), new Point (0, 1)),
				    new Point (1, 1),
				    new Line (new Point (0, 0), new Point (1, 0)),
				    new Point (1, 1));
	Testcase H2 = new Testcase (new Line (new Point (0, 0), new Point (0, 1)),
				    new Point (5, 0),
				    new Line (new Point (1, 0), new Point (1, 1)),
				    new Point (7, 0));
	Testcase H3 = new Testcase (new Line (new Point (0, 0), new Point (0, 1)),
				    new Point (1, 0),
				    new Line (new Point (1, 0), new Point (1, 1)),
				    new Point (2, 1));
	Testcase H4 = new Testcase (new Line (new Point (0, 0), new Point (0, 1)),
				    new Point (2, 1),
				    new Line (new Point (1, 0), new Point (1, 1)),
				    new Point (2, 2));
	Testcase H5 = new Testcase (new Line (new Point (0, 0), new Point (0, 1)),
				    new Point (1, 1),
				    new Line (new Point (2, 0), new Point (2, 1)),
				    new Point (1, 2));
	Testcase H6 = new Testcase (new Line (new Point (0, 0), new Point (0, 1)),
				    new Point (1, 1),
				    new Line (new Point (0, 0), new Point (2, 3)),
				    new Point (4, 5));
	T = new Testset ();
	T.add (H1);
	T.add (H2);
	T.add (H3);
	T.add (H4);
	T.add (H5);
	T.add (H6);
	B.add(T);
	
	T = new Testset ();
	for (int i = 0; i < 1000; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (R.nextInt (2), R.nextInt (2)), new Point (R.nextInt (2), R.nextInt (2))),
				new Point (R.nextInt (2), R.nextInt (2)),
				new Line (new Point (R.nextInt (2), R.nextInt (2)), new Point (R.nextInt (2), R.nextInt (2))),
				new Point (R.nextInt (2), R.nextInt (2)));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);
	
	T = new Testset ();
	for (int i = 0; i < 5000; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (R.nextInt (3), R.nextInt (3)), new Point (R.nextInt (3), R.nextInt (3))),
				new Point (R.nextInt (3), R.nextInt (3)),
				new Line (new Point (R.nextInt (3), R.nextInt (3)), new Point (R.nextInt (3), R.nextInt (3))),
				new Point (R.nextInt (3), R.nextInt (3)));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);
	
	T = new Testset ();
	for (int i = 0; i < 10000; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (R.nextInt (4), R.nextInt (4)), new Point (R.nextInt (4), R.nextInt (4))),
				new Point (R.nextInt (4), R.nextInt (4)),
				new Line (new Point (R.nextInt (4), R.nextInt (4)), new Point (R.nextInt (4), R.nextInt (4))),
				new Point (R.nextInt (4), R.nextInt (4)));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);


	T = new Testset ();
	for (int i = 0; i < MaxCases; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (R.nextInt (2), R.nextInt (2)), new Point (R.nextInt (2), R.nextInt (2))),
				new Point (R.nextInt (2), R.nextInt (2)),
				new Line (new Point (R.nextInt (2), R.nextInt (2)), new Point (R.nextInt (2), R.nextInt (2))),
				new Point (R.nextInt (2), R.nextInt (2)));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);

	for (int k = 0; k < 25; k++) {
	    T = new Testset ();
	    for (int i = 0; i < MaxCases; i++) {
		Testcase C;
		do {
		    C = new Testcase (new Line (new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC), new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC)),
				      new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC),
				      new Line (new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC), new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC)),
				      new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC));
		} while (!C.check());
		T.add(C);
	    }
	    B.add(T);
	}

	for (int k = 0; k < 20; k++) {
	    T = new Testset ();
	    for (int i = 0; i < MaxCases; i++) {
		Testcase C;
		do {
		    C = new Testcase (new Line (new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC), new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC)),
				      new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC),
				      new Line (new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC), new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC)),
				      new Point (R.nextInt(MaxC * 2 + 1) - MaxC, R.nextInt(MaxC * 2 + 1) - MaxC));
		} while (!C.check() || !C.isParallel ());
		T.add(C);
	    }
	    B.add(T);
	}
	T = new Testset ();
	for (int i = 0; i < MaxCases; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (R.nextInt (MaxC), R.nextInt (MaxC)), new Point (R.nextInt (MaxC), R.nextInt (MaxC))),
				new Point (R.nextInt (MaxC), R.nextInt (MaxC)),
				new Line (new Point (R.nextInt (MaxC), R.nextInt (MaxC)), new Point (R.nextInt (MaxC), R.nextInt (MaxC))),
				new Point (R.nextInt (MaxC), R.nextInt (MaxC)));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);

	T = new Testset ();
	for (int i = 0; i < MaxCases; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (-10, -7), new Point (-9, -10)),
				new Point (-10, -10),
				new Line (new Point (-10, -8), new Point (-5, -10)),
				new Point (-10, -10));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);
	
	T = new Testset ();
	for (int i = 0; i < MaxCases; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (-10, -3), new Point (-9, -10)),
				new Point (-10, -9),
				new Line (new Point (-10, -8), new Point (-5, -10)),
				new Point (-10, -10));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);
	
	T = new Testset ();
	for (int i = 0; i < MaxCases; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (-10, -3), new Point (-9, -10)),
				new Point (-10, -2),
				new Line (new Point (-10, -8), new Point (-5, -10)),
				new Point (-10, -10));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);
	
	T = new Testset ();
	for (int i = 0; i < MaxCases; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (-10, -9), new Point (-9, -10)),
				new Point (-10, -7),
				new Line (new Point (-10, -8), new Point (-8, -10)),
				new Point (-10, -10));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);
	
	T = new Testset ();
	for (int i = 0; i < MaxCases; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (-10, -9), new Point (-9, -10)),
				new Point (-10, -7),
				new Line (new Point (-10, -3), new Point (-3, -10)),
				new Point (-10, -6));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);
	
	T = new Testset ();
	for (int i = 0; i < MaxCases; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (-10, -9), new Point (-9, -10)),
				new Point (-10, -8),
				new Line (new Point (-10, -7), new Point (-7, -10)),
				new Point (-10, -6));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);

	T = new Testset ();
	for (int i = 0; i < MaxCases; i++) {
	    Testcase C;
	    do {
	      C = new Testcase (new Line (new Point (4, -9), new Point (10, 8)),
				new Point (-9, -5),
				new Line (new Point (10, 10), new Point (3, -10)),
				new Point (-4, -4));
	    } while (!C.check());
	    T.add(C);
	}
	B.add(T);

	T = new Testset ();
	H1 = new Testcase (new Line (new Point (3, -3), new Point (-2, 1)),
			   new Point (-1, 3),
			   new Line (new Point (1, -2), new Point (4, 2)),
			   new Point (-5, 0));
	H2 = new Testcase (new Line (new Point (-8, -8), new Point (-4, 9)),
			   new Point (10, 0),
			   new Line (new Point (8, 7), new Point (5, -6)),
			   new Point (-6, 8));
	H3 = new Testcase (new Line (new Point (-9, 10), new Point (10, 9)),
			   new Point (-2, -10),
			   new Line (new Point (9, -9), new Point (-9, -8)),
			   new Point (3, 9));
	H4 = new Testcase (new Line (new Point (-10, 6), new Point (9, 7)),
			   new Point (4, -10),
			   new Line (new Point (10, -7), new Point (-10, -8)),
			   new Point (-8, 10));
	H5 = new Testcase (new Line (new Point (9, 0), new Point (-10, -1)),
			   new Point (10, 0),
			   new Line (new Point (-10, -3), new Point (8, -2)),
			   new Point (3, 9));
	H6 = new Testcase (new Line (new Point (4, -5), new Point (-4, 3)),
			   new Point (-2, 8),
			   new Line (new Point (-7, 2), new Point (0, -5)),
			   new Point (-4, 6));
	Testcase H7 = new Testcase (new Line (new Point (-5, -8), new Point (-1, 5)),
				    new Point (0, 8),
				    new Line (new Point (-5, -6), new Point (8, 9)),
				    new Point (9, -10));
	Testcase H8 = new Testcase (new Line (new Point (-7, -6), new Point (8, 2)),
				    new Point (-4, 9),
				    new Line (new Point (7, -1), new Point (-10, -10)),
				    new Point (5, -2));
	Testcase H9 = new Testcase (new Line (new Point (-3, -9), new Point (5, -8)),
				    new Point (-10, 9),
				    new Line (new Point (8, -3), new Point (-9, -5)),
				    new Point (-1, -4));
	T.add (H1);
	T.add (H2);
	T.add (H3);
	T.add (H4);
	T.add (H5);
	T.add (H6);
	T.add (H7);
	T.add (H8);
	T.add (H9);
	B.add (T);

	int id = 0;
	for (Testset X : B) {
	    outputTest (++id, X);
	}

    }

    private static void outputTest(int testId, Testset c) {
        String name = "" + testId;
        while (name.length() < 2) name = "0" + name;
        PrintWriter writer;
        try {
            writer = new PrintWriter("tests/" + name);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }

	if (!c.check ()) throw new RuntimeException ("Attempting to create an invalid testset");

        writer.print(c);
        writer.close();
    }
}
