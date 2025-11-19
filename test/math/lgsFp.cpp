#include "../util.h"
#include <math/shortModInv.cpp>
constexpr ll mod = 1'000'000'007;
namespace lgs {
	#include <math/lgsFp.cpp>
}


vector<vector<ll>> inverseMat(const vector<vector<ll>>& m) {
	int n = ssize(m);
	vector<vector<ll>> mat = m;
	for (int i = 0; i < n; i++) {
		if (ssize(mat[i]) != n) cerr << "error: no square matrix" << FAIL;
		mat[i].resize(2*n);
		mat[i][n+i] = 1;
	}
	vector<int> pivots = lgs::gauss(mat);
	for (int i = 0; i < n; i++) {
		if (pivots[i] != i) cerr << "error: not full rank?" << FAIL;
		mat[i].erase(begin(mat[i]), begin(mat[i]) + n);
	}
	return mat;
}

vector<vector<ll>> mul(const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
	int n = ssize(a);
	int m = ssize(b[0]);
	int x = ssize(b);
	if (ssize(a[0]) != ssize(b)) cerr << "error: wrong dimensions" << FAIL;
	vector<vector<ll>> res(n, vector<ll>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < x; k++) {
				res[i][j] += a[i][k] * b[k][j];
				res[i][j] %= mod;
			}
		}
	}
	return res;
}

//this should just not crash...
void test_square() {
	ll queries = 0;
	hash_t hash = 0;
	for (int tries = 0; tries < 1'000; tries++) {
		int n = Random::integer<int>(1, 30);

		vector<vector<ll>> m(n);
		for (auto& v : m) v = Random::integers<ll>(n, 0, mod);
		lgs::gauss(m);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				hash += m[i][j];
			}
		}

		queries += n;
	}
	cerr << "tested squares: " << queries << " (hash: " << hash << ")" << endl;;
}

void stress_test_inv() {
	ll queries = 0;
	for (int tries = 0; tries < 20'000; tries++) {
		int n = Random::integer<int>(1, 30);

		vector<vector<ll>> m(n);
		for (auto& v : m) v = Random::integers<ll>(n, 0, mod);
		// m hopefully has full rank...

		auto inv = inverseMat(m);

		auto prod = mul(m, inv);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (prod[i][j] != (i == j)) cerr << "error: not inverted" << FAIL;
			}
		}

		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 250;
void performance_test() {
	timer t;

	vector<vector<ll>> m(N);
	for (auto& v : m) v = Random::integers<ll>(N, 0, mod);

	t.start();
	lgs::gauss(m);
	t.stop();
	hash_t hash = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			hash += m[i][j];
		}
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	test_square();
	stress_test_inv();
	if (!sanitize) performance_test();
}
