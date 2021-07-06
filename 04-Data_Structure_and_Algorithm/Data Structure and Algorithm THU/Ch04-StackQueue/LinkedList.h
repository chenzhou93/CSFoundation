#ifndef LINKEDLIST_H__
#define LINKEDLIST_H__

#include "ListNode.h"


template <typename T>
class List{
    private:
    int _size;
    ListNodePosi(T) head;
    ListNodePosi(T) tail;

    protected:
    void init();
    int clear();
    void copyNodes(ListNodePosi(T), int);
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
    void mergeSort(ListNodePosi(T)&, int);
    void selectionSort(ListNodePosi(T), int);
    void insertionSort(ListNodePosi(T), int);

    public:
    List() { init(); } //默认
    List ( List<T> const& L ); //整体复制列表L
    List ( List<T> const& L, Rank r, int n ); //复制列表L中自第r项起的n项
    List ( ListNodePosi(T) p, int n ); //复制列表中自位置p起的n项
    // 析构函数
    ~List(); //释放（包含头、尾哨兵在内的）所有节点
    // 叧读访问接口
    Rank size() const { return _size; } //规模
    bool empty() const { return _size <= 0; } //判空
    T& operator[] ( Rank r ) const; //重载，支持循秩访问（效率低）
    ListNodePosi(T) first() const { return head->succ; } //首节点位置
    ListNodePosi(T) last() const { return tail->pred; } //末节点位置
    bool valid ( ListNodePosi(T) p ) //判断位置p是否对外合法
    { return p && ( tail != p ) && ( head != p ); } //将头、尾节点等同亍NULL
    int disordered() const; //判断列表是否已排序
    ListNodePosi(T) find ( T const& e ) const //无序列表查找
    { return find ( e, _size, tail ); }
    ListNodePosi(T) find ( T const& e, int n, ListNodePosi(T) p ) const; //无序区间查找
    ListNodePosi(T) search ( T const& e ) const //有序列表查找
    { return search ( e, _size, tail ); }
    ListNodePosi(T) search ( T const& e, int n, ListNodePosi(T) p ) const; //有序区间查找
    ListNodePosi(T) selectMax ( ListNodePosi(T) p, int n ); //在p及其n-1个后继中选出最大者
    ListNodePosi(T) selectMax() { return selectMax ( head->succ, _size ); } //整体最大者
    // 可写访问接口
    ListNodePosi(T) insertAsFirst ( T const& e ); //将e当作首节点揑入
    ListNodePosi(T) insertAsLast ( T const& e ); //将e当作末节点揑入
    ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e ); //将e当作p的后继揑入
    ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e ); //将e当作p的前驱揑入
    T remove ( ListNodePosi(T) p ); //初除合法位置p处的节点,迒回被初除节点
    void merge ( List<T>& L ) { merge ( first(), size(), L, L.first(), L._size ); } //全列表归并
    void sort ( ListNodePosi(T) p, int n ); //列表区间排序
    void sort() { sort ( first(), _size ); } //列表整体排序
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    void reverse(); //前后倒置（习题）
    void reverse1();
    void reverse2();
// 遍历
    void traverse ( void (* ) ( T& ) ); //遍历，依次实现visit操作（函数指针，叧读戒局部性修改）
    template <typename VST> //操作器
    void traverse ( VST& ); //遍历，依次实现visit操作（函数对象，可全局性修改）
};

template<typename T>
void List<T>::init(){
    head = new ListNode<T>;
    tail = new ListNode<T>;
    head->succ = tail;
    head->pred = NULL;
    tail->succ = NULL;
    tail->pred = head;
    _size = 0;
}

template <typename T>
T& List<T>::operator[](Rank r) const{
    ListNodePosi(T) p = first();
    while(0 < r--){
        p = p->succ;
    }
    return p->data;
}

template<typename T>//在无序列表内节点p的n个前驱中，找到等于e的最后一个节点
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const{
    while(0 < n--){
        if(e == (p=p->pred)->data){
            return p;
        }
    }
    return NULL;
}

//插入
template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e){
    _size++;
    return head->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e){
    _size++;
    return tail->insertAsPred(e);
}

template <typename T>//insert after
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e){
    _size++;
    return p->insertAsSucc(e);
}

