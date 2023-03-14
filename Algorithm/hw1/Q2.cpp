#include <iostream>

using namespace std;

int max_calories = 0;  // 记录消耗卡路里的最大值
int pre_calories = 0;  // 一条从上到下路径上消耗的卡路里
int sum = 0;  // 记录有多少种方法


/**
 * @brief 每次走一步消耗1卡路里，每次走两步消耗2卡路里，尽可能多消耗卡路里
 *        使用回溯算法解决
 * @param m 步数
 * @param n 卡路里数
 * @return int 多少种情况  
 */
void Solution1(int m, int n)
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
    Solution1(m - 1, n - 1);
    pre_calories -= 1;  // 撤销选择

    pre_calories += 3;
    Solution1(m - 2, n - 3);
    pre_calories -= 3;
}

/**
 * @brief 计算组合数 Cnr n在下，r在上
 * 
 * @param n 
 * @param r 
 */
int  Combination(int n, int r)
{
    if (r == 0 || r == n)
        return 1;
    return Combination(n - 1, r - 1) + Combination(n - 1, r); 
}

/**
 * @brief 每次走一步消耗1卡路里，每次走两步消耗2卡路里，尽可能多消耗卡路里
 *        使用数学方法得出计算公式，再利用计算机求解（纯数学题）
 * @param m 步数
 * @param n 卡路里数
 * @return int 多少种情况  
 */
int Solution2(int m, int n)
{
    if (n < 3 * m / 2)
        return Combination(2 * m - n, n - m);
    else if (n >= 3 * m / 2 && m % 2 == 0)  // m为偶数
        return 1;
    else // m为奇数
        return (m + 1) / 2;
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

    Solution1(m, n);
    Solution2(m, n);
    cout << "方法一 " << "ouput: " << sum << endl;
    // cout << "消耗卡路里：" << max_calories << endl;
    cout << "方法二 " << "ouput: " << Solution2(m, n) << endl; 
    if (sum == Solution2(m, n))
        cout << "两种方法结果相同" << endl;
    else
        cout << "出现bug!!!" << endl;
    return 0;
}