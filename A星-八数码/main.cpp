#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

// 偏移数组：上，右，下，左
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
string pos[4] = {"up", "right", "down", "left"};
// 目标状态，其中0代表空格
vector<vector<int>>
    finalBorad = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}};
// 目标状态的数码对应的坐标，便于计算f(n)，finalMap的每个元素的格式为 { 数码，{ 行标，列标 } }
unordered_map<int, vector<int>> finalMap = {
    {1, {0, 0}}, {2, {0, 1}}, {3, {0, 2}}, {4, {1, 2}}, {5, {2, 2}}, {6, {2, 1}}, {7, {2, 0}}, {8, {1, 0}}, {0, {1, 1}}};

/**
 * @brief Node类，一个Node存储了八数码问题的的一个节点，提供求解问题过程中需要用到的各种方法
 */
class Node
{
private:
    vector<vector<int>> board = vector<vector<int>>(3, vector<int>(3, 0)); // 棋盘状态
    int depth;                                                             // 当前节点的深度
    int zeroX;                                                             // 空格的行标
    int zeroY;                                                             // 零格的列
    int prePosition;                                                       // 上一次移动位置
    int weight;                                                            // 代价函数f(n)的值
    Node *father;                                                          // 父节点指针
public:
    Node();                                        // 生成存储初始状态的节点
    Node(Node *n, int prePos, int newX, int newY); // 生成存储中间状态节点
    int getDepth();                                // 获取当前节点深度
    int getZeroX();                                // 获取空格的行号
    int getZeroY();                                // 获取空格的列号
    int getPrePosition();                          // 获取当前节点的上一次移动方向
    int getWeight();                               // 获取代价函数f(n)的值
    Node *getFather();                             // 获取父亲节点
    int calculateFn(int mode);                     // 根据mode计算对应的f(n)
    void print();                                  // 输出棋盘状态，深度，上一次移动，f(n)
    bool isFinal();                                // 判断当前状态是否为目标状态
    void backtrace();                              // 回溯获得起始状态到当前节点的路径
    void solutionAStar(int mode);                  // A*算法求解结果，根据mode使用不用的f(n)
    void solutionBFS();                            // BFS遍历求解结果
};

/** 
 * @brief Node无参构造函数，生成存储初始状态的节点
 */
Node::Node()
{
    cout << "Please enter the initial status of Eight Digits: " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> this->board[i][j];
            if (this->board[i][j] == 0)
            {
                this->zeroX = i;
                this->zeroY = j;
            }
        }
    }
    this->depth = 0;
    this->prePosition = -1;
    this->father = nullptr;
}

/** 
 * @brief Node有参构造函数，生成存储中间状态的节点
 * @param n 扩展节点
 * @param prePos 移动的方向
 * @param newX 空格的行号
 * @param newY 空格的列号
 */
Node::Node(Node *n, int prePos, int newX, int newY)
{
    for (int i = 0; i < 3; i++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                this->board[i][j] = n->board[i][j];
            }
        }
    }
    this->zeroX = newX;
    this->zeroY = newY;
    swap(this->board[newX][newY], this->board[n->getZeroX()][n->getZeroY()]);
    this->depth = n->getDepth() + 1;
    this->prePosition = prePos;
    this->father = n;
}

/** 
 * @brief 获取当前节点的深度
 * @return 当前节点的深度
 */
int Node::getDepth()
{
    return this->depth;
}

/** 
 * @brief 获取当前节点空白格的行号
 * @return 当前节点空白格的行号
 */
int Node::getZeroX()
{
    return this->zeroX;
}

/** 
 * @brief 获取当前节点空白格的列号
 * @return 当前节点空白格的列号
 */
int Node::getZeroY()
{
    return this->zeroY;
}

/** 
 * @brief 获取当前节点的上一次移动方向
 * @return 当前节点的上一次移动方向
 */
int Node::getPrePosition()
{
    return this->prePosition;
}

/** 
 * @brief 当前节点的代价
 * @return 当前节点的代价
 */
int Node::getWeight()
{
    return this->weight;
}

