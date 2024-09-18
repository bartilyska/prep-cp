#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <numeric>
#include <stack>
#include <limits.h>
using namespace std;
using ll = long long int;

class SegmentTree {
    vector<ll> tree;
    int size; //4 razy mniejszy niz tree size
public:
    SegmentTree(vector<int>& array) {
        size = array.size();
        tree.resize(4 * size);
        buildTree(array, 0, 0, size - 1);
    }
private:
    void buildTree(vector<int>& array, int treeIndex, int left, int right) {
        if (left == right) {
            tree[treeIndex] = array[left];
            return;
        }
        int mid = left + (right - left) / 2;
        buildTree(array, 2 * treeIndex + 1, left, mid);
        buildTree(array, 2 * treeIndex + 2, mid + 1, right);
        tree[treeIndex] = tree[2 * treeIndex + 1] + tree[2 * treeIndex + 2];//tu zmieniac
    }

    long long int query(int treeIndex, int left, int right, int queryLeft, int queryRight) {
        if (queryLeft <= left && right <= queryRight)
            return tree[treeIndex];
        if (right < queryLeft || left > queryRight)
            return 0;  
        int mid = left + (right - left) / 2;
        long long int sum = 0; // tu int max moze trzeba zmienic
        if (queryLeft <= mid)
            sum += query(2 * treeIndex + 1, left, mid, queryLeft, queryRight);//tu zmieniac
        if (queryRight > mid)
            sum += query(2 * treeIndex + 2, mid + 1, right, queryLeft, queryRight);//tu zmieniac
        return sum;
    }

    void update(int treeIndex, int left, int right, int arrayIndex, int newValue) {
        if (left == right) { 
            tree[treeIndex] = newValue;
            return;
        }
        int mid = left + (right - left) / 2;

        if (arrayIndex <= mid)
            update(2 * treeIndex + 1, left, mid, arrayIndex, newValue);
        else
            update(2 * treeIndex + 2, mid + 1, right, arrayIndex, newValue);
        tree[treeIndex] = tree[2 * treeIndex + 1] + tree[2 * treeIndex + 2];//tu zmieniac
    }

public:
    ll query(int left, int right) {
        return query(0, 0, size - 1, left, right);
    }
    //int odp = seg.query(l - 1, r - 1); do uzywania query gdy wchodzi 1-indexed
    void update(int index, int newValue) {
        update(0, 0, size - 1, index, newValue);
    }
    //seg.update(zmien-1, upd); do update gdy 1-indexed
    void wypisz()
    {
        for (int i = 0; i < 4 * size; i++)
        {
            cout << tree[i] << endl;
        }
    }
};

void solve()
{
   int n,q;
cin >> n>>q;
vector<int>v(n);
for (int i = 0; i < n; i++)
{
    cin >> v[i];
}
SegmentTree seg(v);
while (q--)
{
    int k;
    cin >> k;
    if (k == 1)
    {
        int zmien, upd;
        cin >>  zmien >> upd;
        seg.update(zmien-1, upd);
    }
    else
    {
        int l, r;
        cin >> l >> r;
        long long int odp=  seg.query(l-1, r-1);
        cout << odp << endl;
    }
}
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}