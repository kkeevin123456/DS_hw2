#include <iostream>
#include <fstream>

using namespace std;

enum state {Unvisited, Visited};

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

int main(){
    // Read file
    string M, N, Battery;
    int m, n, battery;
    char data;
    ifstream input("floor.data");
    input >> M;
    m = stoi(M);
    input >> N;
    n = stoi(N);
    input >> Battery;
    battery = stoi(Battery);

    char map[m][n];
    int dis_map[m][n];
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            input >> data;
            map[i][j] = data;
        }
    }

    // Debug
    /*for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cout << map[i][j] << " ";
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