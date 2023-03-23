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
    f = pow(x,3);
    
    return f;
}

int main(void)
{
    double a=-3.0, b=3.0, c;
    int N=4, K=3 , M, i, j, k;
    double p,d,h;
    
    if(N<3) {printf("Try greater N\n"); return 1;}

    if(a>b) {i=a; a=b; b=i;}
    
    M=K*(N-1)+1;
    h=(b-a)/static_cast<double>(M-1);
    
    double arr_x[M];
    double arr_y[M];
    double lp[(N-1)*100+1][N];
    
    double abs_pogresh1=0.0;
    double pogresh1=0.0;
    double abs_pogresh2=0.0;
    double pogresh2=0.0;
    double abs_pogresh3=0.0;
    double pogresh3=0.0;
    
    ofstream file1;
    file1.open("out1.txt");
    
//генерируем массив х и по нему строим массив у, одновременно выгружаем в файл
    
    for (i=0; i<M; i++)
    {
        arr_x[i] = a+i*h;
        arr_y[i]= func(arr_x[i]);
        file1 << arr_x[i] << " " << arr_y[i] << endl;
    }
    file1.close();

    //базисные функции
    double Sum;
    d=h/100.0;
    for(k=0; k<(N-1)*100+1; k++)
    {
        p=a+k*d;
        for ( i = 0; i < N; i++)
        {
            Sum = 1.0;
            for ( j = 0; j < N; j++)
                if (j != i)
                {
                    Sum *= (p - arr_x[j])/ (arr_x[i] - arr_x[j]);
                }
            lp[k][i]=Sum;
        }
    }
    
    //интерполяция
    ofstream file2;
    file2.open("out2.txt");
    
    
    for(i=0; i<K; i++)
    {
        c= a+ i*h*(N-1);
        
        for(j=0; j<(N-1)*100+1; j++)
        {
            p=c+j*d;
            Sum = 0.0;
            for(k=0; k<N; k++)
            {
                Sum += lp[j][k]*arr_y[k+(N-1)*i];
            }
            // теперь в Сум лежит значение интерполяции в точке р
            
            file2 << p << " " << Sum << endl;
            
            
            //Считаем погрешности
            abs_pogresh1+=fabs( func(p) - Sum );
            pogresh1+=fabs(func(p));
            
            abs_pogresh2+= pow( fabs(func(p)-Sum) ,2);
            pogresh2+= pow( fabs(func(p)) ,2);
            
            if( fabs(func(p)-Sum) > abs_pogresh3)
            {
                abs_pogresh3 = fabs(func(p)-Sum);
            }
            
            if( fabs(func(p)) > pogresh3)
            {
                pogresh3 = fabs(func(p));
            }
            
        }
    }
    
    file2.close();
    
    cout << "\n\nПогрешность интерполяции\n" << endl;
    
    cout << "Норма  | Абсолютная погрешность  | Относительная погрешность" << endl;
    cout << "-------|-------------------------|--------------------------" << endl;
    
    cout << "  1    | " <<fixed<<setw(24)<<left << scientific << abs_pogresh1 << "| " << abs_pogresh1/pogresh1 << endl;
    cout << "  2    | " <<fixed<<setw(24)<<left << scientific << pow(abs_pogresh2 , 0.5) << "| " << pow(abs_pogresh2/pogresh2 , 0.5) << endl;
    cout << "  inf  | " <<fixed<<setw(24)<<left << scientific << abs_pogresh3 << "| " << abs_pogresh3/pogresh3 << "\n" << endl;
    
    
    system("python3 project2.py");
    return 0;
     
 
}
