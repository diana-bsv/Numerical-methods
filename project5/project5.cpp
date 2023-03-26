#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

double func(double x)
{
    double f;
    f = pow(x,5);
    
    return f;
}

double integrate_func(double a, double b)
{
    double J;
    J= (pow(b,6)-pow(a,6))/6.0;
    return J;
}

double Rectang(double a, double b, int K, double h)
{
    double J=0.0;
    for(int i=0; i<K; i++)
    {
        J+=func(a+(i+0.5)*h);
    }
    J=J*h;
    
    return J;
}

double Trapeeze(double a, double b, int K, double h)
{
    double J=func(a)+func(b);
    for(int i=1; i<K; i++)
    {
        J=J+2*func(a+i*h);
    }
    J=J*h/2.0;
    
    return J;
}

double Simpson(double a, double b, int K, double h)
{
    double J=0.0;
    J=func(a)+func(b);
    for(int i=1; i<K; i++)
    {
        J=J+2.0*(1+i%2)*func(a+i*h);
    }
    J=J*h/3.0;
    
    return J;
}

double Newton(double a, double b, int K, double h)
{
    double J=0.0;
    double h_s=h/4.0;
    for (int i = 0;i < K; i++)
    {
        J= J+  7.0*func(a+h*i) + 32.0*func(a+h_s+h*i) + 12.0*func(a+2.0*h_s+h*i) + 32.0*func(a+3*h_s+h*i) + 7.0*func(a+h*(i+1));
    }
    J=J*h/90.0;
    
    return J;
}

double Gauss(double a, double b, int K, double h)
{
    double J=0.0;
    double kk=0.774596669241483/2.0;
    
    for (int i = 0;i < K; i++)
    {
        J= J+  5.0*func(a+h*(i+0.5-kk)) + 8.0*func(a+h*(i+0.5)) + 5.0*func(a+h*(i+0.5+kk));
    }
    J=J*h/18.0;
    
    return J;
}

int main(void)
{
    double a = 1.0, b = 10.0, h;
    int K=100;
    
    h=(b-a)/static_cast<double>(K);
    
    double J, J_1, J_2;
    J= integrate_func(a,b);
    
    cout << "\n\nТаблица результатов численного интегрирования\n" <<  endl;
    cout << "                   | Количество интервалов: " << K <<" | Количество интервалов: " << 2*K <<" " <<  endl;
    cout << "Квадратурная схема | относительная погрешность  |  относительная погрешность" <<  endl;
    cout << "-------------------|----------------------------|---------------------------" <<  endl;
    J_1= fabs((Rectang(a,b,K,h)-J)/J);
    J_2= fabs((Rectang(a,b,K*2,h*0.5)-J)/J);
    cout <<" Прямоугольников   | " <<  J_1<< "                  | " << J_2 <<  endl;
    J_1= fabs((Trapeeze(a,b,K,h)-J)/J);
    J_2= fabs((Trapeeze(a,b,K*2,h*0.5)-J)/J);
    cout <<" Трапеций          | " <<  J_1<< "                | " << J_2 <<  endl;
    J_1= fabs((Simpson(a,b,K,h)-J)/J);
    J_2= fabs((Simpson(a,b,K*2,h*0.5)-J)/J);
    cout <<" Симпсона          | " <<  J_1<< "                | " << J_2 <<  endl;
    J_1= fabs((Newton(a,b,K,h)-J)/J);
    J_2= fabs((Newton(a,b,K*2,h*0.5)-J)/J);
    cout <<" Ньютона-Котеса    | " <<  J_1<< "                 | " << J_2 <<  endl;
    J_1= fabs((Gauss(a,b,K,h)-J)/J);
    J_2= fabs((Gauss(a,b,K*2,h*0.5)-J)/J);
    cout <<" Гаусса            | " <<  J_1<< "                | " << J_2 << "\n" << endl;
     
    
    return 0;
}
