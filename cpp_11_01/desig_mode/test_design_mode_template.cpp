
//算法原理与实践

#include <iostream>
using namespace std;
#include <iostream>
#include <cmath>
#include <assert.h>
#include <cstring>
#include <memory>
class Libarery 
{
public:
    void run() {
        step1();
        if(step2())  //！ 支持变化 虚函数多态调用
        {
            step3();
        }
        for (int i=0;i<4;i++) {
            step4();
        }
        step5();
    }
    virtual ~Libarery(){cout <<"~Libarery()"<<endl; }
    Libarery(){cout <<"Libarery()"<<endl; }
    Libarery(const Libarery& a){cout <<"Libarery拷贝构造"<<endl;}
    Libarery& operator=(const Libarery& a){ cout <<"Libarery赋值构造"<<endl; return *this;}
  protected:
        void step1() {cout <<"step1"<<endl;}
        void step3(){cout <<"step3"<<endl;}
        void step5(){cout <<"step5"<<endl;}
        virtual bool step2() = 0;
        virtual void step4() = 0;
};
class Application: public Libarery
{
public:
        Application(){cout <<"Application()"<<endl;}
        virtual ~Application(){cout <<"~Application()"<<endl;}
        Application(const Application& a){cout <<"Application拷贝构造"<<endl;}
        Application& operator=(const Application& a){ cout <<"Application赋值构造"<<endl; return *this;};
   protected:
     virtual bool step2(){ 
         cout<< "step2"<<endl;
         return true;
     }
    virtual void step4(){
        cout <<"step4"<<endl;
        
    }
    
};
int main () 
{
	cout << " test design mode  "<<endl;
    //  Libarery* pLib = new Application();
    //   pLib->run();
     std::shared_ptr<Libarery> shLib = std::make_shared<Application>();
     //auto shLib = std::make_shared<Application>();
     shLib->run();


}