//以下内容均由deepseek生成
// 习题1.4：模拟 C++ 预处理器的 #include 展开（简化版）。
// 读入一个文件（由命令行参数指定），把里面形如：
//   #include "文件名"
// 的语句，递归地"内联"成被包含文件的内容，并输出完全展开后的结果。
//
// 为便于理解，本程序只支持一种写法：#include "文件名"（引号写法）。
// include 可以嵌套；用 active 集合防御循环包含。

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cctype>
using namespace std;

// 判断一行是否形如 #include "文件名"，若是则取出文件名放到 filename，返回 true。
// 若不是，返回 false。
bool parseInclude(const string & line, string & filename)
{
    // 1. 跳过行首空白
    size_t i = 0;
    while (i < line.size() && isspace((unsigned char)line[i]))
        ++i;

    // 2. 行首必须是 #include
    if (line.compare(i, 8, "#include") != 0)
        return false;

    size_t after = i + 8;   // 跳过 "#include"

    // 3. 跳过 include 后面的空白
    while (after < line.size() && isspace((unsigned char)line[after]))
        ++after;

    // 4. 后面必须紧跟一个引号 "
    if (after >= line.size() || line[after] != '"')
        return false;

    // 5. 找到第二个引号 "
    size_t close = line.find('"', after + 1);
    if (close == string::npos)
        return false;

    // 6. 两个引号中间的内容就是文件名
    filename = line.substr(after + 1, close - after - 1);
    return true;
}

// 递归地把 filename 这个文件展开，并输出到 cout。
// active：当前正在展开的"链"上的文件名集合，用来检测循环包含（防御）。
void processFile(const string & filename, set<string> & active)
{
    // 防御：若该文件已在展开链上，说明出现了循环包含（A -> B -> A）
    if (active.count(filename))
    {
        cerr << "// 警告：检测到循环包含：" << filename << "，已跳过。\n";
        return;
    }

    ifstream in(filename);
    if (!in)
    {
        // 打不开：警告后跳过，不打断整体输出
        cerr << "// 警告：打不开文件：" << filename << "，已跳过。\n";
        return;
    }

    active.insert(filename);          // 进入该文件，加入展开链

    string line;
    while (getline(in, line))
    {
        string incFile;
        if (parseInclude(line, incFile))
            processFile(incFile, active);   // 是 include 行 → 递归展开被包含文件
        else
            cout << line << '\n';           // 普通行原样输出
    }

    active.erase(filename);           // 离开该文件，从展开链移除
}

int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        cerr << "用法：" << argv[0] << " <主文件>\n";
        return 1;
    }

    string mainFile = argv[1];
    set<string> active;               // 当前展开链上的文件集合（初始为空）
    processFile(mainFile, active);
    return 0;
}