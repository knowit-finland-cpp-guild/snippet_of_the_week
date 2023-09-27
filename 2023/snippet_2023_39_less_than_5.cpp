// Compiles in C++17+

#include <iostream>
#include <vector>

int barTLtComp{};
int barFLtComp{};

template<bool B>
struct Foo
{
Foo(int i) : i{i} {}

bool operator==(Foo const& rhs) const {++fooEqComp; return i == rhs.i;}
bool operator<(Foo const& rhs) const {++fooLtComp; return i < rhs.i;}

int i{};

inline static int fooEqComp{};
inline static int fooLtComp{};
};

template<bool B>
struct Bar
{
Foo<B> a;
Foo<B> b;
Foo<B> c;
Foo<B> d;
Foo<B> e;
};

bool operator<(Bar<true> const& lhs, Bar<true> const& rhs)
{
++barTLtComp;
return lhs.a == rhs.a
    ? lhs.b == rhs.b
        ? lhs.c == rhs.c
            ? lhs.d == rhs.d
                ? lhs.e < rhs.e
                : lhs.d < rhs.d
            : lhs.c < rhs.c
        : lhs.b < rhs.b
    : lhs.a < rhs.a;
}

bool operator<(Bar<false> const& lhs, Bar<false> const& rhs)
{
++barFLtComp;
return lhs.a < rhs.a
    || (lhs.a == rhs.a && lhs.b < rhs.b)
    || (lhs.a == rhs.a && lhs.b == rhs.b && lhs.c < rhs.c)
    || (lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c && lhs.d < rhs.d)
    || (lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c && lhs.d == rhs.d && lhs.e < rhs.e);
}

int main()
{
std::vector<Bar<true>> vTlhs, vTrhs;
std::vector<Bar<false>> vFlhs, vFrhs;
for(int i=0; i<2; ++i)
    for(int j=0; j<2; ++j)
        for(int k=0; k<2; ++k)
            for(int m=0; m<2; ++m)
                for(int n=0; n<2; ++n)
                    for(int p=0; p<2; ++p)
                        for(int q=0; q<2; ++q)
                            for(int r=0; r<2; ++r)
                                for(int s=0; s<2; ++s)
                                    for(int t=0; t<2; ++t)
                    {
                    vTlhs.push_back(Bar<true>{i,j,k,m,n});
                    vTrhs.push_back(Bar<true>{p,q,r,s,t});
                    vFlhs.push_back(Bar<false>{i,j,k,m,n});
                    vFrhs.push_back(Bar<false>{p,q,r,s,t});
                    }
for(auto& i: vTlhs)
    for(auto& j: vTrhs)
        i<j;

for(auto& i: vFlhs)
    for(auto& j: vFrhs)
        i<j;

std::cout << "Result T: "
    << "Foo == comp: " << Foo<true>::fooEqComp
    << ", Foo < comp: " << Foo<true>::fooLtComp
    << ", Bar < comp: " << barTLtComp << std::endl;

std::cout << "Result F: "
    << "Foo == comp: " << Foo<false>::fooEqComp
    << ", Foo < comp: " << Foo<false>::fooLtComp
    << ", Bar < comp: " << barFLtComp << std::endl;
}
