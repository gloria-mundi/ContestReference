vector<ll> res(in);
for (int i = 1; i < ssize(res); i *= 2) {
	for (int mask = 0; mask < ssize(res); mask++){
		if (mask & i) {
			res[mask] += res[mask ^ i];
}}}
