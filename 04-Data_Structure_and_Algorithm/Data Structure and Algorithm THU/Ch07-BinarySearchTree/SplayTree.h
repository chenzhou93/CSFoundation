#include "BST.h"
template <typename T>
class Splay : public BST<T>{
    protected:
        BinNodePosi(T) splay(BinNodePosi(T) v);
    public:
        BinNodePosi(T)& search(const T& e);
        BinNodePosi(T) insert(const T& e);
        bool remove(const T& e);
};

template <typename NodePosi> inline
void attachAsLChild(NodePosi p, NodePosi lc){
    p->lc = lc;
    if(lc){
        lc->parent = p;
    }
}
template <typename NodePosi> inline
void attachAsRChild(NodePosi p, NodePosi rc){
    p->rc = rc;
    if(rc){
        rc->parent = p;
    }
}

template <typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v){
    if(!v){
        return NULL;
    }
    BinNodePosi(T) p;
    BinNodePosi(T) g;
    
    while((p=v->parent) && (g=p->parent)){
        BinNodePosi(T) gg = g->parent;
        if(IsLChild(*v)){
            if(IsLChild(*p)){//zig-zig
                attachAsLChild(g, p->rc);
                attachAsLChild(p, v->rc);
                attachAsRChild(p, g);
                attachAsRChild(v, p);
            }else{//zig-zag
                attachAsLChild(p, v->rc);
                attachAsRChild(g, v->lc);
                attachAsLChild(v, g);
                attachAsRChild(v, p);
            }
        }else if(IsRChild(*p)){
            attachAsRChild(g, p->lc);
            attachAsRChild(p, v->lc);
            attachAsLChild(p, g);
            attachAsLChild(v, p);
        }else{
            attachAsRChild(p, v->lc);
            attachAsLChild(g, v->rc);
            attachAsRChild(v, g);
            attachAsLChild(v, p);
        }
        if(!gg){
            v->parent = NULL;
        }else{
            (g = gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
        }
        updateHeight(g); updateHeight(p); updateHeight(v);
    }
    if(p = v->parent){
        if(IsLChild(*v)){
            attachAsLChild(p, v->rc);
            attachAsRChild(v, p);
        }else{
            attachAsRChild(p, v->lc);
            attachAsLChild(v, p);
        }
        updateHeight(p);
        updateHeight(v);
    }
    v->parent = NULL;
    return v;
}

template <typename T>
BinNodePosi(T)& Splay<T>::search(const T& e){
    BinNodePosi p = searchIn(_root, e, _hot=NULL);//searchIn 二叉树通用算法
    _root = splay(p ? p : _hot);
    return _root;
}

template <typename T>
BinNodePosi(T) Splay<T>::insert(const T& e){
    if(!_root){
        _size++;
        return _root = new BinNode<T>(e);
    }
    if(e == search(e)->data){
        return _root;
    }
    _size++;
    BinNodePosi(T) t = _root;
    if(_root->data < e){
        t->parent = _root = new BinNode<T>(e, NULL, t, t->rc);
        if(HasRChild(*t)){
            t->rc->parent = _root;
            t->rc = NULL;
        }
    }else{
        t->parent = _root = new BinNode<T>(e, NULL, t->lc, t);
        if(HasLChild(*t)){
            t->lc->parent = _root;
            t->lc = NULL;
        }
    }
    updateHeightAbove(t);
    return _root;
}

template <typename T>
bool Splay<T>::remove(const T& e){
    if(!_root || (e != search(e)->data)){
        return false;
    }
    BinNodePosi(T) w = _root;
    if(!HasLChild(*root)){//若无左子树 则直接删除
        _root = _root->rc;
        if(_root){
            _root->parent = NULL;
        }
    }else if(!HasRChild(*_root)){//若无右子树 则直接删除
        _root = _root->lc;
        if(_root){
            _root->parent = NULL;
        }
    }else{
        BinNodePosi(T) lTree = _root->lc;
        lTree->parent = NULL;
        _root->lc = NULL;
        _root = _root->lc;
        _root->parent = NULL;

        search(w->data);//以原树根为目标，做一次必定失败的查找
        //至此，右子树中最小节点必伸展至根， 且因无雷同节点其左子树必空
        _root->lc = lTree;//只需要将左子树接回原位即可
        lTree->parent = _root;
    }
    release(w->data);
    release(w);
    _size--;
    if(_root){
        updateHeight(_root);
    }
    return true;
}