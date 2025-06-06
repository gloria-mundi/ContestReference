vector<int> pivots; // ith pivot is in ith row
void gauss(int n, int m) {
	for (int r = 0, c = 0; c < m; c++) {
		for (int i = r; i < n; i++) {
			if (mat[i][c] != 0){
				swap(mat[r], mat[i]);
				break;
		}}
		if (mat[r][c] == 0) continue;
		ll f = multInv(mat[r][c], mod);
		for (ll& x : mat[r]) x = x * f % mod;
		for (int i = 0; i < n; i++) {
			if (i == r) continue;
			f = mat[i][c];
			for (int j = c; j < m; j++) {
				mat[i][j] = (mat[i][j] - f * mat[r][j] % mod + mod) % mod;
		}}
		pivots.push_back(c);
		if (++r == n) break;
}} // no solution if pivots.back() == m-1