/** 
 * @brief 获取父亲节点
 * @return 父亲节点
 */
Node *Node::getFather()
{
    return this->father;
}

/** 
 * @brief 根据mode计算对应的f(n)
 * @param mode 0 -> f(n) = 当前节点深度
 *             1 -> f(n) = 当前节点深度 + 当前节点不在其位的数码个数
 *             2 -> f(n) = 当前节点深度 + 不在其位的数码移动到目标状态的最少步数总和
 * @return f(n)
 */
int Node::calculateFn(int mode)
{
    // BFS，f(n) = 当前节点深度
    if (mode == 0)
    {
        return this->getDepth();
    }
    int w = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->board[i][j] != 0 && this->board[i][j] != finalBorad[i][j])
            {
                // f(n) = 当前节点深度 + 当前节点不在其位的数码个数
                if (mode == 1)
                {
                    w += 1;
                }
                // f(n) = 当前节点深度 + 不在其位的数码移动到目标状态的最少步数总和
                else if (mode == 2)
                {
                    int finalX = finalMap[this->board[i][j]][0];
                    int finalY = finalMap[this->board[i][j]][1];
                    w += abs(finalX - i) + abs(finalY - j);
                }
            }
        }
    }
    w += this->getDepth();
    return w;
}

/** 
 * @brief 输出棋盘状态，深度，上一次移动方向，f(n)
 */
void Node::print()
{
    cout << "Depth: " << this->getDepth() << ", Direction: " << pos[this->getPrePosition()] << ", f(n) = " << this->getWeight() << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << this->board[i][j] << " ";
        }
        cout << endl;
    }
}

/** 
 * @brief 判断当前节点状态是否为目标状态
 * @return true  -> 当前节点是目标状态
 *         false -> 当前节点不是目标状态
 */
bool Node::isFinal()
{
    bool flag = true;
    for (int i = 0; flag && i < 3; i++)
    {
        for (int j = 0; flag && j < 3; j++)
        {
            if (this->board[i][j] != finalBorad[i][j])
            {
                flag = false;
            }
        }
    }
    return flag;
}

/** 
 * @brief 回溯输出从起始状态到当前节点的路径
 */
void Node::backtrace()
{
    Node *cur = this;
    vector<Node *> res;
    while (cur != nullptr)
    {
        res.push_back(cur);
        cur = cur->getFather();
    }
    for (int i = res.size() - 1; i >= 0; i--)
    {
        res[i]->print();
    }
}

/** 
 * @brief 重写仿函数用于支持优先权队列，返回true时，a的优先级低于b的优先级
 * @param a Node 
 * @param b Node 
 * @return 优先比较代价函数f(n)，当f(n)一致时优先扩展深度较小的节点
 */
struct cmp
{
    bool operator()(Node *a, Node *b)
    {
        if (a->getWeight() > b->getWeight())
        {
            return true;
        }
        else if (a->getWeight() == b->getWeight())
        {
            return a->getDepth() > b->getDepth();
        }
        return false;
    }
};

/** 
 * @brief A*算法求解结果，根据mode使用不用的f(n)
 * @param mode 1 -> f(n) = 当前节点深度 + 当前节点不在其位的数码个数
 *             2 -> f(n) = 当前节点深度 + 不在其位的数码移动到目标状态的最少步数总和
 * @return 问题有解 -> 输出求解问题的走法
 *         问题无解 -> 输出无解
 */
