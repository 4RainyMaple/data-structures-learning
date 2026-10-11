#include<map>
#include<string>
#include<vector>
#include<iostream>
using namespace std;

//打印adjacentWords个数大于minWords（默认值为1）的单词，及其adjacentWords和个数
void printHighChangeables 
( const map <string, vector<string>> & adjacentWords , int minWords = 1 )
{
    for ( auto & entry : adjacentWords )
    {
        const vector<string> & words = entry.second;

        if ( words.size() >= minWords )
        {
            cout << entry.first << "(" << words.size() << "):";
            for ( auto & word : words )
                cout << word << " ";
            cout << endl;
        }
    }
}

//检测两个单词是否只有一个字母不同
bool oneCharOff( const string & word1, const string & word2 )
{
    //先查长度
    if ( word1.size() != word2.size() )
        return false;

    int diffs = 0;

    int len = (int)word1.size();
    for ( int i = 0; i < len; i++ )
    {
        if ( word1[i] != word2[i] )
            diffs++;
        if ( diffs > 1 )
            return false;   //提前终止提速
    }
    return diffs == 1;
}

//给adjacentWords填入元素
map<string,vector<string>> computeAdjacentWords( vector <string> & words )
{
    map <string,vector<string>> adjacentWords;

    int len = (int)words.size();
    for ( int i = 0; i < len; i++ )
        for ( int j = i + 1; j < len; j++ ) //从 i+1 开始枚举防止重复
            if ( oneCharOff(words[i],words[j]))
            {
                adjacentWords[words[i]].push_back(words[j]);
                adjacentWords[words[j]].push_back(words[i]);
            }

    return adjacentWords;
}

int main()
{
    vector <string> words = {"dine","fine","nine","wine","foot","boot"};
    map <string,vector<string>> adjacentWords = computeAdjacentWords( words );
    printHighChangeables( adjacentWords );
}