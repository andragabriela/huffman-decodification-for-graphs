#include <fstream>
#include <queue>
#include <algorithm>
#include <tuple>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

const int NMAX = 1e4 + 10;
int st[NMAX], dr[NMAX];
int fr[NMAX], root;
char let[NMAX], minCode[NMAX];

const int LMAX = 500;
int frec[LMAX];

map < string, char >  mp;

void dfs(int node, string cod) {
    //g << node << " " << cod << "\n";
    if (st[node] == -1 && dr[node] == -1) {
        //mp[let[node]] = cod;
        mp[cod] = let[node];
        return;
    }
    if (st[node] != -1) {
        dfs(st[node], cod + "0");
    }
    if (dr[node] != -1) {
        dfs(dr[node], cod + "1");
    }
}

int main(int argc, char** argv) {

    ifstream f(argv[1]);
    ofstream g(argv[2]);

    //ifstream f("date.in");
    //ofstream g("date.out");

    int n;
    f >> n;

    for (int i = 0; i < NMAX; i++)
        st[i] = dr[i] = -1;

    vector < pair < char, int > > aux(n);
    string buf;
    getline(f, buf);
    for (auto& it : aux) {
        char x; int y;
        getline(f, buf);
        x = buf[0];
        y = 0;
        for (int i = 2; i < buf.size(); i++)
            y = y * 10 + buf[i] - '0';
        //cout << x << " " << y << "\n";
        it = { x, y };
    }

    sort(aux.begin(), aux.end());

    int first_available = aux.size() + 1;
    int root=0;
    int node = 0;
    priority_queue < tuple < int, char, int > > q;
    for (auto it : aux) {
        node++;
        q.push({ -it.second, -it.first, node });
        let[node] = it.first;
        minCode[node] = it.first;
    }

    while (q.size() > 1) {
        int f1 = -get<0>(q.top());
        char c1 = -get<1>(q.top());
        int node1 = get<2>(q.top());
        q.pop();

        int f2 = -get<0>(q.top());
        char c2 = -get<1>(q.top());
        int node2 = get<2>(q.top());
        q.pop();

        st[first_available] = node1;
        dr[first_available] = node2;
        let[first_available] = 0;
        fr[first_available] = f1 + f2;
        minCode[first_available] = min(c1, c2);

        q.push({ -fr[first_available], -minCode[first_available], first_available });
        root = first_available;
        first_available++;

    }

    dfs(root, "");

    string work;
    string s;
    f >> s;
    for (auto it : s) {
        work += it;
        if (mp.find(work) != mp.end()) {
            g << mp[work];
            work = "";
        }
    }

    return 0;
}
