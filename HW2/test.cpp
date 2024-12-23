#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

int N, Q;
vector<int> skills;

long long getMinImbalance() {
    vector<bool> used(N, false);
    vector<pair<int, int>> teams;
    long long totalImbalance = 0;

    // 모든 선수에 대해 최적의 팀 찾기
    for (int i = 0; i < N; i++) {
        if (used[i]) continue;

        int bestPair = -1;
        long long minDiff = LLONG_MAX;

        // i 선수와 가장 잘 맞는 파트너 찾기
        for (int j = i + 1; j < N; j++) {
            if (!used[j]) {
                long long diff = abs(skills[i] - skills[j]);
                if (diff < minDiff) {
                    minDiff = diff;
                    bestPair = j;
                }
            }
        }

        // 팀 구성
        if (bestPair != -1) {
            teams.push_back({i, bestPair});
            used[i] = true;
            used[bestPair] = true;
            totalImbalance += minDiff;
        }
    }

    return totalImbalance;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    skills.resize(N);

    for (int i = 0; i < N; i++) {
        cin >> skills[i];
    }

    // 각 훈련 프로그램 처리
    for (int q = 0; q < Q; q++) {
        int k;
        cin >> k;
        
        int guest;
        cin >> guest;

        // 초청 선수 추가
        skills.push_back(guest);
        N++;

        // 최소 불균형 계산 및 출력
        cout << getMinImbalance() << "\n";

        // 초청 선수 제거
        skills.pop_back();
        N--;
    }

    return 0;
}
