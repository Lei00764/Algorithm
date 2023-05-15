## 编程题

请使用 C++11 及以上编译 main.cpp

```shell
g++ main.cpp --std=c++11
```

### 算法思路

遍历所有单元格，对于黄金数量为 0 的单元格，跳过，否则以该单元格为起点，进行探索。每次探索中，回更新最大黄金数量 max_gold。

在以(i, j)为起点的探索中，从(i, j)开始，依次向上右下左四个方向进行探索，如果搜索到的单元格未被访问过且有黄金，则将当前黄金数量加上该单元格的黄金数量，并继续向四个方向进行搜索。如果搜索到的单元格已经被访问过或者没有黄金，则回溯到上一个单元格。最终返回最大的黄金数量。

这里并不需要减去之前加上的单元格的黄金数量，因此当前黄金数量 current_gold 是函数形参，不会对上一层的 current_gold 产生影响。

### 算法时空复杂度

m = grid.size()

n = grid[0].size()

k 表示有黄金的单元格的数量

两层 for 循环遍历存在黄金数量的单元格，对应时间复杂度 $O(mn)$，其中有 k 个有黄金的单元格，显然 k < mn。对于每一个有黄金的单元格，作为起点开始遍历，除了第一步有 3 个方向可以试探外，其余均最多有 3 个方向可以试探。因此，每个单元格遍历对应时间复杂度 $O(3^k)$。

因此，最终时间复杂度为 $O(k * 3^k)$

时间复杂度：$O(k \times 3^k)$

因为我们维护了两个大小为 mxn 的二维数组，因此空间复杂度为 $O(mn)$

### 主要函数

```c++
void backtrack(vector<vector<int>> &grid, int i, int j, int current_gold, vector<vector<int>> &visited);
int getMaximumGold(vector<vector<int>> &grid);
```

![截屏2023-05-13 20.57.29](https://lei-1306809548.cos.ap-shanghai.myqcloud.com/Obsidian/%E6%88%AA%E5%B1%8F2023-05-13%2020.57.29.png)

![截屏2023-05-13 20.57.39](https://lei-1306809548.cos.ap-shanghai.myqcloud.com/Obsidian/%E6%88%AA%E5%B1%8F2023-05-13%2020.57.39.png)

### 运行结果示例

<img src="https://lei-1306809548.cos.ap-shanghai.myqcloud.com/Obsidian/%E6%88%AA%E5%B1%8F2023-05-13%2020.56.15.png" alt="截屏2023-05-13 20.56.15" style="zoom:67%;" />

<img src="https://lei-1306809548.cos.ap-shanghai.myqcloud.com/Obsidian/%E6%88%AA%E5%B1%8F2023-05-13%2020.56.37.png" alt="截屏2023-05-13 20.56.37" style="zoom:67%;" />

<img src="https://lei-1306809548.cos.ap-shanghai.myqcloud.com/Obsidian/%E6%88%AA%E5%B1%8F2023-05-13%2020.56.47.png" alt="截屏2023-05-13 20.56.47" style="zoom:67%;" />

### 力扣测试

题目链接：https://leetcode.cn/problems/path-with-maximum-gold/

![力扣](https://lei-1306809548.cos.ap-shanghai.myqcloud.com/Obsidian/%E5%8A%9B%E6%89%A3.png)