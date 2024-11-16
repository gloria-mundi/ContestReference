string lcss(const string& a, const string& b) {
	vector<vector<int>> m(ssize(a) + 1, vector<int>(ssize(b) + 1));
	for (int i = ssize(a) - 1; i >= 0; i--) {
		for (int j = ssize(b) - 1; j >= 0; j--) {
			if (a[i] == b[j]) m[i][j] = 1 + m[i+1][j+1];
			else m[i][j] = max(m[i+1][j], m[i][j+1]);
	}} // Für die Länge: return m[0][0];
	string res;
	for (int j = 0, i = 0; j < ssize(b) && i < ssize(a);) {
		if (a[i] == b[j]) res += a[i++], j++;
		else if (m[i][j+1] > m[i+1][j]) j++;
		else i++;
	}
	return res;
}
