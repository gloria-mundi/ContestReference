vector<ll> mul(vector<ll> a, vector<ll> b) {
	int n = 1 << bit_width(size(a) + size(b) - 1);
	a.resize(n), b.resize(n);
	ntt(a), ntt(b);
	for (int i=0; i<n; i++) a[i] = a[i] * b[i] % mod;
	ntt(a, true);
	return a;
}
