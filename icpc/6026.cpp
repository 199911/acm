#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <bitset>
#include <map>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

#define N 55
#define M 1333
#define EPS 1e-9

struct P {
  double x, y, z;
  P() {}
  P( double x, double y, double z ): x(x), y(y), z(z) {}
  void eat() { scanf( "%lf%lf%lf", &x, &y, &z ); }

  P operator+( P p ) const { return P( x + p.x, y + p.y, z + p.z ); }
  P operator-( P p ) const { return P( x - p.x, y - p.y, z - p.z ); }
  P operator*( double s ) const { return P( x * s, y * s, z * s ); }
  double operator*( P p ) const { return x * p.x + y * p.y  + z * p.z; }

  double mag2() { return x * x + y * y + z * z; }
  double mag() { return sqrt( x * x + y * y + z * z ); }
};

P p[N], v[N];
double curT;
int n, m, qn;
int rnk[M];
int T[M], S[M];
pair<double, PII> q[M*M];

struct E {
  P st, vl;
  int a, b, idx;
  double len2;
  E() {}
  E( int a, int b, int idx ): a(a), b(b), idx(idx) { st = p[b] - p[a]; vl = v[b] - v[a]; }

  double length2( double t ) { return len2 = ( st + vl * t ).mag2(); }
  bool operator<( const E &e ) const { return len2 < e.len2; }
};

int pp[N];
E edge[M];

int find( E e1, E e2, double &t1, double &t2 ) {
  double A = e1.vl.mag2() - e2.vl.mag2(), B = 2.0 * ( e1.st * e1.vl - e2.st * e2.vl ), C = e1.st.mag2() - e2.st.mag2();
  if ( fabs( A ) > EPS ) {
    double dt = B * B - 4.0 * A * C;
    if ( dt > -EPS ) {
      dt = sqrt( dt + EPS );
      t1 = -B + dt; t2 = -B - dt;
      t1 /= 2.0 * A; t2 /= 2.0 * A;
      return 2;
    } else {
      return 0;
    }
  } else {
    if ( fabs( B ) < EPS ) {
      return 0;
    } else {
      t1 = t2 = -C / B;
      return 1;
    }
  }
  return 0;
}

void ms() { REP( i, n ) pp[i] = i; }
int f( int x ) { return x == pp[x] ? x : ( pp[x] = f( pp[x] ) ); }
void u( int x, int y ) { pp[f( x )] = f( y ); } 

void compute( double t, int T[] ) {
  int cc = n;
  ms();
  fill( T, T + m, 0 );
  REP( i, m ) edge[i].length2( t );
  sort( edge, edge + m );
  REP( i, m ) {
    E e = edge[i];
    if ( f( e.a ) != f( e.b ) ) {
      u( e.a, e.b );
      T[e.idx] = 1;
      if ( --cc == 1 ) break; 
    } 
  }
}

int main() {
  int cas = 1;
  while( scanf( "%d", &n ) != EOF ) {
    REP( i, n ) {
      p[i].eat(); 
      v[i].eat();
    }

    m = 0;
    REP( i, n ) {
      FOR( j, i + 1, n ) {
        edge[m] = E( i, j, m );
        m++;
      }
    }

    qn = 0;
    REP( i, m ) {
      FOR( j, i + 1, m ) {
        double t1, t2;
        int k = find( edge[i], edge[j], t1, t2 );
        if ( k == 2 ) {
          if( t1 > EPS ) q[qn++] = pair<double, PII>( t1, PII( edge[i].idx, edge[j].idx ) );
          if( t2 > EPS ) q[qn++] = pair<double, PII>( t2, PII( edge[i].idx, edge[j].idx ) );
        } else if ( k == 1 ) {
          if( t1 > EPS ) q[qn++] = pair<double, PII>( t1, PII( edge[i].idx, edge[j].idx ) );
        }
      }
    }

    sort( q, q + qn );

    int ans = 1;
    compute( 0.0, T );

    double lastT = 0;
    REP( i, qn ) {
      double t = q[i].first;
      int u = q[i].second.first, v = q[i].second.second;
      if ( T[u] == T[v] ) { 
        lastT = t;
        continue;
      }
      if ( t < lastT + EPS ) {
        lastT = t;
        continue;
      }
      compute( t - 1e-8, S );
      compute( t + 1e-8, T );
      REP( i, m ) 
        if ( T[i] != S[i] ) {
          ans++;
          break;
        }
      lastT = t;
    }

    printf( "Case %d: %d\n", cas++, ans );
  }
  return 0;
}
