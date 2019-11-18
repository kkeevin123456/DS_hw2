#include <iostream>
#include <fstream>

using namespace std;

enum state{Visited, Unvisited};
char map[1001][1001];
int dis_map[1001][1001], m, n;
state check_map[1001][1001];
state map_state[1001][1001];

class QueueList;
class QueueNode{
    friend QueueList;
    public:
        pair <int, int> data;
        QueueNode *next;
        QueueNode *prev;
        QueueNode():data(0, 0), next(0), prev(0){};
        QueueNode(pair <int, int> x):data(x), next(0), prev(0){};
};

class QueueList{
    private:
        QueueNode *front;
        QueueNode *back;
        int size;
    public:
        QueueList():front(0), back(0), size(0){};
        void Push(QueueNode *node);
        void Pop();
        void Pop_back();
        bool IsEmpty();
        QueueNode *getFront();
        QueueNode *getBack();
        int getSize();
};

void QueueList::Push(QueueNode *node){
    if(IsEmpty()) {
        front = node;
        back = front;
        size = 1;
        return;
    }
    if(node == nullptr) return;

    node->prev = back;
    back->next = node;
    back = node;
    size++;
}

void QueueList::Pop(){
    if(IsEmpty()) return;

    QueueNode *temp = front;
    front = front->next;

    if(front == 0)
        back = 0;
    else
        front->prev = 0;

    size--;
    delete temp;
    temp = 0;
}

void QueueList::Pop_back(){
    if(IsEmpty()) return;

    QueueNode *temp = back;
    back = back->prev;

    if (back == 0)
        front == 0;
    else
        back->next = 0;

    size--;
    delete temp;
    temp = 0;
}

QueueNode *QueueList::getFront(){
    if(IsEmpty()) return 0;
    return front;
}

QueueNode *QueueList::getBack(){
    if(IsEmpty()) return 0;
    return back;
}

bool QueueList::IsEmpty(){
    return ( (front && back) == 0);
}

int QueueList::getSize(){
    return size;
}

void my_BFS(int x, int y){
    QueueList que;
    // initialize map_state  dis_map
    //state map_state[m][n];
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            //cout << i << ' ' << j << endl;
            if(map[i][j]=='0') map_state[i][j] = Unvisited;
            dis_map[i][j] = -1;
        }
    }
    // position of R
    dis_map[x][y] = 0;
    QueueNode *R = new QueueNode(make_pair(x, y));
    que.Push(R);
    while(!que.IsEmpty()){
        // pick a node from que.front
        pair<int, int> p = que.getFront()->data;
        que.Pop();
        map_state[p.first][p.second] = Visited;

        int temp_x, temp_y; // new point
        // go through all points
        for(int i=0; i<4; i++){
            if(i==0){ // direction upon
                temp_x = p.first - 1;
                temp_y = p.second;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] == -1 && map_state[temp_x][temp_y] == Unvisited && map[temp_x][temp_y] == '0'){
                    QueueNode *temp = new QueueNode(make_pair(temp_x, temp_y));
                    que.Push(temp);
                    dis_map[temp_x][temp_y] = dis_map[p.first][p.second] + 1;
                }
            }
            else if(i==1){  // direction down
                temp_x = p.first + 1;
                temp_y = p.second;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] == -1 && map_state[temp_x][temp_y] == Unvisited && map[temp_x][temp_y] == '0'){
                    QueueNode *temp = new QueueNode(make_pair(temp_x, temp_y));
                    que.Push(temp);
                    dis_map[temp_x][temp_y] = dis_map[p.first][p.second] + 1;
                }
            }
            else if(i==2){ // direction right
                temp_x = p.first;
                temp_y = p.second + 1;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] == -1 && map_state[temp_x][temp_y] == Unvisited && map[temp_x][temp_y] == '0'){
                    QueueNode *temp = new QueueNode(make_pair(temp_x, temp_y));
                    que.Push(temp);
                    dis_map[temp_x][temp_y] = dis_map[p.first][p.second] + 1;
                }
            }
            else if(i==3){ // direction left
                temp_x = p.first;
                temp_y = p.second - 1;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] == -1 && map_state[temp_x][temp_y] == Unvisited && map[temp_x][temp_y] == '0'){
                    QueueNode *temp = new QueueNode(make_pair(temp_x, temp_y));
                    que.Push(temp);
                    dis_map[temp_x][temp_y] = dis_map[p.first][p.second] + 1;
                }
            }
        }
    }
}

