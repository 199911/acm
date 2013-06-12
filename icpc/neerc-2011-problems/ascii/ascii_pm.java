import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class ascii_pm {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("ascii.in"));
        PrintWriter out = new PrintWriter("ascii.out");

        int h = in.nextInt();
        int w = in.nextInt();

        int res = 0;
        for (int i = 0; i < h; i++) {
            String s = in.next();
            boolean inside = false;
            for (int j = 0; j < w; j++) {
                char c = s.charAt(j);
                if (c == '\\' || c == '/') {
                    inside = !inside;
                    res++;
                } else {
                    if (inside) {
                        res += 2;
                    }
                }
            }
        }

        res /= 2;
        out.println(res);

        out.close();

    }
}
