// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<PT> convex_hull(vector<PT> P)
{
	int n = P.size(), k = 0;
	if (n == 1) return P;
	vector<PT> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-1]-H[k-2], P[i]-H[k-2]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-1]-H[k-2], P[i]-H[k-2]) <= 0) k--;
		H[k++] = P[i];
	}

	H.resize(k);
	return H;
}

