import java.io.*;
import java.util.*;
import java.math.*;

class Main() {
  public static void main( String args[] ) {
    Scanner cin = new Scanner( System.in );
    BigInteger a = cin.nextBigInteger(), b = BigInteger.valueof( 100 );
    a.isProablePrime( 10 );
    a.modInverse( new BigInteger( "100000007" ) );
    a.modPow( b, m );

    BigDecimal c = new BigDecimal( a );
    c.setScale( 10, BigDecimal.ROUND_HALF_UP );
    c.stripTrailingZeros();
    BigDecimal e[] = c.divideAndRemainder( d );
    c.divideToIntegralValue( d );
  }
}
