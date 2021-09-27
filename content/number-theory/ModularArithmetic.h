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

struct mint {
	static const ll mod = 17; // change to something else
	ll x;
	mint(ll xx) : x(xx) {}
	mint operator+(mint b) { return mint((x + b.x) % mod); }
	mint operator-(mint b) { return mint((x - b.x + mod) % mod); }
	mint operator*(mint b) { return mint((x * b.x) % mod); }
	mint operator/(mint b) { return *this * invert(b); }
	mint invert(mint a) {
		ll x, y, g = euclid(a.x, mod, x, y);
		assert(g == 1); return mint((x + mod) % mod);
	}
	mint operator^(ll e) {
		if (!e) return mint(1);
		mint r = *this ^ (e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
};
