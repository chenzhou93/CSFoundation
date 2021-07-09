#include "BinNode.h"
#include "../Ch04-StackQueue/Stack.h"
#include "../Ch04-StackQueue/Queue.h"

template <typename T>
class BinTree{
    protected:
    int _size;
    BinNodePosi(T) _root;
    virtual int updateHeight(BinNodePosi(T) x);//更新节点x的高度
    void updateHeightAbove(BinNodePosi(T) x);

    public:
    BinTree() : _size(0), _root(NULL){ }
    ~BinTree(){
        if(0 < _size){
            remove(_root);
        }
    }

    int size() const{
        return _size;
    }
    bool empty() const{
        return !_root;
    }
    BinNodePosi(T) root() const { return _root; } //树根
    BinNodePosi(T) insertAsRoot ( T const& e ); //插入根节点
    BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e ); //e作为x的左孩子（原无）插入
    BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e ); //e作为x的右孩子（原无）插入
    BinNodePosi(T) attachAsLC ( BinNodePosi(T) x, BinTree<T>* &T ); //T作为x左子树接入
    BinNodePosi(T) attachAsRC ( BinNodePosi(T) x, BinTree<T>* &T ); //T作为x右子树接入
    int remove ( BinNodePosi(T) x ); //删除以位置x处节点为根的子树，返回该子树原先的规模
    BinTree<T>* secede ( BinNodePosi(T) x ); //将子树x从当前树中摘除，并将其转换为一棵独立子树
    
    template <typename VST> //操作器
    void travLevel ( VST& visit ) { 
        if ( _root ){
            _root->travLevel ( visit ); 
        } 
    } //层次遍历

    template <typename VST>
    void travPre ( VST& visit ) { 
        if ( _root ){
            _root->travPre ( visit );
        } 
    }
    template <typename VST> //操作器
    void travIn ( VST& visit ) { 
        if ( _root ){
            _root->travIn ( visit ); 
        } 
            
    } //中序遍历

    template <typename VST> //操作器
    void travPost ( VST& visit ) { 
        if ( _root ){
            _root->travPost ( visit ); 
        }
    } //后序遍历
    
    bool operator< ( BinTree<T> const& t ){  //比较器 
        return _root && t._root && lt ( _root, t._root ); 
    }
    bool operator== ( BinTree<T> const& t ) { //判等器
        return _root && t._root && ( _root == t._root ); 
    }
};

template <typename T> 
int BinTree<T>::updateHeight ( BinNodePosi(T) x ){
    return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template <typename T> 
void BinTree<T>::updateHeightAbove ( BinNodePosi(T) x ){
    while ( x ) { 
        updateHeight ( x ); 
        x = x->parent; 
    }
}

template <typename T> 
BinNodePosi(T) BinTree<T>::insertAsRoot ( T const& e ){//将e当作根节点插入空的二叉树
    _size = 1;
    return _root = new BinNode<T>(e);
}

template <typename T> 
BinNodePosi(T) BinTree<T>::insertAsRC ( BinNodePosi(T) x, T const& e ){
    _size++; 
    x->insertAsRC ( e ); 
    updateHeightAbove ( x ); 
    return x->rc;
}

template <typename T> 
BinNodePosi(T) BinTree<T>::insertAsLC ( BinNodePosi(T) x, T const& e ){
    _size++; 
    x->insertAsLC ( e ); 
    updateHeightAbove ( x ); 
    return x->lc;
}

template <typename T> //二叉树子树接入算法 将S当作节点x的右子树接入 S本身置空
BinNodePosi(T) BinTree<T>::attachAsRC( BinNodePosi(T) x, BinTree<T>* &S ){
    if ( x->rc = S->_root ){
        x->rc->parent = x;
    }
    _size += S->_size; 
    updateHeightAbove ( x );
    S->_root = NULL; 
    S->_size = 0;
    release(S);
    S = NULL; 
    return x;
}

template <typename T> //二叉树子树接入算法 将S当作节点x的左子树接入 S本身置空
BinNodePosi(T) BinTree<T>::attachAsRC( BinNodePosi(T) x, BinTree<T>* &S ){
    if ( x->lc = S->_root ){
        x->lc->parent = x;
    }
    _size += S->_size; 
    updateHeightAbove ( x );
    S->_root = NULL; 
    S->_size = 0;
    release(S);
    S = NULL; 
    return x;
}

template <typename T> //删除二叉树中位置x处的节点及其后代 返回被删除节点的数值
int BinTree<T>::remove ( BinNodePosi(T) x ) {
    FromParentTo ( *x ) = NULL; //切断来自父节点的指针 
    updateHeightAbove ( x->parent ); //更新祖先高度
    int n = removeAt ( x ); 
    _size -= n; 
    return n; //删除子树x，更新规模，返回删除节点总数
}

template <typename T> //删除二叉树中位置x处的节点及其后代  返回被删除节点的数值
static int removeAt ( BinNodePosi(T) x ) {
    if ( !x ){
        return 0;
    }
    int n = 1 + removeAt ( x->lc ) + removeAt ( x->rc );
    release ( x->data ); 
    release ( x ); 
    return n;
}

template <typename T> //二叉树子树分离算法 将子树x从的前树中摘除 将其封装为一棵独立子树返回
BinTree<T>* BinTree<T>::secede ( BinNodePosi(T) x ) {
    FromParentTo ( *x ) = NULL; //切断来自父节点的指针 
    updateHeightAbove ( x->parent ); //更新原树中所有祖先的高度
    BinTree<T>* S = new BinTree<T>; 
    S->_root = x;  //新树以x为根
    x->parent = NULL;
    S->_size = x->size(); 
    _size -= S->_size; 
    return S;
}

template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit){
    if(!x){
        return;
    }
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit){
    if(!x){
        return;
    }
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit){
    if(!x){
        return;
    }
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

template <typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S){
    while(x){
        visit(x->data);
        S.push(x->rc);
        x = x->lc;
    }
}

