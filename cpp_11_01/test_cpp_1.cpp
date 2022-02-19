
//如何优雅地利用C++编程从1乘到20

#include <iostream>
using namespace std;
#include <iostream>
#include <cmath>

namespace ss01{

	int fun1()
	{
		std::cout << std::tgamma(20 + 1) << std::endl;
		return 0;
	}
}


#include <iostream>
#include <utility>

template<std::size_t...I> 
constexpr auto foo(std::index_sequence<I...>) 
{ 
	return ((I+1) * ...); 
}

int fun2() 
{
	std::cout << "fun2:"<< foo(std::make_index_sequence<20>()) << std::endl;
	return 0;
}

void fun3() {
    int i;
    long long j;
    for(i = 1, j = 1;i <= 20; j *= i++);
     cout << "func3:" <<j<<endl;
}

#include <iostream>
#include <string>
#include <memory>

struct IBaseInterface {
    virtual ~IBaseInterface() = 0;
};
inline IBaseInterface::~IBaseInterface() = default;

struct IDataProvider : virtual public IBaseInterface {
    virtual int first() = 0;
    virtual int last() = 0;
    virtual int next(int v) = 0;
};

struct ICalculator : virtual public IBaseInterface {
    virtual long long calc(IDataProvider *) = 0;
};

struct IPrinter : virtual public IBaseInterface {
    virtual void print(const std::string &) = 0;
};

struct ISerializer : virtual public IBaseInterface {
    virtual std::string serialize(long long value) = 0;
};

struct IRunnable : virtual public IBaseInterface {
    virtual void run() = 0;
};

class Foo : virtual public IRunnable {
    std::shared_ptr<IDataProvider> m_dp;
    std::shared_ptr<ICalculator> m_c;
    std::shared_ptr<ISerializer> m_s;
    std::shared_ptr<IPrinter> m_p;
public:
    Foo(std::shared_ptr<IDataProvider> dp, std::shared_ptr<ICalculator> c,
	 std::shared_ptr<ISerializer> s, std::shared_ptr<IPrinter> p) 
	 : m_dp(std::move(dp)),m_c(std::move(c)), m_s(std::move(s)),m_p(std::move(p)) {}
    void run() override 
	{ 
		return  m_p->print(m_s->serialize(m_c->calc(m_dp.get()))); 
	}
};

class DefaultSerializer : virtual public ISerializer {
public:
    std::string serialize(long long value) override { return std::to_string(value); }
};

class StreamPrinter : virtual public IPrinter {
    std::ostream &m_os;
public:
    explicit StreamPrinter (std::ostream &os) : m_os(os) {}
    void print(const std::string &s)  override { m_os << s << std::endl; }
};

class MultiplyAccumulateCalculator : virtual public ICalculator {
public:
    long long calc(IDataProvider *dp) override {
        int i = dp->first();
        long long j = i;
        do
            j *= (i = dp->next(i));
        while(i != dp->last());
        return j;
    }
};

int fun4() {
    struct MyDataProvider : virtual public IDataProvider {
        int first() override { return 1; }
        int last() override { return 20; }
        int next(int v) override { return v+1; }
    };
    Foo foo(std::make_shared<MyDataProvider>(), std::make_shared<MultiplyAccumulateCalculator>(),
	         std::make_shared<DefaultSerializer>(), std::make_shared<StreamPrinter>(std::cout));
    foo.run();
	return 0;
}

#include <iostream>
#include <xmmintrin.h>

double foo(int x) {
    __m128 a = {1.0f, 2.0f, 3.0f, 4.0f};
    __m128 b = {4.0f, 4.0f, 4.0f, 4.0f};
    __m128 c = {1.0f, 1.0f, 1.0f, 1.0f};
    for(int i = 0; i < x / 4; ++i, a = _mm_add_ps(a, b))
        c = _mm_mul_ps(c, a);
    for(int i = x % 4; i < 4; ++i)
        a[i] = 1.0f;
    c = _mm_mul_ps(c, a);
    return (double)c[0] * (double)c[1] * (double)c[2] * (double)c[3];
}

int fun5() {
    std::cout << "fun5 " << foo(20) << std::endl;
	return 0;
}

// #include <iostream>
// #include <numeric>
// #include <vector>
// #include <functional>
// int fun6() {
//  std::vector<int> v(std::atoi(std::end(__DATE__) - (__LINE__) / 2) - 1); // 2021年，第六行
//  std::iota(v.begin(), v.end(), 1);
//  std::cout << std::accumulate(v.begin(), v.end(), 1ull, std::multiplies<>()) << std::endl;
// }


#include <iostream>
#include <iomanip>
#include <type_traits>

using BaseType_t = long long;
constexpr BaseType_t lgBase = 9; // 注意10000*10000刚刚好小于int的取值范围
constexpr BaseType_t Base = 1000000000; // 注意10000*10000刚刚好小于int的取值范围

