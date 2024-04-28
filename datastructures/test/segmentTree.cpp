#include "segmentTree.tmp.cpp"

void test(int n) {
	vector<ll> a(n);
	for (ll &x: a) x = util::randint();
	SegTree seg(a);
	for (int i = 0; i < 5*n; i++) {
		{
			int j = util::randint(n);
			ll v = util::randint();
			a[j] = v;
			seg.update(j, v);
		}
		{
			int l = util::randint(n+1);
			int r = util::randint(n+1);
			if (l > r) swap(l, r);
			assert(
				seg.query(l, r)
				==
				accumulate(a.begin() + l, a.begin() + r, 0ll)
			);
		}
	}
}

int main() {
	test(1000);
	test(1);
}
