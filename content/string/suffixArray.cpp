constexpr int MAX_CHAR = 256;
struct SuffixArray {
	int n;
	vector<int> SA, LCP;
	vector<vector<int>> P;

	SuffixArray(const string& s) : n(ssize(s)), SA(n), LCP(n),
		P(__lg(2 * n - 1) + 1, vector<int>(n)) {
		P[0].assign(begin(s), end(s));
		iota(begin(SA), end(SA), 0);
		ranges::sort(SA, {}, [&](int x) { return s[x]; });
		vector<int> x(n);
		for (int k = 1, c = 1; c < n; k++, c *= 2) {
			iota(begin(x), end(x), n - c);
			for (int ptr = c; int i : SA) if (i >= c) x[ptr++] = i - c;

			vector<int> cnt(k == 1 ? MAX_CHAR : n);
			for (int i : P[k-1]) cnt[i]++;
			partial_sum(begin(cnt), end(cnt), begin(cnt));
			for (int i : x | views::reverse) SA[--cnt[P[k-1][i]]] = i;

			auto p = [&](int i) { return i < n ? P[k-1][i] : -1; };
			for (int i = 1; i < n; i++) {
				int a = SA[i-1], b = SA[i];
				P[k][b] = P[k][a] + (p(a) != p(b) || p(a+c) != p(b+c));
		}}
		for (int i = 1; i < n; i++) LCP[i] = lcp(SA[i-1], SA[i]);
	}

	// x & y are text-indices, not SA-indices
	int lcp(int x, int y) {
		if (x == y) return n - x;
		int res = 0;
		for (int i = ssize(P)-1; i >= 0 && max(x, y) + res < n; i--){
			if (P[i][x + res] == P[i][y + res]) res |= 1 << i;
		}
		return res;
	}
};
