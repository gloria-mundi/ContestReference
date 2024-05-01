#include "lazyPropagation.tmp.cpp"

void test(int n) {
#ifndef SEGTREE_INIT_DEFAULT
	vector<ll> a(n);
	for (ll &x: a) x = util::randint();
	SegTree seg(a);
#else
	ll init = util::randint();
# ifdef SEGTREE_FIRST_NEG
	init = abs(init);
# endif
	vector<ll> a(n, init);
	SegTree seg(n, init);
#endif
	for (int i = 0; i < 5*n; i++) {
		{
			int l = util::randint(n+1);
			int r = util::randint(n+1);
			if (l > r) swap(l, r);
			ll v = util::randint();
#ifndef SEGTREE_FIRST_NEG
# ifndef SEGTREE_MAX
			if (v == 0) v = 1;
# endif
#endif
			for (int j = l; j < r; j++) {
#ifndef SEGTREE_MAX
				a[j] = v;
#else
				a[j] += v;
#endif
			}
			seg.update(l, r, v);
		}
		{
			int l = util::randint(n+1);
			int r = util::randint(n+1);
			if (l > r) swap(l, r);
#ifndef SEGTREE_FIRST_NEG
# ifndef SEGTREE_MAX
			ll comp = 0;
# else
			ll comp = numeric_limits<ll>::min();
# endif
#else
			ll comp = numeric_limits<ll>::max();
#endif
			for (int j = l; j < r; j++) {
#ifndef SEGTREE_FIRST_NEG
# ifndef SEGTREE_MAX
				comp += a[j];
# else
				comp = max(comp, a[j]);
# endif
#else
				if (comp >= 0 && comp > a[j]) comp = a[j];
#endif
			}
			assert(seg.query(l, r) == comp);
		}
#ifdef SEGTREE_MAX
		{
			int l = util::randint(n+1);
			int r = util::randint(n+1);
			if (l > r) swap(l, r);
			ll bound = util::randint();
			int found = -1;
			for (int j = l; j < r; j++) {
				if (a[j] >= bound) {
					found = j;
					break;
				}
			}
			assert(seg.lower_bound(l, r, bound) == found);
		}
#endif
	}
}

int main() {
	test(1000);
	test(1);
	{
#ifndef SEGTREE_INIT_DEFAULT
		vector<ll> a;
		SegTree seg(a);
#else
		SegTree seg(0);
#endif
		seg.update(0, 0, util::randint());
#ifndef SEGTREE_FIRST_NEG
# ifndef SEGTREE_MAX
		assert(seg.query(0, 0) == 0);
# else
		assert(seg.query(0, 0) == numeric_limits<ll>::min());
# endif
#else
		assert(seg.query(0, 0) == numeric_limits<ll>::max());
#endif
	}
}
