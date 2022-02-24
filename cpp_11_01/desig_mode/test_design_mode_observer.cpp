
//算法原理与实践

#include <iostream>
using namespace std;
#include <iostream>
#include <cmath>
#include <assert.h>
#include <cstring>
#include <memory>
//观察者模式定义
// 定义对象的一种一对多的依赖关系，以便于当一个对象的状态发生变化时，所有
// 依赖他的对象都得到通知并自动更新
#include <iostream>
#include <list>
using namespace std;
 
class Observer
{
public:
    virtual void Update(int) = 0;
    virtual  ~Observer(){ cout << " ~Observer:"  << endl;}
};
 
class Subject
{
public:
    virtual void Attach(std::shared_ptr<Observer>) = 0;
    virtual void Detach(std::shared_ptr<Observer>) = 0;
    virtual void Notify() = 0;
};
 
class ConcreteObserver : public Observer
{
public:
    ConcreteObserver(std::shared_ptr<Subject> pSubject) : m_pSubject(pSubject){}
 
    void Update(int value)
    {
        cout << "ConcreteObserver get the update. New State:" << value << endl;
    }
   ~ConcreteObserver(){ cout << " ~ConcreteObserver:"  << endl;}
private:
    std::weak_ptr<Subject> m_pSubject;
};
 
class ConcreteObserver2 : public Observer
{
public:
    ConcreteObserver2(std::shared_ptr<Subject> pSubject) : m_pSubject(pSubject){}
 
    void Update(int value)
    {
        cout << "ConcreteObserver2 get the update. New State:" << value << endl;
    }
   ~ConcreteObserver2(){ cout << " ~ConcreteObserver2:"  << endl;}
private:
    std::weak_ptr<Subject> m_pSubject;
};
 
class ConcreteSubject : public Subject
{
public:
    void Attach(std::shared_ptr<Observer>pObserver);
    void Detach(std::shared_ptr<Observer>pObserver);
    void Notify();
 
    void SetState(int state)
    {
        m_iState = state;
    }
    ~ConcreteSubject(){ cout << " ~ConcreteSubject:"  << endl;}
private:
    std::list<std::shared_ptr<Observer>> m_ObserverList;
    int m_iState;
};
 
void ConcreteSubject::Attach(std::shared_ptr<Observer> pObserver)
{
    m_ObserverList.push_back(pObserver);
}
 
void ConcreteSubject::Detach(std::shared_ptr<Observer> pObserver)
{
    m_ObserverList.remove(pObserver);
}
 
void ConcreteSubject::Notify()
{
    std::list<std::shared_ptr<Observer>>::iterator it = m_ObserverList.begin();
    while (it != m_ObserverList.end())
    {
        (*it)->Update(m_iState);
        ++it;
    }
}
 
int main()
{
    cout << "test 2:" <<endl;
    std::shared_ptr<ConcreteSubject> pSubjecttt = std::make_shared<ConcreteSubject>();

    std::shared_ptr<Observer>  p1 = std::make_shared<ConcreteObserver>(pSubjecttt);
    std::shared_ptr<Observer>  pObserver66 = std::make_shared<ConcreteObserver>(pSubjecttt);
    std::shared_ptr<Observer>  pObserver67 = std::make_shared<ConcreteObserver2>(pSubjecttt);
 
    pSubjecttt->SetState(2);
    pSubjecttt->Attach(pObserver66);
    pSubjecttt->Attach(pObserver67);
 
    pSubjecttt->Notify();
 
   
    pSubjecttt->Detach(pObserver66);
 
    pSubjecttt->SetState(3);
    pSubjecttt->Notify();
    
}

