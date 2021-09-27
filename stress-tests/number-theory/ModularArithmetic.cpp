#include "../utilities/template.h"

#include "../../content/number-theory/ModularArithmetic.h"


int main() {
    //test construction
    rep(a,0,mint::mod+1) {
        assert(mint(a).x == mint(a-mint::mod).x);
    }
    
	rep(a,0,mint::mod) rep(b,1,mint::mod) {
		mint ma(a);
		mint mb(b);
		mint mc = ma / mb;
		assert((mc * mb).x == a);
	}
	mint a = 2;
	ll cur=1;
	rep(i, 0, 17) {
		assert((a ^ i).x == cur);
		cur = (cur * 2) % mint::mod;
		// cout << i << ": " << (a ^ i).x << endl;
	}
	cout<<"Tests passed!"<<endl;
}
