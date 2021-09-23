#include "BTNode.h"

template <typename T>
class BTree{
    protected:
    int _size;
    int _order;
    BTNodePosi(T) _root;
    BTNodePosi(T) _hot;
    void solveOverflow(BTNodePosi(T));
    void solveUnderflow(BTNodePosi(T));

    public:
    BTree(int order = 3) : _order(order), _size(0){
        _root = new BTNode<T>();
    }
    ~BTree(){
        if(_root){
            release(_root);
        }
    }
    int const order(){
        return _order;
    }
    int const size(){
        return _size;
    }
    BTNodePosi(T) & root(){
        return _root;
    }
    bool empty() const {
        return !_root;
    }
    BTNodePosi(T) search(const T& e);
    bool insert(const T& e);
    bool remove(const T& e);
};

template <typename T>
BTNodePosi(T) BTree<T>::search(const T& e){
    BTNodePosi(T) v = _root;
    _hot = NULL;
    while(v){
        Rank r = v->key.search(e);
        if((0<=r)&&(e==v->key[r])){
            return v;
        }
        _hot = v;
        v = v->child[r+1];
    }
    return NULL;
}

template <typename T>
bool BTree<T>::insert(const T& e){
    BTNodePosi(T) v = search(e);
    if(v){
        return false;
    }
    Rank r = _hot->key.search(e);
    _hot->key.insert(r+1, e);
    _hot->child.insert(r+2, NULL);
    _size++;
    solveOverflow(_hot);
    return true;
}

template <typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v){
    if(_order >= v->child.size()){//递归基-当前节点并未上溢
        return;
    }
    Rank s = _order/2;
    BTNodePosi(T) u = new BTNode<T>();
    for(Rank j = 0; j<_order-s-1; j++){// v 右侧 _order-s-1个孩子及关键码分裂为右侧节点u
        u->child.insert(j, v->child.remove(s+1));
        u->key.insert(j, v->key.remove(s+1));
    }
    u->child[_order-s-1] = v->child.remove(s+1);
    if(u->child[0]){
        for(Rank j=0; j<_order-s; j++){
            u->child[j]->parent = u;
        }
    }
    BTNodePosi(T) p = v->parent;
    if(!p){
        _root = p = new BTNode<T>();
        p->child[0] = v;
        v->parent = p;
    }
    Rank r = 1 + p->key.search(v->key[0]);
    p->key.insert(r, v->key.remove(s));
    p->child.insert(r+1, u);
    u->parent = p;
    solveOverflow(p);

}

template <typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v){ //关键码插入后若节点上溢，则做节点分裂处理
    if(_order >= v->child.size()){
        return;
    }
    Rank s = _order/2;
    BTNodePosi(T) u = new BTNode<T>();
    for(Rank j=0; j<_order-s-1; j++){//v右侧_order-s-1个孩子及关键码分裂为右侧节点u
        u->child.insert(j, v->child.remove(s+1));
        u->key.insert(j, v->key.remove(s+1));
    }
    u->child[_order-s-1] = v->child.remove(s+1);

    if(u->child[0]){
        for(Rank j=0; j<_order-s; j++){
            u->child[j]->parent = u;
        }
    }
    BTNodePosi(T) p = v->parent;
    if(!p){//若u的孩子们非空，则令它们的父节点统一
        _root = p = new BTNode<T>();
        p->child[0] = v;
        v->parent = p;
    }
    Rank r = 1 + p->key.search(v->key[0]);//p中指向u的指针的秩
    p->key.insert(r, v->key.remove(s));//轴点关键码上升
    p->child.insert(r+1, u);
    u->parent = p; //新节点u与父节点p互联
    solveOverflow(p);
}

template <typename T>
bool BTree<T>::remove(const T& e){
    BTNodePosi(T) v = search(e);
    if(!v){
        return false;
    }
    Rank r = v->key.search(e);
    if(v->child[0]){//若v非叶子，则e的后继必属于某叶节点
        BTNodePosi(T) u = v->child[r+1];//在右子树中一直向左，即可
        while(u->child[0]){
            u = u->child[0];//找出e的后继
            //并与之交换位置
            v->key[r] = u->key[0];
            v = u;
            r = 0;
        }//至此，v必然位于最底局，且其中第r个关键码就是待删除者
    }
    v->key.remove(r);
    v->child.remove(r+1);
    _size--;
    solveUnderflow(v);
    return true;
}