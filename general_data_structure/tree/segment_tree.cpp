#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 10001;
int arr[maxn], tree[maxn << 2];

int pushup(int k)
{
    tree[k] = max(tree[k * 2 + 1], tree[k * 2 + 2]);
}

void build(int k, int l, int r)
{
    if (l == r)
    {
        cout << l << " " << r << " " << k << endl;
        tree[k] = arr[l];
        return;
    }
    else
    {
        int m = (l + r) >> 1;
        build((k << 1) + 1, l, m);
        build((k << 1) + 2, m + 1, r);
        pushup(k);
    }
}

int query(int k, int l, int r, int left, int right)
{
    if (l > right || r < left)
    {
        return -1;
    }
    if (l >= left && r <= right)
    {
        return tree[k];
    }

    int mid = (l + r) / 2;

    return max(query(k * 2 + 1, l, mid, left, right), query(k * 2 + 2, mid + 1, r, left, right));
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    build(0, 0, n - 1);
    cout << query(0, 0, 4, 0, 4) << query(0, 0, 4, 0, 1) << query(0, 0, 4, 0, 2) << endl;
    return 0;
}