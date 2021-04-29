#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <windows.h>
#include <time.h>
using namespace std;

void AddPrezero(string &s, int len);
void AddLastzero(string &s, int L);
void removePrezero(string &s);
string MulLargeNumBR(string num1, string num2);
string Add(string num1, string num2);
string Sub(string num1, string num2);
string Mul(string num1, string num2);
string NewBRNum(int n);

int main()
{
    double time1 = 0, time2 = 0;
    double counts = 0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    for (int i = 5000; i <= 15000; i += 1000)
    {
        string num1 = NewBRNum(i), num2 = NewBRNum(i), res1 = "", res2 = "";
        cout << i << "位的二进制数：\t";
        //  << "num1 = " << num1 << endl
        //  << "num2 = " << num2 << endl;

        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBeginTime); //开始计时
        res1 = MulLargeNumBR(num1, num2);
        QueryPerformanceCounter(&nEndTime);
        time1 = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
        cout << "Brute-Force法：\t" << time1 * 1000 << "ms\t";
        //  << "Brute-Force法计算结果：\t" << res1 << endl;

        QueryPerformanceCounter(&nBeginTime); //开始计时
        res2 = Mul(num1, num2);
        QueryPerformanceCounter(&nEndTime);
        time2 = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
        cout << "分治法：\t" << time2 * 1000 << "ms\t"
             << "比例：" << time1 / time2 << endl;
        //  << "分治法计算结果：\t" << res2 << endl;
    }

    return 0;
}

/*
* @brief Brute-Force实现大数乘法，无任何优化的按位相乘再相加
* @param num1: 第一个乘数
* @param num1: 第二个乘数
* @return: s: Brute-Force相乘后的结果
*/
string MulLargeNumBR(string num1, string num2)
{
    if (num1 == "0" || num2 == "0")
    {
        return "0";
    }
    int m = num1.size(), n = num2.size();
    string s = "0";
    for (int i = m - 1; i >= 0; i--)
    {
        string tmp = "";
        int a = num1.at(i) == '1';
        for (int j = 0; j < n; j++)
        {
            int b = (num2.at(j) == '1');
            tmp += a && b ? "1" : "0";
        }
        AddLastzero(tmp, m - i - 1);
        s = Add(s, tmp);
    }
    return s;
}

/*
* @brief 增加前置0
* @param s: 待处理字符串/数字
* @param len: 补0后的目标长度
*/
void AddPrezero(string &s, int len)
{
    for (int i = 0; i < len; i++)
        s = s.insert(0, "0");
}

/*
* @brief 增加后置0
* @param s: 待处理字符串/数字
* @param len: 补0后的长度
*/
void AddLastzero(string &s, int L)
{
    for (int i = 0; i < L; i++)
        s += "0";
}

/* 
* @brief 去除前置0
* @param s: 要去除前置0的数字，用string存储
*/
void removePrezero(string &s)
{
    if (s.length() == 1)
        return;
    int k = 0, i = 0;
    while (s[i++] == '0')
    {
        k++;
    }
    s = k == s.length() ? "0" : s.substr(k);
}

/*
* @brief 大数相加
* @param num1: 第一个加数
* @param num1: 第二个加数
* @return s: 相加后的结果
*/
string Add(string num1, string num2)
{
    string s = "";
    // 去掉前置0
    removePrezero(num1);
    removePrezero(num2);
    // 逆置字符串以便于按位相加
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    int n = max(num1.size(), num2.size()), c = 0;
    for (size_t i = 0; i < n; ++i)
    {
        int a = i < num1.size() ? (num1.at(i) == '1') : 0;
        int b = i < num2.size() ? (num2.at(i) == '1') : 0;
        s.insert(0, a ^ b ^ c ? "1" : "0");
        c = (a && b) || (b && c) || (a && c);
    }
    s.insert(0, c ? "1" : "");
    return s;
}

