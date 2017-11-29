//
// Created by Zhenggang Xue on 10/23/16.
//

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>

#define INFINITY 9999


struct Vertex{
    int id;
    std::vector<std::pair<int, int> > adjacents;  //first: adjacent node index;  second: weight
};

struct Edge{
    int startPoint;
    int endPoint;
    int weight;
};

class Graph
{
private:
    std::vector<struct Vertex> vertices;
    int number_of_vertices;
    int number_of_edges;

public:
    Graph();

    int get_num_of_vertices ();

    int get_num_of_edges();

    int search_node(int nodeID);

    void addEdge(int vertexStartID, int vertexEndID, int edgeWeight);

    std::vector<std::pair<int, int> > get_adjacents(int nodeID);

    struct Vertex get_vertex(int index);

    void printGraph();
};

class MinHeap {

private:
    std::vector<std::pair<int, int> > pq;  // first: node;    second: key_value

public:
    //insert(v, key value): insert an element v, whose associated key value is key value.
    int insert(int v, int key_value);

    //return and remove the element in queue with the smallest key value
    std::pair<int, int> extract_min();

    //decrease the key value of an node v in prioriy queue to new key value
    int decrease_key(int v, int new_key_value);

    bool is_newkey_smaller(int v, int new_key_value);

    int printpq();

    int printA(std::vector<int> A);

private:

    int heapify_up(int i);

    int heapify_down(int i);

    int swap_elements(int i, int j);

};


class MSTPrim {

private:
    Graph vGraph;
    MinHeap myminHeap;
    std::vector<int> S;
    int parents[INFINITY];  //this is hashmap, use id to access, return id of parent.
    std::vector<struct Edge> MSTedges;

public:

    MSTPrim(){
        for (int i = 0; i < INFINITY; ++i) {
            parents[i] = -1;
        }
    }

    int build_graph_from_file(std::string path);   // Build
    int build_priority_queue();
    int prim();

    void sortMSTedges();

    void output();
    void output(std::string path);




    int printvGraph();
    int printmyminHeap();
};



/********                          ***********/
/********         main.cpp           ***********/
/********                          ***********/
void test_priority_heap();
void test_MSTPrim();
void test_MSTPrimWithArguments(int argc, char **argv);

int main(int argc, char **argv){

    std::string path = "input.txt";
    MSTPrim myMSTPrim;
    myMSTPrim.build_graph_from_file(path);
    myMSTPrim.build_priority_queue();
    myMSTPrim.prim();
    myMSTPrim.output("output.txt");

}

void test_MSTPrim(){
    // correct
    std::string path = "/Users/zhenggangxue/ClionProjects/AlgorithmProject1/input.txt";
    MSTPrim myMSTPrim;
    myMSTPrim.build_graph_from_file(path);
    //myMSTPrim.printvGraph();

    myMSTPrim.build_priority_queue();
    //myMSTPrim.printmyminHeap();
    myMSTPrim.prim();
    myMSTPrim.output();
    myMSTPrim.output("output.txt");
}


void test_MSTPrimWithArguments(int argc, char **argv){
    std::string path = "input.txt";
    MSTPrim myMSTPrim;
    myMSTPrim.build_graph_from_file(path);
    //myMSTPrim.printvGraph();

    myMSTPrim.build_priority_queue();
    //myMSTPrim.printmyminHeap();
    myMSTPrim.prim();
    myMSTPrim.output();
    myMSTPrim.output("output.txt");
}

void test_priority_heap(){
    // correct
    MinHeap myMinHeap;

    //give the example of B
    std::vector<int> B;
    for(int i = 0; i < 50; i++){
        B.push_back(rand() % 100);
    }
    std::cout << "Now print input array: " << std::endl;
    myMinHeap.printA(B);

    //original build-heap
    for (int i = 0; i < B.size(); i++){
        myMinHeap.insert(B[i],B[i]);
    }
    std::cout << "Now print in min-priority queue: " <<std::endl;
    myMinHeap.printpq();
}

/*********************************************/






Graph::Graph() {
    this->number_of_edges = 0;
    this->number_of_vertices = 0;
    this->vertices = {};
}

int Graph::get_num_of_vertices() {
    return this->number_of_vertices;
}

int Graph::get_num_of_edges() {
    return this->number_of_edges;
}

int Graph::search_node(int nodeID) {

    //Why use search? Because that in this case we can store such nodes {10, 11, 15, 20} other than only {2,1,4,3}

    for (int i = 0; i < this->vertices.size(); ++i) {
        if(this->vertices[i].id == nodeID){
            return i;
        }
    }

    return -1;
}

