#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <set>
using namespace std;

int n,t;
vector<vector<int>> food;
vector<vector<int>> heart;
vector<pair<int,int>> owner;
int priority[7]{0,0,0,1,1,1,2};
int dr[4]{-1,1,0,0};
int dc[4]{0,0,-1,1};

void makeGroup() {
    owner.clear();
    vector<vector<bool>> visited(n+1, vector<bool>(n+1, false));

    for (int r=1; r<=n; r++) {
        for (int c=1; c<=n; c++) {
            if (visited[r][c]) continue;
            vector<pair<int,int>> candidate;

            int id = food[r][c];
            int maxR = r, maxC = c;
            int maxVal = heart[r][c];

            queue<pair<int,int>> q;
            q.push({r,c});
            visited[r][c] = true;
            candidate.push_back({r,c});

            while (!q.empty()) {
                int curR = q.front().first;
                int curC = q.front().second;
                q.pop();

                for (int i=0; i<4; i++) {
                    int nr = curR + dr[i];
                    int nc = curC + dc[i];

                    if (nr<=0 || nc<=0 || nr>n || nc>n) continue;
                    if (food[nr][nc] != id) continue;
                    if (visited[nr][nc]) continue;

                    visited[nr][nc] = true;
                    q.push({nr,nc});
                    candidate.push_back({nr,nc});
                    if (heart[nr][nc] > maxVal) {
                        maxVal = heart[nr][nc];
                        maxR = nr;
                        maxC = nc;
                    }
                    else if (heart[nr][nc] == maxVal) {
                        if (nr < maxR) {
                            maxR = nr;
                            maxC = nc;
                        }
                        else if (nr == maxR) {
                            if (nc < maxC) {
                                maxR = nr;
                                maxC = nc;
                            }
                        }
                    }
                }
            }

            for (pair<int,int> p : candidate) {
                if (p.first == maxR && p.second == maxC) heart[p.first][p.second] += (candidate.size() - 1);
                else heart[p.first][p.second]--;
            }

            owner.push_back({maxR, maxC});
        }
    }
}

bool cmp(pair<int,int> p1, pair<int,int> p2) {
    int id1 = food[p1.first][p1.second];
    int id2 = food[p2.first][p2.second];

    if (priority[id1] != priority[id2]) return priority[id1] < priority[id2];

    int h1 = heart[p1.first][p1.second];
    int h2 = heart[p2.first][p2.second];

    if (h1 != h2) return h1 > h2;
    if (p1.first != p2.first) return p1.first < p2.first;
    return p1.second < p2.second;
}

void getFood(int id, set<int>& s) {
    if (id <= 2) s.insert(id);
    else if (id == 3) {
        s.insert(1);
        s.insert(2);
    }
    else if (id == 4) {
        s.insert(0);
        s.insert(2);
    }
    else if (id == 5) {
        s.insert(0);
        s.insert(1);
    }
    else {
        s.insert(0);
        s.insert(1);
        s.insert(2);
    }
}

int getId(set<int>& s) {
    vector<bool> used(3, false);
    for (int i : s) used[i] = true;

    bool used0 = used[0];
    bool used1 = used[1];
    bool used2 = used[2];

    if (used0 && used1 && used2) return 6;
    else if (used0 && used1 && !used2) return 5;
    else if (used0 && !used1 && used2) return 4;
    else if (!used0 && used1 && used2) return 3;
    else if (!used0 && !used1 && used2) return 2;
    else if (!used0 && used1 && !used2) return 1;
    else if (used0 && !used1 && !used2) return 0;
}

void spread() {
    vector<vector<bool>> defended(n+1, vector<bool>(n+1, false));

    for (pair<int,int>& p : owner) {
        int r = p.first, c = p.second;
        if (defended[r][c]) continue;
        int spreadFood = food[r][c];

        int x = heart[r][c] - 1;
        int dir = heart[r][c] % 4;
        heart[r][c] = 1;

        while(x > 0) {
            r += dr[dir];
            c += dc[dir];

            if (r<=0 || c<=0 || r>n || c>n) break;

            if (spreadFood == food[r][c]) continue;

            int y = heart[r][c];
            defended[r][c] = true;
            
            if (x > y) {
                x -= (y+1);
                food[r][c] = spreadFood;
                heart[r][c]++;
            }
            else {
                set<int> s;
                getFood(food[r][c], s);
                getFood(spreadFood, s);
                int id = getId(s);

                food[r][c] = id;
                heart[r][c] += x;
                x = 0;
            }
        }
    }
}

void print() {
    vector<int> sum(7, 0);

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) sum[food[i][j]] += heart[i][j];
    }

    for (int i=6; i>=0; i--) cout << sum[i] << " ";
}

