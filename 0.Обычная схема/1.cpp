#include <iostream> 
#include <fstream> 
#include <cmath> 
#include <stdlib.h> 

using namespace std; 

int main () 
{ 

ofstream fout("file.txt"); 

int const N = 101;
int const M = 200;
double L1;
double L2;
double Max;


int i,j,k;

double **A = new double* [N+1];
for (i = 0; i < N+1; i++)
	A[i] = new double [N+1];


double **B = new double* [N+1];
for (i = 0; i < N+1; i++)
	B[i] = new double [N+1];


L1=0.5;
L2=-0.5;

//Задание начальных данных массива
for (i=0; i<N+1; i++)
{
	for (j=0; j<N+1; j++)
	{
		B[i][j] = 0;
		A[i][j] = exp(-(pow(i-N/2,2) + pow(j-N/2,2))/300);
		fout << i << " "<< j << " " << A[i][j] << endl;
	}
	fout << endl;
}

fout << endl << endl<< endl;

//Цикл по времени
for (k=1; k<=M; k++)
{

//Закольцоввывание	
	for (j=1; j<N; j++)
	{
		A[N][j]=A[1][j];
		A[0][j]=A[N-1][j]; 
	}
	for (i=1; i<N; i++)
	{
		A[i][N]=A[i][1];
		A[i][0]=A[i][N-1]; 
	}

	A[0][0]=A[N-1][N-1];
	A[0][N]=A[N-1][1];
	A[N][0]=A[1][N-1];
	A[N][N]=A[1][1];
 
//Нахождение следующего значения по времени
	for (j=0; j<N+1; j++)
	{
		for (i=1; i<N; i++)
		{
  		B[i][j]= A[i][j] - L1 * (A[i+1][j]-A[i-1][j])+ abs(L1) * (A[i+1][j]-2 * A[i][j]+A[i-1][j]); 
		}
	}
	
	for (i=1; i<N; i++)
	{
		for (j=1; j<N; j++)
		{
  		A[i][j]= B[i][j] - L2 * (B[i][j+1]-B[i][j-1])+ abs(L2) * (B[i][j+1]-2 * B[i][j]+B[i][j-1]); 
		}
	}

	if ((k%1) == 0 ) 
	{  
		fout << endl << endl<< endl;
	}

//Вывод результата
	for (i=0; i<N+1; i++)
	{
  	for (j=0; j<N+1; j++)
		{
  
		if ((k%1) == 0 ) 
  		{
    			fout << i << " " << j << " "<< A[i][j] << endl; 
		}
		}
	fout << endl;
	}

if ((k%50) == 0)
{    
	cout << k << " / " << M << endl;    
}

}

fout.close();
return 0; 
}
