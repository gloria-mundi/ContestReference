#include "../util.h"
constexpr ll INF = LL::INF;
#include <graph/dijkstra.cpp>
struct edge {
	int from, to;
	ll cost;
};
#include <graph/bellmannFord.cpp>

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(2, 30);
		int m = Random::integer<int>(n-1, max<int>(n, min<int>(500, n*(n-1) / 2 + 1)));

		vector<vector<pair<int, ll>>> adj(n);
		vector<edge> edges;

		Graph<NoData, true> g(n);
		g.erdosRenyi(m);
		g.forEdges([&](int a, int b){
			ll w = Random::integer<ll>(1, 1'000'000'000'000ll);
			adj[a].emplace_back(b, w);
			edges.push_back({a, b, w});
		});

		for (int i = 0; i < n; i++) {
			auto got = dijkstra(adj, i);
			auto expected = bellmannFord(n, edges, i);

			if (got != expected) cerr << "error" << FAIL;
			queries += n;
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 500'000;
constexpr int M = 3'000'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.erdosRenyi(M);
	vector<vector<pair<int, ll>>> adj(N);
	g.forEdges([&](int a, int b){
		ll w1 = Random::integer<ll>(1, 1'000'000'000'000ll);
		ll w2 = Random::integer<ll>(1, 1'000'000'000'000ll);
		adj[a].emplace_back(b, w1);
		adj[b].emplace_back(a, w2);
	});

	t.start();
	auto got = dijkstra(adj, 0);
	t.stop();
	hash_t hash = 0;
	for (auto x : got) hash += x;
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