QueueList find_path(QueueNode *start, QueueNode *target){
    QueueList path;
    QueueNode *temp = new QueueNode(make_pair(target->data.first, target->data.second));
    path.Push(temp);

    if(start->data.first == target->data.first && start->data.second == target->data.second)
        return path;
    int flag=1;
    while(1){
        pair<int, int> p = path.getBack()->data;

        int temp_x, temp_y; // new point
        // go through all points
        int i;
        for(i=0; i<4; i++){
            // 決定從哪個方向開始走 從還沒走過的開始走 如果都走過了 就從上面開始拜訪
            if(dis_map[p.first-1][p.second] != -1 && check_map[p.first-1][p.second] == Unvisited && dis_map[p.first-1][p.second] < dis_map[p.first][p.second])// upon
                i=0;
            else if(dis_map[p.first+1][p.second] != -1 && check_map[p.first+1][p.second] == Unvisited && dis_map[p.first+1][p.second] < dis_map[p.first][p.second])// down
                i=1;
            else if(dis_map[p.first][p.second+1] != -1 && check_map[p.first][p.second+1] == Unvisited && dis_map[p.first][p.second+1] < dis_map[p.first][p.second])// right
                i=2;
            else if(dis_map[p.first][p.second-1] != -1 && check_map[p.first][p.second-1] == Unvisited && dis_map[p.first][p.second-1] < dis_map[p.first][p.second])// left
                i=3;

            if(i==0){ // direction upon
                temp_x = p.first - 1;
                temp_y = p.second;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] < dis_map[p.first][p.second] && dis_map[temp_x][temp_y] != -1){
                    QueueNode *temp = new QueueNode(make_pair(temp_x, temp_y));
                    path.Push(temp);
                    break;
                }
            }
            else if(i==1){  // direction down
                temp_x = p.first + 1;
                temp_y = p.second;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] < dis_map[p.first][p.second] && dis_map[temp_x][temp_y] != -1){
                    QueueNode *temp = new QueueNode(make_pair(temp_x, temp_y));
                    path.Push(temp);
                    break;
                }
            }
            else if(i==2){ // direction right
                temp_x = p.first;
                temp_y = p.second + 1;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] < dis_map[p.first][p.second] && dis_map[temp_x][temp_y] != -1){
                    QueueNode *temp = new QueueNode(make_pair(temp_x, temp_y));
                    path.Push(temp);
                    break;
                }
            }
            else if(i==3){ // direction left
                temp_x = p.first;
                temp_y = p.second - 1;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] < dis_map[p.first][p.second] && dis_map[temp_x][temp_y] != -1){
                    QueueNode *temp = new QueueNode(make_pair(temp_x, temp_y));
                    path.Push(temp);
                    break;
                }
            }
        }
        if(dis_map[temp_x][temp_y] == 0)
            return path;
    }
}

bool is_clean(){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(check_map[i][j] == Unvisited) return false;
        }
    }
    return true;
}


int main(){
    // Read file
    string M, N, Battery;
    int battery, R_x, R_y;
    char data;
    ifstream input("floor.data");
    input >> M;
    m = stoi(M);
    input >> N;
    n = stoi(N);
    input >> Battery;
    battery = stoi(Battery);

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            input >> data;
                if(data=='R'){
                    R_x = i;
                    R_y = j;
                }
            map[i][j] = data;
        }
    }

    my_BFS(R_x, R_y);

    // 等等要用while迴圈包起來 檢查如果還有沒有清乾淨的點 就繼續 否則 遊戲結束!!!
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(map[i][j]=='0' || map[i][j]=='R') check_map[i][j] = Unvisited;
            else if(map[i][j]=='1') check_map[i][j] = Visited;
        }
    }
    ofstream output("final.path");

    int count = 0;
    QueueList ans;
    QueueNode *temp;
    QueueNode *temp1;
    QueueNode *temp2;
    while(!is_clean()){
        int target_x=0, target_y=0, max_dis=0;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(dis_map[i][j] >= max_dis && check_map[i][j] == Unvisited) {
                    max_dis = dis_map[i][j];
                    target_x = i;
                    target_y = j;
                }
            }
        }
        QueueNode *start = new QueueNode(make_pair(R_x, R_y));
        QueueNode *target = new QueueNode(make_pair(target_x, target_y));

        QueueList path = find_path(start, target);

        check_map[R_x][R_y] = Visited;
        while(path.getSize()!=1){
            temp = path.getBack();

            check_map[temp->data.first][temp->data.second] = Visited;

            int x = temp->data.first;
            int y = temp->data.second;
            temp1 = new QueueNode(make_pair(x, y));
            ans.Push(temp1);
            path.Pop_back();
            count++;
        }

        path.Pop_back();
        path = find_path(start, target);
        while(path.getSize()!=1){
            temp = path.getFront();

            check_map[temp->data.first][temp->data.second] = Visited;
            temp1 = new QueueNode(make_pair(temp->data.first, temp->data.second));
            ans.Push(temp1);

            path.Pop();
            count++;
        }
    }
    temp = new QueueNode(make_pair(R_x, R_y));
    ans.Push(temp);

    temp = ans.getFront();
    output << count << endl;
    while(temp!=0){
        output << temp->data.first << " " << temp->data.second << endl;
        ans.Pop();
        temp = ans.getFront();
    }

}
