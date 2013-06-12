import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Locale;
import java.util.Scanner;

/**
 * @author Roman Elizarov
 */
public class FlightsVisualize extends JComponent {
	private static final int MARGIN = 15;

	public static void main(String[] args) throws FileNotFoundException {
		int t1 = args.length > 0 ? Integer.parseInt(args[0]) : 1;
		int t2 = args.length > 1 ? Integer.parseInt(args[1]) : Integer.MAX_VALUE;
		new FlightsVisualize(t1, t2).go();
	}

	static double sqr(double x) {
		return x * x;
	}

	static double det2(double a11, double a12, double a21, double a22) {
		return a11 * a22 - a12 * a21;
	}

	static double det3(double a11, double a12, double a13,
					   double a21, double a22, double a23,
					   double a31, double a32, double a33)
	{
		return a11 * det2(a22, a23, a32, a33)
		     - a21 * det2(a12, a13, a32, a33)
		     + a31 * det2(a12, a13, a22, a23);
	}

	// y = a*x^2 + b*x + c
	static class Missile {
		final int x;
		final int y;

		final int x1;
		final int x2;

		final double a; // max |a| ~ max |y| ~ 1e2
		final double b; // max |b| ~ max |x*y| ~ 1e7
		final double c;

		Missile(int p, int x, int y) {
			this.x = x;
			this.y = y;
			x1 = p;
			x2 = 2 * x - p;
			// 0 = a * x1^2 + b * x1 + c
			// 0 = a * x2^2 + b * x2 + c
			// y = a * x^2  + b * x  + c
			double a11 = sqr(x1); double a12 = x1; double a13 = 1;    double b1 = 0;
			double a21 = sqr(x2); double a22 = x2; double a23 = 1;    double b2 = 0;
			double a31 = sqr(x);  double a32 = x;  double a33 = 1;    double b3 = y;
			double d = det3(a11, a12, a13, a21, a22, a23, a31, a32, a33);
			a = det3(b1 , a12, a13, b2 , a22, a23, b3 , a32, a33) / d;
			b = det3(a11, b1 , a13, a21, b2 , a23, a31, b3 , a33) / d;
			c = det3(a11, a12, b1 , a21, a22, b2 , a31, a32, b3 ) / d;
		}

		double at(double x) {
			return a * sqr(x) + b * x + c;
		}

		double max(double x1, double x2) {
			return x1 < x && x < x2 ? y : Math.max(at(x1), at(x2));
		}

		@Override
		public String toString() {
			return String.format(Locale.US, "[%d,%d] {%.4f %.4f %.4f}", x1, x2, a, b, c);
		}
	}

	int t1;
	int t2;

	int n;
	Missile[] missiles;

	int x1 = Integer.MAX_VALUE;
	int x2;
	int y2;

	FlightsVisualize(int t1, int t2) {
		this.t1 = t1;
		this.t2 = t2;
	}

	private void go() throws FileNotFoundException {
		read();

		t1--;
		t2 = Math.min(t2, n) - 1;

		JFrame frame = new JFrame("Flights");
		frame.add(this);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(800, 600);
		frame.setVisible(true);
	}

	private void read() throws FileNotFoundException {
		Scanner in = new Scanner(new File("flights.in"));
		n = in.nextInt();
		missiles = new Missile[n];
		for (int i = 0; i < n; i++) {
			missiles[i] = new Missile(in.nextInt(), in.nextInt(), in.nextInt());
			x1 = Math.min(x1, missiles[i].x1);
			x2 = Math.max(x2, missiles[i].x2);
			y2 = Math.max(y2, missiles[i].y);
		}
		in.close();
	}

	@Override
	protected void paintComponent(Graphics g) {
		int w = getWidth() - 2 * MARGIN;
		int h = getHeight() - 2 * MARGIN;
		for (int i = t1; i <= t2; i++) {
			Missile m = missiles[i];
			markX(g, m.x1);
			markX(g, m.x2);
			markX(g, m.x);
			mark(g, m.x, m.y, "#" + Integer.toString(i + 1) + " (" + m.x + "," + m.y + ")");
			boolean first = true;
			int px = 0;
			int py = 0;
			for (int j = 0; j < w; j++) {
				int x = MARGIN + j;
				double xx = (double)j / w * (x2 - x1) + x1;
				if (xx >= m.x1 && xx <= m.x2) {
					double yy = m.at(xx);
					int y = getY(yy);
					if (!first)
						g.drawLine(px, py, x, y);
					first = false;
					px = x;
					py = y;
				}
			}
		}
	}

	private void markX(Graphics g, int xx) {
		g.drawString(Integer.toString(xx), getX(xx), getHeight());
	}

	private void mark(Graphics g, int xx, int yy, String s) {
		g.drawString(s, getX(xx), getY(yy));
	}

	private int getY(double yy) {
		return (int)((1 - yy / y2) * (getHeight() - 2 * MARGIN) + 0.5) + MARGIN;
	}

	private int getX(double xx) {
		return (int)((xx - x1) / (x2 - x1) * (getWidth() - 2 * MARGIN) + 0.5) + MARGIN;
	}
}
