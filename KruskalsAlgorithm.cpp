#include<algorithm>

bool cmp(vector<int> &a, vector<int> &b) {
  return a[2] < b[2];
}

void makeSet(vector<int> &parent, vector<int> &rank, int n) {
  for(int i = 0; i < n; i++) {
    parent[i] = i;
    rank[i] = 0;
  }
}

int findParent(int u, vector<int> &parent) {
  if(parent[u] == u) {
    return u;
  }

  parent[u] = findParent(parent[u], parent);
  return parent[u];
}

void unionSet(int u, int v, vector<int> &parent, vector<int> &rank) {
  u = findParent(u, parent);
  v = findParent(v, parent);

  if(rank[u] < rank[v]) {
    parent[u] = v;
  }
  else if(rank[v] < rank[u]) {
    parent[v] = u;
  }
  else {
    parent[u] = v;
    rank[v]++;
  }
}

int minimumSpanningTree(vector<vector<int>>& edges, int n)
{
  sort(edges.begin(), edges.end(), cmp);
  vector<int> parent(n);
  vector<int> rank(n);

  int minWt = 0;

  makeSet(parent, rank, n);

  for(int i = 0; i < edges.size(); i++) {

    int u = findParent(edges[i][0], parent);
    int v = findParent(edges[i][1], parent);
    int w = edges[i][2];

    if(u != v) {
      minWt += w;
      unionSet(u, v, parent, rank);
    }
  }

  return minWt;
}