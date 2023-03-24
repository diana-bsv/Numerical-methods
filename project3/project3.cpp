#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <eigen3/Eigen/Dense>
#include <iomanip>

using namespace std;
using namespace Eigen;

double func(double x)
{
    double f;
    f = sin(x);
    
    return f;
}

int main(void)
{
    double a = -10.0, b = 10.0, h, len, p, d;
    double g;
    int K=4;    //число интервалов(конечных эл-тов)
    int N=4;    //число узлов на конечном элементе
    int kk, i,j,k,q;
    int M_viz=100*(N-1)*K+1;    //визуализация
    int L=30;   //кол-во случайных точек на отрезке
    
    double abs_pogresh1=0.0, abs_pogresh2=0.0, abs_pogresh3=0.0, pogresh1=0.0, pogresh2=0.0, pogresh3=0.0;
    
    int M=K*(N-1)+1;    //общее кол-во узлов
    h=(b-a)/static_cast<double>(M-1);
    d=(b-a)/static_cast<double>(M_viz-1);
    len=(b-a)/static_cast<double>(K); //Длина интервала
    
    
    
    double rand_x[L*K];
    double rand_y[L*K];
    
    //Генерируем Л случайных точек на каждом элементе
   
    
    int l,u;
    double pp;
    srand(time(NULL));
    for( q=0; q<K; q++)
    {
        p=len/static_cast<double>(RAND_MAX);
        for (i=0; i<L; i++)
        {
            u=L*q+i;
            for(k=0; k<5; k++)
            {
                l=0;
                pp= static_cast<double>(rand())*p+(a+q*len);
                for(j=L*q; j<u; j++)
                {
                    if((fabs(rand_x[j])+fabs(pp))/(200000.0) > fabs(rand_x[j]-pp))
                    {
                        break;
                    }
                    l++;
                }
                if(l==i){break;}
            }
            if(l!=i){printf("Probably sth wrong with the segment. Try again\n"); return 1;}
            rand_x[u]=pp;
            rand_y[u]= func(rand_x[u]);
        }
        
    }
    
    
    
    //Матрицы
    double koeff[M];
    double lp[L][N];
    
    Eigen::MatrixXf A(M,M);
    Eigen::VectorXf bbb(M);
    Eigen::VectorXf c;
    A.setZero();
    bbb.setZero();
    
    double Sum;
    ofstream file1;
    file1.open("out1.txt");
    
    
    for(i=0; i<K; i++)
    {
        kk = (N-1)*i;
        
        //функции
        for(k=0; k<L; k++)
        {
            for ( q = 0; q < N; q++)
            {
                Sum = 1.0;
                for ( j = 0; j < N; j++)
                    if (j != q)
                    {
                        Sum *= (rand_x[L*i+k] - (a+(i*(N-1)+j)*h))/((q-j)*h);
                    }
                lp[k][q]=Sum;
            }
        }
        
        
        
        for(j=0; j<N; j++)
        {
            for(k=0; k<N; k++)
            {
                for(q=0; q<L; q++)
                {
                    A(kk+k,kk+j)= A(kk+k,kk+j) + lp[q][j]*lp[q][k];
                }
            }
            for(q=0; q<L; q++)
            {
                bbb(kk+j)=bbb(kk+j)+rand_y[L*i+q]*lp[q][j];
            }
            
            file1 << a+(i*(N-1)+j)*h << " " << func(a+(i*(N-1)+j)*h) << endl;
        }
    }
    c = A.colPivHouseholderQr().solve(bbb);
    
    file1.close();
    
    // считаем многочлен для случайных точек
    
    double  Random[K*L];
    for(i=0; i<K; i++)
    {
        
        kk = (N-1)*i;
        
        //функции
        for(k=0; k<L; k++)
        {
            for ( q = 0; q < N; q++)
            {
                Sum = 1.0;
                for ( j = 0; j < N; j++)
                    if (j != q)
                    {
                        Sum *= (rand_x[L*i+k] - (a+(i*(N-1)+j)*h))/((q-j)*h);
                    }
                lp[k][q]=Sum;
            }
        }
        
        
        
        for(j=0; j<L; j++)
        {
            Sum=0.0;
            for(k=0; k<N; k++)
            {
                Sum+= lp[j][k]*c(i *(N-1) + k);
            }
            Random[i*L+j]=Sum;
            
            g=func(rand_x[i*L+j]);
            abs_pogresh1+=fabs( g -Sum);
            pogresh1+=fabs(g);
            
            abs_pogresh2+= pow( fabs(g-Sum) , 2);
            pogresh2+= pow(  fabs(g) , 2 );
            
            if( fabs(g-Sum) > abs_pogresh3)
            {
                abs_pogresh3 = fabs(g-Sum);
            }
            
            if( fabs(g) > pogresh3)
            {
                pogresh3 = fabs(g);
            }
                           
                           
        }
    }
    

    
    cout << "\n\nПогрешность наилучшего приближения\n" << endl;
    
    cout << "   В случайных точках" << endl;
    cout << "-------|-------------------------|--------------------------" << endl;
    cout << "Норма  | Абсолютная погрешность  | Относительная погрешность" << endl;
    cout << "-------|-------------------------|--------------------------" << endl;
    
    cout << "  1    | " <<fixed<<setw(24)<<left << scientific << abs_pogresh1 << "| " << abs_pogresh1/pogresh1 << endl;
    cout << "  2    | " <<fixed<<setw(24)<<left << scientific << pow(abs_pogresh2 , 0.5) << "| " << pow(abs_pogresh2/pogresh2 , 0.5) << endl;
    cout << "  inf  | " <<fixed<<setw(24)<<left << scientific << abs_pogresh3 << "| " << abs_pogresh3/pogresh3 << "\n" << endl;
    
    
    abs_pogresh1=0.0;
    abs_pogresh2=0.0;
    abs_pogresh3=0.0;
    pogresh1=0.0;
    pogresh2=0.0;
    pogresh3=0.0;
    
    
    // считаем многочлен для сетки
    ofstream file2;
    file2.open("out2.txt");
    
    double lp1[100*(N-1)][N];
    double  neRandom[M_viz];
    for(i=0; i<K; i++)
    {
        
        //функции
        for(k=0; k<(N-1)*100; k++)
        {
            for ( q = 0; q < N; q++)
            {
                Sum = 1.0;
                for ( j = 0; j < N; j++)
                    if (j != q)
                    {
                        Sum *= (len*i+d*k - (i*(N-1)+j)*h)/((q-j)*h);
                        //cout << a+len*i+d*k << " " << a+(i*(N-1)+j)*h << "  " << (q-j)*h << endl;
                    }
                lp1[k][q]=Sum;
                //cout << Sum << "<-------"<< endl;
            }
        }
        
        for(j=0; j<(N-1)*100; j++)
        {
            Sum=0.0;
            for(k=0; k<N; k++)
            {
                Sum+= lp1[j][k]*c(i*(N-1) + k);
                //cout << Sum << "<-------"<< endl;
            }
            neRandom[i*(N-1)*100+j]=Sum;
            //cout << Sum << "<++++++-"<< endl;
            
            file2 << a+(i*(N-1)*100+j)*d << " " << Sum << endl;
            
            g=func(a+(i*(N-1)*100+j)*d);
            
            abs_pogresh1+=fabs( g -Sum);
            pogresh1+=fabs(g);
            
            abs_pogresh2+= pow( fabs(g-Sum) , 2);
            pogresh2+= pow(  fabs(g) , 2 );
            
            if( fabs(g-Sum) > abs_pogresh3)
            {
                abs_pogresh3 = fabs(g-Sum);
            }
            
            if( fabs(g) > pogresh3)
            {
                pogresh3 = fabs(g);
            }
        }
    }
    
    
    file2.close();
 
    
    
    
    
    
    cout << "   В равномерной сетке" << endl;
    cout << "-------|-------------------------|--------------------------" << endl;
    cout << "Норма  | Абсолютная погрешность  | Относительная погрешность" << endl;
    cout << "-------|-------------------------|--------------------------" << endl;
    
    cout << "  1    | " <<fixed<<setw(24)<<left << scientific << abs_pogresh1 << "| " << abs_pogresh1/pogresh1 << endl;
    cout << "  2    | " <<fixed<<setw(24)<<left << scientific << pow(abs_pogresh2 , 0.5) << "| " << pow(abs_pogresh2/pogresh2 , 0.5) << endl;
    cout << "  inf  | " <<fixed<<setw(24)<<left << scientific << abs_pogresh3 << "| " << abs_pogresh3/pogresh3 << "\n" << endl;
    
    system("python3 project3.py");
    return 0;
}
