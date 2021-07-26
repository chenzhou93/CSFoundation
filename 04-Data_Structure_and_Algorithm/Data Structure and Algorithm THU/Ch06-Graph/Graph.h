#include "../Ch02-Vector/Vector.h"
#include "../Ch04-StackQueue/Queue.h"
#include "../Ch04-StackQueue/Stack.h"

typedef enum{UNDISCOVERED, DISCOVERED, VISITED} VStatus;
typedef enum{UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} EType;

template <typename Tv, typename Te>
class Graph{
    private:
    void reset(){
        for(int i=0; i<n; i++){
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1;
            parent(i) = -1;
            priority(i) = INT_MAX;
            for(int j=0; j<n; j++){
                if(exists(i,j)){
                    type(i,j) = UNDETERMINED;
                }
            }
        }
    }

    void BFS(int, int&);
    void DFS(int, int&);
    void BCC(int, int&, Stack<int>&);
    bool TSort(int, int&, Stack<Tv>*);
    template<typename PU> void PFS(int, PU);

    public:
    int n;
    virtual int insert(Tv const&) = 0;//插入顶点，返回编号
    virtual Tv remove(int) = 0;//删除顶点及其关联边，返回该顶点信息
    virtual Tv& vertex(int) = 0;//顶点v的数据（该顶点的确存在） 
    virtual int inDegree ( int ) = 0; //顶点v的入度（该顶点的确存在） 
    virtual int outDegree ( int ) = 0; //顶点v的出度
    virtual int firstNbr ( int ) = 0; //顶点v的首个邻接顶点
    virtual int nextNbr ( int, int ) = 0; //顶点v的（相对于顶点j的）下一个邻接顶点
    virtual VStatus& status ( int ) = 0; //顶点v的状态
    virtual int& dTime ( int ) = 0; //顶点v的时间标签dTime
    virtual int& fTime ( int ) = 0; //顶点v的时间标签fTime
    virtual int& parent ( int ) = 0; //顶点v在遍历树中的父亲
    virtual int& priority ( int ) = 0; //顶点v在遍历树中的优先级数

    //这里约定 无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
    int e; // 总数
    virtual bool exists ( int, int ) = 0; //边(v, u)是否存在
    virtual void insert ( Te const&, int, int, int ) = 0; //在顶点v和u之间插入权重为w的边e
    virtual Te remove ( int, int ) = 0; //删除顶点v和u之间的边e，返回该边信息
    virtual EType& type ( int, int ) = 0; //边(v, u)的类型
    virtual Te& edge ( int, int ) = 0; //边(v, u)的数据
    virtual int& weight ( int, int ) = 0; //边(v, u)的权重

    // 算法
    void bfs ( int ); //广度优先搜索算法
    void dfs ( int ); //深度优先搜索算法
    void bcc ( int ); //基于DFS的双连通分量分解算法
    Stack<Tv>* tSort ( int ); //基于DFS的拓扑排序算法
    void prim ( int ); //最小支撑树Prim算法
    void dijkstra ( int ); //最短路径Dijkstra算法
    template <typename PU> void pfs ( int, PU ); //优先级搜索框架
};

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s){//广度优先搜索BFS算法 全图 
    reset();
    int clock = 0;
    int v = s;
    do{//逐一检查所有顶点
        if(UNDISCOVERED == status(v)){
            BFS(v, clock);
        }
    }while(s != (v=(++v%n)));//按序号检查故不重不漏
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock){//广度优先搜索BFS算法 单个连通域 
    Queue<int> Q;
    status(v) = DISCOVERED;
    Q.enqueue(v);

    while(!Q.empty()){
        int v = Q.dequeue();
        dTime(v) = ++clock;
        for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u)){
            if(UNDISCOVERED == status(u)){
                status(u) = DISCOVERED;
                Q.enqueue(u);
                type(v, u) = TREE;
                parent(u) = v;
            }else{
                type(v, u) = CROSS;
            }
        }
        status(v) = VISITED;
    }

}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s){
    reset();
    int clock = 0;
    int v = s;
    do{
        if(UNDISCOVERED == status(v)){
            DFS(v, clock);
        }
    }while(s != (v = (v++ % n)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock){
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    for(int u=firstNbr(v); -1<u; u=nextNbr(v,u)){
        switch(status(u)){
            case UNDISCOVERED:
                type(v,u) = TREE;
                parent(u) = v;
                DFS(u, clock);
                break;
            case DISCOVERED:
                type(v,u) = BACKWARD;
                break;
            default:
                type(v,u) = (dTime(v) < dTime(u) ? FORWARD : CROSS);
                break;
        }
        status(v) = VISITED;
        fTime(v) = ++clock;
    }
}

template<typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S){
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    for(int u=firstNbr(v); -1<u; u=nextNbr(v, u)){
        switch(status(u)){
            case UNDISCOVERED:
                parent(u) = v;
                type(v,u) = TREE;
                if(!TSort(u, clock, S)){
                    return false;
                }
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                return false;
            default:
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
    return true;
}

template<typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s){
    reset();
    int clock = 0;
    int v = s;
    do{
        if(UNDISCOVERED == status(v)){
            if(!TSort(v, clock, S)){
                while(!S->empty()){
                    S->pop();
                    break;
                }
            }
        }
    }while(s != (v=(++v%n)));
    return S;
}

template <typename Tv, typename Te> template <typename PU>//优先级搜索 全图 
void Graph<Tv, Te>::pfs (int s, PU prioUpdater) { 
    reset(); int v = s; 
    do{//逐一检查所有顶点
        if (UNDISCOVERED == status (v)){//一旦遇到尚未发现的顶点
            PFS (v, prioUpdater); //即从该顶点出发启动一次PFS
        }
    }while (s != (v = (++v % n))); 
}

template <typename Tv, typename Te> template <typename PU>//顶点类型、边类型、优先级更新器
void Graph<Tv, Te>::PFS ( int s, PU prioUpdater ) {
    priority ( s ) = 0; status ( s ) = VISITED; parent ( s ) = -1;//初始化，起点s加入pfs树中
    while ( 1 ) {//将下一顶点和边加入PFS树中
        for ( int w = firstNbr ( s ); -1 < w; w = nextNbr ( s, w ) ){//枚举s所有的邻居w
            prioUpdater ( this, s, w );//更新顶点w的优先级及其父亲顶点
        }
        for ( int shortest = INT_MAX, w = 0; w < n; w++ ){
            if ( UNDISCOVERED == status ( w ) ){//从尚未加入遍历树的顶点中选出下一个
                if ( shortest > priority ( w ) ){
                    shortest = priority ( w ); 
                    s = w;//优先级最高顶点s
                }
            }
        }
        if ( VISITED == status ( s ) ) break;//直至所有顶点均已加入
        status ( s ) = VISITED; 
        type ( parent ( s ), s ) = TREE;//将s及与其父节点的联边加入遍历树
    }
}//通过定义具体的优先级更新策略 prioUpdater 即可实现不同的算法功能