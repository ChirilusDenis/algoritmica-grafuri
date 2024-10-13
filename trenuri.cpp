#include <fstream>
#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

string f_src, f_dst;
int i_src, i_dst;
int n;
string *all;
int num_cities;
list<int> *g;
unordered_map<string, int> hsht;
int max_depth;
int *d;

int find(string city) {
    if (hsht.find(city) == hsht.end()) {
        hsht[city] = num_cities;
        num_cities++;
        return (num_cities - 1);
    }
    return hsht[city];
}

int trying_dfs(int node) {
    if (node == i_dst) {
        return 1;
    }
    if (d[node] != -1) {
        return d[node];
    }

    int crt_d;
    for (int neigh : g[node]) {
        crt_d = trying_dfs(neigh);
        if (1 + crt_d > d[node]) d[node] = 1 + crt_d;
    }
    return d[node];
}

int main() {
    ifstream INPUT("trenuri.in");
    ofstream OUTPUT("trenuri.out");

    INPUT >> f_src;
    INPUT >> f_dst;
    INPUT >> n;

    g = new list<int>[n];

    i_src = find(f_src);
    i_dst = find(f_dst);

    string src, dst;
    for (int i = 0; i < n; i ++) {
        INPUT >> src >> dst;
        g[find(src)].push_back(find(dst));
    }

    d = new int[num_cities];
    for (int i = 0; i < num_cities; i++) {
        d[i] = -1;
    }

    int res = trying_dfs(i_src);
    OUTPUT << res << '\n';

    OUTPUT.close();
    INPUT.close();
    return 0;
}
