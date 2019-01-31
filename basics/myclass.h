#include <string>

class MyClass {
public:
    const int& foo() const;

private:
    static int fooPrivate(const std::string & ac);
};
