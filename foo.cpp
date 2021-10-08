// extern "C" void foo()
// {
// }

//[[gnu::used]]
//void bar()
//{
//}
//
//__declspec(dllexport)
//void foo()
//{
//}

#include "foo.hpp"

struct Foo
{
  Foo(int) {}
  Foo(char) {}
  Foo(float) {}
};

void bar()
{
}

int main(int argc, char const * argv[])
{
  //Foo{42};
  //Bar{42};
}

// m declRefExpr(isExpansionInMainFile()).bind("declRef")
// clang-query 'Source\3D\K3dDoc04\D3vedit.cpp'

// xunused 3D\K3dDoc04\D3vedit.cpp


// set bind-root true
// set output detailed-ast
// m functionDecl( hasAttr("attr::Used") )
// m functionDecl( unless(hasAttr("attr::Used")) )
// m functionDecl( unless(hasAttr("attr::DLLExport")) )
// m functionDecl( unless(hasAttr("attr::DLLImport")) )