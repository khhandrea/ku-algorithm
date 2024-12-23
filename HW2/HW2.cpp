#include <algorithm>
#include <iostream>
#define INF 2000000000

int main() {
  int N, Q, k, new_power, idx, diff, min_diff;
  int *powers, *min_diffs, *rmin_diffs;

  // Input
  std::cin >> N >> Q;
  powers = new int[N];
  min_diffs = new int[N];
  rmin_diffs = new int[N];
  for (int n = 0; n < N; n++) {
    std::cin >> powers[n];
  }
  std::sort(powers, powers + N);

  // Make min_diffs and rmin_diffs (DP)
  for (idx = 2; idx < N; idx++) {
    if (idx <= 4) {
      min_diffs[idx] = 2 * (powers[idx] - powers[0]);
      rmin_diffs[N - 1 - idx] = 2 * (powers[N - 1] - powers[N - 1 - idx]);
    }
    else {
      min_diffs[idx] = INF;
      rmin_diffs[N - 1 - idx] = INF;
      for (int i = 2; i <= 4 && idx - i - 1 >= 2; i++) {
        diff = 2 * (powers[idx] - powers[idx - i]) + min_diffs[idx - i - 1];
        min_diffs[idx] = (diff < min_diffs[idx] ? diff : min_diffs[idx]);

        diff = 2 * (powers[N - 1 - idx + i] - powers[N - 1 - idx]) + rmin_diffs[N - idx + i];
        rmin_diffs[N - 1 - idx] = (diff < rmin_diffs[N - 1 - idx] ? diff : rmin_diffs[N - 1 - idx]);
      }
    }
  }

  for (int q = 0; q < Q; q++) {
    std::cin >> k >> new_power;
    
    // Search idx for new_power
    for (idx = 0; new_power > powers[idx] && idx < N; idx++);
    min_diff = INF;

    // New power is in the right end of a new group
    for (int size = 3;
         size <= 5 && idx - size + 1 >= 0;
         size++) {
      if ((idx - size < 2 && idx - size + 1 != 0)
          || (idx > N - 3 && idx != N)) {
        continue;
      }

      diff = 2 * (new_power - powers[idx - size + 1]);
      if (idx - size >= 2) {
        diff += min_diffs[idx - size];
      }
      if (idx <= N - 3) {
        diff += rmin_diffs[idx];
      }
      min_diff = (diff < min_diff ? diff : min_diff);
    }

    // New power is in the left end of a new group
    for (int size = 3;
         size <= 5 && idx + size - 2 < N;
         size++) {
      if ((idx - 1 < 2 && idx != 0)
          || (idx + size - 1 > N - 3 && idx + size - 2 != N - 1)) {
        continue;
      }

      diff = 2 * (powers[idx + size - 2] - new_power);
      if (idx - 1 >= 2) {
        diff += min_diffs[idx - 1];
      }
      if (idx + size - 1 <= N - 3) {
        diff += rmin_diffs[idx + size - 1];
      }
      min_diff = (diff < min_diff ? diff : min_diff);
    }

    // New power is between a new group
    for (int pos = 1; pos <= 3 && idx - pos >= 0; pos++) {
      for (int end = 0; end <= 3 - pos && idx + end < N; end++) {
        if ((idx - pos - 1 < 2 && idx - pos != 0)
            || (idx + end + 1 > N - 3 && idx + end != N - 1)) {
          continue;
        }

        diff = 2 * (powers[idx + end] - powers[idx - pos]);
        if (idx - pos - 1 >= 2) {
          diff += min_diffs[idx - pos - 1];
        }
        if (idx + end + 1 <= N - 3) {
          diff += rmin_diffs[idx + end + 1];
        }
        min_diff = (diff < min_diff ? diff : min_diff);
      }
    }

    std::cout << min_diff << '\n';
  }

  return 0;
}

