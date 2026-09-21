#include <iostream>
#include <stack>
#include <string>
#include "BinaryNode.h"


// 练习范围：合法的后缀表达式，单字符操作数，二元运算符 + - * /。
// 输入不包含空格，例如 ab+c* 表示 (a+b)*c。
// 创建节点时，记得把 left 和 right 初始化为 nullptr。

// 判断字符是否为上述四种运算符。
bool isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// 根据后缀表达式构造表达式树，返回根指针；空串返回 nullptr。
// 可以使用 std::stack<BinaryNode<char>*> 保存子树的根指针。
BinaryNode<char> * buildTree(const std::string & postfix)
{
    if ( postfix.empty() )
        return nullptr;

    // 保存各子树根指针的栈
    std::stack<BinaryNode<char>*> trees;

    // 从左到右读取后缀表达式的每一个字符。
    for ( char ch : postfix )
    {
        // 为当前字符创建节点，左右孩子先设为空。
        BinaryNode<char> * node = new BinaryNode<char>{ch, nullptr, nullptr};

        if ( isOperator(ch) )
        {
            // 遇到运算符，取出两棵子树，连接到新节点下面。
            // 先弹出的是右子树，后弹出的是左子树，顺序不能反。
            node->right = trees.top();
            trees.pop();

            node->left = trees.top();
            trees.pop();
        }

        // 操作数：压入只有一个节点的树。
        // 运算符：压入刚刚连接好的新树。
        trees.push(node);
    }

    // 合法表达式处理完后，栈里只剩整棵表达式树的根指针。
    // 栈销毁时只移除指针，不会释放指针所指向的节点。
    return trees.top();
}

// 中序输出：每个运算符节点对应的表达式加一对括号，以保留运算顺序。
// 空树不输出；函数内部不换行。
void printInfix(const BinaryNode<char> * root)
{
    if ( root == nullptr )
        return;

    if ( isOperator(root->element) )
        std::cout << "(";
    
    printInfix(root->left);
    std::cout << root->element;
    printInfix(root->right);

    if ( isOperator(root->element) )
        std::cout << ")";
}

// 后序输出：结果应与输入的后缀表达式相同。
// 空树不输出；函数内部不换行。
void printPostfix(const BinaryNode<char> * root)
{
    if ( root == nullptr )
        return;

    printPostfix(root->left);
    printPostfix(root->right);

    std::cout << root->element;
}

// 释放树的所有节点，并将传入的根指针置为 nullptr；空树直接返回。
void destroyTree(BinaryNode<char> * & root)
{
    // 空树没有节点需要释放，也是递归结束的条件。
    if ( root == nullptr )
        return;

    // 先释放左右子树，最后释放当前节点：这是后序遍历。
    destroyTree(root->left);
    destroyTree(root->right);

    // 孩子都处理完了，现在可以删除当前节点。
    delete root;

    // root 是指针的引用，这会把调用者传入的指针也置为空。
    // delete 不会自动清空指针，需要我们手动设置。
    root = nullptr;
}

int main()
{
    const std::string postfix = "ab+c*";
    BinaryNode<char> * root = buildTree(postfix);

    std::cout << "Infix: ";
    printInfix(root);                 // 完成后应输出：((a+b)*c)
    std::cout << '\n';

    std::cout << "Postfix: ";
    printPostfix(root);               // 完成后应输出：ab+c*
    std::cout << '\n';

    destroyTree(root);
    
}
