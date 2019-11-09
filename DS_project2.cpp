#include <iostream>
#include <fstream>

using namespace std;

char map[1000][1000];
int dis_map[1000][1000], m, n, map_state[1000][1000];

class QueueList;
class QueueNode{
    friend QueueList;
    public:
        pair <int, int> data;
        QueueNode *next;
        QueueNode():data(0, 0), next(0){};
        QueueNode(pair <int, int> x):data(x), next(0){};
};

class QueueList{
    private:
        QueueNode *front;
        QueueNode *back;
        int size;
    public:
        QueueList():front(0), back(0), size(0){};
        void Push(pair <int, int> x);
        void Pop();
        bool IsEmpty();
        QueueNode *getFront();
        QueueNode *getBack();
        int getSize();
};

void QueueList::Push(pair <int, int> x){
    if(IsEmpty()) {
        front = new QueueNode(x);
        back = front;
        size = 1;
        return;
    }

    back->next = new QueueNode(x);
    back = back->next;
    size++;
}

void QueueList::Pop(){
    if(IsEmpty()) return;

    QueueNode *temp = front;
    front = front->next;
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
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            //cout << i << ' ' << j << endl;
            if(map[i][j]=='0') map_state[i][j] = 0;
            dis_map[i][j] = -1;
        }
    }
    // position of R
    dis_map[x][y] = 0;

    que.Push(make_pair(x, y));
    while(!que.IsEmpty()){
        // pick a node from que.front
        pair<int, int> p = que.getFront()->data;
        que.Pop();
        map_state[p.first][p.second] = 1;

        int temp_x, temp_y; // new point
        // go through all points
        for(int i=0; i<4; i++){
            if(i==0){ // direction upon
                temp_x = p.first - 1;
                temp_y = p.second;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] == -1 && map_state[temp_x][temp_y] == 0 && map[temp_x][temp_y] == '0'){
                    que.Push(make_pair(temp_x, temp_y));
                    dis_map[temp_x][temp_y] = dis_map[p.first][p.second] + 1;
                }
            }
            else if(i==1){  // direction down
                temp_x = p.first + 1;
                temp_y = p.second;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] == -1 && map_state[temp_x][temp_y] == 0 && map[temp_x][temp_y] == '0'){
                    que.Push(make_pair(temp_x, temp_y));
                    dis_map[temp_x][temp_y] = dis_map[p.first][p.second] + 1;
                }
            }
            else if(i==2){ // direction right
                temp_x = p.first;
                temp_y = p.second + 1;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] == -1 && map_state[temp_x][temp_y] == 0 && map[temp_x][temp_y] == '0'){
                    que.Push(make_pair(temp_x, temp_y));
                    dis_map[temp_x][temp_y] = dis_map[p.first][p.second] + 1;
                }
            }
            else if(i==3){ // direction left
                temp_x = p.first;
                temp_y = p.second - 1;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(dis_map[temp_x][temp_y] == -1 && map_state[temp_x][temp_y] == 0 && map[temp_x][temp_y] == '0'){
                    que.Push(make_pair(temp_x, temp_y));
                    dis_map[temp_x][temp_y] = dis_map[p.first][p.second] + 1;
                }
            }
        }

    }

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

    /*for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            dis_map[i][j] = -1;
        }
    }*/

    my_BFS(R_x, R_y);

    // Debug
    /*for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }*/

    /*for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            printf("%3d ", dis_map[i][j]);
        }
        cout << endl;
    }*/

    // Debug myqueue
    /*QueueList *head = new QueueList();
    for(int i=0; i<5; i++){
        for(int j=0; j<3; j++){
            head->Push(make_pair(i,j));
        }
    }
    for(int i=0; i<5; i++){
        for(int j=0; j<3; j++){
            cout << '(' << head->getFront()->data.first << ", " << head->getFront()->data.second << ')' << " ";
            head->Pop();
        }
    }*/


}
