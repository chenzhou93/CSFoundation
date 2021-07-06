#ifndef LIST_NODE_H__
#define LIST_NODE_H__

typedef int Rank;

#define ListNodePosi(T) ListNode<T>*

template <typename T>
struct ListNode{
    T data;
    ListNodePosi(T) pred; //ListNode<T>* pred;
    ListNodePosi(T) succ;

    //Constructor
    ListNode(){}
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) : data(e), pred(p), succ(s){}

    //APIs
    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);

};

#endif