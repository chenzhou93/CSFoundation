#include "../Ch05-BinaryTree/BinTree.h"

template <typename K, typename V>
struct Entry{
    K key; V value;
    Entry(K k = K(), V v = V()) : key(k), value(v){};
    Entry(Entry<K,V> const& e) : key(e.key), value(e.value){};

    bool operator<(Entry<K,V> const& e){
        return key < e.key;
    }
    bool operator>(Entry<K,V> const& e){
        return key > e.key;
    }
    bool operator==(Entry<K,V> const& e){
        return key == e.key;
    }
    bool operator!=(Entry<K,V> const& e){
        return key != e.key;
    }
};

template <typename T>
class BST : public BinTree<T>{
    protected:
    BinNodePosi(T) _hot; //"命中"节点的父亲
    BinNodePosi(T) connect34(//按照3+4结构，联接3个节点及4棵子树
        BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
        BinNodePosi(T),BinNodePosi(T),BinNodePosi(T),BinNodePosi(T));
    
    BinNodePosi(T) rotateAt(BinNodePosi(T) x);//对x及其父亲、祖父做统一旋转调整

    public:
    virtual BinNodePosi(T) & search(const T& e);
    virtual BinNodePosi(T) insert(const T& e);
    virtual bool remove(const T& e);
};

template <typename T>
static BinNodePosi(T)& searchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T)& hot){
    if(!v || (e == v->data)){
        return v;
    }
    hot = v;
    return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);
}

template <typename T>
BinNodePosi(T)& BST<T>::search(const T& e){
    return searchIn(_root, e, _hot=NULL);
}

template <typename T>
BinNodePosi(T) BST<T>::insert(const T& e){
    BinNodePosi(T)& x = search(e);
    if(x){
        return x;
    }
    x = new BinNode<T>(e, _hot);
    _size++;
    updateHeightAbove(x);
    return x;
}


template <typename T>
bool BST<T>::remove(const T& e){
    BinNodePosi(T)& x = search(e);
    if(!x){
        return false;
    }
    removeAt(x, _hot);
    _size--;
    updateHeightAbove(_hot);
    return true;
}

/*
    BST节点删除算法： 删除位置x所指的节点（全局静态模板函数 ，用于AVL、Splay、RedBlack等各种BST
    目标x在此前经查找定位，并确认非NULL，故必删除成功；与searchIn不同，调用之前不必将hot置空
    返回值指向实际被删除节点的接替者，hot指向实际被删除节点的父亲；二者均有可能是NULL
*/
template<typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot){
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = NULL;//实际被删除节点的接替 
    if(!HasLChild(*x)){//若*x的左子树为空 则可直接将*x替换为其右子树
        succ = x = x->rc;
    }else if(!HasRChild(*x)){//若右子树为空 则可对称地处理——注意 此时succ != NULL
        succ = x = x->lc;
    }else{//若左右子树均存在，则选择x的直接后继作为实际摘除节点，为此需要（在右子树中）找到 *x的直接后继 *w  
        w = w->succ();
        swap(x->data, w->data);
        BinNodePosi(T) u = w->parent;
        ((u==x) ? u->rc : u->lc) = succ = w->rc;//隔离节点*w
    }
    hot = w->parent;//记录实际被删除节点的父亲
    if(succ){
        succ->parent = hot;//并将被删除节点的接替者与hot相联
    }
    release(w->data);//释放被摘除节点，返回接替者
    release(w);
    return succ;
}