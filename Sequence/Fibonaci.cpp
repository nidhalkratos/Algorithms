/*
This code is made by Nidhal Abidi, it demonstrates the implementation of Fibonaci algorithm with the
different methods and gives you an experimental overview about the runtime of the algorithms using those methods.
*/

#include <iostream>

using namespace std;

int fibonaci_recursive(int n)
{
    if(n == 1 || n == 2)
        return 1;
    else
        return fibonaci_recursive(n-1) + fibonaci_recursive(n-2);
}

int fibonaci_iterative(int n)
{
    int fib[n+1];
    fib[1] = 1;
    fib[2] = 1;
    for(int i =3;i<=n;i++)
        fib[i] = fib[i-1] + fib[i-2];
    return fib[n];

}

int main()
{
    int n;
    cin>>n;
    cout<<"Fibonaci with iteration: "<<fibonaci_iterative(n)<<endl;
    //Believe me, you don't want to use the recursive version because it is not efficient at all
    //and that is because allot of calculations are recalculated again and again. you can test
    // the running time for n = 45 for example is noticeable and you can test that for your self
    cout<<"Fibonaci with recursion: "<<fibonaci_recursive(n)<<endl;
    return 0;
}
