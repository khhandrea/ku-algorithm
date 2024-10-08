#include <iostream>
#include <vector>

class Triple {
public:
  int a, b, w;
};

class PQ {
public:
  int n;
  Triple arr[1000];

  PQ();
  Triple del();
  void insert(Triple x);
  int is_empty();
};

PQ::PQ() {
  n = 0;
}

void PQ::insert(Triple x) {
  int i;
  n += 1;
  arr[n] = x;
  i = n;
  while (i > 1 && arr[i].w < arr[i / 2].w) {
    std::swap(arr[i], arr[i/2]);
    i /= 2;
  }
}

int PQ::is_empty() {
  return (n == 0);
}

Triple PQ::del() {
  Triple ret = arr[1];

  if (n == 1) {
    n = 0;
    return ret;
  }

  int i, j;

  arr[1] = arr[n];
  i = 1;
  n -= 1;

  while (1) {
    if (i * 2 > n) {
      break;
    }
    else if (i * 2 + 1 > n) { // Left child only
      if (arr[i * 2].w < arr[i].w) {
        std::swap(arr[i * 2], arr[i]);
        i *= 2;
      }
      else {
        break;
      }
    }
    else {
      if (arr[i].w > arr[i * 2].w && arr[i].w > arr[i * 2 + 1].w) {
        j = i * 2;
        if (arr[i * 2].w >= arr[i * 2 + 1].w) {
          j += 1;
        }
        std::swap(arr[i], arr[j]);
        i = j;
      }
      else if (arr[i].w > arr[i * 2].w && arr[i].w <= arr[i * 2 + 1].w) {
        j = i * 2;
        std::swap(arr[i], arr[j]);
        i = j;
      }
      else if (arr[i].w <= arr[i * 2].w && arr[i].w > arr[i * 2 + 1].w) {
        j = i * 2 + 1;
        std::swap(arr[i], arr[j]);
        i = j;
      }
      else {
        break;
      }
    }
  }
  return ret;
}

PQ pq;

int n, m;
std::vector<std::pair<int, int> > edges[1000];
int M[1000];
std::vector<int> prevs[1000];

int main() {
  int c, i, a, b, w;
  Triple x, y;
  std::cin >> n >> m;
  for (i = 0; i < m; i++) {
    std::cin >> a >> b >> w;
    edges[a].push_back(std::make_pair(b, w));
    edges[b].push_back(std::make_pair(a, w));
  }
  for (i = 1; i <= n; i++) {
    M[i] = 1000000;
  }
  c = 1;
  M[c] = 0;
  for (i = 0; i < edges[c].size(); i++) {
    x.a = c;
    x.b = edges[c][i].first;
    x.w = M[c] + edges[c][i].second;
    pq.insert(x);
  }

  while (pq.is_empty() == 0) {
    y = pq.del();
    if (M[y.b] < 100000) {
      if (M[y.b] == y.w) {
        std::cout << "Edge from Node " << y.a << " to Node " << y.b << " of Total Path Length " << y.w << " ADDED. Previous node " << y.a << '\n';
        prevs[y.b].push_back(y.a);
      }
      else {
        std::cout << "IGNORED Edge from Node " << y.a << " to Node " << y.b << " of Total Path Length " << y.w << ".\n";
      }
    }
    else {
      std::cout << "Edge from Node " << y.a << " to Node " << y.b << " of Total Path Length " << y.w << " Selected. Previous node " << y.a << ".\n";
      c = y.b;
      M[c] = y.w;
      prevs[c].push_back(y.a);

      for (i = 0; i < edges[c].size(); i++) {
        x.a = c;
        x.b = edges[c][i].first;
        x.w = M[c] + edges[c][i].second;
        pq.insert(x);
      }
    }
  }
  return 0;
}
