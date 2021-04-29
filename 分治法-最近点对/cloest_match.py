import random
import math
import matplotlib.pyplot as plt
import time

# Brute-force法计算次数
BRCount = 0
# 分治法计算次数
DCCount = 0
# 分治法最近点对结果
distDC = {}
# 分治法最近点对缓存
buff = {}
# 分治法最短距离
minDistDC = float("inf")


def NewPointPair(point):
    """
    随机生成点，存储到point中
    Args:
        point: 存储点左边的数组，shape = n * 2，其中n为点的数量，2为x和y坐标
    """
    n = 1000
    while n > 0:
        tmp = [random.randint(0, 2000), random.randint(0, 2000)]
        point.append(tmp)
        n -= 1


def Distance(point, id1, id2, mode):
    """
    返回point中标号为id1和id2的两点间距
    Args:
        point: 存储点坐标的数组
        id1: 第一个点的标号
        id2: 第二个点的标号
        mode: BR-Brute-force法，DC-分治法，不同模式对应不同的操作
    Return:
        point[id1]和point[id2]的欧式距离
    """
    global BRCount
    global DCCount
    dist = math.sqrt(
        math.pow(point[id1][0] - point[id2][0], 2)
        + math.pow(point[id1][1] - point[id2][1], 2)
    )
    if mode == "BR":
        # BR-Brute-force法模式
        # 计算次数计数器加一
        BRCount += 1
    elif mode == "DC":
        # 分治法模式
        # 计算次数计数器加一
        DCCount += 1
        # 判断是否加入点对缓存
        if dist in buff:
            # 可能存在多个点对拥有相同的距离，将其存在同一key下
            buff[dist].append((id1, id2))
        else:
            buff[dist] = [(id1, id2)]
    return dist


def BRFindCloestMatch(point):
    """
    Brute-force法求point中的最近点对
    Args:
        point: 存储点左边的数组，shape = n 2，n为点的数量
    Return:
        dist: 最近点对信息的数组
        minDistBR: 最近点对间距
    """
    dist = [
        [Distance(point, i, j, "BR"), i, j]
        for i in range(len(point))
        for j in range(0, i)
    ]
    minDistBR = min(dist)[0]
    dist = list(filter(lambda item: item[0] == minDistBR, dist))
    return dist, minDistBR


def IsMin(dist):
    """
    判断当前距离dist是否为最近距离
    Args:
        dist: 某一点对的间距
    Return:
        minDistDC: 最近点对间距
    """
    global minDistDC
    global buff
    if dist not in buff:
        return minDistDC
    if minDistDC == dist:
        for i in range(0, len(buff[dist])):
            distDC[minDistDC].append(buff[dist][i])
    elif minDistDC > dist:
        minDistDC = dist
        distDC.clear()
        distDC[dist] = buff[dist][:]
    return minDistDC


def MergeToGetMin(point, l, mid, r, minDistDC):
    """
    将左中右三个部分的分治结果合并，求得全局最近点对
    Args:
        point: 点集
        l: 左边界点在点集的标号
        mid: 交界点在点集的标号
        r: 右边界点在点集的标号
        minDistDC: 当前最短距离
    Return:
        res: 合并结果，即三者中的最短距离
    """
    global buff, distDC
    # 由推导可知，合并时只需计算左右临近的6点的间距即可
    l_index = max(mid - 3, l)
    r_index = min(mid + 3, r)
    for i in range(l_index, mid):
        if abs(point[i][0] - point[mid][0]) <= minDistDC:
            for j in range(mid, r_index):
                if (
                    abs(point[i][0] - point[j][0]) <= minDistDC
                    and abs(point[i][1] - point[j][1]) <= minDistDC
                ):
                    Distance(point, i, j, "DC")
    if len(buff) > 0:
        buff = sorted(buff.items(), key=lambda buff: buff[0])
        res = buff[0][0]
        buff = dict(buff)
    else:
        res = float("inf")
    return res


def DCFindCloestMatch(point, l, r):
    global minDistDC, buff
    """
    分治法求最近点对
    Args:
        point: 点集
        l: 左边界点在点集的标号
        r: 右边界点在点集的标号
    Return:
        分治法求得的最近点距离
    """
    if r - l < 2:
        return float("inf")
    elif r - l == 2:  # 已分解到最小
        return Distance(point, l, l + 1, "DC")
    else:  # 还可以继续分解子问题
        mid = int((l + r) / 2)
        # 左半部分的最短距离
        min_l = DCFindCloestMatch(point, l, mid)
        minDistDC = IsMin(min_l)
        buff.clear()
        # 右半部分的最短距离
        min_r = DCFindCloestMatch(point, mid, r)
        minDistDC = IsMin(min_r)
        buff.clear()
        # 左右交叉部分的最短距离
        temp = MergeToGetMin(point, l, mid, r, minDistDC)
        minDistDC = IsMin(temp)
        buff.clear()
        return min(min_l, min_r, temp)


if __name__ == "__main__":

    # 初始化用于存储1000个点坐标的数组point，并随机生成点
    point = []
    NewPointPair(point)

    # Brute-force法求最近点对
    time_start = time.time()
    distBR, mindBR = BRFindCloestMatch(point)
    time_end = time.time()
    pBR = [[point[item[1]], point[item[2]]] for item in distBR]
    print("Brute-force法：\n计算次数：", BRCount, "\n最短距离：", mindBR, "\n最近点对数量：", len(pBR))
    print("最近点对：", pBR)
    print("耗时：", (time_end - time_start) * 1000, "ms")

    # 分治法求最近点对
    time_start = time.time()
    point.sort()  # 首先排序
    mindDC = DCFindCloestMatch(point, 0, len(point))
    time_end = time.time()
    pDC = [[point[item[0]], point[item[1]]] for item in list(distDC.values())[0]]
    print("分治法：\n计算次数：", DCCount, "\n最短距离：", mindDC, "\n最近点对数量：", len(pDC))
    print("最近点对：", pDC)
    print("耗时：", (time_end - time_start) * 1000, "ms")

    plt.title("Cloest Match")
    for i in range(len(point)):
        plt.plot(point[i][0], point[i][1], "ro")
    for item in pBR:
        plt.plot(item[0][0], item[0][1], "k+")
        plt.plot(item[1][0], item[1][1], "k+")
    for item in pDC:
        plt.plot(item[0][0], item[0][1], "kx")
        plt.plot(item[1][0], item[1][1], "kx")
    plt.show()
