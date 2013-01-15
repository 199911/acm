import java.util.*;
import java.math.*;

class Main {

  public static void main( String args[] ) {
    BigInteger[] g = new BigInteger[51], f = new BigInteger[51], p = new BigInteger[1301];
    BigInteger[][] c = new BigInteger[51][51];
    g[1] = new BigInteger( "0" );
    f[1] = new BigInteger( "1" );
    for( int i = 0; i <= 50; i++ )
      c[i][0] = new BigInteger( "1" );
    for( int i = 0; i <= 50; i++ )
      for( int j = i + 1; j <= 50; j++ ) 
        c[i][j] = new BigInteger( "0" );
    for( int i = 1; i <= 50; i++ ) 
      for( int j = 1; j <= i; j++ ) 
        c[i][j] = c[i - 1][j - 1].add( c[i - 1][j] );
    p[0] = new BigInteger( "1" );
    for( int i = 1; i <= 1300; i++ ) 
      p[i] = p[i - 1].multiply( new BigInteger( "2" ) );

    g[1] = new BigInteger( "0" );
    f[1] = new BigInteger( "1" );

    for( int i = 2; i <= 50; i++ ) {
      g[i] = new BigInteger( "0" );
      for( int j = 1; j < i; j++ ) {
        int a = ( i - j ) * ( i - j - 1 ) / 2;
        g[i] = g[i].add( c[i - 1][j - 1].multiply( p[a] ).multiply( f[j] ) );
      }
      f[i] = p[i * (i - 1) / 2].subtract( g[i] );
    }

    Scanner cin = new Scanner( System.in );
    while( cin.hasNextInt() ) {
      int k = cin.nextInt();
      if ( k == 0 ) break;
      System.out.println( f[k] );
    }

  }
}
