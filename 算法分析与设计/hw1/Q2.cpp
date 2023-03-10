#include <iostream>

using namespace std;

int max_calories = 0;  // 记录消耗卡路里的最大值
int pre_calories = 0;  // 一条从上到下路径上消耗的卡路里
int sum = 0;  // 记录有多少种方法


/**
 * @brief 每次走一步消耗1卡路里，每次走两步消耗2卡路里，尽可能多消耗卡路里
 * 
 * @param m 步数
 * @param n 卡路里数
 * @return int 多少种情况  
 */
void backtrack(int m, int n)
{
    // 结束条件
    if (m == 0 && n >= 0)
    {
        if (pre_calories == max_calories)
            sum++;
        else if (max_calories < pre_calories)  // 说明之前的路错了，并非消耗最多卡路里
        {
            sum = 1;
            max_calories = pre_calories;
        }
        return;
    }

    // 判断是否应该继续往下走
    if (m < 0 || n < 0)
        return;
    pre_calories += 1;  // 做选择
    backtrack(m - 1, n - 1);
    pre_calories -= 1;  // 撤销选择

    pre_calories += 3;
    backtrack(m - 2, n - 3);
    pre_calories -= 3;
}

int main()
{
    int m, n;
    while (1) // 输入错误处理
    {
        cout << "input: ";
        cin >> m >> n;  
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1024, '\n');
            
            continue;
        }
        break;
    }
    backtrack(m, n);
    cout << "ouput: " << sum << endl;
    cout << "消耗卡路里：" << max_calories << endl;
    return 0;
}