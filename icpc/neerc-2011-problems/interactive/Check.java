import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

public class Check implements Checker {
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		while (true) {
			String verdict = ouf.nextLine();
			if (verdict.equals(""))
				throw new Outcome(Outcome.Type.WA, "User program terminated too early");
			String[] s = verdict.split(" ", 2);
			if (s[0].equals("INP") || s[0].equals("OUT"))
				continue; // skip log lines
			Outcome.Type type = Outcome.Type.valueOf(s[0]);
			throw new Outcome(type, s[1]);
		}
	}
}
 
import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

public class Check implements Checker {
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
		while (true) {
			String verdict = ouf.nextLine();
			if (verdict.equals(""))
				throw new Outcome(Outcome.Type.WA, "User program terminated too early");
			String[] s = verdict.split(" ", 2);
			if (s[0].equals("INP") || s[0].equals("OUT"))
				continue; // skip log lines
			Outcome.Type type = Outcome.Type.valueOf(s[0]);
			throw new Outcome(type, s[1]);
		}
	}
}
