int fastSubsetSum(vector<int> w, int t){
	int a = 0, b = 0;
	while(b < ssize(w) && a + w[b] <= t) a += w[b++];
	if(b == ssize(w)) return a;
	int m = *ranges::max_element(w);
	vector<int> dp(2*m, -1), old;
	dp[m+a-t] = b;
	for(int i = b; i < ssize(w); i++){
		old = dp;
		for(int j = 0; j < m; j++){
			dp[j+w[i]] = max(dp[j+w[i]], old[j]);
		}
		for(int j = 2*m-1; j > m; j--){
			for(int k = max(old[j], 0); k < dp[j]; k++){
				dp[j-w[k]] = max(dp[j-w[k]], k);
			}
		}
	}
	for(a = t; dp[m+a-t] < 0; a--);
	return a;
}
