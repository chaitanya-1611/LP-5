#include <iostream>
#include <stack>
#include <vector>
#include <omp.h>

using namespace std;

const int MAX = 10000;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int node)
{
    stack<int> s;
    s.push(node);

    while (!s.empty())
    {
        int current = s.top();
        s.pop();

        if (!visited[current])
        {
            visited[current] = true;

            if(visited[current]){
                cout<< current<<" ";
            }
               

            // Don't parallelize this part - unsafe on stack
            
            for (int i = 0; i < graph[current].size(); i++)
            {
                int neighbor = graph[current][i];
                if (!visited[neighbor])
                {
                    s.push(neighbor);
                }
            }
        }
    }
}

int main()
{
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // undirected
    }

    int startNode;
    cout << "Enter starting node for DFS: ";
    cin >> startNode;

    // Parallel initialize visited
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
        visited[i] = false;

    cout << "DFS Traversal: ";
    dfs(startNode);
    cout << endl;

    return 0;
}
