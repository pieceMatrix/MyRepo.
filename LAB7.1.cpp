#include <iostream>
#include <vector>
//#include "heapgraph.h"
using namespace std;
class Edge {
public:
    int weight;
    int knot[2];

    Edge(int weight, int vertex1, int vertex2) : weight(weight) {
        knot[0] = vertex1;
        knot[1] = vertex2;
    }

    // Оператор сравнения для сортировки рёбер по их весу
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
     bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
      friend std::ostream& operator<<(std::ostream& os, const Edge& edge) {
        os << edge.weight << ", [" << edge.knot[0] << ", " << edge.knot[1] << "]";
        return os;
    }
     friend void swap(Edge &first, Edge &second) {
        using std::swap;
        swap(first.weight, second.weight);
        swap(first.knot, second.knot);
    }
};

class Graph {
private:
    int numVertices;
    vector<vector<int>> A;
     vector<Edge> B;// Заменили adjacencyMatrix на A
    int weight=0;
public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        A.resize(numVertices, vector<int>(numVertices, 0));        
    }

    void addEdge(int i, int j) {
        A[i][j] = 1;
        A[j][i] = 1; 
    }
      void addWeight(int i, int j, int w) {
        A[i][j] = w;
        A[j][i] = w; 
        weight+=w;
        B.push_back(Edge(w,i,j)); // Добавляем новый объект Graph2 в вектор B
        //B.back().weight.push_back(w); // Добавляем вес ребра в вектор рёбер в последний объект Graph2
       // B.back().knot.push_back({i, j}); 
    }
    void printAdjacencyMatrix() {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        } cout << "Вес графа:"<<weight << endl;
 // for (Edge v : B) {
   //     cout << v << " ";
    //}
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
        if (visit[current]) {cout << "Вершина посещена еще раз: ";return false;}
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
    for (Edge v : B) {
        cout << v << " ";
    }cout << std::endl;
    }
void deleteLast(int i, int j, int w) {
    //A.pop_back();
      A[i][j] = 0;
      A[j][i] = 0;
      weight-=w;
    B.pop_back();
}
  int getEdge(int i, int j) const {
        // Проверяем, что индексы не выходят за пределы матрицы
       // if (i >= 0 && i < numVertices) {
            const Edge& edge = B[i];
            if (j == 0) {
                return edge.knot[0];
            } else if (j == 1) {
                return edge.knot[1];
            } else if (j == 2) {
                return edge.weight;
            }
        //}
        // Возвращаемое значение по умолчанию, если индексы некорректны
        return -1; // Например, -1 для обозначения некорректного значения
    }
};

int main() {
    // Create a graph with 5 vertices
   int num=7;int edge=11;
    Graph graph(num);
    // Add edges
   
    // Add edges
    graph.addWeight(0,1,7);
    graph.addWeight(0,3,5);
    graph.addWeight(1,3,9);
    graph.addWeight(1,2,8);
    graph.addWeight(1,4,7);
    graph.addWeight(2,4,5);
    graph.addWeight(3,5,6);
    graph.addWeight(3,4,15);
    graph.addWeight(4,5,8);
    graph.addWeight(4,6,9);
    graph.addWeight(5,6,11);

    /* graph.addWeight(0, 1, 4);
    graph.addWeight(0, 2, 8);
    graph.addWeight(1, 2, 9);
    graph.addWeight(1, 3, 5);
    graph.addWeight(2, 4, 7);
    graph.addWeight(3, 4, 15);
    graph.addWeight(3, 5, 6);
    graph.addWeight(4, 5, 8);
    graph.addWeight(4, 6, 10);
    graph.addWeight(5, 7, 11);
    graph.addWeight(6, 7, 13);
    graph.addWeight(6, 8, 12);
    graph.addWeight(7, 8, 9);
    graph.addWeight(8, 9, 2);
    graph.addWeight(7, 9, 14);*/
    if (graph.dfs()== false) {
        cout << "В графе есть циклы." << endl;
    } else {
        cout << "В графе нет циклов." << endl;
    }
    // Print adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    graph.printAdjacencyMatrix();
    // cout << "Original array: ";
   // graph.printA();

    graph.HEAPSORT(edge);

    std::cout << "Sorted array: ";
    graph.printA();
    Graph graph2(num);
   for (int i = 0; i < edge; i++) {   
    graph2.addWeight(graph.getEdge(i, 0), graph.getEdge(i, 1), graph.getEdge(i, 2));
     cout << "i: "<<i<<endl;
     graph2.printA();
     graph2.printAdjacencyMatrix();
if (!graph2.dfs()) {
            cout << "В графе есть циклы, удаляем последнее добавленное ребро." << endl;
            graph2.deleteLast(graph.getEdge(i, 0), graph.getEdge(i, 1), graph.getEdge(i, 2));
        } else {
            cout << "В графе нет циклов." << endl;
        }
}
  cout << "МОД:." <<endl;
 graph2.printAdjacencyMatrix();
 graph2.printA();	
   return 0;
}
    