// 大整数的表示
template<BaseType_t...I> struct BigInteger {
    using type = BigInteger;
};

// 连接
template<class T1, class T2> 
struct BI_Cat;

template<BaseType_t...I1, BaseType_t...I2> 
struct BI_Cat <BigInteger<I1...>, BigInteger<I2...>> : BigInteger<I1..., I2...> {};

// 左移一个单元（即*Base）
template<class T> 
struct BI_SHL;

template<BaseType_t...I> 
struct BI_SHL<BigInteger<I...>> : BigInteger<I..., 0> {};

// 去除开头的0
template<class T> struct BI_Remove_Zeros : T {};
template<BaseType_t...I> struct BI_Remove_Zeros<BigInteger<0, I...>> : BI_Remove_Zeros<BigInteger<I...>> {};

// 填充0到N个单元
template<int X, class IS> 
struct BI_Fill_Impl;

template<int X, class T, T...I> 
struct BI_Fill_Impl<X, std::integer_sequence<T, I...>> : BigInteger<(I, X)...> {};

template<int Size> 
struct BI_Fill_Zeros : BI_Fill_Impl<0, std::make_index_sequence<Size>> {};

template<class T, int N> 
struct BI_Resize;
template<BaseType_t...I, int N> 
struct BI_Resize<BigInteger<I...>, N> : BI_Cat<typename BI_Fill_Zeros<N - sizeof...(I)>::type, BigInteger<I...>> {};

// 返回较大的数值
template<int A, int B> 
struct int_min : std::integral_constant<int, (A<B?B:A)> {};

// 非进位加法：先把两个数的位数改成一样的然后依次相加
template<class A, class B, class ShouldResize> 
struct BI_AddNotCarry_Impl;
template<BaseType_t...I1, BaseType_t...I2> 
struct BI_AddNotCarry_Impl <BigInteger<I1...>, BigInteger<I2...>, std::true_type> : BigInteger<(I1 + I2)...> {};

template<BaseType_t...I1, BaseType_t...I2> 
struct BI_AddNotCarry_Impl <BigInteger<I1...>, BigInteger<I2...>, std::false_type>
     : BI_AddNotCarry_Impl<
         typename BI_Resize<BigInteger<I1...>, int_min<sizeof...(I1), sizeof...(I2)>::value>::type,
         typename BI_Resize<BigInteger<I2...>, int_min<sizeof...(I1), sizeof...(I2)>::value>::type,
         std::true_type
     >{};

template<class A, class B> 
struct BI_AddNotCarry;
template<BaseType_t...I1, BaseType_t...I2> 
struct BI_AddNotCarry <BigInteger<I1...>, BigInteger<I2...>>
    : BI_AddNotCarry_Impl<BigInteger<I1...>, BigInteger<I2...>, std::bool_constant<sizeof...(I1) == sizeof...(I2)>> {};

// 判断是否为0
template<class Y> 
struct BI_IsZero;
template<BaseType_t...I> 
struct BI_IsZero<BigInteger<I...>> : std::bool_constant<((I == 0) && ...)> {};

// 自动进位
template<class A> 
struct BI_Carry;
template<class A, class B> 
struct BI_Add : BI_Carry<typename BI_AddNotCarry<A, B>::type> {};

template<class Mod, class Div, class ShouldCalc = typename BI_IsZero<Div>::type> 
struct BI_Carry_Impl;

template<class Mod, class Div> 
struct BI_Carry_Impl<Mod, Div, std::true_type> : Mod {};

template<class Mod, class Div> 
struct BI_Carry_Impl<Mod, Div, std::false_type>
        : BI_Add<Mod, typename BI_SHL<Div>::type > {};

template<BaseType_t...I> 
struct BI_Carry<BigInteger<I...>>
        : BI_Remove_Zeros<typename BI_Carry_Impl<BigInteger<(I % Base)...>, BigInteger<(I / Base)...>>::type> {};

// 乘以X并自动进位
template<class A, int X> 
struct BI_MulX;
template<BaseType_t...I1, int X> 
struct BI_MulX <BigInteger<I1...>, X>
        : BI_Carry<BigInteger<(I1 * X)...>> {};

// 计算阶乘
template<int X> 
struct BI_Fact : BI_MulX<typename BI_Fact<X-1>::type, X> {};
template<> 
struct BI_Fact<0> : BigInteger<1> {};

template<BaseType_t...I>
std::ostream &operator<<(std::ostream &out, BigInteger<I...>) {
    return ((out << std::setfill('0') << I << std::setw(lgBase)), ...);
}

int fun7()
{
    std::cout <<"fun7:"<< typename BI_Fact<20>::type() << std::endl;
	return 0;
}
int main ()
{
	cout << " test start "<<endl;
	 ss01::fun1();
	fun2();
	fun3();
	fun4();
	fun5();

	fun7();

}