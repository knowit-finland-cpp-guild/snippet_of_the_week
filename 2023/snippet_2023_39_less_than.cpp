#include <iostream>
#include <vector>

int fooEqComp{};
int fooLtComp{};
int barTLtComp{};
int barFLtComp{};

struct Foo
{
Foo(int i) : i{i} {}

bool operator==(Foo const& rhs) const {++fooEqComp; return i == rhs.i;}
bool operator<(Foo const& rhs) const {++fooLtComp; return i < rhs.i;}

int i{};
};

template<bool B>
struct Bar
{
Foo a;
Foo b;
Foo c;
};

bool operator<(Bar<true> const& lhs, Bar<true> const& rhs)
{
++barTLtComp;
return lhs.a == rhs.a
    ? lhs.b == rhs.b
        ? lhs.c < rhs.c
        : lhs.b < rhs.b
    : lhs.a < rhs.a;
}

bool operator<(Bar<false> const& lhs, Bar<false> const& rhs)
{
++barFLtComp;
return lhs.a < rhs.a
    || (lhs.a == rhs.a && lhs.b < rhs.b)
    || ((lhs.a == rhs.a && lhs.b == rhs.b && lhs.c < rhs.c));
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
                    {
                    vTlhs.push_back(Bar<true>{i,j,k});
                    vTrhs.push_back(Bar<true>{m,n,p});
                    vFlhs.push_back(Bar<false>{i,j,k});
                    vFrhs.push_back(Bar<false>{m,n,p});
                    }
for(auto& i: vTlhs)
    for(auto& j: vTrhs)
        i<j;

std::cout << "Result T: Foo == comp: " << fooEqComp
    << ", Foo < comp: " << fooLtComp
    << ", Bar < comp: " << barLtComp << std::endl;

fooEqComp = fooLtComp = barLtComp = 0;

for(auto& i: vFlhs)
    for(auto& j: vFrhs)
        i<j;

std::cout << "Result F: Foo == comp: " << fooEqComp
    << ", Foo < comp: " << fooLtComp
    << ", Bar < comp: " << barLtComp << std::endl;
}
