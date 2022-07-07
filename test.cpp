#include <iostream>
class test{
    public:
    int a;
    short b;
    test(int c = 10):a{0},b{3}{
        std::cout<<"tested"<<std::endl;
    }
};
int main(){
    test t(3);
    std::cout <<t.a;
    return 0;
}