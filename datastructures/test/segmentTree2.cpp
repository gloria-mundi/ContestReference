#include "segmentTree2.tmp.cpp"

void test(int n) {
	vector<ll> a(n);
	for (ll &x: a) x = util::randint();
	SegTree seg(a);
	for (int i = 0; i < 5*n; i++) {
		{
			int l = util::randint(n+1);
			int r = util::randint(n+1);
			if (l > r) swap(l, r);
			ll v = util::randint();
			for (int i = l; i < r; i++) a[i] += v;
			seg.modify(l, r, v);
		}
		{
			int j = util::randint(n);
			assert(seg.query(j) == a[j]);
		}
	}
}

int main() {
	test(1000);
	test(1);
}