template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST& visit){
    Stack<BinNodePosi(T)> S;
    while(true){
        visitAlongLeftBranch(x, visit, S);
        if(S.empty()){
            break;
        }
        x = S.pop();
    }
}

template <typename T, typename VST>
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S){
    while(x){
        S.push(x);
        x = x->lc;
    }
}

template <typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST& visit){
    Stack<BinNodePosi(T)> S;
    while(true){
        goAlongLeftBranch(x, S);
        if(S.empty()){
            break;
        }
        x = S.pop();
        visit(x->data);
        x = x->rc;
    }
}

template<typename T>
BinNodePosi(T) BinNode<T>::succ(){
    BinNodePosi(T) s = this;
    if(rc){
        s = rc;
        while(HasChild(*s)){
            s = s->lc;
        }
    }else{
        while(IsRChild(*s)){
            s = s->parent;
        }
        s = s->parent;
    }
    return s;
}

template <typename T, typename VST>
 void travIn_I2 ( BinNodePosi(T) x, VST& visit ) {
    Stack<BinNodePosi(T)> S;
    while(true){
        if(x){
            S.push(x);
            x = x->lc;
        }else if(!S.empty()){
            x = S.pop();
            visit(x->data);
            x = x->rc;
        }else{
            break;
        }
    }
}

template <typename T, typename VST>
void travIn_I3(BinNodePosi(T) x, VST& visit){
    bool backtrack = false;
    while(true){
        if(!backtrack && HasLChild(*x)){
            x = x->lc;
        }else{
            visit(x->data);
        }
        if(HasRChild(*x)){
            x = x->rc;
            backtrack = false;
        }else{
            if(!(x = x->succ)){
                break;
            }
            backtrack = true;
        }
    }
}

template <typename T>
static void gotoHLVFL(Stack<BinNodePosi(T)>& S){
    while(BinNodePosi(T) x = S.top()){
        if(HasLChild(*x)){
            if(HasRChild(*x)){
                S.push(x->rc);
            }
            S.push(x->lc);
        }else{
            S.push(x->rc);
        }
    }
    S.pop();
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit){
    Stack<BinNodePosi(T)> S;
    if(x){
        S.push(x);
    }
    while(!S.empty()){
        if(S.top() != x->parent){
            gotoHLVFL(S);
        }
        x = S.pop();
        visit(x->data);
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST& visit){
    Queue<BinNodePosi(T)> Q;
    Q.enqueue(this);
    while(!Q.empty()){
        BinNodePosi(T) x = Q.dequeue();
        visit(x->data);
        if(HasLChild(*x)){
            Q.enqueue(x->lc);
        }
        if(HasRChild(*x)){
            Q.enqueue(x->rc);
        }
    }
}





