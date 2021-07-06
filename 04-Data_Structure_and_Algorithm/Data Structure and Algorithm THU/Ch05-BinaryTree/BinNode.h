#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)
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