void Graph::addEdge(int vertexStartID, int vertexEndID, int edgeWeight) {
    int si = this->search_node(vertexStartID);
    int ei = this->search_node(vertexEndID);

    this->number_of_edges += 1;
    if(si >= 0 && ei >= 0){   //both nodes have being added, now add the edge between them

        this->vertices[si].adjacents.push_back(std::make_pair(vertexEndID,edgeWeight));
        this->vertices[ei].adjacents.push_back(std::make_pair(vertexStartID,edgeWeight));

        // increase num of vertices edges
    }
    else if (si < 0 && ei >= 0){   // new a vertex then push into vector of vertices
        struct Vertex tempVertex;
        tempVertex.id = vertexStartID;
        tempVertex.adjacents.push_back(std::make_pair(vertexEndID,edgeWeight));
        this->vertices[ei].adjacents.push_back(std::make_pair(vertexStartID,edgeWeight));
        this->vertices.push_back(tempVertex);
        this->number_of_vertices += 1;
    }
    else if (si >= 0 && ei < 0){
        struct Vertex tempVertex;
        tempVertex.id = vertexEndID;
        tempVertex.adjacents.push_back(std::make_pair(vertexStartID,edgeWeight));
        this->vertices[si].adjacents.push_back(std::make_pair(vertexEndID,edgeWeight));
        this->vertices.push_back(tempVertex);
        this->number_of_vertices += 1;
    }
    else{
        // both are new vertex and should been added.
        struct Vertex tempVertex1;
        struct Vertex tempVertex2;
        tempVertex1.id = vertexStartID;
        tempVertex2.id = vertexEndID;
        tempVertex1.adjacents.push_back(std::make_pair(vertexEndID,edgeWeight));
        tempVertex2.adjacents.push_back(std::make_pair(vertexStartID,edgeWeight));
        this->vertices.push_back(tempVertex1);
        this->vertices.push_back(tempVertex2);
        this->number_of_vertices += 2;
    }
}

std::vector<std::pair<int, int> > Graph::get_adjacents(int nodeID) {
    int sIndex = this->search_node(nodeID);
    if(sIndex < 0){
        std::cerr << "Error: try to return a nonexist adjacents because this nodeID is not contained.";
        //return NullObject;
    }
    return this->vertices[sIndex].adjacents;
}

void Graph::printGraph() {
    std::cout << "NO. of Vertices: "<< this->number_of_vertices << std::endl;
    std::cout << "NO. of Edges: "<< this->number_of_edges << std::endl;
    std::cout << "vertices.size()" << this->vertices.size()<<std::endl;
    for (int i = 0; i < this->vertices.size(); ++i) {
        std::cout << i << " : " << vertices[i].id << " : { ";
        for (int j = 0; j < this->vertices[i].adjacents.size(); ++j) {
            std::cout << "(" << this->vertices[i].adjacents[j].first << ","
                      << this->vertices[i].adjacents[j].second
                      << "), ";
        }
        std::cout << " } "<<std::endl;
    }
}

struct Vertex Graph::get_vertex(int index) {
    if(index >= 0 && index < this->vertices.size()){
        return this->vertices[index];
    }
    else{
        std::cerr << "ERROR: try to access overstack: Vertex Graph :: get_vertex(int index)";
    }

}

int MinHeap::swap_elements(int i, int j) {
    int n = this->pq.size();
    if(i >= 0 && i < n && j>= 0 && j < n){
        std::pair<int, int> temp = pq[i];
        pq[i] = pq[j];
        pq[j] = temp;
        return 0;
    }
    else
        return -1;
}

//insert v node with key_value, we assume this v node is represented by number
int MinHeap::insert(int v, int key_value) {

    this->pq.push_back(std::make_pair(v, key_value));

    this->heapify_up(this->pq.size()-1);

    return 0;
}

int MinHeap::heapify_up(int i) {
    if(this->pq.size() > 1 && i >= 0 && i < this->pq.size()){
        int ind = i;
        while (ind != 0){
            int parent = (ind-1)/2;
            if(this->pq[ind].second < this->pq[parent].second){
                swap_elements(parent, ind);
                ind = parent;
            }
            else
                break;
        }
    }

    return 0;
}

std::pair<int, int> MinHeap::extract_min() {
    std::pair<int, int> ret = std::make_pair(-1,-1);
    if(this->pq.size() == 0){
        std::cerr << "Extract from a empty heap!";
        return ret;
    }
    ret = this->pq.front();
    this->pq.front() = this->pq.back();
    this->pq.pop_back();
    this->heapify_down(0);
    return ret;
}

int MinHeap::heapify_down(int i) {
    int n = this->pq.size();
    if(n > 1 && i >= 0 && i < n){
        int ind = i;
        int ind_smallest = ind;
        while (ind_smallest < n){
            int lchild = ind*2 + 1;
            int rchild = ind*2 + 2;

            if(lchild < n && this->pq[ind].second > this->pq[lchild].second)
                ind_smallest = lchild;
            if(rchild < n && this->pq[ind_smallest].second > this->pq[rchild].second)
                ind_smallest = rchild;

            if(ind_smallest != ind){
                swap_elements(ind, ind_smallest);
                ind = ind_smallest;
            }
            else
                break;
        }
    }
    return 0;
}

