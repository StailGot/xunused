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

//#include "foo.hpp"

struct Foo
{
  Foo(int, int, int) {}
  //Foo(char) {}
  //Foo(float) {}
};

struct Bar : Foo
{

};
//void bar()
//{
//}

int main(int argc, char const * argv[])
{
  //Foo * f = new Foo{42, 0, 1};
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