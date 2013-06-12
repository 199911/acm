import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Locale;

/**
 * Checker for NEERC'2011 Problem F: Flights
 * @author Roman Elizarov
 */
public class Check implements Checker {
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		int n = 0;
		while (!ans.seekEoF()) {
			double pa = ouf.nextDouble();
			double ja = ans.nextDouble();
			n++;
			if (Math.abs(pa - ja) > 1.1e-4)
				throw new Outcome(Outcome.Type.WA, String.format(Locale.US, "#%d : %.6f instead of %.6f", n, pa, ja));
		}
		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.PE, "extra information in the output file");
		return new Outcome(Outcome.Type.OK, String.format("%d", n));
	}
}
 
import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Locale;

/**
 * Checker for NEERC'2011 Problem F: Flights
 * @author Roman Elizarov
 */
public class Check implements Checker {
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		int n = 0;
		while (!ans.seekEoF()) {
			double pa = ouf.nextDouble();
			double ja = ans.nextDouble();
			n++;
			if (Math.abs(pa - ja) > 1.1e-4)
				throw new Outcome(Outcome.Type.WA, String.format(Locale.US, "#%d : %.6f instead of %.6f", n, pa, ja));
		}
		if (!ouf.seekEoF())
			throw new Outcome(Outcome.Type.PE, "extra information in the output file");
		return new Outcome(Outcome.Type.OK, String.format("%d", n));
	}
}
