#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Box {
    int k,r,h,w,c;
    bool alive;
};

int n,m;
vector<vector<int>> v;
vector<Box> boxes;

void eraseBox(int id) {
    Box& b = boxes[id];

    for (int r=b.r; r<b.r+b.h; r++) {
        for (int c=b.c; c<b.c+b.w; c++) v[r][c] = 0;
    }
}

void drawBox(int id) {
    Box& b = boxes[id];

    for (int r=b.r; r<b.r+b.h; r++) {
        for (int c=b.c; c<b.c+b.w; c++) v[r][c] = b.k;
    }
}

void drop(int id) {
    Box& b = boxes[id];

    eraseBox(id);

    while(true) {
        int bottom = b.r + b.h - 1;
        if (bottom == n) break;

        bool canDown = true;

        for (int c=b.c; c<b.c+b.w; c++) {
            if (v[bottom+1][c] != 0) {
                canDown = false;
                break;
            }
        }

        if (!canDown) break;
        b.r++;
    }

    drawBox(id);
}

int leftBox() {
    int idx = -1;

    for (int i=0; i<m; i++) {
        Box& b = boxes[i];
        if (!b.alive) continue;

        bool canMove = true;
        for (int r=b.r; r<b.r+b.h && canMove; r++) {
            for (int c=1; c<b.c && canMove; c++) {
                if (v[r][c] != 0) canMove = false;
            }
        }
        
        if (!canMove) continue;
        
        if (idx == -1 || b.k < boxes[idx].k) idx = i;
    }

    return idx;
}

int rightBox() {
    int idx = -1;

    for (int i=0; i<m; i++) {
        Box& b = boxes[i];
        if (!b.alive) continue;

        bool canMove = true;
        for (int r=b.r; r<b.r+b.h && canMove; r++) {
            for (int c=n; c>=b.c+b.w && canMove; c--) {
                if (v[r][c] != 0) canMove = false;
            }
        }
        
        if (!canMove) continue;
        
        if (idx == -1 || b.k < boxes[idx].k) idx = i;
    }

    return idx;
}

void removeBox(int id) {
    eraseBox(id);
    boxes[id].alive = false;
}

void allGravity() {
    vector<int> candidate;

    for (int i=0; i<m; i++) {
        if (boxes[i].alive) candidate.push_back(i);
    }

    sort(candidate.begin(), candidate.end(), [&](int a, int b) {
        int bottomA = boxes[a].r + boxes[a].h - 1;
        int bottomB = boxes[b].r + boxes[b].h - 1;
        
        if (bottomA != bottomB) return bottomA > bottomB;
        return boxes[a].k < boxes[b].k;
    });

    for (int id : candidate) drop(id);
}

int main() {

    cin >> n >> m;
    v.assign(n+1, vector<int>(n+1, 0));
    boxes.resize(m);

    // Step1
    for (int i=0; i<m; i++) {
        int k,h,w,c;
        cin >> k >> h >> w >> c;

        boxes[i] = {k, 1, h, w, c, true};

        drop(i);
    }

    // Step2, 3
    int remain = m;
    while(remain > 0) {
        // Step2
        int id = leftBox();
        if (id != -1) {
            removeBox(id);
            remain--;
            cout << boxes[id].k << "\n";
            allGravity();
        }

        if (remain == 0) break;

        // Step3
        id = rightBox();
        if (id != -1) {
            removeBox(id);
            remain--;
            cout << boxes[id].k << "\n";
            allGravity();
        }
    }

    return 0;
}