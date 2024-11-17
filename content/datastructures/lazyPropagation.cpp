struct SegTree {
	using T = ll; using U = ll;
	static constexpr T E = 0; // Neutral element for combine
	static constexpr U UF = 1e18; // Unused value by updates
	int n;
	vector<T> tree; vector<U> lazy;
	int h;
	vector<ll> k; // size of segments (optional)

	SegTree(const vector<T>& a) : n(ssize(a) + 1), tree(2 * n, E),
	//SegTree(int size, T def = E) : n(size + 1), tree(2 * n, def),
			lazy(n, UF), h(__lg(2 * n)), k(2 * n, 1) {
		ranges::copy(a, tree.begin() + n);
		for (int i = n - 1; i > 0; i--) {
			k[i] = 2 * k[2 * i];
			tree[i] = comb(tree[2 * i], tree[2 * i + 1]);
	}}

	T comb(T a, T b) { return a + b; } // Modify this + E

	void apply(int i, U val) { // And this + UF
		tree[i] = val * k[i];
		if (i < n) lazy[i] = val; // Don't forget this
	}

	void push_down(int i) {
		if (lazy[i] != UF) {
			apply(2 * i, lazy[i]);
			apply(2 * i + 1, lazy[i]);
			lazy[i] = UF;
	}}

	void push(int i) {
		for (int s = h; s > 0; s--) push_down(i >> s);
	}

	void build(int i) {
		while (i /= 2) {
			push_down(i);
			tree[i] = comb(tree[2 * i], tree[2 * i + 1]);
	}}

	void update(int l, int r, U val) {
		l += n, r += n;
		int l0 = l, r0 = r;
		push(l0), push(r0);
		for (; l < r; l /= 2, r /= 2) {
			if (l&1) apply(l++, val);
			if (r&1) apply(--r, val);
		}
		build(l0), build(r0);
	}

	T query(int l, int r) {
		l += n, r += n;
		push(l), push(r);
		T resL = E, resR = E;
		for (; l < r; l /= 2, r /= 2) {
			if (l&1) resL = comb(resL, tree[l++]);
			if (r&1) resR = comb(tree[--r], resR);
		}
		return comb(resL, resR);
	}

	// Optional:
	int binary_search(int l, int r, auto &&f) {
		if (f(E)) return l;
		l += n, r += n;
		push(l), push(r);
		int a[64] = {}, lp = 0, rp = 64;
		for (; l < r; l /= 2, r /= 2) {
			if (l&1) a[lp++] = l++;
			if (r&1) a[--rp] = --r;
		}
		T x = E, y = x;
		for (int i : a) if (i != 0 && f(x = comb(y = x, tree[i]))) {
			while (i < n) {
				push_down(i);
				if (f(x = comb(y, tree[2*i]))) i = 2 * i;
				else i = 2 * i + 1, y = x;
			}
			return i - n + 1;
		}
		return -1;
	}
};
