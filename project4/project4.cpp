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

double* diff_func(double* d,double x, int K, double b, double a)
{
    d = new double [K+1];
    for(int i=0; i<K+1; i++)
    {
        d[i]=pow(x,4)*5.0;
    }
    return d;
}

double* Raznosti(double* d, double h, int K, double a, double c)
{
    h=h*c;
    d = new double[K+1];
    d[0]=(func(a+h)-func(a))/h;
    for(int i=1; i<K; i++)
    {
        d[i]=(func(a+h*(i/c+1))-func(a+h*(i/c-1)))/2/h;
    }
    d[K]=(func(a+K*h/c)-func(a+(K/c-1)*h))/h;
    return d;
}

double* Runge1(double* R, int K, int p, double* diff_1, double* diff_2)
{
    R = new double[K+1];
    
    //Первый Рунге
    double rp=pow(0.5, p)-1;
    for(int i=0; i<K+1; i++)
    {
        R[i]=(diff_1[i]-diff_2[i])/rp;
    }
    return R;
}
    
double* Runge2(double* R, int K, int p, double* diff_1, double* diff_r1)
{
    R = new double[K+1];
    //Второй Рунге
    for(int i=0; i<K+1; i++)
    {
        R[i]=diff_1[i]+diff_r1[i];
    }
    
    return R;
}

