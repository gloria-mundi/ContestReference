ll kruskal(int n, vector<Edge> edges, vector<Edge> &mst) {
	ranges::sort(edges, less{});
	ll cost = 0;
	UnionFind uf(n); // union find @\sourceref{datastructures/unionFind.cpp}@
	for (Edge &e: edges) {
		if (uf.link(e.from, e.to)) {
			mst.push_back(e);
			cost += e.cost;
	}}
	return cost;
}
