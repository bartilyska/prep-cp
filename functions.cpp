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


class TrieNode {
public:
    TrieNode* children[26];
    bool isEnd;

    TrieNode() : isEnd(false) {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() 
    {
        root = new TrieNode();
    }
    void insert(string& word)
    {
        TrieNode* node = root;
        for (char litera : word) 
        {
            int index = litera - 'a';
            if (node->children[index] == nullptr)
            {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEnd = true;
    }
    
    bool search(string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return node->isEnd;
    }
    
    bool startsWith(string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }
};

class DSU {
private:
    vector<int> parent;
    vector<int> size; // Size of each set

public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1); // Initial size of each set is 1
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Initially, each element is its own set
        }
    }

    void make_set(int v) {
        parent[v] = v;
        size[v] = 1; // Single element set
    }

    int find_set(int v) {
        if (v != parent[v]) {
            parent[v] = find_set(parent[v]); // Path compression
        }
        return parent[v];
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            // Union by size
            if (size[a] < size[b]) {
                parent[a] = b;
                size[b] += size[a]; // Update size of new root
            } else {
                parent[b] = a;
                size[a] += size[b]; // Update size of new root
            }
        }
    }

    bool are_connected(int a, int b) {
        return find_set(a) == find_set(b);
    }

    // Method to get the size of the set containing element `v`
    int get_size(int v) {
        int root = find_set(v);
        return size[root]; // Return the size of the set's root
    }
};

class SegmentTree {
    vector<int> tree;
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
        tree[treeIndex] = tree[2 * treeIndex + 1] + tree[2 * treeIndex + 2];//tu zmieniac(jak inna operacja niz suma)
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
    void wypisz(){
        for (int i = 0; i < 4 * size; i++)
        {
            cout << tree[i] << endl;
        }
    }
};

const int mod=1e9+7;
class Combinatorics
{
private:
    int n;
    vector<long long int>  silnia,inv;
public:
    Combinatorics(int m)
    {
        n=m;
        silnia.resize(m);
        inv.resize(m);
    }
    long long int C(int n, int k)
    {
        if (k > n) return 0;
        return ((((silnia[n] * inv[k]) % mod) * inv[n - k]) % mod);
    }
    void wypelnijSilnieModulo()
    {
        silnia[0] = 1;
        for ( int i = 1; i < n ; i++)
        {
            silnia[i] = (silnia[i - 1] * i) % mod;
        }
    }
    void wypelnijInvModulo()
    {
        inv[n - 1] = szybkapotega(silnia[n - 1], mod - 2);
        for ( int i = n - 2; i >= 0; i--) 
        {
            inv[i] = (inv[i + 1] * (i + 1)) % mod;
        }
    }
    long long int szybkapotega(long long int a, long long int b)
    {
        long long int odp = 1;
        while (b >= 1)
        {
            if (b % 2 == 1)
                odp = (odp * a) % mod;
            b = b / 2;
            a = (a * a) % mod;
        }
        return odp;
    }
};

const int N = 100;//moze byc 10^7
void generujpierwsze()
{
    vector<int> lp(N+1);
    vector<int> pr; //wektor do trzymania liczb pierwszych
    for (int i=2; i <= N; i++) 
    {
        if (lp[i] == 0) 
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

//Z-function do znajdowania ilosci wystapien slowa w innym slowie
vector<int>calculateZ(string &s)
{
    int l=0,r=0;
    int n=s.length();
    vector<int>z(n);
    for(int i=1;i<n;i++)
    {
        if(i>r){
            //i is outside the current [l, r] interval
            l=r=i;
            while(r<n && s[r]==s[r-l])
                r++;
            z[i]=r-l;
            r--;
        }
        else{
            //i is inside the current [l, r] interval
            int rel_ind=i-l;
            if(z[rel_ind]+i<=r)
                z[i]=z[rel_ind];
            else{
                l=i;
                while(r<n && s[r]==s[r-l])
                    r++;
                z[i]=r-l;
                r--;
            }
        }
    }
    return z;
}

vector<int> findAllOccurrences(const string &pattern, const string &text) {
    string combined = pattern + "$" + text; //dolar nie moze byc uzywany w tych slowach
    vector<int> z = calculateZ(combined);
    vector<int> result;
    int m = pattern.length();
    //znaleziono pattern gdy z[i] == m do wektora wrzucane indeksy poczatkow tych slow od 0
    for (int i = m + 1; i < z.size(); ++i) {
        if (z[i] == m) {
            result.push_back(i - m - 1);
        }
    }
}

void solve()
{
    //vector<int>v(10);
    //for(int i=0;i<10;i++)
    //{
    //    v[i]=i+1;
    //}
    //SegmentTree seg(v);
    //seg.wypisz();
    //DSU dsu(100);
    //Combinatorics comb(100);
    //comb.wypelnijSilnieModulo();
    //comb.wypelnijInvModulo();
    //int n = 65, k = 40;
    //long long result = comb.C(n, k);
    //cout<<result<<endl;
    //generujpierwsze();
    findAllOccurrences("ab","ababcab");
}
int main()
{
    //int t;
    //cin>>t;
    //while(t--)
    //{
        solve();
    //}
    return 0;
}