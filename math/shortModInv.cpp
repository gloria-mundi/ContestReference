ll multInv(ll a, ll b){ // a^{-1} mod b
    return 1 < a ? b - multInv(b % a, a) * b / a : 1;
}
