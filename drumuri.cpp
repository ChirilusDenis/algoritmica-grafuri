#include <fstream>
#include <iostream>
#include <list>
#include <queue>
using namespace std;



int n, m;
int x, y, z;
list<pair<int, unsigned long int>> *g;
list<pair<int, unsigned long int>> *g_i;

unsigned long long MAX = 9223372036854775807;

unsigned long long get_min(unsigned long long *dx,
                            unsigned long long *dy,
                            unsigned long long *dz) {
    unsigned long long min =  MAX;
    unsigned long long crt;

    for (int i = 1; i <= n; i++) {
        if (dx[i] == MAX || dy[i] == MAX || dz[i] == MAX) continue;

        crt = dx[i] + dy[i] + dz[i];
        if (crt < min) min = crt;
    }
    return min;
}

unsigned long long *D(int source, list<pair<int, unsigned long int>> *graph) {
    unsigned long long *dist = new unsigned long long[n + 1];
    for (int i = 1; i <= n; i++) {
        dist[i] = MAX;
    }

    auto comp = [dist](pair<int, unsigned long int> a,
                         pair<int, unsigned long int> b) -> bool{
            return dist[a.first] > dist[b.first];};

    priority_queue<pair<int, unsigned long int>,
        vector<pair<int, unsigned long int>>, decltype(comp)> pq(comp);

    dist[source] = 0;
    pq.push(pair(source, 0));

    pair<int, unsigned long int> node;
    while (!pq.empty()) {
        node = pq.top();
        pq.pop();

        for (pair<int, unsigned long int> neigh : graph[node.first]) {
            if (dist[node.first] + neigh.second < dist[neigh.first]) {
                dist[neigh.first] = dist[node.first] + neigh.second;

                pq.push(neigh);
            }
        }
    }
    return dist;
}


int main() {
    ifstream INPUT("drumuri.in");
    ofstream OUTPUT("drumuri.out");

    INPUT >> n >> m;
    g = new list<pair<int, unsigned long int>>[n + 1];
    g_i = new list<pair<int, unsigned long int>>[n + 1];

    int a, b;
    unsigned long long c;
    for (int i = 0; i < m; i++) {
        INPUT >> a >> b;
        INPUT >> c;
        g[a].push_back(pair(b, c));
        g_i[b].push_back(pair(a, c));
    }
    INPUT >> x >> y >> z;

    unsigned long long *dx = D(x, g);
    unsigned long long *dy = D(y, g);
    unsigned long long *dz = D(z, g_i);

    unsigned long long res = get_min(dx, dy, dz);

    OUTPUT << res << "\n";

    INPUT.close();
    OUTPUT.close();
    return 0;
}
