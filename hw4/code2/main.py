# 无约束的最优化问题

import math


def f(x1, x2):
    """
    定义函数表达式
    """
    return math.exp(x1 + 3*x2 - 0.1) + math.exp(x1 - 3*x2 - 0.1) + math.exp(-x1 - 0.1)


def df(x1, x2):
    """
    分别求出 x1, x2 的梯度
    """
    grad_x1 = math.exp(x1 + 3*x2 - 0.1) + math.exp(x1 -
                                                   3*x2 - 0.1) - math.exp(-x1 - 0.1)
    grad_x2 = 3*math.exp(x1 + 3*x2 - 0.1) - 3*math.exp(x1 - 3*x2 - 0.1)
    return grad_x1, grad_x2


def update(n):
    """
    更新 n 次
    如果梯度小于阈值则停止迭代
    """

    x1 = 0
    x2 = 0
    alpha = 0.01
    for i in range(n):
        grad_x1, grad_x2 = df(x1, x2)
        # print(abs(grad_x1), abs(grad_x2))
        # 梯度小于阈值时停止迭代
        if (abs(grad_x1) < 1e-12) and abs(grad_x2 < 1e-12):
            break
        x1 = x1 - alpha * grad_x1
        x2 = x2 - alpha * grad_x2
    print('x1: ', x1, 'x2: ', x2)
    print('f(x1, x2): ', f(x1, x2))


if __name__ == "__main__":
    update(10000)
