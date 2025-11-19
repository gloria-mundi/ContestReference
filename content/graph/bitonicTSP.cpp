vector<vector<double>> dist; // Initialisiere mit Entfernungen zwischen Punkten.

auto bitonicTSP() { // n >= 2
	vector<double> dp(ssize(dist), HUGE_VAL);
	vector<int> pre(ssize(dist)); // nur für Tour
	dp[0] = 0; dp[1] = 2 * dist[0][1]; pre[1] = 0;
	for (unsigned int i = 2; i < ssize(dist); i++) {
		double link = 0;
		for (int j = i - 2; j >= 0; j--) {
			link += dist[j + 1][j + 2];
			double opt = link + dist[j][i] + dp[j + 1] - dist[j][j + 1];
			if (opt < dp[i]) {
				dp[i] = opt;
				pre[i] = j;
	}}}
	// return dp.back(); // Länge der Tour

	int j, n = ssize(dist) - 1;
	vector<int> ut, lt = {n, n - 1};
	do {
		j = pre[n];
		(lt.back() == n ? lt : ut).push_back(j);
		for (int i = n - 1; i > j + 1; i--) {
			(lt.back() == i ? lt : ut).push_back(i - 1);
		}
	} while(n = j + 1, j > 0);
	(lt.back() == 1 ? lt : ut).push_back(0);
	ranges::reverse(lt);
	lt.insert(end(lt), begin(ut), end(ut));
	return lt; // Enthält Knoten 0 zweimal. An erster und letzter Position.
}
