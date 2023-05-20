// g++ main.cpp --std=c++11
#include <iostream>
#include <vector>

using namespace std;

int max_gold; // 最大黄金数量

void backtrack(vector<vector<int>> &grid, int i, int j, int current_gold, vector<vector<int>> &visited);
int getMaximumGold(vector<vector<int>> &grid);

int getMaximumGold(vector<vector<int>> &grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 0) // 该单元格黄金数量为 0 跳过
                continue;

            vector<vector<int>> visited(grid.size(), vector<int>(grid[0].size(), 0)); // 初始化一个二维数组，用于记录已访问过的单元格
            backtrack(grid, i, j, 0, visited);                                        // 回溯
        }
    }
    return max_gold;
}

/**
 * @brief 回溯
 */
void backtrack(vector<vector<int>> &grid, int i, int j, int current_gold, vector<vector<int>> &visited)
{
    // 越界 或 已访问 或 该单元格黄金数量为 0
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || visited[i][j] == 1 || grid[i][j] == 0)
    {
        if (current_gold > max_gold)
            max_gold = current_gold;
        return;
    }

    visited[i][j] = 1;
    current_gold += grid[i][j]; // 当前黄金数量加上该单元格黄金数量

    backtrack(grid, i - 1, j, current_gold, visited); // 上
    backtrack(grid, i, j + 1, current_gold, visited); // 右
    backtrack(grid, i + 1, j, current_gold, visited); // 下
    backtrack(grid, i, j - 1, current_gold, visited); // 左

    visited[i][j] = 0;
}

int main()
{
    vector<vector<int>> grid = {{0, 6, 0}, {5, 8, 7}, {0, 9, 0}};
    // vector<vector<int>> grid = {{1, 0, 7}, {2, 0, 6}, {3, 4, 5}, {0, 3, 0}, {9, 0, 20}};
    // vector<vector<int>> grid = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

    // 打印 grid
    cout << "grid:" << endl;
    for (int i = 0; i < grid.size(); i++)
    {
        cout << "  ";
        for (int j = 0; j < grid[0].size(); j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    cout << "max_gold: " << getMaximumGold(grid) << endl;
    return 0;
}