/*
* @brief 大数相减
* @param num1: 减数
* @param num2: 被减数
* @return: s: 相减后的结果
*/
string Sub(string num1, string num2)
{
    string s = "";
    string flag = "+";
    //去掉前置0
    removePrezero(num1);
    removePrezero(num2);
    // 提取符号，并保证绝对值大的数在前
    int len1 = num1.length();
    int len2 = num2.length();
    int len = len1 > len2 ? len1 : len2;
    if (len1 < len2)
    {
        flag = "-";
        swap(num1, num2);
        swap(len1, len2);
    }
    else if (len1 == len2)
    {
        int i = 0;
        while (i < len1 && num1.at(i) == num2.at(i))
            i++;
        if (i == len1)
            return "0"; // 两数相等
        else if (num1.at(i) < num2.at(i))
        {
            flag = "-";
            swap(num1, num2);
            swap(len1, len2);
        }
    }
    vector<int> num(len);
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    int c = 0, i = 0;
    for (; i < len; i++)
    {
        int a = i < len1 ? num1.at(i) == '1' : 0;
        int b = i < len2 ? num2.at(i) == '1' : 0;
        s.insert(0, to_string(int((a != b) != c))); //同或
        c = a - c >= b ? 0 : 1;                     // 借位
    }
    // 去除高位的0
    removePrezero(s);
    return flag == "-" ? flag + s : s;
}

/*
* @brief 分治法大数相乘
* @param num1: 乘数
* @param num2: 乘数
* @return: result: 分治法相乘后的结果
*/
string Mul(string num1, string num2)
{
    // 取出符号位并判断结果的正负
    bool flag1 = false, flag2 = false;
    if (num1.at(0) == '-')
    {
        flag1 = true;
        num1 = num1.substr(1);
    }
    if (num2.at(0) == '-')
    {
        flag2 = true;
        num2 = num2.substr(1);
    }
    //将数前置若干个0，使其长度为2的幂
    int L = 4;
    if (num1.length() > 2 || num2.length() > 2)
    {
        if (num1.length() >= num2.length())
        {
            while (L < num1.length())
                L *= 2;
            if (L != num1.length())
                AddPrezero(num1, L - num1.length());
            AddPrezero(num2, L - num2.length());
        }
        else
        {
            while (L < num2.length())
                L *= 2;
            if (L != num2.length())
                AddPrezero(num2, L - num2.length());
            AddPrezero(num1, L - num1.length());
        }
    }

    int n = num1.length();
    string result = "";
    string a = num1.substr(0, n / 2);
    string b = num1.substr(n / 2, n);
    string c = num2.substr(0, n / 2);
    string d = num2.substr(n / 2, n);
    if (n == 1) // 已分解到最小的子问题
    {
        string tmp1 = Add(a, b), tmp2 = Add(c, d);
        result = MulLargeNumBR(tmp1, tmp2);
    }
    else // 还可以分治
    {
        if (n == 2)
        {
            // result = (a * 2 + b) * (c * 2 + d)
            a += "0";
            c += "0";
            string tmp1 = Add(a, b), tmp2 = Add(c, d);
            result = MulLargeNumBR(tmp1, tmp2);
        }
        else
        {
            // result = ac * 2^n + ((a + b)(d + c) - ac - bd) * 2^(n/2) + bd
            string ac = Mul(a, c);
            string bd = Mul(b, d);
            string aAddB = Add(a, b);
            string dAddC = Add(d, c);
            string tmp1 = Mul(aAddB, dAddC);
            string adAddBc = Sub(Sub(tmp1, ac), bd);
            AddLastzero(ac, n);
            AddLastzero(adAddBc, n / 2);
            result = Add(Add(ac, adAddBc), bd);
        }
    }

    if ((flag1 || flag2) && !(flag1 && flag2))
        result.insert(0, "-");
    return result;
}

/*
* @brief 随机生成任意长度的二进制数
* @param n: 需要生成的二进制数的位数
* @return: str: 随机生成的n位数字
*/
string NewBRNum(int n)
{
    string str = "";
    srand(time(NULL));
    int i;
    str += "1";
    for (i = 0; i < n - 1; ++i)
    {
        switch ((rand() % 2))
        {
        case 1:
            str += '1';
            break;
        default:
            str += '0';
            break;
        }
    }
    return str;
}