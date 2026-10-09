#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Box {
    int k,r,c,w,h;
    bool alive;
};

int n,m;
vector<vector<int>> v;
vector<Box> boxes;

void eraseBox(int idx) {
    Box& b = boxes[idx];

    for (int r=b.r; r<b.r+b.h; r++) {
        for (int c=b.c; c<b.c+b.w; c++) v[r][c] = 0;
    }
}

void drawBox(int idx) {
    Box& b = boxes[idx];

    for (int r=b.r; r<b.r+b.h; r++) {
        for (int c=b.c; c<b.c+b.w; c++) v[r][c] = b.k;
    }
}

void drop(int idx) {
    Box& b = boxes[idx];

    // 기존 박스 지우기
    eraseBox(idx);

    while(true) {
        int bottom = b.r + b.h - 1;
        bool isBreak = false;

        if (bottom == n) break;
        for (int c=b.c; c<b.c+b.w; c++) {
            if (v[bottom+1][c] != 0) {
                isBreak = true;
                break;
            }
        }
        if (isBreak) break;

        b.r++;
    }

    // 현재 위치에 박스 그리기
    drawBox(idx);
}

int leftBox() {
    int idx = -1;

    for (int i=0; i<m; i++) {
        Box& b = boxes[i];
        if (!b.alive) continue;

        bool check = true;
        for (int r=b.r; r<b.r+b.h; r++) {
            for (int c=1; c<b.c; c++) {
                if (v[r][c] != 0) {
                    check = false;
                    break;
                }
            }
            if (!check) break;
        }
        if (!check) continue;
        
        if (idx == -1 || b.k < boxes[idx].k) idx = i;
    }

    return idx;
}

int rightBox() {
    int idx = -1;

    for (int i=0; i<m; i++) {
        Box& b = boxes[i];
        if (!b.alive) continue;

        bool check = true;
        for (int r=b.r; r<b.r+b.h; r++) {
            for (int c=n; c>=b.c+b.w; c--) {
                if (v[r][c] != 0) {
                    check = false;
                    break;
                }
            }
            if (!check) break;
        }
        if (!check) continue;
        
        if (idx == -1 || b.k < boxes[idx].k) idx = i;
    }

    return idx;
}

void removeBox(int idx) {
    eraseBox(idx);
    boxes[idx].alive = false;
}

bool cmp(int a, int b) {
    int bottomA = boxes[a].r + boxes[a].h - 1;
    int bottomB = boxes[b].r + boxes[b].h - 1;

    if (bottomA != bottomB) return bottomA > bottomB;
    return boxes[a].k < boxes[b].k;
}

void allGravity() {
    vector<int> candidate;

    for (int i=0; i<m; i++) {
        if (boxes[i].alive) candidate.push_back(i);
    }

    // 정렬은 bottom이 큰 애들(밑에 있는 애들)부터 해야함
    sort(candidate.begin(), candidate.end(), cmp);

    for (int idx : candidate) drop(idx);
}

int main() {

    cin >> n >> m;
    v.assign(n+1, vector<int>(n+1, 0));
    boxes.resize(m);

    for (int i=0; i<m; i++) {
        int k,h,w,c;
        cin >> k >> h >> w >> c;
        boxes[i] = {k, 1, c, w, h, true};

        drop(i);
    }

    // step2, 3
    // 일단 모든 박스를 보는데 그 때 박스의 c 미만에서 하나라도 박스가 있는가
    // 좌측에 있다는 뜻이므로 그건 패스
    // 그때 범위가 그 박스의 r ~ r+h 까지 고려해서 살펴봐야함
    // 즉 모든 박스를 탐색하는데
    // 각 박스의 r ~ r+h 범위에서 c미만에 박스가 있느냐를 판단
    // 있으면 continue
    // 없으면 idx의 k 값들 비교 후 갱신
    // 그 k가 정해지면 k 관련 박스는 삭제 delete 하는데 erase 및 alive 삭제
    // 이후 모든 박스 중력 적용
    // 중력은 bottom이 큰 애들부터 정렬시킨 뒤에
    // 모든애들을 drop 하면 되네
    int remain = m;
    while(true) {

        // step2
        int idx = leftBox();
        if (idx != -1) {
            cout << boxes[idx].k << "\n";
            removeBox(idx);
            allGravity();
            remain--;            
        }

        if (remain == 0) break;

        // step3
        idx = rightBox();
        if (idx != -1) {
            cout << boxes[idx].k << "\n";
            removeBox(idx);
            allGravity();
            remain--;            
        }

        if (remain == 0) break;
    }



    return 0;
}