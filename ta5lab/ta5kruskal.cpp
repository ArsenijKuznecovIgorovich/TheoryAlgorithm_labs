#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define edge pair<int, int>

class Graph {
private:
    vector<pair<int, edge>> G; // усі ребра графа
    vector<pair<int, edge>> T; // ребра МКД
    int *parent;
    int V;
public:
    Graph(int V);
    void AddWeightedEdge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
};

Graph::Graph(int V) {
    this->V = V;
    parent = new int[V];
    for (int i = 0; i < V; i++)
        parent[i] = i;
    G.clear();
    T.clear();
}
void Graph::AddWeightedEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}
int Graph::find_set(int i) {
    if (i == parent[i])
        return i;
    return find_set(parent[i]);
}
void Graph::union_set(int u, int v) {
    int root_u = find_set(u);
    int root_v = find_set(v);
    parent[root_u] = root_v;
}
void Graph::kruskal() {
    int uRep, vRep;
    sort(G.begin(), G.end()); // за зростанням ваги
    for (int i = 0; i < (int)G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            T.push_back(G[i]);
            union_set(uRep, vRep);
        }
    }
}
void Graph::print() {
    int total = 0;
    cout << "Edge : Weight" << endl;
    for (int i = 0; i < (int)T.size(); i++) {
        cout << T[i].second.first << " - " << T[i].second.second
             << " : " << T[i].first << endl;
        total += T[i].first;
    }
    cout << "Total weight = " << total << endl;
}

int main() {
    Graph g(9);
    g.AddWeightedEdge(1, 2, 2);  g.AddWeightedEdge(1, 3, 7);
    g.AddWeightedEdge(1, 4, 5);  g.AddWeightedEdge(1, 7, 10);
    g.AddWeightedEdge(2, 5, 9);  g.AddWeightedEdge(3, 6, 5);
    g.AddWeightedEdge(3, 7, 9);  g.AddWeightedEdge(4, 5, 6);
    g.AddWeightedEdge(4, 6, 4);  g.AddWeightedEdge(4, 7, 4);
    g.AddWeightedEdge(5, 6, 3);  g.AddWeightedEdge(5, 8, 3);
    g.AddWeightedEdge(6, 8, 1);  g.AddWeightedEdge(7, 8, 6);
    g.kruskal();
    g.print();
    return 0;
}
