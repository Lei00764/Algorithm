#include <iostream>

using namespace std;

/**
 * @brief 每次走一步消耗1卡路里，每次走两步消耗2卡路里
 * 
 * @param m 步数
 * @param n 卡路里数
 * @return int 多少种情况 
 */
int fun1(int m, int n)
{
    if (m < 0 || n < 0 || m > n)  // 终止条件
        return 0;
    else if (m == 0 && n >= 0)
        return 1;
    return fun1(m - 1, n - 1) + fun1(m - 2, n - 3); 
}


int main()
{
    // 样例
    cout << fun1(6, 6) << endl;
    cout << fun1(3, 6) << endl;
    cout << fun1(-5, 7) << endl;
    
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
    
    cout << "ouput: " << fun1(m, n) << endl;
    return 0;
}