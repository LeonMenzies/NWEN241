#include<iostream>
class A{
    int b;
public:
    A(int x, int y = 10):a(x),b(y){}

    int a;
};
int main(){
    A a1(5);

    std::cout<<a1.a;

    int fun(int x, int y = 0, int z=0);


    //int fun(int x = 0, int y = 0, int z);


    int fun(int x, int y = 0, int z=0);



}