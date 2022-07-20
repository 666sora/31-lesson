#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

class IGraph {
public:
    virtual ~IGraph () {};
    IGraph () {};
    IGraph (IGraph *_oth) {};
    virtual void AddEdge (int from, int to) = 0; // Метод принимает вершины начала и конца ребра и добавляет ребро
    virtual int VerticesCount () const = 0; // Метод должен считать текущее количество вершин
    virtual std::unordered_set<int> GetNextVertices (int vertex) const = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, в которые можно дойти по ребру из данной
    virtual std::unordered_set<int> GetPrevVertices (int vertex) const = 0; // Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
};

class ListGraph : public IGraph {
    std::set<int> verticesList;
    std::map<int, std::unordered_set<int>> listGraph;
public:
    virtual void AddEdge(int from, int to) override {
        verticesList.insert(from);
        verticesList.insert(to);
        listGraph[from].insert(to);
    }
    virtual std::unordered_set<int> GetNextVertices(int vertex) const override {
        return listGraph.find(vertex)->second;
    }
    virtual std::unordered_set<int> GetPrevVertices(int vertex) const override {
        std::unordered_set<int> tempUnSet;
        for (auto it: listGraph) {
            if (it.second.count(vertex)) {
                tempUnSet.insert(it.first);
            }
        }
        return tempUnSet;
    }
    virtual int VerticesCount() const override {
        return verticesList.size();
    }
    ListGraph (IGraph *_oth) {
        if (_oth == nullptr) return;
        for (int i = 0; i < _oth->VerticesCount(); i++) {
            verticesList.insert(i);
        }
        for (auto &s: verticesList) {
            std::unordered_set<int> tempUnSet = _oth->GetNextVertices(s);
            listGraph[s] = tempUnSet;
        }
    }
    ListGraph& operator=(IGraph *_oth) {
        if (this == _oth) {
            return *this;
        }
        if (_oth == nullptr) return *this;

        for (int i = 0; i < _oth->VerticesCount(); i++) {
            verticesList.insert(i);
        }
        for (auto &s: verticesList) {
            std::unordered_set<int> tempUnSet = _oth->GetNextVertices(s);
            listGraph[s] = tempUnSet;
        }
        return *this;
    }
    ListGraph () {};
    ~ListGraph () {};
};

class MatrixGraph : public IGraph {
    std::set<int> verticesMatrix;
    std::vector<std::vector<bool>> matrixGraph;
public:
    virtual void AddEdge(int from, int to) override {
        verticesMatrix.insert(from);
        verticesMatrix.insert(to);
        int tempResize = (from > to ? from + 1 : to + 1);
        if (matrixGraph.size() < tempResize) {
            matrixGraph.resize(tempResize);
            for (auto &v: matrixGraph) {
                v.resize(tempResize);
            }
        }
        matrixGraph[from][to] = true;
    }
    virtual std::unordered_set<int> GetNextVertices(int vertex) const override {
        std::unordered_set<int> tempUnSet;
        for (int i = 0; i < matrixGraph[vertex].size(); i++) {
            if (matrixGraph[vertex][i] == true) {
                tempUnSet.insert(i);
            }
        }
        return tempUnSet;  
    }
    virtual std::unordered_set<int> GetPrevVertices(int vertex) const override {
        std::unordered_set<int> tempUnSet;
        for (int i = 0; i < matrixGraph.size(); i++) {
            if (matrixGraph[i][vertex] == true) {
                tempUnSet.insert(i);
            }
        }
        return tempUnSet;
    }
    virtual int VerticesCount() const override {
        return verticesMatrix.size();
    }
    MatrixGraph (IGraph *_oth) {
        if (_oth == nullptr) return;
        for (int i = 0; i < _oth->VerticesCount(); i++) {
            verticesMatrix.insert(i);
        }
        matrixGraph.resize(_oth->VerticesCount());
        for (auto &v: matrixGraph) {
            v.resize(matrixGraph.size());
        }
        for (int i = 0; i < verticesMatrix.size(); i++) {
            std::unordered_set<int> tempUnSet = _oth->GetNextVertices(i);
            for (auto &us: tempUnSet) {
                matrixGraph[i][us] = true;
            }
        } 
    }
    MatrixGraph& operator=(IGraph *_oth) {
        if (this == _oth) {
            return *this;
        }
        if (_oth == nullptr) return *this;

        for (int i = 0; i < _oth->VerticesCount(); i++) {
            verticesMatrix.insert(i);
        }
        matrixGraph.resize(_oth->VerticesCount());
        for (auto &v: matrixGraph) {
            v.resize(matrixGraph.size());
        }
        for (int i = 0; i < verticesMatrix.size(); i++) {
            std::unordered_set<int> tempUnSet = _oth->GetNextVertices(i);
            for (auto &us: tempUnSet) {
                matrixGraph[i][us] = true;
            }
        }
        return *this;
    }
    void show() {
        for (int i = 0; i < matrixGraph.size(); i++) {
            for (int j = 0; j < matrixGraph[i].size(); j++) {
                std::cout << matrixGraph[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    MatrixGraph () {};
    ~MatrixGraph () {};
};


int main() {
    MatrixGraph matrixGraph;
    matrixGraph.AddEdge(0, 1);
    matrixGraph.AddEdge(0, 7);
    matrixGraph.AddEdge(1, 2);
    matrixGraph.AddEdge(2, 3);
    matrixGraph.AddEdge(3, 4);
    matrixGraph.AddEdge(4, 5);
    matrixGraph.AddEdge(4, 6);
    matrixGraph.AddEdge(5, 6);
    matrixGraph.show();
    std::cout << std::endl;

    ListGraph listGraph(&matrixGraph);

    matrixGraph = &listGraph;
    matrixGraph.show();
    std::cout << std::endl;
    listGraph = &matrixGraph;
    matrixGraph = &listGraph;
    matrixGraph.show();
}

/*
Прочитайте, что такое графы в дискретной математике, как граф можно представить 
в программе, что такое матрицы смежности и списки смежности. Ссылки на источники даны в «Рекомендациях».
Вам дан базовый интерфейс для представления ориентированного графа. Напишите две реализации интерфейса:
ListGraph, хранящий граф в виде массива списков смежности.
MatrixGraph, хранящий граф в виде матрицы смежности.
Реализуйте конструктор, принимающий IGraph. Такой конструктор должен 
скопировать переданный граф в создаваемый объект. Обратите внимание, 
что иногда в одну реализацию графа копируется другая. Реализуйте в 
том числе все конструкторы копий и операторы присваивания, если это необходимо.
*/