#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>
#include <set>

using namespace std;

class Graph
{
private:
    unordered_map<char, list<pair<char, int>>> graph;
    vector<tuple<int, char, char>> edges; 

public:
    void addVertex(char vertex) {
        if (graph.find(vertex) == graph.end()) {
            graph[vertex] = list<pair<char, int>>();
        }
    }

    void addEdge(char vertex1, char vertex2, int cost) {
        addVertex(vertex1);
        addVertex(vertex2);
        graph[vertex1].push_back(make_pair(vertex2, cost));
        graph[vertex2].push_back(make_pair(vertex1, cost));
        edges.push_back(make_tuple(cost, vertex1, vertex2));
    }

    // BFS function for task 1
    void bfs(char start) {
        unordered_set<char> visited;
        queue<char> q;
        q.push(start);

        while (!q.empty()) {
            char vertex = q.front();
            q.pop();

            if (visited.find(vertex) == visited.end()) {
                cout << vertex << " ";
                visited.insert(vertex);

                for (auto neighbor : graph[vertex]) {
                    if (visited.find(neighbor.first) == visited.end()) {
                        q.push(neighbor.first);
                    }
                }
            }
        }
    }

    // DFS function for task 1
    void dfs(char start) {
        unordered_set<char> visited;
        stack<char> s;
        s.push(start);

        while (!s.empty()) {
            char vertex = s.top();
            s.pop();

            if (visited.find(vertex) == visited.end()) {
                cout << vertex << " ";
                visited.insert(vertex);

                for (auto neighbor : graph[vertex]) {
                    if (visited.find(neighbor.first) == visited.end()) {
                        s.push(neighbor.first);
                    }
                }
            }
        }
    }

    // Kruskal's MST function for task 2
    char findSet(char vertex, unordered_map<char, char>& parent) {
        if (parent[vertex] != vertex) {
            parent[vertex] = findSet(parent[vertex], parent);
        }
        return parent[vertex];
    }

    void unionSets(char set1, char set2, unordered_map<char, char>& parent, unordered_map<char, int>& rank) {
        if (rank[set1] < rank[set2]) {
            parent[set1] = set2;
        }
        else if (rank[set1] > rank[set2]) {
            parent[set2] = set1;
        }
        else {
            parent[set2] = set1;
            rank[set1]++;
        }
    }

    void kruskalMST() {
        vector<tuple<int, char, char>> mst;
        unordered_map<char, char> parent;
        unordered_map<char, int> rank;

        for (const auto& edge : edges) {
            char vertex1 = get<1>(edge);
            char vertex2 = get<2>(edge);
            parent[vertex1] = vertex1;
            parent[vertex2] = vertex2;
            rank[vertex1] = 0;
            rank[vertex2] = 0;
        }

        sort(edges.begin(), edges.end());

        for (const auto& edge : edges) {
            int cost = get<0>(edge);
            char vertex1 = get<1>(edge);
            char vertex2 = get<2>(edge);

            char set1 = findSet(vertex1, parent);
            char set2 = findSet(vertex2, parent);

            if (set1 != set2) {
                mst.push_back(edge);
                unionSets(set1, set2, parent, rank);
            }
        }

        cout << "Kruskal's MST:" << endl;
        for (const auto& edge : mst) {
            cout << get<1>(edge) << " - " << get<2>(edge) << " : " << get<0>(edge) << endl;
        }
    }

    // Prim's MST function for task 3
    void primMST(char start) {
        unordered_map<char, int> key;
        unordered_map<char, char> parent;
        unordered_set<char> inMST;
        for (const auto& pair : graph) {
            key[pair.first] = INT_MAX;
        }
        key[start] = 0;
        parent[start] = -1;

        auto comp = [&](char left, char right) { return key[left] > key[right]; };
        set<char, decltype(comp)> pq(comp);
        pq.insert(start);

        while (!pq.empty()) {
            char vertex = *pq.begin();
            pq.erase(pq.begin());
            inMST.insert(vertex);

            for (auto neighbor : graph[vertex]) {
                char neighborVertex = neighbor.first;
                int weight = neighbor.second;

                if (inMST.find(neighborVertex) == inMST.end() && key[neighborVertex] > weight) {
                    pq.erase(neighborVertex);
                    key[neighborVertex] = weight;
                    pq.insert(neighborVertex);
                    parent[neighborVertex] = vertex;
                }
            }
        }

        cout << "Prim's MST:" << endl;
        for (const auto& pair : parent) {
            if (pair.second != -1) {
                cout << pair.second << " - " << pair.first << " : " << key[pair.first] << endl;
            }
        }
    }
};

int main()
{
    Graph graph;

    graph.addEdge('A', 'B', 1);
    graph.addEdge('A', 'C', 4);
    graph.addEdge('B', 'C', 2);
    graph.addEdge('B', 'D', 7);
    graph.addEdge('C', 'D', 3);
    graph.addEdge('C', 'E', 1);
    graph.addEdge('D', 'F', 5);
    graph.addEdge('E', 'F', 5);

    cout << "Task 1\n";
    cout << "Breadth First Traversal starting from vertex A: ";
    graph.bfs('A');

    cout << "\nDepth First Traversal starting from vertex A: ";
    graph.dfs('A');

    cout << "\n\nTask 2\n";
    graph.kruskalMST();

    cout << "\n\nTask 3\n";
    Graph graph1;

    graph1.addEdge('A', 'B', 6);
    graph1.addEdge('A', 'C', 1);
    graph1.addEdge('A', 'D', 5);
    graph1.addEdge('B', 'C', 5);
    graph1.addEdge('B', 'E', 3);
    graph1.addEdge('C', 'D', 5);
    graph1.addEdge('C', 'E', 6);
    graph1.addEdge('C', 'F', 4);
    graph1.addEdge('D', 'F', 2);
    graph1.addEdge('E', 'F', 6);
    
    graph1.primMST('A');

    return 0;
}
