using Dist = ll;

auto dijkstra(vector<vector<pair<int, Dist>>> &adj, int start) {
	priority_queue<pair<Dist, int>> pq;
	vector<Dist> dist(ssize(adj), INF);
	dist[start] = 0, pq.emplace(0, start);

	while (!empty(pq)) {
		auto [du, u] = pq.top();
		du = -du, pq.pop();
		if (du > dist[u]) continue; // WICHTIG!

		for (auto [v, d]: adj[u]) {
			Dist dv = du + d;
			if (dv < dist[v]) dist[v] = dv, pq.emplace(-dv, v);
	}}
	return dist;
}
