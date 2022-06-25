#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void buildtree(ll arr[], ll tree[], ll start, ll end, ll treenode)
{
    int mid = (start + end) / 2;
    if (start == end)
    {
        tree[treenode] = arr[start];
        return;
    }
    buildtree(arr, tree, start, mid, 2 * treenode);
    buildtree(arr, tree, mid + 1, end, 2 * treenode + 1);
    tree[treenode] = tree[treenode * 2] + tree[(treenode * 2) + 1];
}

void update(ll arr[], ll tree[], ll s, ll e, ll tn, ll idx, ll val)
{
    if (s == e)
    {
        arr[idx] = val;
        tree[tn] = val;
        return;
    }
    ll mid = (s + e) / 2;
    if (mid >= idx)
    {
        // go left
        update(arr, tree, s, mid, 2 * tn, idx, val);
    }
    else
    {
        update(arr, tree, mid + 1, e, (2 * tn) + 1, idx, val);
    }
    tree[tn] = tree[2 * tn] + tree[(2 * tn) + 1];
}

ll query(ll arr[], ll tree[], ll s, ll e, ll tn, ll left, ll right)
{
    ll mid = (s + e) / 2;
    //  out
    if (s > right || left > e)
    {
        return 0;
    }
    // in
    if (s >= left && e <= right)
    {
        return tree[tn];
    }
    // half in half out
    ll ans1 = query(arr, tree, s, mid, 2 * tn, left, right);
    ll ans2 = query(arr, tree, mid + 1, e, 2 * tn + 1, left, right);
    return ans1 + ans2;
}
