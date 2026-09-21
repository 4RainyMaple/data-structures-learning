#include <iostream>
#include <string>
#include <vector>

// 一个对象就是树中的一个节点。为方便练习，成员直接公开。
struct FileSystem
{
    std::string name;                  // 节点名字
    bool directory;                    // true：文件夹；false：普通文件
    std::vector<FileSystem> children;   // 直接子节点，普通文件没有子节点

    bool isDirectory() const;
    void printName(int depth) const;
    void listAll(int depth = 0) const;
};

bool FileSystem::isDirectory() const
{
    return directory; 
}

void FileSystem::printName(int depth) const
{
    for ( int i = 0; i < depth; ++i )
        std::cout << "\t";

    std::cout << name << std::endl;
}

void FileSystem::listAll(int depth) const
{
    // children 中每个元素都是 FileSystem 对象，可以调用它的成员函数。
    printName(depth);
    if ( isDirectory() )
    {
        for ( const auto & c : children )   //引用避免不必要的拷贝
            c.listAll(depth + 1);
    }
}

int main()
{
    // 每个节点的初始化顺序：名字、是否为文件夹、子节点列表。
    FileSystem root{
        "study", true, {
            {"math", true, {
                {"notes.txt", false, {}}
            }},
            {"english.txt", false, {}},
            {"empty", true, {}}
        }
    };

    root.listAll();
}