void Node::solutionAStar(int mode)
{
    if (mode == 1)
    {
        cout << "A*: f(n) = depth + the number of digits that are not in their bits." << endl;
    }
    else if (mode == 2)
    {
        cout << "A*: f(n) = depth + sum of steps that move to final status." << endl;
    }
    // 活结点表，使用小顶堆构造活结点表
    priority_queue<Node *, vector<Node *>, cmp> slipknot;
    this->weight = this->calculateFn(mode);
    slipknot.push(this);
    // total为生成节点数，ext为扩展节点数
    int total = 1, ext = 0;
    // 判断有无解的标志
    bool flag = false;
    // 在BFS的基础上用A*算法扩展节点
    while (!slipknot.empty())
    {
        // 取出f(n)最小的活结点
        Node *cur = slipknot.top();
        ext += 1;
        // cout << "----Extend----" << endl;
        // cur->print();
        // 若为目标状态，结束遍历，输出结果
        if (cur->isFinal())
        {
            // cur->print();
            flag = true;
            cout << "Get a solution! The total number of steps needed is " << cur->getDepth() << "." << endl;
            cur->backtrace();
            break;
        }
        else
        {
            // cout << "----Generat----" << endl;
            // 删除堆顶元素，即当前要扩展的活结点
            slipknot.pop();
            // 将该活结点的子结点加入活结点表
            for (int i = 0; i < 4; i++)
            {
                // 防止重复扩展节点
                int prePos = (cur->getPrePosition() + 2) % 4;
                if (cur->getPrePosition() == -1 || i != prePos)
                {
                    int newX = cur->getZeroX() + dx[i];
                    int newY = cur->getZeroY() + dy[i];
                    if (newX < 3 && newX >= 0 && newY < 3 && newY >= 0)
                    {
                        Node *tmp = new Node(cur, i, newX, newY);
                        tmp->weight = tmp->calculateFn(mode);
                        // tmp->print();
                        slipknot.push(tmp);
                        total += 1;
                    }
                }
            }
        }
    }
    if (!flag)
    {
        cout << "No solution!" << endl;
    }
    cout << "A total of " << total << " nodes were generated." << endl
         << "A total of " << ext << " nodes were extended." << endl;
    cout << endl;
}

/** 
 * @brief 用BFS求解给定八数码问题初始状态的解
 * @return 问题有解 -> 输出求解问题的走法
 *         问题无解 -> 输出无解
 */
void Node::solutionBFS()
{
    cout << "BFS: f(n) = depth." << endl;
    // 活结点表，使用队列
    queue<Node *> slipknot;
    this->weight = this->calculateFn(0);
    slipknot.push(this);
    // total为生成节点数，ext为扩展节点数
    int total = 1, ext = 0;
    // 判断有无解的标志
    bool flag = false;
    // 用BFS的方式扩展节点
    while (!slipknot.empty() && !flag)
    {
        int s = slipknot.size();
        for (int i = 0; !flag && i < s; i++)
        {
            // 取出队头节点进行扩展
            // cout << "----Extend----" << endl;
            Node *cur = slipknot.front();
            slipknot.pop();
            ext += 1;
            // cur->print();
            // cout << "----Generat----" << endl;
            // 将该活结点的子结点加入活结点表
            for (int i = 0; i < 4; i++)
            {
                // 防止重复扩展节点
                int prePos = (cur->getPrePosition() + 2) % 4;
                if (cur->getPrePosition() == -1 || i != prePos)
                {
                    int newX = cur->getZeroX() + dx[i];
                    int newY = cur->getZeroY() + dy[i];
                    if (newX < 3 && newX >= 0 && newY < 3 && newY >= 0)
                    {
                        Node *tmp = new Node(cur, i, newX, newY);
                        tmp->weight = tmp->calculateFn(0);
                        // tmp->print();
                        slipknot.push(tmp);
                        total += 1;
                        // 若为目标状态，结束遍历，输出结果
                        if (tmp->isFinal())
                        {
                            flag = true;
                            cout << "Get a solution! The total number of steps needed is " << tmp->getDepth() << "." << endl;
                            cur->backtrace();
                            break;
                        }
                    }
                }
            }
        }
    }
    if (!flag)
    {
        cout << "No solution!" << endl;
    }
    cout << "A total of " << total << " nodes were generated." << endl
         << "A total of " << ext << " nodes were extended." << endl;
    cout << endl;
}

int main()
{
    /*
    测试组-1
        2 8 3
        1 0 4
        7 6 5
    测试组-2
        3 7 2
        8 1 5
        4 6 0
    */
    while (true)
    {
        Node *n = new Node();
        cout << endl;
        n->solutionBFS();
        n->solutionAStar(1);
        n->solutionAStar(2);
    }
    system("pause");
    return 0;
}