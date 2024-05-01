#ifdef SEGTREE_MUL
constexpr ll MOD = 1'000'000'007;
#endif

#include "segmentTree.tmp.cpp"

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
#ifndef SEGTREE_RANGE_UPDATE
			int j = util::randint(n);
			ll v = util::randint();
			a[j] = v;
			seg.update(j, v);
#else
			int l = util::randint(n+1);
			int r = util::randint(n+1);
			if (l > r) swap(l, r);
			ll v = util::randint();
			for (int j = l; j < r; j++) {
# ifndef SEGTREE_MUL
				a[j] += v;
# else
				a[j] = a[j]*v % MOD;
# endif
			}
			seg.modify(l, r, v);
#endif
		}
		{
#ifndef SEGTREE_RANGE_UPDATE
			int l = util::randint(n+1);
			int r = util::randint(n+1);
			if (l > r) swap(l, r);
# ifndef SEGTREE_MUL
#  ifndef SEGTREE_FIRST_NEG
			ll comp = 0;
#  else
			ll comp = numeric_limits<ll>::max();
#  endif
# else
			ll comp = 1;
# endif
			for (int j = l; j < r; j++) {
# ifndef SEGTREE_MUL
#  ifndef SEGTREE_FIRST_NEG
				comp += a[j];
#  else
				if (comp >= 0 && comp > a[j]) comp = a[j];
#  endif
# else
				comp = comp * a[j] % MOD;
# endif
			}
			assert(seg.query(l, r) == comp);
#else
			int j = util::randint(n);
			assert(seg.query(j) == a[j]);
#endif
		}
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
#ifndef SEGTREE_RANGE_UPDATE
# ifndef SEGTREE_MUL
#  ifndef SEGTREE_FIRST_NEG
		assert(seg.query(0, 0) == 0);
#  else
		assert(seg.query(0, 0) == numeric_limits<ll>::max());
#  endif
# else
		assert(seg.query(0, 0) == 1);
# endif
#else
		seg.modify(0, 0, util::randint());
#endif
	}
}
