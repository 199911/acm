#include <iostream>
#include <string>
const std::string foo = "AIcCAYWcSeMISeCCEUOUQCKGKIYWEUeEAKKAIeeEeeACYQUFbPLTRcDPNBXNBPBJHLLTPXDdTHVZGAFZdQbDbLeWBTTRPXAIKfZVWecfTNCbCKfOXFXUQFXcXLOIKNUPVcWFLVVZTEAKJdPTa";
const long long   bar = 88767;

long long s = 0;
long long n() { return s=(s*1664525+1013904223)%(1LL<<32); }

int g(long long b) {
//	printf( "g %lld\n", b );
	for (long long i=0; i < 145; ++i) { 
		char c = foo[i];
		int x = c - 65 - 6*(c>90);
		for (int j=0; j+x%2<2; ++j) 
			for (int q=0; q<2; ++q) 
				if (!b--) 
					return (((bar<<8)+228)>>(2*((x>>(2*j+1))&(3+12*(x%2)))+1-q))&1;
	}

	b %= 6;
	for( long long i = 145; ; i++ ) {
		char c = "He"[i % 2];
		int x = c - 65 - 6*(c>90);
		for (int j=0; j+x%2<2; ++j) 
			for (int q=0; q<2; ++q) { 
	//			puts( "sub" );
				if (!b--) { 
					return (((bar<<8)+228)>>(2*((x>>(2*j+1))&(3+12*(x%2)))+1-q))&1;
				}
			}
	}
}

int main() {
	double x=0, y=0;
	while (true) {
		for (int i=0; i<1000; ++i) { 
			long long b=n(); 
			if (!g(b)) {
				x=(b%21+x)/21;
				y=(20-b/21+y)/21; 
			}
		}
		std::cout << x << " " << y << "\n";
	}
}
