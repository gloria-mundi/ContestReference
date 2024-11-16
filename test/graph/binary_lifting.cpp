#include "../util.h"
#include <graph/binary_lifting.cpp>
namespace expected {
#include <graph/hld.cpp>
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 200'000; tries++) {
		int n = Random::integer<int>(2, 30);
		Graph<NoData> g(n);
		g.tree();

		vector<vector<int>> adj(n);
		g.forEdges([&](int a, int b){
			adj[a].push_back(b);
			adj[b].push_back(a);
		});

		Lift lift(adj, 0);

		expected::adj = adj;
		expected::init();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= i; j++) {
				auto got = lift.lca(i, j);
				auto expected = expected::get_lca(i, j);
				if (got != expected) cerr << "got: " << got  << ", expected: " << expected << FAIL;
			}
		}
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.tree();
	vector<vector<int>> adj(N);
	g.forEdges([&](int a, int b){
		adj[a].push_back(b);
		adj[b].push_back(a);
	});

	hash_t hash = 0;
	t.start();
	Lift lift(adj, 0);
	for (int i = 1; i < N; i++) hash += lift.lca(i-1, i);
	t.stop();
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
