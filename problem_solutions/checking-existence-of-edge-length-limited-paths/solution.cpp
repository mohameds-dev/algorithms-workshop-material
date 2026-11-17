#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
private:
    vector<int> parent;
    vector<int> rank;

    int findRoot(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = findRoot(parent[i]);
    }

    void unionSets(int u, int v) {
        int rootU = findRoot(u);
        int rootV = findRoot(v);
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                swap(rootU, rootV);
            }
            parent[rootV] = rootU;
            if (rank[rootU] == rank[rootV]) {
                rank[rootU]++;
            }
        }
    }

public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        rank.assign(n, 0);

        sort(edgeList.begin(), edgeList.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        int numQueries = queries.size();
        vector<int> queryIndices(numQueries);
        iota(queryIndices.begin(), queryIndices.end(), 0);

        sort(queryIndices.begin(), queryIndices.end(), [&](int i, int j) {
            return queries[i][2] < queries[j][2];
        });

        vector<bool> answer(numQueries);
        int edgeIndex = 0;
        int numEdges = edgeList.size();

        for (int qIdx : queryIndices) {
            int p = queries[qIdx][0];
            int q = queries[qIdx][1];
            int limit = queries[qIdx][2];

            while (edgeIndex < numEdges && edgeList[edgeIndex][2] < limit) {
                unionSets(edgeList[edgeIndex][0], edgeList[edgeIndex][1]);
                edgeIndex++;
            }

            answer[qIdx] = (findRoot(p) == findRoot(q));
        }

        return answer;
    }
};