int MinHeap::decrease_key(int v, int new_key_value) {
    int n = this->pq.size();
    if(n > 0){
        for (int i = 0; i < n; ++i) {
            if(this->pq[i].first == v){
                this->pq[i].second = new_key_value;
                heapify_up(i);
                return i;
            }
        }
    }
    return -1;
}

int MinHeap::printpq() {
    if(this->pq.empty()){
        std::cout << "PQ is null" <<std::endl;
        return -1;
    }
    while (this->pq.size() > 0){
        std::cout << this->extract_min().first <<" ";
    }
    return 0;
}

int MinHeap::printA(std::vector<int> A) {
    for (int i = 0; i < A.size(); ++i) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

bool MinHeap::is_newkey_smaller(int v, int new_key_value) {
    int n = this->pq.size();
    if(n > 0){
        for (int i = 0; i < n; ++i) {
            if(this->pq[i].first == v){
                if(new_key_value < this->pq[i].second){
                    return true;
                }
            }
        }
    }
    return false;

    return 0;
}

int MSTPrim::build_graph_from_file(std::string path) {

    std::ifstream fin(path);
    int tx,ty;
    fin >> tx >> ty;

    int u,v,w;   // vertex (u,v) and the weight between them. Assume that w is integer.

    while( fin >> u >> v >> w )
    {
        //std::cout << "(" << u <<", " << v <<") : " << w << std::endl;
        vGraph.addEdge(u, v, w);
    }

    return 0;
}

int MSTPrim::build_priority_queue() {
    //return the index of an arbitrary vertex in vGraph, normally is the vGraph[0], from which we begin min-extracting.
    int n = this->vGraph.get_num_of_vertices();
    if(n == 0)
        return -1;

    for (int i = 0; i < n; ++i) {
        if(i == 0){
            myminHeap.insert(vGraph.get_vertex(i).id, 0);
        }
        else{
            myminHeap.insert(vGraph.get_vertex(i).id, INFINITY);
        }
    }

    return 0;
}

int MSTPrim::printvGraph() {
    this->vGraph.printGraph();
    return 0;
}

int MSTPrim::printmyminHeap() {
    this->myminHeap.printpq();
    return 0;
}

int MSTPrim::prim() {
    int MSTnumofVertices = 0;  // counting the current num of vertices of MST

    int n = vGraph.get_num_of_vertices();
    while (MSTnumofVertices < n){
        int uid = myminHeap.extract_min().first;   // extract the min - node "uid"

        this->S.push_back(uid);

        if(this->parents[uid] != -1){
            // output edge and weight
            int parent = this->parents[uid];
            std::vector<std::pair<int, int> > padj = this->vGraph.get_adjacents(parent);
            for (int i = 0; i < padj.size(); ++i) {
                if(padj[i].first == uid){
                    //std::cout << "Edge: (" << parent <<", "<<uid<<") : weight: "<< padj[i].second <<std::endl;
                    struct Edge cedge;
                    cedge.startPoint = parent;
                    cedge.endPoint = uid;
                    cedge.weight = padj[i].second;
                    MSTedges.push_back(cedge);
                    break;
                }
            }

        }

        //for each v shuyu V\S, such that (u,v) shuyu E
        int uindex = this->vGraph.search_node(uid);
        struct Vertex uVertex = this->vGraph.get_vertex(uindex);  //find the Vertex of u in Graph V

        for (int i = 0; i < uVertex.adjacents.size(); ++i) {  //find the least weight of edges (u,v)s
            int vid = uVertex.adjacents[i].first;

            if(std::find(this->S.begin(),this->S.end(),vid) == this->S.end()){  //indicate that it is not in S.
                int weightUV = uVertex.adjacents[i].second;
                if(myminHeap.is_newkey_smaller(vid, weightUV)){
                    myminHeap.decrease_key(vid, weightUV);
                    this->parents[vid] = uid;
                }
            }
        }

        //std::cout << "the next edge and weight are: " << min_w_vid << " : " << min_w<<std::endl;
        //find the weight
        MSTnumofVertices++;
    }
    return 0;
}

void MSTPrim::output() {
    int totalWeights = 0;
    for (int i = 0; i < MSTedges.size(); ++i) {
        totalWeights += MSTedges[i].weight;
    }

    std::cout << totalWeights <<std::endl;
    for (int j = 0; j < MSTedges.size(); ++j) {
        std::cout << MSTedges[j].startPoint << " "
                  << MSTedges[j].endPoint << " "
                  << MSTedges[j].weight << std::endl;
    }
}

void MSTPrim::sortMSTedges() {
    ;
}

void MSTPrim::output(std::string path) {

    std::ofstream fout;
    fout.open(path);


    int totalWeights = 0;
    for (int i = 0; i < MSTedges.size(); ++i) {
        totalWeights += MSTedges[i].weight;
    }

    fout << totalWeights << "\n";
    for (int j = 0; j < MSTedges.size(); ++j) {
        fout << MSTedges[j].startPoint << " "
             << MSTedges[j].endPoint << " "
             << MSTedges[j].weight << "\n";
    }
    fout.close();
}

