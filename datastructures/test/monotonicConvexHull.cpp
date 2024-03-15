#include "../monotonicConvexHull.cpp"

int main() {
	{
		Envelope env;
		env.add(10, 0);
		assert(env.query(0) == 0);
		assert(env.query(1) == 10);
		env.add(8, 5);
		assert(env.query(1) == 10);
		assert(env.query(2) == 20);
		assert(env.query(3) == 29);
		env.add(7, 10);
		assert(env.query(10) == 80);
		env.add(0, 0);
		assert(env.query(11) == 0);
	}

	{
		Envelope env;
		env.add(1, 0);
		env.add(0, 10);
		env.add(-1, 10);
		assert(env.query(7) == 3);
	}
}
