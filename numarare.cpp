#include <fstream>
#include <iostream>
#include <list>
using namespace std;

int MOD = 1000000007;
list<int> *graph1;
list<int> *graph2;
int *num_paths;
int n, m;

bool has_edge(list<int> *graph, int src, int dst) {
    for (int neigh : graph[src]) {
        if (neigh == dst) return true;
    }
    return false;
}

int dfs(int crt) {
    if (crt == n) {
        return 1;
    }
    if (num_paths[crt] != 0) {
        return num_paths[crt];
    }

    for (int neigh : graph1[crt]) {
        if (has_edge(graph2, crt, neigh)) {
                num_paths[crt] += dfs(neigh);
                num_paths[crt] = num_paths[crt] % MOD;
        }
    }
    return num_paths[crt];
}

int main() {
    ifstream INPUT("numarare.in");
    ofstream OUTPUT("numarare.out");
    INPUT >> n;
    INPUT >> m;

    graph1 = new list<int>[n+1];
    graph2 = new list<int>[n+1];
    num_paths = new int[n+1];
    for (int i = 0; i <= n; i++) num_paths[i] = 0;
    num_paths[n] = 1;

    int src, dst;
    for (int i = 0; i < m; i++) {
        INPUT >> src >> dst;
        graph1[src].push_back(dst);
    }
    for (int i = 0; i < m; i++) {
        INPUT >> src >> dst;
        graph2[src].push_back(dst);
    }

    int res = dfs(1);

    OUTPUT << res << '\n';

    INPUT.close();
    OUTPUT.close();
    return 0;
}