int main(void)
{
    double a = 1.0, b = 10.0, h, c=0.5;
    double abs_pogresh1=0.0, abs_pogresh2=0.0, abs_pogresh3=0.0, pogresh1=0.0, pogresh2=0.0, pogresh3=0.0;
    double pogresh_r1=0.0, pogresh_r2=0.0, pogresh_r3=0.0;
    int K=9, p=2,i;
    
    h=(b-a)/static_cast<double>(K);
    
    double* g = NULL;
    double* diff_1 = NULL;
    double* diff_2 = NULL;
    double* diff_r1 = NULL;
    double* diff_r2 = NULL;
    
    diff_1 = Raznosti(diff_1, h, K, a, 1.0);
    diff_2 = Raznosti(diff_2, h, K, a, c);
    diff_r1 = Runge1(diff_r1, K, p, diff_1, diff_2);
    diff_r2 = Runge2(diff_r2, K, p, diff_1, diff_r1);
    
    //ошибки на сетке с шагом h
    abs_pogresh1=0.0;
    abs_pogresh2=0.0;
    abs_pogresh3=0.0;
    pogresh1=0.0;
    pogresh2=0.0;
    pogresh3=0.0;
    pogresh_r1=0.0;
    pogresh_r2=0.0;
    pogresh_r3=0.0;
    
    
    ofstream file1;
    file1.open("out1.txt");
    
    for(i=0; i<K+1; i++)
    {
        g = diff_func(g, a+i*h, K, b, a);
        file1 << a+i*h << " " << diff_1[i] << endl;
        
        abs_pogresh1+=fabs( g[i] - diff_1[i]);
        pogresh1+=fabs(g[i]);
        
        abs_pogresh2+= pow( fabs(g[i] - diff_1[i]) , 2);
        pogresh2+= pow(  fabs(g[i]) , 2 );
        
        if( fabs(g[i] - diff_1[i]) > abs_pogresh3)
        {
            abs_pogresh3 = fabs(g[i] - diff_1[i]);
        }
        
        if( fabs(g[i]) > pogresh3)
        {
            pogresh3 = fabs(g[i]);
        }
        
        //
        
        pogresh_r1+=fabs(diff_r1[i]);
        
        pogresh_r2+= pow(fabs(diff_r1[i]) , 2 );
        
        if( fabs(diff_r1[i]) > pogresh_r3)
        {
            pogresh_r3 = fabs(diff_r1[i]);
        }
        
    }
    file1.close();
    
    
    cout << "\n\nПогрешность численного дифференцирования на сетке h\n" << endl;
    
    cout << "-------|-------------------------|---------------------------|---------------------------" << endl;
    cout << "Норма  | Абсолютная погрешность  | Относительная погрешность |  Главный член погрешности " << endl;
    cout << "-------|-------------------------|---------------------------|---------------------------" << endl;
    
    cout << "  1    | " <<fixed<<setw(24)<<left << scientific << abs_pogresh1 << "| " <<fixed<<setw(24)<<left << scientific << abs_pogresh1/pogresh1 << "  | " << pogresh_r1 << endl;
    cout << "  2    | " <<fixed<<setw(24)<<left << scientific << pow(abs_pogresh2 , 0.5) << "| "<<fixed<<setw(24)<<left << scientific << pow(abs_pogresh2/pogresh2 , 0.5) << "  | " << pow(pogresh_r1, 0.5) << endl;
    cout << "  inf  | " <<fixed<<setw(24)<<left << scientific << abs_pogresh3 << "| " <<fixed<<setw(24)<<left << scientific << abs_pogresh3/pogresh3 << "  | " << pogresh_r3 << endl;
    
    
    //ошибки на сетке с шагом h/2
    abs_pogresh1=0.0;
    abs_pogresh2=0.0;
    abs_pogresh3=0.0;
    pogresh1=0.0;
    pogresh2=0.0;
    pogresh3=0.0;
    
    
    for(i=0; i<2*(K+1); i++)
    {
        g = diff_func(g, a+i*h*0.5, 2*K, b, a);
        
        
        abs_pogresh1+=fabs( g[i] - diff_2[i]);
        pogresh1+=fabs(g[i]);
        
        abs_pogresh2+= pow( fabs(g[i] - diff_2[i]) , 2);
        pogresh2+= pow(  fabs(g[i]) , 2 );
        
        if( fabs(g[i] - diff_2[i]) > abs_pogresh3)
        {
            abs_pogresh3 = fabs(g[i] - diff_2[i]);
        }
        
        if( fabs(g[i]) > pogresh3)
        {
            pogresh3 = fabs(g[i]);
        }
        
    }
    
    
    cout << "\n\nПогрешность численного дифференцирования на сетке h/2\n" << endl;
    
    cout << "-------|-------------------------|---------------------------|---------------------------" << endl;
    cout << "Норма  | Абсолютная погрешность  | Относительная погрешность |  Главный член погрешности " << endl;
    cout << "-------|-------------------------|---------------------------|---------------------------" << endl;
    
    cout << "  1    | " <<fixed<<setw(24)<<left << scientific << abs_pogresh1 << "| " <<fixed<<setw(24)<<left << scientific << abs_pogresh1/pogresh1 << "  | " << pogresh_r1 << endl;
    cout << "  2    | " <<fixed<<setw(24)<<left << scientific << pow(abs_pogresh2 , 0.5) << "| "<<fixed<<setw(24)<<left << scientific << pow(abs_pogresh2/pogresh2 , 0.5) << "  | " << pow(pogresh_r1, 0.5) << endl;
    cout << "  inf  | " <<fixed<<setw(24)<<left << scientific << abs_pogresh3 << "| " <<fixed<<setw(24)<<left << scientific << abs_pogresh3/pogresh3 << "  | " << pogresh_r3 << endl;
    
    //ошибки Рунге
    abs_pogresh1=0.0;
    abs_pogresh2=0.0;
    abs_pogresh3=0.0;
    pogresh1=0.0;
    pogresh2=0.0;
    pogresh3=0.0;
    
    ofstream file2;
    file2.open("out2.txt");
    
    for(i=0; i<K+1; i++)
    {
        g = diff_func(g, a+i*h, K, b, a);
        file2 << a+i*h << " " << diff_r2[i] << endl;
        
        abs_pogresh1+=fabs( g[i] - diff_r2[i]);
        pogresh1+=fabs(g[i]);
        
        abs_pogresh2+= pow( fabs(g[i] - diff_r2[i]) , 2);
        pogresh2+= pow(  fabs(g[i]) , 2 );
        
        if( fabs(g[i] - diff_r2[i]) > abs_pogresh3)
        {
            abs_pogresh3 = fabs(g[i] - diff_r2[i]);
        }
        
        if( fabs(g[i]) > pogresh3)
        {
            pogresh3 = fabs(g[i]);
        }
        
    }
    
    file2.close();
    
    cout << "\n\nПогрешность численного дифференцирования уточненного по Рунге\n" << endl;
    
    cout << "-------|-------------------------|---------------------------|---------------------------" << endl;
    cout << "Норма  | Абсолютная погрешность  | Относительная погрешность |  Главный член погрешности " << endl;
    cout << "-------|-------------------------|---------------------------|---------------------------" << endl;
    
    cout << "  1    | " <<fixed<<setw(24)<<left << scientific << abs_pogresh1 << "| " <<fixed<<setw(24)<<left << scientific << abs_pogresh1/pogresh1 << "  | " << pogresh_r1 << endl;
    cout << "  2    | " <<fixed<<setw(24)<<left << scientific << pow(abs_pogresh2 , 0.5) << "| "<<fixed<<setw(24)<<left << scientific << pow(abs_pogresh2/pogresh2 , 0.5) << "  | " << pow(pogresh_r1, 0.5) << endl;
    cout << "  inf  | " <<fixed<<setw(24)<<left << scientific << abs_pogresh3 << "| " <<fixed<<setw(24)<<left << scientific << abs_pogresh3/pogresh3 << "  | " << pogresh_r3 << endl;
    
    
    system("python3 project4.py");
    
}