template <typename T>//insert before
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e){
    _size++;
    return p->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e){
    ListNodePosi(T) x = new ListNode(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e){
    ListNodePosi(T) x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n){
    init();
    while(n--){
        insertAsLast(p->data);
        p = p->succ;
    }
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n){
    copyNodes(p, n);
}

template <typename T>
List<T>::List(List<T> const& L){
    copyNodes(L.first(), L._size());
}

template <typename T>
List<T>::List(List<T> const& L, int r, int n){
    copyNodes(L[r], n);
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p){
    T e = p->data;
    p->pred = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template <typename T>
List<T>::~List(){
    clear();
    delete head;
    delete tail;
}

template <typename T>
int List<T>::clear(){
    int oldSize = _size;
    while(0 < _size){
        remove(head->succ);//反复删除首节点，直到列表为空
    }
    return oldSize;
}

template <typename T>
int List<T>::deduplicate(){
    if(_size < 2){
        return 0;
    }
    int oldSize = _size;
    ListNodePosi(T) p = head;
    Rank r = 0;

    while(tail != (p=p->succ)){
        ListNodePosi(T) q = find(p->data, r, p);
        q ? remove(q) : r++;
    }

    return oldSize - _size;
}

template <typename T>
void List<T>::traverse(void(*visit)(T& )){
    for(ListNodePosi(T) p = head->succ; p != tail; p=p->succ){
        visit(p->data);
    }
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST& visit){
    for(ListNodePosi(T) p = head->succ; p!=tail; p=p->succ){
        visit(p->data);
    }
}

template <typename T>
int List<T>::uniquify(){
    if(_size < 2){
        return 0;
    }
    int oldSize = _size;
    ListNodePosi(T) p = first();
    ListNodePosi(T) q;
    while(tail != (q=p->succ)){
        if(p->data != q->data){
            p = q;
        }else{
            remove(q);
        }
    }
    return oldSize - _size;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const{
    while(0 <= n--){
        if(((p=p->pred)->data) <= e){
            break;
        }
    }
    return p;
}//失败时，返回区间左边界的前驱（可能是header）——调用者可通过valid()判断成功与否

template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n){
    switch(rand() % 3){
        case 1: insersionSort(p, n); break;
        case 2: selectionSort(p, n); break;
        default: mergeSort(p, n); break;
    }
}

template <typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n){
    for(int r=0; r<n; r++){
        insertA(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>//列表的选择排序算法：对起始于位置p的n个元素排序
void List<T>::selectionSort(ListNodePosi(T) p, int n){
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for(int i=0; i<n; i++){
        tail = tail->succ;
    }
    while(1 < n){
        ListNodePosi(T) max = selectMax(head->succ, n);
        insertB(tail, remove(max));
        tail = tail->pred;
        n--;
    }
}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n){
    ListNodePosi(T) max = p;
    for(ListNodePosi(T) cur=p; 1<n; n--){
        if(!lt((cur=cur->succ)->data,max->data)){
            max = cur;
        }
    }
    return max;
}

template <typename T>
//有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m){
    ListNodePosi(T) pp = p->pred;
    while(0 < m){
        if((0<n) && (p->data <= q->data)){
            if(q == (p=p->succ))
                break;
            n--;
        }else{
            insertB(p, L.remove((q=q->succ)->pred));
            m--;
        }
    }
    p = pp->succ;
}

template <typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n){
    if(n < 2){
        return;
    }
    int m = n >> 1;
    ListNodePosi(T) q = p;
    for(int i=0; i<m; i++){
        q = q->succ;
    }
    mergeSort(p, m);
    mergeSort(q, n-m);
    merge(p, m, *this, q, n-m);
}

template <typename T>
void List<T>::reverse(){
    if(_size < 2) return;
    ListNodePosi(T) p;
    ListNodePosi(T) q;
    for(p=head, q=p->succ; p != tail; p=q, q=p->succ){
        p->pred = q;//自前向后，依次颠倒各节点的前驱指针
    }
    tail->pred = NULL;
    
    for(p=head, q=p->pred; p != tail; p=q, q=p->pred){
        q->succ = p;//自前向后，依次颠倒各节点的后继指针
    }
    head->succ = NULL;
    swap(head, tail);
}

template <typename T>
void List<T>::reverse1(){
    if(_size < 2){
        return;
    }
    for(ListNodePosi(T) p=head; p; p=p->pred){
        swap(p->pred, p->succ);
    }
    swap(head, tail);
}

template <typename T>
void List<T>::reverse2(){
    ListNodePosi(T) p = head;
    ListNodePosi(T) q = tail;
    for(int i=1; i<_size; i+=2){
        swap((p=p->succ)->data, (q=q->pred)->data);
    }
}



#endif