// And or convolution

/**
* Description: Similar to FWHT
* Source: CSA - FFT And Variations
*/

typedef vector<double> vd;
typedef vector<long long> vl;
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
#define pb push_back

int get(int s) {
    return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
}

namespace andConv {
    vd andConv(vd P, bool inv = 0) {
        for (int len = 1; 2 * len <= sz(P); len <<= 1) {
            for (int i = 0; i < sz(P); i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    double u = P[i + j];
                    double v = P[i + len + j];

                    if (!inv) {
                        P[i + j] = v;
                        P[i + len + j] = u + v;
                    } else {
                        P[i + j] = -u + v;
                        P[i + len + j] = u;
                    }
                }
            }
        }

        return P;
    }

    vd conv(vd a, vd b) {
        int s = max(sz(a),sz(b)), L = get(s), n = 1<<L;
        if (s <= 0) return {};

        a.resize(n); a = andConv(a);
        b.resize(n); b = andConv(b);

        for(int i=0;i<n;i++) a[i] = a[i]*b[i];
        a = andConv(a,1);
        return a;
    }

    vd orConv(vd a, vd b) {
        int s = max(sz(a),sz(b)), L = get(s), n = 1<<L;
        if (s <= 0) return {};

        a.resize(n); reverse(all(a)); a = andConv(a);
        b.resize(n); reverse(all(b)); b = andConv(b);

        for(int i=0;i<n;i++) a[i] = a[i]*b[i];
        a = andConv(a,1);
        reverse(all(a));

        return a;
    }

    vl orConv(vl a, vl b) {
        vd A; for (auto x: a) A.pb(x);
        vd B; for (auto x: b) B.pb(x);
        vd c = orConv(A,B);
        vl C; for (auto x: c) C.pb(round(x));
        return C;
    }

    vl conv(vl a, vl b) {
        vd A; for (auto x: a) A.pb(x);
        vd B; for (auto x: b) B.pb(x);
        vd c = conv(A,B);
        vl C; for (auto x: c) C.pb(round(x));
        return C;
    }
}
