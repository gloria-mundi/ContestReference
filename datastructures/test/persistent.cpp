#define all(X) begin(X), end(X)
#include "../persistent.cpp"

int main() {
	int time = 0;
	persistent<int> p(time, 0);
	p.set(1);
	int t1 = time;
	p.set(2);
	assert(p.get(t1) == 1);
}
