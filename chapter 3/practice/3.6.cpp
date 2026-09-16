#include <list>     //保存人员编号，方便删除出局的人

//3.6：Josephus问题，N个人编号为1~N，从1号开始传递
//M为每轮传递次数（M >= 0），N为人数（N >= 1）
//每轮传递M次后清除当前的人，从其后一个人继续，返回最后获胜者的编号
int josephus ( int M, int N )
{
    std::list <int> l;
    for ( int i = 1; i <= N; ++i )
    {
        l.push_back(i);
    }

    if ( M == 0 )
        return *(--l.end());

    //迭代器不要在里面初始化，避免每次循环迭代器从头开始
    auto itr = l.begin();
    while ( l.size() != 1 )
    {
        for ( int j = 1; j <= M; ++j )
        {
            ++itr;
            if ( itr == l.end() )
                itr = l.begin();
        }
        itr = l.erase(itr);
        //此处也涉及迭代器移动，要检查是否到头
        if ( itr == l.end() )
                itr = l.begin();
    }
    return *l.begin();
}
