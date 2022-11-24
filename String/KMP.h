vector<int> kmpPreprocess(string p) {
    int m = p.length();
    vector<int> pref(m, 0);

    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && p[j] != p[i])
            j = pref[j - 1];
        if (p[i] == p[j])
            j++;
        pref[i] = j;
    }

    return pref;
}

vector<int> kmpSearch(string t, string p, const vector<int>& pref) {
    int n = t.length(), m = p.length();
    vector<int> found;

    int i, j = 0;
    for (i = 0; i < n; i++) {
        while (j > 0 && t[i] != p[j])
            j = pref[j - 1];
        if (t[i] == p[j])
            j++;
        if (j == m) {
            found.push_back(i - m + 1);
            j = pref[j - 1];
        }
    }

    return found;
}