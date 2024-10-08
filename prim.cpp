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
  arr[n + 1] = x;
  i = n + 1;
  n = n + 1;
  while (i > 1 && arr[i].w < arr[i/2].w) {
    std::swap(arr[i], arr[i/2]);
    i /= 2;
  }
}

int PQ::is_empty() {
  return n == 0;
}

Triple PQ::del() {
  Triple ret = arr[1];
  int i, j;

  if (n == 1) {
    n = 0;
    return ret;
  }

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
        if (arr[i * 2].w < arr[i * 2 + 1].w) {
          j *= 2;
        }
        else {
          j = i * 2 + 1;
        }
        std::swap(arr[i], arr[j]);
        i = j;
      }
      if (arr[i].w > arr[i * 2].w && arr[i].w <= arr[i * 2 + 1].w) {
        j = i * 2;
        std::swap(arr[i], arr[j]);
        i = j;
      }
      if (arr[i].w <= arr[i * 2].w && arr[i].w > arr[i * 2 + 1].w) {
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

int main() {
  int c, i, a, b, w;
  Triple x, y;
  std::cin >> n >> m;
  for (i = 0; i < m; i++) {
    std::cin >> a >> b >> w;
    edges[a].push_back(std::make_pair(b, w));
    edges[b].push_back(std::make_pair(a, w));
  }
  c = 1;
  M[c] = 1;
  for (i = 0; i < edges[c].size(); i++) {
    x.a = c;
    x.b = edges[c][i].first;
    x.w = edges[c][i].second;
    pq.insert(x);
  }

  while (pq.is_empty() == 0) {
    y = pq.del();
    if (M[y.a] == 1 && M[y.b] == 1) {
      continue;
    }
    else {
      std::cout << "Edge from Node " << y.a << " to Node " << y.b << " Weight " << y.w << " Selected.\n";
      c = y.b;
      M[c] = 1;
      for (i = 0; i < edges[c].size(); i++) {
        x.a = c;
        x.b = edges[c][i].first;
        x.w = edges[c][i].second;
        pq.insert(x);
      }
    }
  }
  return 0;
}
