#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>


using namespace std;

double lagrange(double* x, double* y, int N, double p)
{
    double L = 0.0;
    for (int i = 0; i < N; i++)
    {
        double Sum = 1.0;
        for (int j = 0; j < N; j++)
            if (j != i)
            {
                Sum *= (p - x[j])/ (x[i] - x[j]);
            }
        L += Sum * y[i];
    }

    return L;
}

int main(void)
{
    int a=-3, b=3, N=30, i, K, j, k, l;
    double p;
    double m=250.0, pp;
    int M=250;

    //double points[M];
    //double lagr[M];

    if(a>b) {i=a; a=b; b=i;}
    
    double arr_x[N];
    double arr_y[N];
    
//генерируем массив х и по нему строим массив у
    
    ofstream file1;
    file1.open("out1.txt");
    
    
    srand(time(NULL));
    p=(b-a)/static_cast<double>(RAND_MAX);
    for (i=0; i<N; i++)
    {
        for(k=0; k<5; k++)
        {
            l=0;
            pp= static_cast<double>(rand())*p+a;
            for(j=0; j<i; j++)
            {
                if((abs(arr_x[j])+abs(pp))/(200000.0)>abs(arr_x[j]-pp))
                {
                    break;
                }
                l++;
            }
            if(l==i){break;}
        }
        if(l!=i){printf("Probably sth wrong with the segment. Try again\n"); return 1;}
        arr_x[i]=pp;
        arr_y[i]= sin(arr_x[i]);
        
        file1 << arr_x[i] << " " << arr_y[i] << endl;
    }

    file1.close();
    
    ofstream file2;
    file2.open("out2.txt");
    
    double c;
    for (i=0; i<M; i++)
    {
        //points[i]=a+(b-a)*i/m;
        //lagr[i]=lagrange(arr_x, arr_y, N, points[i]);
        
        c= a+(b-a)*i/m;
    
        file2 << c << " " << lagrange(arr_x, arr_y, N, c) << endl;
    }
    
    file2.close();
    
    system("python3 project1.py");
     
    return 0;
 
}
