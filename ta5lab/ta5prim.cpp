#include <iostream>
#include <cstring>
using namespace std;
#define INF 9999999
#define V 8 // 8 вершин для 14 варіанта

// Матриця графної суміжності
int G[V][V] = {
    {0,   2,   7,   5,   INF, INF, 10,  INF},
    {2,   0,   INF, INF, 9,   INF, INF, INF},
    {7,   INF, 0,   INF, INF, 5,   9,   INF},
    {5,   INF, INF, 0,   6,   4,   4,   INF},
    {INF, 9,   INF, 6,   0,   3,   INF, 3},
    {INF, INF, 5,   4,   3,   0,   INF, 1},
    {10,  INF, 9,   4,   INF, INF, 0,   6},
    {INF, INF, INF, INF, 3,   1,   6,   0}
};

int main() {
    int selected[V];
    memset(selected, false, sizeof(selected));
    int no_edge = 0;
    int total = 0;
    selected[0] = true;
    cout << "Edge : Weight" << endl;
    while (no_edge < V - 1) {
        int min = INF;
        int x = 0, y = 0;
        for (int i = 0; i < V; i++) {
            if (selected[i]) {
                for (int j = 0; j < V; j++) {
                    if (!selected[j] && G[i][j] != INF && G[i][j] != 0) {
                        if (min > G[i][j]) {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        cout << (x + 1) << " - " << (y + 1) << " : " << G[x][y] << endl;
        total += G[x][y];
        selected[y] = true;
        no_edge++;
    }
    cout << "Total weight = " << total << endl;
    return 0;
}
