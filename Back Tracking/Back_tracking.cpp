#include <bits/stdc++.h>

using namespace std;

const int maxN = 100;
const int maxK = 10;

int N, K;
int d[maxN], t[maxN][maxN];
int X[maxN];
vector<int> X_min[maxK];
bool is_visited[maxN];
int ans = INT_MAX;

void init() {
    cin >> N >> K;
    for(int i = 1; i <= N; i++)
        cin >> d[i];

    for(int i = 0; i <= N; i++)
        for(int j = 0; j <= N; j++)
        {
            cin >> t[i][j];
            t[i][j] = t[i][j] + d[j];
        }
}

void solve() {
    if(X[N + K] != 0)
        return;
           
    int num_0 = 0;
    int dis = 0, max_dis = 0;
    for(int i = 1; i <= N + K; i++)
    {
        if(X[i] == 0 && X[i-1] == 0)
            return;
        dis = dis + t[X[i-1]][X[i]];
        if(X[i] == 0)
        {
            num_0++;
            max_dis = max(max_dis, dis);
            dis = 0; 
        }
    }
    if(num_0 == K && max_dis < ans)
    {
        ans = max_dis;
        int k = 0;
        for(int i = 0; i <= N + K; i++)
        {
            X_min[k].push_back(X[i]); 
            if(X[i] == 0)
            {
                k++;
                X_min[k].clear();
                X_min[k].push_back(X[i]);
            }
        }
}
}

void Try(int k)
{
    for(int v = 0; v <= N; v++)
    {
        if(!is_visited[v] || v == 0)
        {
            X[k] = v;
            is_visited[v] = true;
            if(k == N + K)
                solve();
            else
                Try(k+1);
            is_visited[v] = false;
        }
    }
}

void output() {
    cout << K << endl;
    for(int i = 1; i <= K; i++)
    {
        cout << X_min[i].size() << endl;
        for(auto j: X_min[i])
            cout << j << " ";
        cout << endl;
    }
    cout << "Nhan vien lam viec nhieu nhat het " << ans << " s" << endl;
}

int main() {
    init();
    Try(1);
    output();
}