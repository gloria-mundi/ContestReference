template<typename T>
struct persistent {
	int& time;
	vector<pair<int, T>> data;

	persistent(int& time, T value = {})
		: time(time), data(1, {2*time, value}) {}

	T get(int t) {
		return ranges::upper_bound(data,pair{2*t+1, T{}})[-1].second;
	}

	int set(T value) {
		time++;
		data.push_back({2*time, value});
		return time;
	}
};
