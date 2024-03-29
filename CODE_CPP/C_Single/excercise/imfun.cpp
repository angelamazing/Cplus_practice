#include "./h1.h"

//交换2个 整型指针 , important
bool swapIntPoint(int *&a, int *&b)
{
    int *tmp = a;
    a = b;
    b = tmp;
    return TRUE;
}

//字符查找函数
string::size_type find_char(const string &s, char c, 
                           string::size_type &occurs)
{
    auto ret = s.size();   // position of the first occurrence, if any
    occurs = 0;            // set the occurrence count parameter 

    for (decltype(ret) i = 0; i != s.size(); ++i) {
        if (s[i] == c) {
            if (ret == s.size()) 
                ret = i;   // remember the first occurrence of c
            ++occurs;      // increment the occurrence count
         }
	}
    return ret;            // count is returned implicitly in occurs
}