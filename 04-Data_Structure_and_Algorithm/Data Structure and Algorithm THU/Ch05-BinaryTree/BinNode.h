#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)

#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) // 少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )
/******************************************************************************************
* 与BinNode具有特定关系的节点及指针
******************************************************************************************/
#define sibling(p) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc )
#define uncle(x) ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )
#define FromParentTo(x) ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )

typedef enum{RB_RED, RB_BLACK} RBColor;

template <typename T>
struct BinNode{
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;//left child
    BinNodePosi(T) rc;//right child
    int height;
    int npl;//null path length
    RBColor color;//for red black tree

    BinNode():parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED){ }
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, 
    int h = 0, int l=1, RBColor c = RB_RED) : 
        data(e), parent(p), lc(lc), rc(rc), height(h),npl(l), color(c){ }

    int size();
    BinNodePosi(T) insertAsLC(T const&);
    BinNodePosi(T) insertAsRC(T const&);
    BinNodePosi(T) succ(T const&);
    template <typename VST> void travLevel ( VST& ); //子树层次遍历
    template <typename VST> void travPre ( VST& );//子树先序遍历
    template <typename VST> void travIn ( VST& );//子树中序遍历
    template <typename VST> void travPost ( VST& );//子树后序遍历
    bool operator< ( BinNode const& bn ) { return data < bn.data; }
    bool operator== ( BinNode const& bn ) { return data == bn.data; }
};

template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC ( T const& e ){
    return lc = new BinNode ( e, this );
}

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC ( T const& e ){
    return rc = new BinNode ( e, this );
}

template <typename T> template <typename VST>
void BinNode<T>::travIn ( VST& visit ) {
    switch ( rand() % 5 ) { //此处暂随机选择以做测试，共五种选择
        case 1: travIn_I1 ( this, visit ); break; // 迭代版#1
        case 2: travIn_I2 ( this, visit ); break; // 迭代版#2
        case 3: travIn_I3 ( this, visit ); break; // 迭代版#3
        case 4: travIn_I4 ( this, visit ); break; // 迭代版#4
        default: travIn_R ( this, visit ); break; // 递归版
    }
}