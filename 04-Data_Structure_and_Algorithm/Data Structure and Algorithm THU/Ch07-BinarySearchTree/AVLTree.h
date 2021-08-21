#include "BST.h"

#define Balanced(x) (stature((x).lc) == stature((x).rc))
#define BalFac(x) (stature((x).lc) - stature((x).rc))
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))

/*
    在左右孩子中取最高者
    在avl平衡调整前，借此确定重构方案
*/
#define tallerChild(x)( \
    stature((x)->lc > stature((x)->rc) ? (x)->lc) : ( \
        stature((x)->lc) < stature((x)->rc) ? (x)->rc : \
        IsLChild(*(x)) ? (x)->lc : (x)->rc) \
    ) \
) 

template <typename T>
class AVL: public BST<T>{
    public:
    BinNodePosi(T) insert(const T& e);
    bool remove(const T& e);
};

template <typename T>
BinNodePosi(T) AVL<T>::insert(const T& e){
    BinNodePosi(T)& x = search(e);
    if(x){
        return x;
    }
    BinNodePosi(T) xx = x = new BinNode<T>(e, _hot); 
    _size++;
    for(BinNodePosi(T) g=_hot; g; g=g->parent){
        if(!AvlBalanced(*g)){
            FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
            break;
        }else{
            updateHeight(g);
        }
    }
    return xx;
}