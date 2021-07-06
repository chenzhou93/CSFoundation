#ifndef VECTOR_H__
#define VECTOR_H__

typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T>
class Vector{
    protected:
    Rank _size;//规模
    int _capacity;//容量
    T* _elem;//数据区
    void copyFrom(T const* A, Rank lo, Rank hi);//赋值数组区间A[lo, hi)
    void expand(); //空间不足时扩容
    void shrink(); //装填因子过小时压缩
    bool bubble ( Rank lo, Rank hi ); //扫描交换
    void bubbleSort ( Rank lo, Rank hi ); //起泡排序算法
    Rank max ( Rank lo, Rank hi ); //选最大元素 
    void selectionSort ( Rank lo, Rank hi ); //选择排序算法
    void merge ( Rank lo, Rank mi, Rank hi ); //归并算法
    void mergeSort ( Rank lo, Rank hi ); //归并排序算法
    Rank partition ( Rank lo, Rank hi ); //轴点构造算法
    void quickSort ( Rank lo, Rank hi ); //快速排序算法
    void heapSort ( Rank lo, Rank hi ); //堆排序（稍后结合完全堆讲解）

    public:
    // 构造函数
    Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ){ //容量为c、规模为s、所有元素初始为v 
        _elem = new T[_capacity = c]; 
        for ( _size = 0; _size < s; _elem[_size++] = v ); 
    } //s<=c
    Vector ( T const* A, Rank n ) { //数组整体复制
        copyFrom ( A, 0, n ); 
    }
    Vector ( T const* A, Rank lo, Rank hi ) { //区间
        copyFrom ( A, lo, hi ); 
    }
    Vector ( Vector<T> const& V ) { //向量整体复制
        copyFrom ( V._elem, 0, V._size ); 
    }
    Vector ( Vector<T> const& V, Rank lo, Rank hi ) { //区间
        copyFrom ( V._elem, lo, hi ); 
    }

    // 析构函数
    ~Vector() {  //释放内部空间
        delete [] _elem; 
    }

    // 只读访问接口
    Rank size() const {  //规模
        return _size; 
    }
    bool empty() const { //判断是否为空 
        return !_size; 
    }
    int disordered() const; //判断向量是否已排序
    Rank find ( T const& e ) const { //无序向量整体查找
        return find ( e, 0, _size ); 
    } 
    Rank find ( T const& e, Rank lo, Rank hi ) const; //无序向量区间查找
    Rank search ( T const& e ) const{ //有序向量整体查找
        return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); 
    }
    Rank search ( T const& e, Rank lo, Rank hi ) const; //有序向量区间查找
 
    // 可写访问接口
    T& operator[] ( Rank r ) const; //重载下标操作符，可以类似于数组形式引用各元素
    Vector<T> & operator= ( Vector<T> const& ); //重载赋值操作符，以便直接克隆向量
    T remove ( Rank r ); //初除秩为r的元素
    int remove ( Rank lo, Rank hi ); //初除秩在匙间[lo, hi)之内的元素
    Rank insert ( Rank r, T const& e ); //插入元素
    Rank insert ( T const& e ) { //默认作为末元素插入
        return insert ( _size, e ); 
    }
    void sort ( Rank lo, Rank hi ); //对[lo, hi)排序
    void sort() { sort ( 0, _size ); } //整体排序
    void unsort ( Rank lo, Rank hi ); //对[lo, hi)置乱
    void unsort() { //整体置乱
        unsort ( 0, _size ); 
    }
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    
    // 遍历
    void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改）
    template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改）
};

