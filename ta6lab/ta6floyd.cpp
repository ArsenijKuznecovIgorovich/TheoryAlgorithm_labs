#include <iostream>
#include <iomanip>
using namespace std;
#define INF 1000000000
#define V 8 // 8 вершин для 14 варіанта

int D[V][V];

void printMatrix(const char* title) {
    cout << title << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (D[i][j] >= INF) cout << setw(4) << "INF";
            else cout << setw(4) << D[i][j];
        }
        cout << endl;
    }
}

void addEdge(int u, int v, int w) { // вершини 1..8 -> індекси 0..7
    D[u - 1][v - 1] = w;
    D[v - 1][u - 1] = w;
}

int main() {
    // D(0) = W: вагова матриця
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            D[i][j] = (i == j) ? 0 : INF;
    addEdge(1, 2, 2);  addEdge(1, 3, 7);  addEdge(1, 4, 5);  addEdge(1, 7, 10);
    addEdge(2, 5, 9);  addEdge(3, 6, 5);  addEdge(3, 7, 9);  addEdge(4, 5, 6);
    addEdge(4, 6, 4);  addEdge(4, 7, 4);  addEdge(5, 6, 3);  addEdge(5, 8, 3);
    addEdge(6, 8, 1);  addEdge(7, 8, 6);

    printMatrix("D(0) = W:");
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (D[i][k] < INF && D[k][j] < INF && D[i][k] + D[k][j] < D[i][j])
                    D[i][j] = D[i][k] + D[k][j];
        if (k == 7) printMatrix("D(8) = distance matrix:");
    }
    return 0;
}
