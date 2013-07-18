
P piv;

bool comp( const P &a, const P &b ) {
  if ( fabs(( a - piv ) ^ ( b - piv )) < EPS ) return ( a - piv ).mag2() < ( b - piv ).mag2();
  else return (( a - piv ) ^ ( b - piv )) > 0;
}
