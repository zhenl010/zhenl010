// http://publib.boulder.ibm.com/infocenter/lnxpcomp/v8v101/index.jsp?topic=%2Fcom.ibm.xlcpp8l.doc%2Flanguage%2Fref%2Ffriends_and_templates.htm
// Friends and templates (C++ only)
//     There are four kinds of relationships between classes and their friends when templates are involved:
// 
// One-to-many: A non-template function may be a friend to all template class instantiations.
//     Many-to-one: All instantiations of a template function may be friends to a regular non-template class.
//     One-to-one: A template function instantiated with one set of template arguments may be a friend to one template class instantiated with the same set of template arguments. This is also the relationship between a regular non-template class and a regular non-template friend function.
//     Many-to-many: All instantiations of a template function may be a friend to all instantiations of the template class.
//     The following example demonstrates these relationships:
// 
// class B{
//     template<class V> friend int j();
// }
// 
// template<class S> g();
// 
// template<class T> class A {
//     friend int e();
//     friend int f(T);
//     friend int g<T>();
//     template<class U> friend int h();
// };
// Function e() has a one-to-many relationship with class A. Function e() is a friend to all instantiations of class A.
//     Function f() has a one-to-one relationship with class A. The compiler will give you a warning for this kind of declaration similar to the following:
//     The friend function declaration "f" will cause an error when the enclosing
//     template class is instantiated with arguments that declare a friend function
//     that does not match an existing definition. The function declares only one
//     function because it is not a template but the function type depends on
//     one or more template parameters.
//     Function g() has a one-to-one relationship with class A. Function g() is a function template. It must be declared before here or else the compiler will not recognize g<T> as a template name. For each instantiation of A there is one matching instantiation of g(). For example, g<int> is a friend of A<int>.
//     Function h() has a many-to-many relationship with class A. Function h() is a function template. For all instantiations of A all instantiations of h() are friends.
//     Function j() has a many-to-one relationship with class B.
//     These relationships also apply to friend classes.
// 
//     Related information
// 
//     Friends (C++ only)
#include <iostream>\

template<typename T>
void Func(T x) {
    std::cout << "A\n";
}

template <typename T>
class A
{
public:
    // operator int(){return 1;}

    friend void Func<A<T>>(A<T> x);
    // {
    //     std::cout << "A\n";
    // }

private:
    int x;
};