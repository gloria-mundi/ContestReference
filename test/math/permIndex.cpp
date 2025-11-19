#include "../util.h"
#include <math/permIndex.cpp>

void stress_test(int LIM) {
	ll queries = 0;
	for (int i = 0; i < LIM; i++) {
		int n = Random::integer<int>(1, 100);
		vector<ll> cur(n);
		iota(begin(cur), end(cur), 0);
		ll expected = 0;
		do {
			auto got = permIndex(cur);
			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
			expected++;
		} while (expected < 100 && ranges::next_permutation(cur).found);
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 500'000;
void performance_test() {
	timer t;
	vector<ll> cur(N);
	iota(begin(cur), end(cur), 0);
	reverse(cur.end() - 10, cur.end());
	t.start();
	auto hash = permIndex(cur);
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(1'000);
	if (!sanitize) stress_test(10'000);
	if (!sanitize) performance_test();
}

