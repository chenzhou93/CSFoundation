#include "../Ch02-Vector/Vector.h"
#include "../Ch04-StackQueue/Queue.h"
#include "Graph.h"

template <typename Tv> struct Vertex{
    Tv Data;
    int inDegree, outDegree;
    VStatus status;
    int dTime, fTime;
    int parent;
    int priority;
    Vertex(Tv const& d = (Tv)0) : 
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
        dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};

template <typename Te> struct Edge{
    Te data; int weight; EType type;
    Edge(Te const& d, int w) : data(d), weight(w), type(UNDETERMINED){}
};

template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>{
    private:
    Vector<Vertex<Tv>> V;//顶点集
    Vector<Vector<Edge<Te> * >> E; //边集，邻接矩阵

    public:
    GraphMatrix(){n = e = 0}
    ~GraphMatrix(){
        for(int j=0; j<n; j++){
            for(int k=0; k<n; k++){
                delete E[j][k];
            }
        }
    }

    virtual Tv& vertex(int i){
        return V[i].data;
    }

    virtual int inDegree(int i){
        return V[i].inDegree;
    }

    virtual int outDegree(int i){
        return V[i].outDegree;
    }

    virtual int firstNbr(int i){
        return nextNbr(i, n);
    }

    virtual int nextNbr(int i, int j){//相对于顶点j的下一临接顶点（改用邻接表可以提高效率）
        while((-1 < j) && (!exists(i, --j)));
        return j;
    }

    virtual VStatus& status(int i){
        return V[i].status;
    }

    virtual int& dTime(int i){
        return V[i].dTime;
    }

    virtual int& fTime(int i){
        return V[i].fTime;
    }

    virtual int& parent(int i){
        return V[i].parent;
    }

    virtual int& priority(int i){
        return V[i].priority;
    }

    virtual int insert(Tv const& vertex){
        for(int j=0; j<n; j++){
            E[j].insert(NULL);
            n++;
        }
        E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*) NULL));
        return V.insert(Vertex<Tv>(vertex));
    }

    virtual Tv remove(int i){
        for(int j=0; j<n; j++){
            if(exists(i, j)){
                delete E[i][j];
                V[j].inDegree--;
            }
        }
        E.remove(i);
        n--;

        Tv vBak = vertex(i);
        V.remove(i);

        for(int j=0; j<n; j++){
            if(Edge<Te>* e = E[j].remove(i)){
                delete e;
                V[j].outDegree--;
            }
        }
        return vBak;
    }

    virtual bool exists(int i, int j){// 边(i, j)是否存在
        return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
    }

    virtual EType& type(int i, int j){
        return E[i][j]->type;
    }

    virtual Te& edge(int i, int j){
        return E[i][j]->data;
    }

    virtual int& weight(int i, int j){
        return E[i][j]->weight;
    }

    virtual void insert(Te const& edge, int w, int i, int j){
        if(exists(i, j)){
            return;
        }
        E[i][j] = new Edge<Te>(edge, w);
        e++;
        V[i].outDegree++;
        V[j].inDegree++;
    }

    virtual Te remove(int i, int j){
        Te eBak = edge(i, j);
        delete E[i][j];
        E[i][j] = NULL;
        e--;
        V[i].outDegree--;
        V[j].inDegree--;
        return eBak;
    }

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