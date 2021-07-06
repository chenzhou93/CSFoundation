#include "LinkedList.h"

template <typename T>
class Queue : public List<T>{
    public:
    void enqueue(T const& e){
        List<T>::insertAsLast(e);
    }
    T dequeue(){
        return List<T>::remove(List<T>::first());
    }
    T& front(){
        return List<T>::first()->data;
    }
    bool empty(){
        return List<T>::empty();
    }
    int size(){
        return List<T>::size();
    }
};
