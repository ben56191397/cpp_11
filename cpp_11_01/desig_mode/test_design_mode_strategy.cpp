
//算法原理与实践

#include <iostream>
using namespace std;
#include <iostream>
#include <cmath>
#include <assert.h>
#include <cstring>
#include <memory>

class Strategy
{
public:
 ~Strategy(){cout<< "~Strategy"<< endl;}
 virtual void AlgrithmInterface()=0;
protected:
 Strategy(){cout<< "Strategy"<< endl;}
};
 
class ConcreteStrategyA : public Strategy
{
public:
 ConcreteStrategyA(){cout<< "ConcreteStrategyA"<< endl;}
 ~ConcreteStrategyA(){cout<< "~ConcreteStrategyA"<< endl;}
 virtual void AlgrithmInterface() override {cout<< " A AlgrithmInterface"<< endl;}
};
 
class ConcreteStrategyB : public Strategy
{
public:
 ConcreteStrategyB(){cout<< "ConcreteStrategyB"<< endl;}
 ~ConcreteStrategyB(){cout<< "~ConcreteStrategyB"<< endl;}
 virtual void AlgrithmInterface()override {cout<< " B AlgrithmInterface"<< endl;}
};
 
class Context
{
public:
 Context(Strategy* st):_strategy(st){}
 ~Context(){}
 void DoAction(){_strategy->AlgrithmInterface();}
private:
 Strategy* _strategy;
};
 
int main()
{
 //策略A与B可替换
 Strategy* pStra = new ConcreteStrategyA();
 Context* pCon = new Context(pStra);
 pCon->DoAction();
  delete pStra;
 delete pCon;
 pStra = new ConcreteStrategyB();
 pCon = new Context(pStra);
 pCon->DoAction();
 delete pStra;
 delete pCon;
 return 0;
}

// if else 多的时时候 变化的，可以考虑 strtegy模式
//用扩展的模式 面对变化