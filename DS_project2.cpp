#include <iostream>
#include <fstream>

using namespace std;

enum state{Visited, Unvisited};
char map[1000][1000];
int dis_map[1000][1000], m, n;
state check_map[1000][1000];

class QueueList;
class QueueNode{
    friend QueueList;
    public:
        pair <int, int> data;
        QueueNode *next;
        QueueNode *next1;
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
        void Push(QueueNode *node);
        void Pop();
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

    back->next = node;
    back = back->next;
    size++;
}

void QueueList::Pop(){
    if(IsEmpty()) return;

    QueueNode *temp = front;
    front = front->next;
    size--;
    /*delete temp;
    temp = 0;*/
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
    state map_state[m][n];
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

QueueNode *find_path(QueueNode *start, QueueNode *target){
    QueueList que;
    // initialize map_state  dis_map
    state map_state[m][n];
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            //cout << i << ' ' << j << endl;
            if(map[i][j]=='0' || map[i][j]=='R') map_state[i][j] = Unvisited;
        }
    }

    que.Push(start);
    while(!que.IsEmpty()){
        // pick a node from que.front
        pair<int, int> p = que.getFront()->data;
        QueueNode *temp1 = que.getFront();

        //cout << "temp1 before pop: " << temp1->data.first << " " << temp1->data.second << endl;

        que.Pop();
        //cout << "temp1 after pop: " << temp1->data.first << " " << temp1->data.second << endl;
        map_state[p.first][p.second] = Visited;

        int temp_x, temp_y; // new point
        // go through all points
        for(int i=0; i<4; i++){
            if(i==0){ // direction upon
                temp_x = p.first - 1;
                temp_y = p.second;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(map_state[temp_x][temp_y] == Unvisited && (map[temp_x][temp_y] == '0' || map[temp_x][temp_y] == 'R')){
                    QueueNode *temp2 = new QueueNode(make_pair(temp_x, temp_y));
                    temp2->next1 = temp1;
                    que.Push(temp2);

                    /*QueueNode *root = temp2;
                    while(root!=0){
                        cout << root->data.first << " " << root->data.second << endl;
                        root = root->next1;
                    }
                    cout << endl;*/

                    if(temp_x == target->data.first && temp_y == target->data.second){ // find target
                        return temp2;
                    }
                }
            }
            else if(i==1){  // direction down
                temp_x = p.first + 1;
                temp_y = p.second;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(map_state[temp_x][temp_y] == Unvisited && (map[temp_x][temp_y] == '0' || map[temp_x][temp_y] == 'R')){
                    QueueNode *temp2 = new QueueNode(make_pair(temp_x, temp_y));
                    que.Push(temp2);
                    temp2->next1 = temp1;

                    /*QueueNode *root = temp2;
                    while(root!=0){
                        cout << root->data.first << " " << root->data.second << endl;
                        root = root->next1;
                    }
                    cout << endl;*/

                    if(temp_x == target->data.first && temp_y == target->data.second){ // find target
                        return temp2;
                    }
                }
            }
            else if(i==2){ // direction right
                temp_x = p.first;
                temp_y = p.second + 1;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(map_state[temp_x][temp_y] == Unvisited && (map[temp_x][temp_y] == '0' || map[temp_x][temp_y] == 'R')){
                    QueueNode *temp2 = new QueueNode(make_pair(temp_x, temp_y));
                    que.Push(temp2);
                    temp2->next1 = temp1;

                    /*QueueNode *root = temp2;
                    while(root!=0){
                        cout << root->data.first << " " << root->data.second << endl;
                        root = root->next1;
                    }
                    cout << endl;*/

                    if(temp_x == target->data.first && temp_y == target->data.second){ // find target
                        return temp2;
                    }
                }
            }
            else if(i==3){ // direction left
                temp_x = p.first;
                temp_y = p.second - 1;
                if(temp_x < 0 || temp_y < 0 || temp_x >= m || temp_y >= n) continue;
                else if(map_state[temp_x][temp_y] == Unvisited && (map[temp_x][temp_y] == '0' || map[temp_x][temp_y] == 'R')){
                    QueueNode *temp2 = new QueueNode(make_pair(temp_x, temp_y));
                    que.Push(temp2);
                    temp2->next1 = temp1;

                    /*QueueNode *root = temp2;
                    while(root!=0){
                        cout << root->data.first << " " << root->data.second << endl;
                        root = root->next1;
                    }
                    cout << endl;*/

                    if(temp_x == target->data.first && temp_y == target->data.second){ // find target
                        return temp2;
                    }
                }
            }
        }
    }
    return 0;
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

    /*for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            dis_map[i][j] = -1;
        }
    }*/

    my_BFS(R_x, R_y);

    // 等等要用while迴圈包起來 檢查如果還有沒有清乾淨的點 就繼續 否則 遊戲結束!!!
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            //cout << i << ' ' << j << endl;
            if(map[i][j]=='0' || map[i][j]=='R') check_map[i][j] = Unvisited;
            else if(map[i][j]=='1') check_map[i][j] = Visited;
        }
    }
    ofstream output("floor.final");
    //output << "         " << endl;
    int count = 0;
    QueueList ans;
    QueueNode *temp;
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
        // from R to target
        QueueNode *root = find_path(target, start);

        while(root->next1!=0){
            check_map[root->data.first][root->data.second] = Visited;
            //cout << root->data.first << " " << root->data.second << endl;
            //output << root->data.first << " " << root->data.second << endl;
            temp = new QueueNode(make_pair(root->data.first, root->data.second));
            ans.Push(temp);
            root = root->next1;
            count++;
        }
        // from target to R
        root = find_path(start, target);
        //root = root->next1;
        while(root->next1!=0){
            check_map[root->data.first][root->data.second] = Visited;
            //cout << root->data.first << " " << root->data.second << endl;
            //output << root->data.first << " " << root->data.second << endl;
            temp = new QueueNode(make_pair(root->data.first, root->data.second));
            ans.Push(temp);
            root = root->next1;
            count++;
        }  
    }
    //cout << R_x << " " << R_y << endl;
    //output << R_x << " " << R_y << endl;
    temp = new QueueNode(make_pair(R_x, R_y));
    ans.Push(temp);

    temp = ans.getFront();
    ans.Pop();
    output << count << endl;
    while(temp!=0){
        output << temp->data.first << " " << temp->data.second << endl;
        temp = ans.getFront();
        ans.Pop();
    }

    /*output.seekp(0, ios::beg);
    ifstream in("floor.final");
    //cout << count;
    //output << count;
    string temp1_in, temp2_in, t1, t2;
    in >> temp1_in >> temp2_in;
    t1 = temp1_in;
    t2 = temp2_in;
    output << count << endl;
    output << temp1_in << " " << temp2_in << endl;
    while(!in.eof()){
        in >> temp1_in >> temp2_in;
        output << temp1_in << " " << temp2_in << endl;
    }*/

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
