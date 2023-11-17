#include <iostream>
#include <string>

template <typename T>
concept ComplexConcept = requires(const T v)
{
    {v.hash()} -> std::convertible_to<long>;
    {v.toString()} -> std::same_as<std::string>;
} && !std::has_virtual_destructor<T>::value;

template <ComplexConcept T>
void concept_method(T val)
{
    std::cout << "Hash: " << val.hash() << std::endl;
    std::cout << "String: " << val.toString() << std::endl;
}

class Test
{
    int _v;
public:
    Test(const int v) :_v(v)
    {}

    long hash() const
    {
        return _v;
    }
    std::string toString() const
    {
        return std::to_string(_v);
    }
};

int main() {
    Test t(1);
    concept_method<Test>(t);
    return 0;
}
