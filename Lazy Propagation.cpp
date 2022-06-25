#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void build(ll arr[], ll tree[], ll s, ll e, ll tn)
{
    if (s == e)
    {
        tree[tn] = arr[s];
        return;
    }
    ll mid = (s + e) / 2;
    build(arr, tree, s, mid, 2 * tn);
    build(arr, tree, mid + 1, e, (2 * tn) + 1);
    tree[tn] = tree[2 * tn] + tree[(2 * tn) + 1];
}

ll query(ll arr[], ll tree[], ll s, ll e, ll tn, ll l, ll r, ll lazy[])
{
    if (lazy[tn] != 0)
    {
        ll x = lazy[tn];
        lazy[tn] = 0;
        tree[tn] += x * (e - s + 1);
        if (s != e)
        {
            lazy[2 * tn] += x;
            lazy[(2 * tn) + 1] += x;
        }
    }

    ll mid = (s + e) / 2;
    // out
    if (s > r || l > e)
    {
        return 0;
    }
    // in
    if (s >= l && r >= e)
    {
        return tree[tn];
    }

    ll ans1 = query(arr, tree, s, mid, 2 * tn, l, r, lazy);
    ll ans2 = query(arr, tree, mid + 1, e, (2 * tn) + 1, l, r, lazy);
    return ans1 + ans2;
}

void update(ll arr[], ll tree[], ll s, ll e, ll tn, ll l, ll r, ll val, ll lazy[])
{
    if (lazy[tn] != 0)
    {
        ll x = lazy[tn];
        lazy[tn] = 0;
        tree[tn] += x * (e - s + 1);
        if (s != e)
        {
            lazy[2 * tn] += x;
            lazy[(2 * tn) + 1] += x;
        }
    }

    // out
    if (s > r || l > e)
    {
        return;
    }
    // in
    if (s >= l && r >= e)
    {
        // insert in lazy
        tree[tn] += val * (e - s + 1);
        if (s != e)
        {
            lazy[2 * tn] += val;
            lazy[(2 * tn) + 1] += val;
        }
        return;
    }

    ll mid = (s + e) / 2;
    update(arr, tree, mid + 1, e, (2 * tn) + 1, l, r, val, lazy);
    update(arr, tree, s, mid, 2 * tn, l, r, val, lazy);
    tree[tn] = tree[2 * tn] + tree[(2 * tn) + 1];
}