#include "../fenwickTree2.cpp"

void test(int n) {
	vector<ll> naive(n);
	for (int i = 0; i < n; i++) naive[i] = util::randint();
	init(naive);

	for (int i = 0; i < 1000; i++) {
		int l = util::randint(n), r = util::randint(n);
		if (l > r) swap(l, r);
		ll delta = util::randint();
		update(l, r, delta);
		for (int i = l; i < r; i++) naive[i] += delta;

		r = util::randint(n+1);

		ll naive_result = 0;
		for (int i = 0; i < r; i++) naive_result += naive[i];
		ll fenwick_result = prefix_sum(r);
		assert(naive_result == fenwick_result);
	}
}

int main() {
	test(1);
	test(100);
	test(1000);
}
