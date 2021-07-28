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