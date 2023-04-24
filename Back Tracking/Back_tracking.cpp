#include <bits/stdc++.h>

using namespace std;

const int maxN = 100;
const int maxK = 10;

int N, K;
int d[maxN], t[maxN][maxN];

/*
X: lưu trữ thứ tự di chuyển lần lượt bởi các nhân viên 1, 2, ..., K
Ví dụ: 
    Nếu thứ tự di chuyển của nhân viên 1 là [0, 1, 2, 0]; nhân viên 2 là [0, 3, 4, 0] và nhân viên 3 là [0, 5, 6, 0]
    thì X = [0, 1, 2, 0, 3, 4, 0, 5, 6, 0]
X_best: lưu trữ tổ hợp tối ưu của bài toán
*/
int X[maxN], X_best[maxN]; 
vector<int> X_min[maxK];  // lưu tổ hợp của từng nhân viên trong trường hợp tối ưu
bool is_visited[maxN];  // is_visited[i] = true khi khách hàng i đã được bảo trì
int cost[maxN], num_0 = 0;
/*
cost[i]: lưu trữ giá trị tổng thời gian làm việc của nhân viên đang ở vị trí X[i]
Ví dụ:
Nếu cấu hình X hiện tại đang gán đến i = 5 là [0, 2, 5, 0, 1, 4]
--> nhân viên 2 đang ở vị trí X[5] = 4 
--> cost[5] sẽ lưu trữ tổng thời gian làm việc hiện tại của nhân viên 2
--> cost[5] = t[0][1] + t[1][4] = 140
Ta có:
Trong quá trình gán các giá trị cho X[i]
    Trường hợp X[i] != 0
        cost[i] = cost[i-1] + t[X[i-1]][X[i]] (1)
        nếu cost[i] >= ans, ta sẽ thực hiện cắt nhánh
    Trường hợp X[i] = 0: vừa biểu diễn 1 nhân viên j đã hoàn thành công việc và trở về 0, và nhân viên j + 1 bắt đầu công việc
        Ta sẽ tính cost[i] theo CT (1), khi này cost[i] là thời gian làm việc của nhân viên j
        Nếu cost[i] > ans --> thực hiện cắt nhánh
        Ngược lại, gán cost[i] = 0 và tiếp tục thực hiện gán cho giá trị tiếp theo
*/
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
    int dis = 0, max_dis = 0;
    for(int i = 1; i <= N + K; i++)
    {
        dis = dis + t[X[i-1]][X[i]];
        if(X[i] == 0)
        {
            max_dis = max(max_dis, dis);
            dis = 0; 
        }
    }

    if(max_dis < ans)
    {
        for(int i = 0; i <= N + K; i++)
        {
            X_best[i] = X[i];
        }
        ans = max_dis;
    }

    
    for(int i = 0; i <= N + K; i++)
        cout << X[i] << " ";
    cout << " --> max_dis = " << max_dis << " --> ans = " << ans << " -->num_0 = " << num_0 << endl;
      
}

void Try(int k)
{
    for(int v = 0; v <= N; v++)
    {
        if(!is_visited[v] || v == 0)
        {
            X[k] = v;
            is_visited[v] = true;
            cost[k] = cost[k-1] + t[X[k-1]][v];
            if(cost[k] < ans)
            {
                if(v == 0)
                {
                    num_0++;
                    cost[k] = 0;
                    if(k == N + K)               
                        solve();
                    else if(num_0 < K)
                        Try(k+1);
                }
                else   
                    if(k < N + K)
                        Try(k+1);

                if(v == 0)
                    num_0--;
            }
            is_visited[v] = false;
        }
            
    }
}


void output() {
    int k = 0;
    for(int i = 0; i <= N + K; i++)
    {
        X_min[k].push_back(X_best[i]); 
        if(X_best[i] == 0)
        {
            k++;
            X_min[k].push_back(X_best[i]);
        }
    }
    cout << endl << "---------------Output----------------" << endl;
    cout << "So nhan vien lam viec la: " << K << endl;
    for(int i = 1; i <= K; i++)
    {
        cout << "-----------------" << endl;
        cout << "NV_" << i << endl << X_min[i].size() << endl;
        for(auto j: X_min[i])
            cout << j << " ";
        cout << endl;
    }
    cout << "-----------------" << endl;
    cout << "Thoi gian lam viec nhieu nhat cua mot nhan vien la " << ans << " s" << endl;
    cout << "-----------------" << endl;
}

int main() {
    init();
    Try(1);
    output();
}