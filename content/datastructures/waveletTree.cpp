struct WaveletTree {
	unique_ptr<WaveletTree> ln, rn;
	vector<int> b = {0};
	ll lo, hi;

	WaveletTree(auto in) : lo(*ranges::min_element(in)),
	                       hi(*ranges::max_element(in) + 1) {
		ll mid = (lo + hi) / 2;
		auto f = [&](ll x) { return x < mid; };
		for (ll x: in) b.push_back(b.back() + f(x));
		if (lo + 1 >= hi) return;
		auto right = ranges::stable_partition(in, f);
		ln = make_unique<WaveletTree>(
		  ranges::subrange(begin(in), begin(right)));
		rn = make_unique<WaveletTree>(right);
	}

	ll kth(int l, int r, int k) {
		if (k < 0 || l + k >= r) return -1;
		if (lo + 1 >= hi) return lo;
		int inLeft = b[r] - b[l];
		if (k < inLeft) return ln->kth(b[l], b[r], k);
		else return rn->kth(l-b[l], r-b[r], k-inLeft);
	}

	int countSmaller(int l, int r, ll k) {
		if (l >= r || k <= lo) return 0;
		if (hi <= k) return r - l;
		return ln->countSmaller(b[l], b[r], k) +
		       rn->countSmaller(l-b[l], r-b[r], k);
	}
};
