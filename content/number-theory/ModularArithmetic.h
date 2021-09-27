/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "euclid.h"

ll safe_mod(ll x, ll m) {
	ll t = x%m;
	return t >= 0 ? t : t + m;
}

struct mint {
	static const ll mod = 17; // change to something else
	ll x;
	mint(ll xx) : x(safe_mod(xx, mod)) {}
	mint operator+(mint b) { return mint((x + b.x) % mod); }
	mint operator-(mint b) { return mint((x - b.x + mod) % mod); }
	mint operator*(mint b) { return mint((x * b.x) % mod); }
	mint operator/(mint b) { return *this * invert(b); }
	mint invert(mint a) {
		ll x, y, g = euclid(a.x, mod, x, y);
		assert(g == 1); return mint((x + mod) % mod);
	}

	/**
	 * Author: Noam527
	 * Date: 2019-04-24
	 * License: CC0
	 * Source: folklore
	 * Description:
	 * Status: tested
	 */
	mint operator^(ll e) {
		ll ans = 1, b = x;
		for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
		return ans;
	}
};
