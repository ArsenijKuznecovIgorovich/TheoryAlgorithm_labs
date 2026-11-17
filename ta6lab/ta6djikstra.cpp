#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INF 1000000000
#define V 8 // 8 вершин для 14 варіанта

// Список суміжності: adj[u] = {(v, вага)}, вершини нумеруються 1..8
vector<pair<int,int>> adj[V + 1];

void addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void dijkstra(int s, vector<int>& dist, vector<int>& pred) {
    dist.assign(V + 1, INF);
    pred.assign(V + 1, -1);
    dist[s] = 0;
    // черга з пріоритетами: (відстань, вершина), мінімум нагорі
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(0, s));
    vector<bool> done(V + 1, false);
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (done[u]) continue;          // застарілий запис черги
        done[u] = true;
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first, w = adj[u][i].second;
            if (dist[v] > dist[u] + w) { // релаксація ребра
                dist[v] = dist[u] + w;
                pred[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

int main() {
    addEdge(1, 2, 2);  addEdge(1, 3, 7);  addEdge(1, 4, 5);  addEdge(1, 7, 10);
    addEdge(2, 5, 9);  addEdge(3, 6, 5);  addEdge(3, 7, 9);  addEdge(4, 5, 6);
    addEdge(4, 6, 4);  addEdge(4, 7, 4);  addEdge(5, 6, 3);  addEdge(5, 8, 3);
    addEdge(6, 8, 1);  addEdge(7, 8, 6);

    int s = 1;
    vector<int> dist, pred;
    dijkstra(s, dist, pred);

    cout << "Vertex : Dist : Path" << endl;
    for (int t = 1; t <= V; t++) {
        vector<int> path;
        for (int x = t; x != -1; x = pred[x]) path.push_back(x);
        reverse(path.begin(), path.end());
        cout << s << " -> " << t << " : " << dist[t] << " : ";
        for (size_t i = 0; i < path.size(); i++)
            cout << path[i] << (i + 1 < path.size() ? "->" : "");
        cout << endl;
    }
    return 0;
}
