constexpr ll mod = 1'000'000'007;

#include "../shortModInv.cpp"
#include "../binomial0.cpp"

int main() {
	precalc();
	assert(calc_binom(5, -1) == 0);
	assert(calc_binom(5, 0) == 1);
	assert(calc_binom(5, 1) == 5);
	assert(calc_binom(5, 2) == 10);
	assert(calc_binom(5, 3) == 10);
	assert(calc_binom(5, 4) == 5);
	assert(calc_binom(5, 5) == 1);
	assert(calc_binom(5, 6) == 0);
	assert(calc_binom(0, 0) == 1);
	assert(calc_binom(-1, 0) == 0);
	assert(calc_binom(-1, -1) == 0);
	assert(calc_binom(-1, -2) == 0);
	assert(calc_binom(100'000, 50'000) == 149033233);
}
