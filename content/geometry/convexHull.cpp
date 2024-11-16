vector<pt> convexHull(vector<pt> pts){
	ranges::sort(pts, {},
		[](pt x) { return pair{real(x), imag(x)}; });
	pts.erase(begin(ranges::unique(pts)), end(pts));
	int k = 0;
	vector<pt> h(2 * ssize(pts));
	auto half = [&](auto &&v, int t) {
		for (auto x: v) {
			while (k > t && cross(h[k-2], h[k-1], x) <= 0) k--;
			h[k++] = x;
	}};
	half(pts, 1); // Untere Hülle.
	half(pts | views::reverse | views::drop(1), k); // Obere Hülle
	h.resize(k);
	return h;
}
