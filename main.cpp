#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vs = vector<string>;
using vb = vector<bool>;
using vvb = vector<vb>;
using PosDist = tuple<ll, ll, ll>;

ll n, m;
vs C;

vl dx{-1, 1, 0, 0};
vl dy{0, 0, -1, 1};

ll ans = 0;
void Pass(ll y, ll x) {
  auto visit = vvb(n, vb(m, false));
  auto q = queue<PosDist>{};
  q.push({y, x, 0});
  visit[y][x] = true;

  while (!q.empty()) {
    auto [fy, fx, fd] = q.front();
    q.pop();

    if (ans < fd) {
      ans = fd;
    }

    for (auto d = 0; d < 4; ++d) {
      const auto& nx = fx + dx[d];
      const auto& ny = fy + dy[d];

      if (nx < 0 || m <= nx || ny < 0 || n <= ny) continue;

      if (visit[ny][nx]) continue;
      if (C[ny][nx] == 'W') continue;

      q.push({ny, nx, fd + 1});
      visit[ny][nx] = true;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> n >> m;
  C = vs(n);
  for (auto&& x : C) {
    cin >> x;
  }

  for (auto i = 0; i < n; ++i) {
    for (auto j = 0; j < m; ++j) {
      if (C[i][j] == 'W') continue;

      Pass(i, j);
    }
  }

  cout << ans;

  return 0;
}