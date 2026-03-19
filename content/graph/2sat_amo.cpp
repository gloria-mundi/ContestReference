void atMostOne(const vector<ll>& vars) {
	int k = n / 2;
	n += 2 * ssize(vars);
	adj.resize(n);
	for (int i = 0; i + 1 < sz(vars); i++) {
		addImpl(vars[i], var(k+i));
		addImpl(var(k+i), var(k+i+1));
		addImpl(var(k+i), vars[i+1] ^ 1);
}}
