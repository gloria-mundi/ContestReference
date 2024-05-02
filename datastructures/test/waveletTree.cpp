#include "../waveletTree.cpp"

void test(int n) {
	vector<ll> values(n);
	for (ll &x: values) x = util::randint();
	vector<ll> backup = values;
	WaveletTree wave(values);
	assert(values == backup);
	for (int i = 0; i < n; i++) {
		int l = util::randint(n+1);
		int r = util::randint(n+1);
		if (l > r) swap(l, r);
		ll bound = util::randint();
		int res = 0;
		for (ll x: values | views::take(r) | views::drop(l)) {
			if (x < bound) res++;
		}
		assert(wave.countSmaller(l, r, bound) == res);
	}
	for (int i = 0; 5*i < n; i++) {
		int l = util::randint(n);
		int m = util::randint(n);
		int r = util::randint(n);
		if (l > m) swap(l, m);
		if (m > r) swap(m, r);
		if (l > m) swap(l, m);
		r++;
		int k = m-l;
		vector<ll> part(values.begin()+l, values.begin()+r);
		ranges::nth_element(part, part.begin() + k);
		assert(wave.kth(l, r, k) == part[k]);
	}
}

int main() {
	test(1000);
	test(1);
}
