vector<mat> pows;

void precalc(mat m) {
	pows = {m};
	for (int i = 0; i < 60; i++) pows.push_back(pows[i] * pows[i]);
}

auto calc(ll b, vector<ll> v) {
	for (ll i = 0; b > 0; i++) {
		if (b & 1) v = pows[i] * v;
		b >>= 1;
	}
	return v;
}
