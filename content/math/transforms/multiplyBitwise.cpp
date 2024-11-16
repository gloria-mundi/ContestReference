vector<ll> mul(vector<ll> a, vector<ll> b) {
	int n = 1 << (__lg(2 * max(ssize(a), ssize(b)) - 1));
	a.resize(n), b.resize(n);
	bitwiseConv(a), bitwiseConv(b);
	for (int i=0; i<n; i++) a[i] *= b[i]; // MOD?
	bitwiseConv(a, true);
	return a;
}
