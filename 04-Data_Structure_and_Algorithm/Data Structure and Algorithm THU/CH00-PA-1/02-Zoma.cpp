#include <iostream>
#include <string>
using namespace std;

class Node{
    public:
    char ch;
    Node* prev;
    Node* next;
};

class LinkedList{
    public:
    int size;
    Node* head;
    Node* tail;
    LinkedList(){
        head = new Node();
        tail = new Node();
        head->ch = '0';
        tail->ch = '0';
        head->prev = NULL;
        head->next = tail;
        tail->prev = head;
        tail->next = NULL;
    }

    ~LinkedList(){
        Node* p = head;
        while(p){
            Node* next = p->next;
            delete p;
            p = next;
        }
    }
    void pushBack(char value);
    void remove(Node* node);
    Node* insertAt(int n, char value);
    bool checkThree(Node* node);
    Node* removeThree(Node* node);
    void output();
};

void LinkedList::pushBack(char value){
    //cout << "value: " << value << endl;
    if(!value){
        return;
    }
    Node* p = head;
    while(p->next != tail){
        p = p->next;
    }

    Node* newNode = new Node();
    newNode->ch = value;
    newNode->next = p->next;
    newNode->prev = p;
    p->next->prev = newNode;
    p->next = newNode;

}

void LinkedList::remove(Node* node){
    Node* p = node;
    p->prev->next = p->next;
    p->next->prev = p->prev;

    p->prev = NULL;
    p->next = NULL;
    delete p;
}

Node* LinkedList::insertAt(int n, char value){
    Node* p = head;
    int i = 0;
    while(p->next != tail && i<n){
        p = p->next;
        i++;
    }

    Node* node = new Node();
    node->ch = value;
    node->prev = p;
    node->next = p->next;
    p->next->prev = node;
    p->next = node;

    return node;
}

bool LinkedList::checkThree(Node* node){
    if(node == head && node->next == tail){
        return false;
    }
    if(node == tail && node->prev == head){
        return false;
    }
    Node* p = node->prev;
    Node* q = node->next;
    int left = 0;
    int right = 0;

    while(p->ch == node->ch || q->ch == node->ch){
        if(p->ch == node->ch){
            p = p->prev;
            left++;
        }else if(q->ch == node->ch){
            q = q->next;
            right++;
        }
    }
    
    if(left + right >= 2){
        return true;
    }
    
    return false;
}

Node* LinkedList::removeThree(Node* node){
    //cout << "remove three: " << node->ch << endl;
    Node* p = node->prev;
    Node* q = node->next;

    while(p->ch == node->ch || q->ch == node->ch){
        if(p->ch == node->ch){
            Node* p1 = p->prev;
            remove(p);
            p = p1;
            //cout << "p1: " << p->ch << endl;
        }else if(q->ch == node->ch){
            Node* q1 = q->next;
            remove(q);
            q = q1;
            //cout << "q1: " << q->ch << endl;
        }
    }
    remove(node);

    Node* res = new Node();

    if(q->ch != '0'){
        res = q;
    }else{
        res = p;
    } 
    //cout << "res ch: " << res->ch << endl;
    return res;
}

void LinkedList::output(){
    Node* p = head->next;
    if(p == tail){
        cout << '-' << endl;
    }else{
        while(p != tail){
            cout << p->ch;
            p = p->next;
        }
        cout << endl;
    }
    
}

int main(){
    LinkedList list;
    string str = "";
    char ch;
    int n;
    cin >> str;
    
    for(int i=0; i<str.size(); i++){
        list.pushBack(str[i]);
    }
    
    
    cin >> n;
    for(int i=0; i<n; i++){
        int pos;
        char v;
        cin >> pos >> v;
        Node* p = list.insertAt(pos, v);
        while(list.checkThree(p)){
            p = list.removeThree(p);
        }
        list.output();
    }
    
    return 0;
}