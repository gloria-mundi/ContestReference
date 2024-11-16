// Laufzeit: O(n*log(n))
ll merge(vector<ll>& v, vector<ll>& left, vector<ll>& right) {
	int a = 0, b = 0, i = 0;
	ll inv = 0;
	while (a < ssize(left) && b < ssize(right)) {
		if (left[a] < right[b]) v[i++] = left[a++];
		else {
			inv += ssize(left) - a;
			v[i++] = right[b++];
		}
	}
	while (a < ssize(left)) v[i++] = left[a++];
	while (b < ssize(right)) v[i++] = right[b++];
	return inv;
}

ll mergeSort(vector<ll> &v) { // Sortiert v und gibt Inversionszahl zurück.
	int n = ssize(v);
	vector<ll> left(n / 2), right((n + 1) / 2);
	for (int i = 0; i < n / 2; i++) left[i] = v[i];
	for (int i = n / 2; i < n; i++) right[i - n / 2] = v[i];

	ll result = 0;
	if (ssize(left) > 1) result += mergeSort(left);
	if (ssize(right) > 1) result += mergeSort(right);
	return result + merge(v, left, right);
}
