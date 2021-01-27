#ifndef __COMPLEX__
#define __COMPLEX__

// 前置声明
#include <cmath>
#include <iostream>
using namespace std;

class complex;

complex&
__doapl(complex* ths, const complex& r);
complex&
__doami(complex* ths, const complex& r);
complex&
__doaml(complex* ths, const complex& r);
complex
conj(const complex& x);


// 类-声明
class complex
{
public:
    complex(double r = 0, double i = 0) : re(r), im(i)  // 初始化
    { }  // 括号里叫assign ments

    complex& operator += (const complex&);
    complex& operator -= (const complex&);
    complex& operator *= (const complex&);
    complex& operator /= (const complex&);
    double real() const { return re; }  // 函数若在class body 内定义完成，便自动成为inline 候选人
    double imag() const { return im; }
private:
    double re, im;
    friend complex& __doapl(complex*, const complex&);
    friend complex& __doami(complex*, const complex&);
    friend complex& __doaml(complex*, const complex&);
};


// 类-定义
inline complex&
complex::operator += (const complex& r)
{
    return __doapl(this, r);
}

inline complex&
complex::operator -= (const complex& r)
{
    return __doami(this, r);
}

inline complex&
complex::operator *= (const complex& r)
{
    return __doaml(this, r);
}


inline complex&
__doapl(complex* ths, const complex& r)
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

inline complex&
__doami(complex* ths, const complex& r)
{
    ths->re -= r.re;
    ths->im -= r.im;
    return *ths;
}

inline complex&
__doaml(complex* ths, const complex& r)
{
    ths->re *= r.re;
    ths->im *= r.im;
    return *ths;
}

inline complex
operator + (const complex& x, const complex& y)
{
    return complex(x.real() + y.real(),
        x.imag() + y.imag());
}

inline complex
operator + (const complex& x, double y)
{
    return complex(x.real() + y, x.imag());
}

inline complex
operator + (double x, const complex& y)
{
    return complex(y.real() + x, y.imag());
}


inline complex
operator - (const complex& x, const complex& y)
{
    return complex(x.real() - y.real(),
        x.imag() - y.imag());
}

inline complex
operator - (const complex& x, double y)
{
    return complex(x.real() - y, x.imag());
}

inline complex
operator - (double x, const complex& y)
{
    return complex(x - y.real(), y.imag());
}


inline complex
operator * (const complex& x, const complex& y)
{
    return complex(x.real() * y.real(),
        x.imag() * y.imag());
}

inline complex
operator * (const complex& x, double y)
{
    return complex(x.real() * y, x.imag());
}

inline complex
operator * (double x, const complex& y)
{
    return complex(x * y.real(), y.imag());
}


inline complex
operator / (const complex& x, const complex& y)
{
    return complex(x.real() / y.real(),
        x.imag() / y.imag());
}

inline complex
operator / (const complex& x, double y)
{
    return complex(x.real() / y, x.imag());
}

inline complex
operator / (double x, const complex& y)
{
    return complex(x / y.real(), y.imag());
}


inline complex
operator + (const complex& x)
{
    return x;
}

inline complex
operator - (const complex& x)
{
    return complex(-x.real(), -x.imag());
}


inline bool
operator == (const complex& x, const complex& y)
{
    return x.real() == y.real() && x.imag() == y.imag();
}

inline bool
operator == (const complex& x, double y)
{
    return x.real() == y && x.imag() == 0;
}

inline bool
operator == (double x, const complex& y)
{
    return y.real() == x && y.imag() == 0;
}


inline bool
operator != (const complex& x, const complex& y)
{
    return x.real() != y.real() || x.imag() != y.imag();
}

inline bool
operator != (const complex& x, double y)
{
    return x.real() != y || x.imag() != 0;
}

inline bool
operator != (double x, const complex& y)
{
    return y.real() != x || y.imag() != 0;
}


inline complex
conj(const complex& x)
{
    return complex(x.real(), -x.imag());
}


inline ostream&
operator << (ostream& os, const complex& x)
{
    return os << '(' << x.real() << ','
        << x.imag() << ')';
}

#endif  // __CPMLPEX__