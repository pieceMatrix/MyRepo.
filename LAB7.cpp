#include <iostream>
#include <vector>
//#include "heapgraph.h"
using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> A;
    vector<int> B; // Заменили adjacencyMatrix на A
    int weight=0;
public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        A.resize(numVertices, vector<int>(numVertices, 0)); // Изменения также в этой строке
    }

    void addEdge(int i, int j) {
        A[i][j] = 1;
        A[j][i] = 1; 
    }
      void addWeight(int i, int j, int w) {
        A[i][j] = w;
        A[j][i] = w; 
        weight+=w;
        B.push_back(w);
    }
    void printAdjacencyMatrix() {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        } cout << "Вес графа:"<<weight << endl;
  for (int v : B) {
        cout << v << " ";
    }
    }
bool dfs() { int current=0;
    vector<bool> visit(numVertices, false); //  для отслеживания посещенных вершин
    vector<int> v1; //  для обхода в глубину
    //  начальная вершина
     v1.push_back(0);
    while (!v1.empty()) {       
        // последняя вершина 
         current = v1.back();
        v1.pop_back();
        if (visit[current]) {return false;}
            visit[current] = true;
            for (int i = numVertices - 1; i >= 0; --i) {
                if (A[current][i] > 0 && !visit[i]) {
                    v1.push_back(i);
                }
            }
        
    }
       cout << endl;
    return true;
 
}
void MAX_HEAPIFY(int i, int heap_size) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < heap_size && B[l] > B[largest])
            largest = l;

        if (r < heap_size && B[r] > B[largest])
            largest = r;

        if (largest != i) {
            std::swap(B[i], B[largest]);
            MAX_HEAPIFY(largest, heap_size);
        }

    }

    void BUILD_MAX_HEAP(int length) {
        int heap_size = length;
        for (int i = length / 2 - 1; i >= 0; i--) {
           
            MAX_HEAPIFY(i, heap_size);
        }
    }

    void HEAPSORT(int length) {
        BUILD_MAX_HEAP(length);
        for (int i = length - 1; i > 0; i--) {
            std::swap(B[0], B[i]);
            int heap_size = i;
            MAX_HEAPIFY(0, heap_size);
        }
    }
  void printA() {
    for (int v : B) {
        cout << v << " ";
    }cout << std::endl;
    }
};

int main() {
    // Create a graph with 5 vertices
   int num=5;
    Graph graph(num);

    // Add edges
   // graph.addEdge(0, 1);
    graph.addWeight(0,1,5);
    graph.addWeight(0, 4, 6);
    graph.addWeight(1, 2, 7);
    graph.addWeight(1, 3, 5);
    graph.addWeight(1, 4, 9);
    graph.addWeight(2, 3, 11);
    graph.addWeight(3, 4, 12);
 
    if (graph.dfs()==false) {
        cout << "В графе есть циклы." << endl;
    } else {
        cout << "В графе нет циклов." << endl;
    }
    // Print adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    graph.printAdjacencyMatrix();
     cout << "Original array: ";
    graph.printA();

    graph.HEAPSORT(num);

    std::cout << "Sorted array: ";
    graph.printA();
   return 0;
}
