#include <iostream>

using namespace std;
namespace Complex
{
    class complex
    {

    private:
        int a, b;

    public:
        complex()
        {
            a = 1;
            b = 1;
        }
        complex(int a1, int b1)
        {
            a = a1;
            b = b1;
        };

        int geta()
        {
            return a;
        }
        int getb()
        {
            return b;
        }
    };
};

using namespace Complex;

int main(void)
{
    complex c1 = complex();
    complex c2 = complex(5, 10);

    cout << "Complex number 1: " << c1.geta() << " + " << c1.getb() << "i\n";
    cout << "Complex number 2: " << c2.geta() << " + " << c2.getb() << "i\n";

    return 0;
}