template<typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi){
    _elem = new T[_capacity = 2*(hi-lo)];
    _size = 0;
    while(lo < hi){
        _elem[_size++] = A[lo++];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V){
    if(_elem){
        delete[] _elem;
    }
    copyFrom(V._elem,0,V.size());
    return *this;
}

template <typename T>
void Vector<T>::expand(){
    if(_size < _capacity){
        return;
    }
    if(_capacity < DEFAULT_CAPACITY){
        _capacity = DEFAULT_CAPACITY;
    }
    T* oldElem = _elem;
    _elem = new T[_capacity << 1];
    for(int i=0; i<_size; i++){
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

template <typename T>
void Vector<T>::shrink(){
    if(_capacity < DEFAULT_CAPACITY << 1){
        return;
    }
    if(_size<<2 > _capacity){
        return;
    }
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for(int i=0; i<_size; i++){
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

template <typename T>
T& Vector<T>::operator[] (Rank r) const{
    return _elem[r];
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi){
    T* V = _elem + lo;
    for(Rank i=hi-lo; i>0; i--){
        swap(V[i-1], V[rand()%i]);
    }
}

template <typename T>
static bool lt(T* a, T* b){
    return lt(*a, *b);
}

template <typename T>
static bool lt(T& a, T& b){
    return a < b;
}

template <typename T>
static bool eq(T* a, T* b){
    return eq(*a, *b);
}

template <typename T>
static bool eq(T& a, T& b){
    return a == b;
}

template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi ) const{
    while((lo < hi--) && (e != _elem[hi]));
    return hi;
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e){
    expand();
    for(int i=_size; i>r; i--){
        _elem[i] = _elem[i-1];
    }
    _elem[r] = e;
    size++;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi){
    if(lo==hi) return 0;
    while(hi < _size){
        _elem[lo++] = _elem[hi++];
    }
    size = lo;
    shrink();
    return hi-lo;//返回被删除元素数
}

template <typename T>
T Vector<T>::remove(Rank r){
    T e = _elem[r];
    remove(r, r+1);
    return e;
}

template <typename T>
int Vector<T>::deduplicate(){
    int oldSize = _size;
    Rank i = 1;
    while(i < _size){
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    }
    return oldSize - _size;
}

template <typename T>
void Vector<T>::traverse(void(*visit) (T&)){//函数指针
    for(int i=0; i<_size; i++){
        visit(_elem[i]);
    }
}

template <typename T> 
template <typename VST>
void Vector<T>::traverse(VST& visit){//函数对象
    for(int i=0; i<_size; i++){
        visit(_elem[i]);
    }
}

//example
template <typename T>
struct Increase{
    virtual void operator()(T& e){
        e++;
    }
};
//example
template <typename T>
void increase(Vector<T> & V){
    V.traverse(Increase<T>());
}

template <typename T>
int Vector<T>::disordered() const{
    int n = 0;
    for(int i=1; i<_size; i++){
        if(_elem[i-1] > _elem[i]){
            n++;
        }
    }
    return n;
}

template <typename T>
int Vector<T>::uniquify(){
    Rank i = 0, j = 0;
    while(++j < _size){
        if(_elem[i] != _elem[j]){
            _elem[++i] = _elem[j];
        }
    }
    _size = ++i;
    shrink();
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const{
    return (rand()%2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

//Binary Search - Version A
template<typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi){
    while(lo < hi){
        Rank mi = (lo+hi)>>1;
        if(e < A[mi]){
            hi = mi;
        }else if(A[mi] < e){
            lo = mi + 1;
        }else{
            return mi;
        }
    }
    return -1;
}

template <typename T>
static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi){
    Fib fib(hi - lo);
    while(lo < hi){
        while(hi - lo < fib.get()){
            fib.prev();
        }
        Rank mi = lo + fib.get() - 1;
        if(e < A[mi]){
            hi = mi;
        }else if(A[mi] < e){
            lo = mi + 1;
        }else{
            return mi;
        }
    }
    return -1;
}

//Binary Search - Version B
template <typename T>
static Rank binSearchB(T* A, T const& e, Rank lo, Rank hi){
    while(1 < hi - lo){
        Rank mi = (lo + hi) >> 1;
        (e<A[mi]) ? hi = mi : lo = mi;
    }
    return (e == A[lo]) ? lo : -1;
}

//Binary Search - Version C
template <typename T>
static Rank binSearchC(T* A, T const& e, Rank lo, Rank hi){
    while(lo < hi){
        Rank mi = (lo + hi) >> 1;
        (e<A[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template <typename T> void Vector<T>::sort(Rank lo, Rank hi){
    switch(rand() % 5){
        case 1: bubbleSort(lo, hi); break;
        case 2: selectionSort(lo, hi); break;
        case 3: mergeSort(lo, hi); break;
        case 4: heapSort(lo, hi); break;
        default: quickSort(lo, hi); break;
    }
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi){
    while(!bubble(lo, hi--));
}

template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi){
    bool sorted = true;
    while(++lo < hi){
        if(_elem[lo-1] > _elem[lo]){
            sorted = false;
            swap(_elem[lo-1], _elem[lo]);
        }
    }
    return sorted;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi){
    if(hi - lo < 2)
        return;
    
    int mi = (lo + hi) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi){
    T* A = _elem + lo;
    int lb = mi - lo;
    T* B = new T[lb];
    for(Rank i=0; i<lb; B[i]=A[i++]);

    int lc = hi - mi;
    T* C = _elem + mi;
    for(Rank i=0, j=0, k=0; j<lb;){
        // if((j<lb) && (!(k<lc)||(B[j]<=C[k]))){
        //     A[i++] = B[j++];
        // }
        if((lc <=k)||(B[j] <= C[k])){
            A[i++] = B[j++];
        }
            
        // if((k<lc) && (!(j<lb)||(C[k] < B[j]))){
        //     A[i++] = C[k++];
        // }
        if((k<lc) && (C[k] < B[j])){
            A[i++] = C[k++];
        }
    }

    delete[] B;
}

template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi){
    while(lo < --hi){
        swap(_elem[max(lo, hi)], elem[hi]);//将[hi]不[lo, hi]中癿最大者交换
    }
}

template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi){
    Rank mx = hi;
    while(lo < hi--){
        if(_elem[hi] > _elem[mx]){
            mx = hi;
        }
    }
    return mx;
}




#endif