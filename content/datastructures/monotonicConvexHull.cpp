struct Envelope {
	struct Line {
		ll m, b;
		ll operator()(ll x) { return m*x+b; }
	};

	vector<Line> ls;
	int ptr = 0;

	static bool bad(Line l1, Line l2, Line l3) {
		return (l3.b-l1.b)*(l1.m-l2.m) < (l2.b-l1.b)*(l1.m-l3.m);
	}

	void add(ll m, ll b) {
		while (sz(ls) > 1 && bad(ls.end()[-2], ls.back(), {m, b})) {
			ls.pop_back();
		}
		ls.push_back({m, b});
		ptr = min(ptr, (int)sz(ls) - 1);
	}

	ll query(ll x) {
		while (ptr < sz(ls)-1 && ls[ptr + 1](x) < ls[ptr](x)) ptr++;
		return ls[ptr](x);
	}
};
