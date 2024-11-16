ll rec(vector<pt>::iterator a, int l, int r) {
	if (r - l < 2) return INF;
	int m = (l + r) / 2;
	ll midx = a[m].real();
	ll ans = min(rec(a, l, m), rec(a, m, r));

	ranges::inplace_merge(a+l, a+m, a+r, {},
		[](pt x) { return imag(x); });

	pt tmp[8];
	ranges::fill(tmp, a[l]);
	for (int i = l + 1, next = 0; i < r; i++) {
		if (ll x = a[i].real() - midx; x * x < ans) {
			for (pt& p : tmp) ans = min(ans, norm(p - a[i]));
			tmp[next++ & 7] = a[i];
		}
	}
	return ans;
}

ll shortestDist(vector<pt> a) { // size(pts) > 1
	ranges::sort(a, {}, [](pt x) { return real(x); });
	return rec(a.begin(), 0, ssize(a));
}
