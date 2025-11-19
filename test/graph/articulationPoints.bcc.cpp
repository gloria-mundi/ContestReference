#include "../util.h"
struct edge {
	ll from, to, id;
};
#define Edge edge
#include <graph/articulationPoints.cpp>
#undef Edge
#include <datastructures/unionFind.cpp>

vector<vector<int>> naiveBCC(int m) {
	UnionFind uf(m);

	vector<int> seen(ssize(adj), -1);
	int run = 0;
	for (int i = 0; i < ssize(adj); i++) {
		for (auto e : adj[i]) {
			run++;
			seen[i] = run;
			vector<ll> todo = {e.to};
			seen[e.to] = run;
			while (!todo.empty()) {
				int c = todo.back();
				todo.pop_back();
				for (auto ee : adj[c]) {
					if (seen[ee.to] == run) continue;
					seen[ee.to] = run;
					todo.push_back(ee.to);
				}
			}
			for (auto ee : adj[i]) {
				if (seen[ee.to] == run) uf.link(ee.id, e.id);
			}
		}
	}
	vector<vector<int>> res(m);
	for (int i = 0; i < m; i++) {
		res[uf.find(i)].push_back(i);
	}
	for (auto& v : res) ranges::sort(v);
	res.erase(begin(ranges::remove_if(res, [](const vector<int>& v){return ssize(v) <= 1;})), end(res));
	ranges::sort(res);
	return res;
}

void stress_test_bcc(int LIM) {
	ll queries = 0;
	for (int tries = 0; tries < LIM; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(0, max<int>(1, min<int>(300, n*(n-1) / 2 + 1)));
		Graph<NoData, 0, 1> g(n);
		g.erdosRenyi(m);

		adj.assign(n, {});
		int nextId = 0;
		g.forEdges([&](int a, int b){
			adj[a].push_back({a, b, nextId});
			adj[b].push_back({b, a, nextId});
			nextId++;
		});

		auto expected = naiveBCC(nextId);
		find();
		vector<vector<int>> got(ssize(bcc));
		for (int i = 0; i < ssize(bcc); i++) {
			for (auto e : bcc[i]) got[i].push_back(e.id);
			ranges::sort(got[i]);
		}
		ranges::sort(got);

		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

int main() {
	stress_test_bcc(20'000);
	if (!sanitize) stress_test_bcc(200'000);
}
