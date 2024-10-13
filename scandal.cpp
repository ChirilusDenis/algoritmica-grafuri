#include <fstream>
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int n, m;
list<int> *g;
int gtime, MAX = 2147483647;
int *low_link, *found, *in_stack, *parent;
int *invited;
list<int> *stack;
int num;

void DFS(int node) {
    gtime++;
    found[node] = gtime;
    low_link[node] = found[node];
    stack->push_front(node);
    in_stack[node] = 1;

    for (int neigh : g[node]) {
        if (parent[neigh] != -1) {
            if (in_stack[neigh]) {
                low_link[node] = min(low_link[node], found[neigh]);
            }
            continue;
        }

        parent[neigh] = node;
        DFS(neigh);
        low_link[node] = min(low_link[node], low_link[neigh]);
    }

    if (low_link[node] == found[node]) {
        int crt;
        do {
            crt = stack->front();
            stack->pop_front();
            in_stack[crt] = 0;

            if (!invited[crt]) {
                invited[crt] = 1;
                if (crt > n) {
                    invited[crt - n] = -1;
                } else {
                    invited[crt + n] = -1;
                    num++;
                }
            }
        } while (crt != node);
    }
}

void tarjan() {
    for (int i = 1; i <= 2 * n; i++) {
        found[i] = MAX;
        low_link[i] = MAX;
        in_stack[i] = 0;
        parent[i] = -1;
        invited[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (parent[i] == -1) {
            stack = new list<int>;
            DFS(i);
        }
    }
}

int main() {
    ifstream INPUT("scandal.in");
    ofstream OUTPUT("scandal.out");

    INPUT >> n >> m;
    int x, y, c;
    g = new list<int>[2 * n + 1];


    for (int i = 0; i < m; i++) {
        INPUT >> x >> y >> c;

        if (c == 0) {
            g[x + n].push_back(y);
            g[y + n].push_back(x);

        } else if (c == 1) {
            g[x + n].push_back(y + n);
            g[y].push_back(x);

        } else if (c == 2) {
            g[y + n].push_back(x + n);
            g[x].push_back(y);

        } else if (c == 3) {
            g[x].push_back(y + n);
            g[y].push_back(x + n);
        }
    }
    low_link = new int[2 *n + 1];
    found = new int[2 * n + 1];
    in_stack = new int[2 * n + 1];
    parent = new int[2 * n + 1];
    invited =new int[2 * n + 1];

    tarjan();

    OUTPUT << num << '\n';
    for (int i = 1; i <= n; i++) {
        if (invited[i] == 1) OUTPUT << i << '\n';
    }

    INPUT.close();
    OUTPUT.close();
    return 0;
}
