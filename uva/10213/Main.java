import java.io.*;
import java.math.*;
import java.lang.*;
import java.util.*;

public class Main {
  public static void main( String[] args ) throws Exception {
    Scanner cin = new Scanner( System.in );

    int cas = cin.nextInt();

    for ( int i = 0; i < cas; i++ ) {
      int n = cin.nextInt();

      BigInteger res = new BigInteger( "1" ), tmp = new BigInteger( "" + n );

      tmp = tmp.multiply( new BigInteger( "" + (n - 1)) ).divide( new BigInteger( "2" ));
      
      res = res.add( tmp );

      tmp = tmp.multiply( new BigInteger( "" + (n - 2)) ).multiply( new BigInteger( "" + (n - 3)) ).divide( new BigInteger( "12" ) );

      res = res.add( tmp );

      System.out.println( res );
    }

  }
}
