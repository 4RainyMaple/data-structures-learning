// 习题1.3：只能用「一次输出单个数字」的 I/O 例程，
//         写出能输出任意实数（可为负数）的过程。
// 思路：先实现一个只输出单个数字的原始例程 printDigit，
//       再用它拼出整数、以及实数的输出。

#include<iostream>
#include<cmath>    // 用到 std::round、std::pow
using namespace std;

// 原始例程：一次只输出一个数字（0~9）。
// 题目假设我们的输出能力只有「打印单个数字」，
// 所以所有数字的打印最终都必须经过这个函数。
void printDigit(int d)
{
    cout << d;
}

// 辅助函数：打印一个非负整数（用 unsigned long long 防止极端值溢出）。
// 递归思路：先把「去掉最后一位」的更高位打印出来，
//          再打印个位，这样自然得到从高位到低位的顺序。
void printNonNeg(unsigned long long m)
{
    if(m >= 10)             // 还有更高位，先递归打印它
        printNonNeg(m / 10);
    printDigit(m % 10);     // 打印当前最低位（个位）
}

// 输出一个整数（可能为负数）。
void printInt(int n)
{
    if(n < 0)
    {
        cout << '-';                    // 先打印负号
        // 转成 long long 再取负，避免对 INT_MIN 取负时溢出
        printNonNeg(-(long long)n);
    }
    else
    {
        printNonNeg(n);
    }
}

// 输出一个实数（可能为负数）。
// 把实数拆成：符号 + 整数部分 + '.' + 小数部分。
// 小数部分每次乘 10，用 (int) 取出下一位数字再输出，循环到剩余小数足够小为止。
void printDouble(double n)
{
    // 处理负数符号
    if(n < 0)
    {
        cout << '-';
        n = -n;
    }

    // 整数部分（向零取整）
    int intPart = (int)n;
    printInt(intPart);
    cout << '.';                        // 小数点

    // 小数部分 = n - intPart
    double frac = n - intPart;

    // 二进制浮点无法精确表示很多十进制小数（如 0.05、0.6789），
    // 若直接逐位放大取整，会残留二进制误差尾巴（3.05 会打出 3.049999...）。
    // 这里先把小数部分舍入到指定精度，再逐位提取，输出更贴近预期。
    const int PRECISION = 6;                       // 保留 6 位小数，保证输出结果干净
    double scale = pow(10.0, PRECISION);
    frac = round(frac * scale) / scale;

    // 用 do-while：即使小数部分为 0（如 0.0），也至少输出一位 '0'，得到 “0.0”
    const int MAX_DIGITS = 15;                     // 小数位上限，进一步防止死循环
    int digitCount = 0;
    do
    {
        frac *= 10;                    // 把下一位小数移到个位
        int d = (int)frac;             // 取出下一位小数数字
        printDigit(d);                 // 输出它
        frac -= d;                     // 消掉已输出的一位
        ++digitCount;
    } while(frac > 1e-9 && digitCount < MAX_DIGITS);
}

int main()
{
    printInt(-115);       cout << endl;    // 期望：-115
    printInt(0);          cout << endl;    // 期望：0
    printDouble(3.05);    cout << endl;    // 期望：3.05
    printDouble(12.5);    cout << endl;    // 期望：12.5
    printDouble(-3.75);   cout << endl;    // 期望：-3.75
    printDouble(0.0);     cout << endl;    // 期望：0.0
    printDouble(1.0/3.0); cout << endl;    // 期望：0.333333（舍入到 6 位）
    return 0;
}
