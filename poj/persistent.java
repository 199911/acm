import java.math.*;
import java.util.*;

class Main {
  public static void main( String args[] ) {
    Scanner cin = new Scanner( System.in );
    while ( cin.hasNext() ) {
      String str = cin.next();
      BigInteger bg = new BigInteger( str );
      int cnt[] = new int[12];
      if ( bg.compareTo( BigInteger.ZERO ) == -1 ) break;

      for( int i = 1; i <= 9; i++ ) cnt[i] = 0;

      if ( bg.compareTo( BigInteger.TEN ) < 0 ) {
        cnt[bg.intValue()] = 1;
        cnt[1]++ ;
        bg = BigInteger.ONE;
      } else {
        for( int div = 9; div >= 2; div-- ) {
          BigInteger dv = new BigInteger( div + "" );
          while( bg.mod( dv ).equals( BigInteger.ZERO ) ) {
            bg = bg.divide( dv );
            cnt[div]++;
          }
        }
      }
      if ( bg.compareTo( BigInteger.ONE ) == 1 ) {
        System.out.println( "There is no such number." );
      } else {
        for( int i = 1; i <= 9; i++ ) {
          for( int j = 0; j < cnt[i]; j++ ) 
            System.out.print( i );
        }
        if ( cnt[0] > 0 ) System.out.print( 0 );
        System.out.println( "" );
      }
    }
  }
};
