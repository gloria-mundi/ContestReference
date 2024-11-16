vector<cplx> mul(vector<ll>& a, vector<ll>& b) {
	int n = 1 << (__lg(ssize(a) + ssize(b) - 1) + 1);
	vector<cplx> c(begin(a), end(a)), d(n);
	c.resize(n);
	for (int i = 0; i < ssize(b); i++) c[i] = {real(c[i]), b[i]};
	fft(c);
	for (int i = 0; i < n; i++) {
		int j = (n - i) & (n - 1);
		cplx x = (c[i] + conj(c[j])) / cplx{2, 0}; //fft(a)[i];
		cplx y = (c[i] - conj(c[j])) / cplx{0, 2}; //fft(b)[i];
		d[i] = x * y;
	}
	fft(d, true);
	return d;
}
