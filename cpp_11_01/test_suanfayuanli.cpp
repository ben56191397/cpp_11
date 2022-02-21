
//算法原理与实践

#include <iostream>
using namespace std;
#include <iostream>
#include <cmath>
#include <assert.h>
#include <cstring>
void* my_memmove(void* dst,const void* src,size_t n) 
{
     assert(dst&& src);
     char* p1 = (char*)dst;
     const char* p2 = (const char*)src;
      
     if (p1 < p2) {
         cout<< " p1 < p2"<<endl;
        while(n-- >0) {
            *p1++ = *p2++;
        }
     }
     else {
         cout << "p1 > =p2"<<endl;
         p1+=n;
         p2+=n;
         while(n-->0) {
            *--p1 = *--p2;
         }
     }
     return dst;
}
void test_memmove()
{
    char test1[20] = {"12345678"};
    char test2[20] = {"abcdefghijk"};
    cout << strlen(test1) <<endl;
    my_memmove(test2,test1,strlen(test1));
    cout << test2<<endl;
}

int main () 
{
	cout << " test suanfyuanli "<<endl;
    test_memmove();

}