int main() {
    cin >> n >> t;
    food.assign(n+1, vector<int>(n+1, 0));
    heart.assign(n+1, vector<int>(n+1, 0));

    for (int i=1; i<=n; i++) {
        string str;
        cin >> str;
        for (int j=1; j<=n; j++) {
            if (str[j-1] == 'T') food[i][j] = 0;
            else if (str[j-1] == 'C') food[i][j] = 1;
            else if (str[j-1] == 'M') food[i][j] = 2;
        }
    }

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) cin >> heart[i][j];
    }

    while (t--) {

        // T : 민트 - 0
        // C : 초코 - 1
        // M : 우유 - 2
        // 초코우유 - 3
        // 민트우유 - 4
        // 민트초코 - 5
        // 민트초코우유 - 6

        // 초코우유 , 민트우유, 민트초코, 민트초코우유 까지도 가능

        // 신앙심
        // T일 

        // Step1
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) heart[i][j]++;
        }

        // Step2
        makeGroup();

        // 상하좌우와 신봉 음식이 완전히 같은 경우에만 그룹 형성

        // TTC*C
        // TT*TM*
        // C*CMM
        // CMMM

        // 아 이거 보니까 그룹이 그냥 bfs돌면서
        // 같은 수면 그룹에 속하게 되고, 
        // 다른 그룹들 수 세는만큼 대표자 생기네
        // 그러면 그냥 그룹을 만들면서 그 그룹에서 대표자 자체를 구해야하나
        // 그럼 bfs 한번 돌면서 그룹이 만들어질때
        // maxHeart인 애의 maxR, maxC를 저장,
        // 그럼 그룹장인 애들은 size-1 만큼 더하고 나머진 -1
        // 그럼 나머지 애들은 어떻게 아나?
        // 이땐 다시 역으로 maxR, maxC 에서 역으로 bfs
        // 가면서 같으면 -- 해주고 maxRmaxC 위치에는 ++ 해주고
        // 아니면 candidate 같은거 하나 만들어서 같은 그룹인 애들 r,c 다 넣어두고
        // maxR, maxC인 애는 size-1 더해주고 아닌 애는 --



        // 그 중 대표자 한 명 선정
        // - 신앙심이 가장 큰 사람
        // - 동일하면 (r, k) 라고 할 때 r이 작은 사람
        // - 동일하면 c가 작은 사람
        // 그릅원들은 대표자에게 1씩 넘김
        // 즉 대표자의 신앙심은 += (그릅원의 수 - 1), 나머지 그룹원은 -1씩 감소
        // 그럼 대표자들 list도 만들어서 넣어두자

        // Step3
        // 대표자들이 신앙 전파
        // 세 그룹 순서대로 진행
        // 1. 단일 - 민트 / 초코 / 우유
        // 2. 이중 - 초코우유 / 민트우유 / 민트초코
        // 3. 삼중 - 민트초코우유
        // 그럼 정렬을 할 때
        // food[][] 번호가 작은 순으로 정렬해야겠네
        // 그리고
        // 같은 그룹 - 0 1 2
        // 같은 그룹 - 3 4 5
        // 같은 그룹 - 6
        // 같은 그룹 내에서는 maxHeart 높은 순으로
        // 같으면 r, c 작은 애들로
        // 그걸 정렬을 어떻게 해야하지
        // 그룹이 같으면 <- 이걸 판단을 어떻게 해야할까
        // 그룹 같은지를 판단하는?
        // 우선순위를 적는? 배열을 만들어서 할까
        // 즉 priority[] 만들어서 []
        // 같은 그룹 내에서는
        // 대표자의 신앙심이 높은 순
        // - 동일하면 대표자의 행 번호가 작은 순
        // - 동일하면 대표자의 열 번호가 작은 순     
        sort(owner.begin(), owner.end(), cmp);

        // 전파자는 B중 1만 남기고 간절함 (B-1) 로 바꿔 전파에 사용
        // 전파 방향은 B%4 값에 따라 상하좌우로 전파
        // 전파자는 전파할 방향으로 한 칸씩 이동하면서 전파 시도
        // 격자밖 or 간절함이 0 되면 전파 종료
        spread();

        // 전파 대상 == 신봉 음식이 완전히 같은 경우에는 전파 하지않고 바로 다음으로 진행
        // 전파 대상이 전파자와 신봉음식이 다른 경우에는 전파 진행
        // 전파 대상의 신앙심이 y라고 할 때 x > y 면 강한 전파
        // - 동일한 음식 신봉, 전파자는 간절함이 (y+1)만큼 깎이며, 전파대상의 신앙심은 1 증가
        // 이 때 전파자의 간절함이 0이 된다면 더 이상 진행 x

        // x <= y 면 약한 전파
        // 전파자가 전파한 음식의 모든 기본 음식에 관심을 가짐
        // 기존에 관심을 가지고 있던 기본 음식 & 
        // 전파자가 관심을 가지고 있는 기본 음식을 모두 합친 음식을 신봉
        // 이 경우 전파자는 간절함이 0이 되고 더이상 전파 진행 x
        // 그러나 대상의 신앙심은 x 만큼 증가

        // 예를 들어, 민트를 신앙하던 사람에게 초코우유 전파자가 약한 전파에 성공한다면,
        // 초코와 우유 각각에 추가로 관심을 가지게 됩니다.
        // 대상은 관심을 가지고 있는 기본 음식들을 모두 합친 음식을 신앙하게 됩니다.
        // 이 경우, 대상은 민트초코우유를 신봉하게 됩니다.
        // 만약 동일한 상황에서 강한 전파에 성공한다면, 대상은 초코우유를 신봉하게 됩니다.

        // 또한 어떤 학생이 다른 음식의 대표자에게 전파를 당했다면
        // 해당 학생은 그 즉시 방어상태가 되어 당일에는 전파 X
        // 방어 상태가 되더라도 추가로 전파를 받는 것은 가능
        
        // 각 

        print();
        cout << "\n";
    }

    return 0;
}