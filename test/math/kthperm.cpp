#include "../util.h"
#include <math/kthperm.cpp>

void stress_test(int LIM) {
	ll queries = 0;
	for (int i = 0; i < LIM; i++) {
		int n = Random::integer<int>(1, 100);
		vector<ll> expected(n);
		iota(begin(expected), end(expected), 0);
		ll k = 0;
		do {
			auto got = kthperm(n, k);
			if (got != expected) cerr << "error" << FAIL;
			k++;
		} while (k < 100 && ranges::next_permutation(expected).found);
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 500'000;
void performance_test() {
	timer t;
	t.start();
	auto got = kthperm(N, 4'168'751'907'498'170ll);
	t.stop();
	hash_t hash = 0;
	for (ll i = 0; i < N; i++) hash += i * got[i];
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(1'000);
	if (!sanitize) stress_test(10'000);
	if (!sanitize) performance_test();
}

