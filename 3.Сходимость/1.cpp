#include <iostream> 
#include <fstream> 
#include <cmath> 
#include <stdlib.h> 

using namespace std; 

int main () 
{ 
//Задание данных
	ofstream fout("file.txt"); 

	int const N = 100;		//Размер пространства
	int const R = 1;  		//Количество циклов
	int const M = R*(N-3);	//Количество шагов по времени
	
	double L;	
	double L1;				//Число Куранта по x
	double L2;				//Число Куранта по y
	
	int w = M/500;			//Частота вывода

	double Sum;				//Отклонение

	double Fp,Fm;			//Коэфф-ты F+ и F- в формуле для схемы

	int i,j,k;				//Икдексы по x,y,t

//Задание основного массива
	double **A = new double* [N+1];
	for (i = 0; i < N+1; i++)
		A[i] = new double [N+1];

//Задание вспомогательного массива
	double **B = new double* [N+1];
	for (i = 0; i < N+1; i++)
		B[i] = new double [N+1];

//Задание начального массива
	double **C = new double* [N+1];
	for (i = 0; i < N+1; i++)
		C[i] = new double [N+1];


cout << "Start of data genegation." << endl;

for (L=0.3; L<=1.00001; L=L+0.01)
{

L1=L;
L2=L;
Sum = 0;

//Задание начальных данных массива
	for (i=0; i<N+1; i++)
	{
		for (j=0; j<N+1; j++)
		{
			B[i][j] = 0;
			A[i][j] = 0;
			if ((i-N/2)*(i-N/2)+(j-N/2)*(j-N/2)<N*N/16)
			{
//				A[i][j] = 1;
//				C[i][j] = 1;
			}
			A[i][j] = exp(-(pow(i-N/2,2) + pow(j-N/2,2))/300);
			C[i][j] = exp(-(pow(i-N/2,2) + pow(j-N/2,2))/300);

		}

	}


//Цикл по времени
	for (k=1; k<=M; k++)
	{

//Закольцоввывание	
		for (j=0; j<N+1; j++)
		{
			A[N][j]   = A[3][j];
			A[N-1][j] = A[2][j];
			A[0][j]   = A[N-3][j];
			A[1][j]   = A[N-2][j]; 
		
		}
	
		for (j=0; j<N+1; j++)
		{
			A[j][N]   = A[j][3];
			A[j][N-1] = A[j][2];
			A[j][0]   = A[j][N-3];
			A[j][1]   = A[j][N-2]; 
		}

 
//Нахождение следующего значения по времени
		for (j=0; j<N+1; j++)
		{
			for (i=2; i<N; i++)
			{
				if (L1 > 0)
				{
					if (abs(A[i+1][j] - A[i][j]) > (A[i][j] - A[i-1][j]))
					{
						Fp = A[i][j] - A[i-1][j];
					}
					else
					{
						Fp = A[i+1][j] - A[i][j];
					}
			
					if (abs(A[i][j] - A[i-1][j]) > (A[i-1][j] - A[i-2][j]))
					{
						Fm = A[i-1][j] - A[i-2][j];
					}
					else
					{
						Fm = A[i][j] - A[i-1][j];
					}
			
					B[i][j]= A[i][j] - L1 * (A[i][j]-A[i-1][j])+ 0.5 * L1 * (1 - L1) * (Fp - Fm); 
				}
				else
				{
					if (abs(A[i+1][j] - A[i][j]) > (A[i][j] - A[i-1][j]))
					{
						Fp = A[i][j] - A[i-1][j];
					}
					else
					{
						Fp = A[i+1][j] - A[i][j];
					}
			
					if (abs(A[i][j] - A[i-1][j]) > (A[i-1][j] - A[i-2][j]))
					{
						Fm = A[i-1][j] - A[i-2][j];
					}
					else
					{
						Fm = A[i][j] - A[i-1][j];
					}
			
					B[i][j]= A[i][j] - L1 * (A[i+1][j]-A[i][j]) - 0.5 * L1 * (L1+1) * (Fp - Fm); 
				}
			}
		}
	
		for (i=2; i<N; i++)
		{
			for (j=2; j<N; j++)
			{
				if (L2 > 0)
				{
					if (abs(B[i][j+1] - B[i][j]) > (B[i][j] - B[i][j-1]))
					{
						Fp = B[i][j] - B[i][j-1];
					}
					else
					{
						Fp = B[i][j+1] - B[i][j];
					}
			
					if (abs(B[i][j] - B[i][j-1]) > (B[i][j-1] - B[i][j-2]))
					{
						Fm = B[i][j-1] - B[i][j-2];
					}
					else
					{
						Fm = B[i][j] - B[i][j-1];
					}
			
					A[i][j]= B[i][j] - L2 * (B[i][j]-B[i][j-1])+ 0.5 * L2 * (1 - L2) * (Fp - Fm); 
				}
				else
				{
					if (abs(B[i][j+1] - B[i][j]) > (B[i][j] - B[i][j-1]))
					{
						Fp = B[i][j] - B[i][j-1];
					}
					else
					{
						Fp = B[i][j+1] - B[i][j];
					}
			
					if (abs(B[i][j] - B[i][j-1]) > (B[i][j-1] - B[i][j-2]))
					{
						Fm = B[i][j-1] - B[i][j-2];
					}
					else
					{
						Fm = B[i][j] - B[i][j-1];
					}
			
					A[i][j]= B[i][j] - L2 * (B[i][j+1] - B[i][j]) - 0.5 * L2 * (L2+1) * (Fp - Fm); 
				}
  		
			}
		}


		//Подсчёт разности и вывод результата
		if (k == M)
		{
			for (i=2; i<N-1; i++)
			{
				for (j=2; j<N-1; j++)
				{
					Sum = Sum + abs((A[i][j] - C[i][j])*(A[i][j] - C[i][j])); 
				}
			}
			Sum = sqrt(Sum)/(N-4);
			fout << L << " " <<  Sum << " " << log(1-L)<< " " << log(Sum) <<  endl; 
		}

				
  

	}

//Вывод стадии обработки в терминал
cout << L << endl;  

}	
	cout << "End of data genegation. Start of making animation." << endl;
	fout.close();
	return 0; 
}
