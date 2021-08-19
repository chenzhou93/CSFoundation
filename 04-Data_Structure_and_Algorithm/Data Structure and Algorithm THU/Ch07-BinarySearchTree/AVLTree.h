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
    BinNodePosi(T) insert(const & e);
    bool remove(const T& e);
};