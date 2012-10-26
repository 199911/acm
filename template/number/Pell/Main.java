import java.io.*;
import java.util.*;

public class Main {

	private BigInteger a[3], B[3], C[3], RD, P[3], Q[3];
	private BigInteger Rx, Ry;
	private BigInteger D;
	
	public boolean pell( int d ) {
		D = new BigInteger( "" + d );
		RD = new BigInteger
		B[0] = new BigInteger( "" + (int) Math.sqrt( d ) );
		C[0] = new BigInteger( "1" );
		a[0] = B[0].multiply( new BigInteger( "2" ) );

		for( int i = 1; i < 1111; i++ ) {
			B[i % 3] = a[(i - 1) % 3].multiply( C[(i - 1) % 3]).minus(B[(i - 1) % 3]);
			C[i % 3] = D.minus( B[i % 3].multiply( B[i % 3] ) ).divide( C[(i - 1) % 3]);
			a[i % 3] = B[i % 3]
		}
	}

	public static void main( String args[] ) {
	}
}
