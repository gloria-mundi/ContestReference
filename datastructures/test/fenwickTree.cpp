#include "../fenwickTree.cpp"

void test(int n) {
	vector<ll> naive(n);
	init(n);

	for (int i = 0; i < 1000; i++) {
		int p = util::randint(n);
		ll delta = util::randint();
		update(p, delta);
		naive[p] += delta;

		int r = util::randint(n+1) - 1;

		ll naive_result = 0;
		for (int i = 0; i <= r; i++) naive_result += naive[i];
		ll fenwick_result = prefix_sum(r);
		assert(naive_result == fenwick_result);
	}
}

int main() {
	test(1);
	test(100);
	test(1000);
}
