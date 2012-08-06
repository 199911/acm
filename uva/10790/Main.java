import java.io.*;
import java.math.*;
import java.lang.*;
import java.util.*;

public class Main {
  public static void main( String[] args ) throws Exception {
    Scanner cin = new Scanner( System.in );
    while ( true ) {
      int a = cin.nextInt(), b = cin.nextInt();

      if ( a == 0 && b == 0 ) {
        break;
      }

      if ( a <= 1 || b <= 1 ) {
        System.out.println( 0 );
        continue;
      } else {
        BigInteger t1 = (new BigInteger( "" + a )).multiply( new BigInteger( "" + (a - 1)) ).divide( new BigInteger("2") );
        BigInteger t2 = (new BigInteger( "" + b )).multiply( new BigInteger( "" + (b - 1)) ).divide( new BigInteger("2") );
        BigInteger res = t1.multiply( t2 );
        System.out.println( res );
      }
    }
  }
}
