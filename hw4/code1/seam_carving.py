# Seam Carving 算法

import numpy as np
import cv2
import time


class SeamCarver:

    def __init__(self, in_image, out_height, out_width):
        """
        file_name:  图片的路径
        out_height: 输出图片的高度
        out_width:  输出图片的宽度
        """

        self.in_image = in_image

        # 最终我们想要的尺寸
        self.out_height = out_height
        self.out_width = out_width

        # 记录移除的列数
        self.count = 0

        self.in_height, self.in_width = self.in_image.shape[:2]  # 输入图片的尺寸

        # 复制一份原始图片，接下来就是要处理 out_image 这张图片
        self.out_image = np.copy(self.in_image)

    def CalculateEnergy(self):
        """
        计算能量图
        能量方程 = X方向梯度幅值 + Y方向梯度幅值
        """

        t = time.time()
        # 分离图片通道
        b, g, r = cv2.split(self.out_image)
        # 计算每个图片通道的能量图
        b_energy = np.absolute(cv2.Scharr(b, -1, 1, 0)) + \
            np.absolute(cv2.Scharr(b, -1, 0, 1))
        g_energy = np.absolute(cv2.Scharr(g, -1, 1, 0)) + \
            np.absolute(cv2.Scharr(g, -1, 0, 1))
        r_energy = np.absolute(cv2.Scharr(r, -1, 1, 0)) + \
            np.absolute(cv2.Scharr(r, -1, 0, 1))
        energy_map = b_energy + g_energy + r_energy
        return energy_map

    def FindPerSeam(self):
        """
        从 out_image 中找到一个 seam
        """

        energy_map = self.CalculateEnergy()  # 计算能量图
        rows, cols = energy_map.shape

        # 最小能量值 = 该像素的能量值 + 上一行相邻像素的最小能量值
        M = energy_map.copy().astype(np.int32)  # 存每个像素的最小能量值

        # 从第二行开始，对应行号1
        for i in range(1, rows):
            for j in range(0, cols):
                if j == 0:  # 第一列
                    M[i, j] += min(M[i-1, j], M[i-1, j+1])
                elif j == cols - 1:  # 最后一列
                    M[i, j] += min(M[i-1, j-1], M[i-1, j])
                else:
                    M[i, j] += min(M[i-1, j-1], M[i-1, j], M[i-1, j+1])
        # 上面是使用for循环的动态规划代码，但实在是太慢了！！！

        # seam 保存我们需要删除的像素点坐标
        seam = np.zeros((rows, 2), dtype=np.int32)

        # 寻找最后一行 M[cols-1] 中值最小的一列，从下往上找
        min_j = np.argmin(M[rows-1])
        seam[rows-1, 1] = min_j  # 把最后一行的最小值的坐标加入seam

        for i in range(rows-1, -1, -1):  # 从最后一行找到第一行
            if (min_j == 0):
                min_j = np.argmin(M[i-1, min_j:min_j+2])
            elif (min_j == cols - 1):
                min_j += np.argmin(M[i-1, min_j-1:min_j+1]) - 1
            else:
                min_j += np.argmin(M[i-1, min_j-1:min_j+2]) - 1
            seam[i] = [i, min_j]

        return seam

    def RemovePerSeam(self):
        """
        从 out_image 中移除一个 seam
        """

        """
        # 使用 for 循环删除的代码 速度太慢了！！！
        seam = self.FindPerSeam()
        rows, cols = self.out_image.shape[:2]

        # mask[i][j] = 0 说明该点要删掉
        mask = np.ones((rows, cols))
        for i, j in seam:
            mask[i, j] = 0

        temp_image = np.zeros((rows, cols-1, 3), dtype=np.uint8)

        for i in range(rows):
            for j in range(cols-1):
                if mask[i, j]:
                    temp_image[i, j] = self.out_image[i, j]
                else:
                    temp_image[i, j] = self.out_image[i, j+1]
        # 这里同理，使用 numpy 处理进行加速

        # 将 temp_image 复制给  self.out_image
        # 注意：两张图片尺寸不一样，故需要 resize
        self.out_image = np.resize(self.out_image, temp_image.shape)
        self.out_image = temp_image.copy()  # 此时 self.out_image 减少了一列
        """
        seam = self.FindPerSeam()
        rows, cols = self.out_image.shape[:2]
        mask = np.ones((rows, cols), dtype=bool)  # True 表示保留，False 表示删除
        mask[seam[:, 0], seam[:, 1]] = False  # 将 seam 中的点标记为 False
        self.out_image = self.out_image[mask].reshape(
            (rows, cols-1, 3))  # 删除 seam 中的点

    def SeamCarving(self):

        for i in range(self.in_width - self.out_width):
            t = time.time()
            self.RemovePerSeam()
            self.count += 1
            print(f"[INFO]: 一轮耗时{time.time() - t}，已移除{self.count}列")

        print(self.out_image.shape)
        cv2.imwrite("./output/out_image1.png", self.out_image)


if __name__ == '__main__':
    t = time.time()
    file_name = './src/image1.png'
    in_image = cv2.imread(file_name).astype(np.float64)  # 读取原始图片

    # 设置输出图片尺寸
    out_height = in_image.shape[0]      # 输出图片的高度
    out_width = in_image.shape[1] // 2  # 输出图片的宽度 原图片的一半

    obj = SeamCarver(in_image, out_height, out_width)
    obj.SeamCarving()
    print(f"[INFO]: 总耗时{time.time() - t}")
