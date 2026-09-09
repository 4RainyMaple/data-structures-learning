/*辗转相除法：
两个数不断相除取余，直到余数为零时，最大公约数为商*/

int EuclidAlgorithm(int & a, int & b)
{
    while (b != 0)
    {
        int rem = a%b;
        a = b;
        b = rem;
    }
    return a;
}