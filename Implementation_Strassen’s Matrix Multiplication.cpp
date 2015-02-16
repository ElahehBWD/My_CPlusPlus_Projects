#include<iostream>
#include <fstream>
#include<cmath>

using namespace std;

//This function takes the integer value dim and returns the smallest value 2^k equal or bigger than dim.
int checkDimension(int dim){
	int k=0;
	int pad;
	while(1){
		if(pow(2,k)<dim && dim<pow(2,k+1)){
			pad=pow(2,k+1);
			break;	
		}
		else if(pow(2,k)==dim){
			pad=dim; //pad=pow(2,k)
			break;
		}
		else{
			k++;
		}
	}
	return pad;
}

//This function takes two input matrices X  and Y and calculates either their summation or subtraction if sign is +1 or -1, respectively. 
int ** SumSubtrac_XY(int **X,int **Y, int dim, int sign){
	int **SumSubtrac_XY=new int*[dim];
	for (int row=0; row<dim; row++) {
		SumSubtrac_XY[row] = new int[dim];
	}
	for (int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			SumSubtrac_XY[i][j]=X[i][j]+(sign*Y[i][j]);
		}
	}
	return SumSubtrac_XY;
}

//This function takes two matrices X and Y as inputs and then calculates their multiplication recursively and using Strassen's algorithm.
int ** Multipl_XY(int **X,int **Y, int n, int m,int p){
	int **MultipleXY1=new int*[n];
	for (int row=0; row<n; row++) {
		MultipleXY1[row] = new int[p];
	}
	if (m>1||n>1||p>1){
		int padn=checkDimension(n);
		int padm=checkDimension(m);
		int padp=checkDimension(p);
		int dim=padn;
		if(padm>dim){
			dim=padm;
		}
		if(padp>dim){
			dim=padp;
		}
		cout<<"elah1\n";
		int NoAddedRow2X=dim-n;
		int NoAddedCol2X=dim-m;// number of zero padding to the columns of the matrix X is the same as number of zero padding to the rows of the matrix Y
		int NoAddedCol2Y=dim-p;
		
		int **MultipleXY=new int*[dim];//multiplication matrix with zero padding
		for (int row=0; row<dim; row++) {
			MultipleXY[row] = new int[dim];
		}
		cout<<"elah2\n";
		int **Z=new int*[dim];
		int **W=new int*[dim];
		for (int row=0; row<dim; row++) {
			Z[row] = new int[dim];
			W[row] = new int[dim];
		}
		for (int i=0;i<n;i++){//Here we are adding zero to the bottom rows and right-most cols of matrix X
			for(int j=0;j<m;j++){
				Z[i][j]=X[i][j];//the size of resulted matrix Z is dim*dim
			}
		}
		cout<<"elah8\n";
		for (int i=0;i<dim;i++){
			for(int j=m;j<dim;j++){
				Z[i][j]=0;
				W[j][i]=0;
			}
		}
		cout<<"elah9\n";
		for (int j=0;j<dim;j++){
			for(int i=n;i<dim;i++){
				Z[i][j]=0;
			}
		}
		cout<<"elah10\n";
		for (int i=0;i<m;i++){    //Here we are adding zero to the bottom rows and right-most cols of matrix Y
			for(int j=0;j<p;j++){
				W[i][j]=Y[i][j];// the size of resulted matrix W is dim*dim
			}
		}
		cout<<"elah11\n";
		for (int j=0;j<dim;j++){
			for(int i=m;i<dim;i++){
				W[i][j]=0;
			}
		}
		cout<<"elah3\n";
		cout<<dim<<"\n";
		int **A=new int*[dim/2];
		int **B=new int*[dim/2];
		int **C=new int*[dim/2];
		int **D=new int*[dim/2];
		int **E=new int*[dim/2];
		int **F=new int*[dim/2];
		int **G=new int*[dim/2];
		int **H=new int*[dim/2];
		for (int row=0; row<dim/2; row++) {
			A[row] = new int[dim/2];
			B[row] = new int[dim/2];
			C[row] = new int[dim/2];
			D[row] = new int[dim/2];
			E[row] = new int[dim/2];
			F[row] = new int[dim/2];
			G[row] = new int[dim/2];
			H[row] = new int[dim/2];
		};

		for (int i=0;i<dim/2;i++){
			for(int j=0;j<dim/2;j++){
				A[i][j]=Z[i][j];//This is the upper left matrix of X
				E[i][j]=W[i][j];//This is the upper left matrix of Y
				
				B[i][j]=Z[i][j+dim/2];//This is the upper right matrix of X
				F[i][j]=W[i][j+dim/2];//This is the upper right matrix of Y
				
				C[i][j]=Z[i+dim/2][j];//This is the lower left matrix of X
				G[i][j]=W[i+dim/2][j];//This is the lower left matrix of Y
				
				D[i][j]=Z[i+dim/2][j+dim/2];//This is the lower right matrix of X
				H[i][j]=W[i+dim/2][j+dim/2];//This is the lower right matrix of Y				
			}		
		}		
		//P1,...,P7 are seven Strassen's algorithm products
		int **P1=Multipl_XY(A,SumSubtrac_XY(F,H,dim/2,-1),dim/2,dim/2,dim/2);//P1=A(F-H)
		int **P2=Multipl_XY(SumSubtrac_XY(A,B,dim/2,1),H,dim/2,dim/2,dim/2);//P2=(A+B)H
		int **P3=Multipl_XY(SumSubtrac_XY(C,D,dim/2,1),E,dim/2,dim/2,dim/2);//P3=(C+E)D
		int **P4=Multipl_XY(D,SumSubtrac_XY(G,E,dim/2,-1),dim/2,dim/2,dim/2);//P4=D(G-E)
		int **P5=Multipl_XY(SumSubtrac_XY(A,D,dim/2,1),SumSubtrac_XY(E,H,dim/2,1),dim/2,dim/2,dim/2);//P5=(A-D)(E-H)
		int **P6=Multipl_XY(SumSubtrac_XY(B,D,dim/2,-1),SumSubtrac_XY(G,H,dim/2,1),dim/2,dim/2,dim/2);//P6=(B-D)(G-H)
		int **P7=Multipl_XY(SumSubtrac_XY(A,C,dim/2,-1),SumSubtrac_XY(E,F,dim/2,1),dim/2,dim/2,dim/2);//P7=(A-C)(E-F)
		//Here, there is the resulted matrix using the the above seven multiplications
		for (int i=0;i<dim/2;i++){
			for(int j=0;j<dim/2;j++){
				MultipleXY[i][j]=SumSubtrac_XY(SumSubtrac_XY(SumSubtrac_XY(P6,P5,dim/2,1),P4,dim/2,1),P2,dim/2,-1)[i][j];
				MultipleXY[i][j+dim/2]=SumSubtrac_XY(P1,P2,dim/2,1)[i][j];
				MultipleXY[i+dim/2][j]=SumSubtrac_XY(P3,P4,dim/2,1)[i][j];
				MultipleXY[i+dim/2][j+dim/2]=SumSubtrac_XY(SumSubtrac_XY(SumSubtrac_XY(P1,P3,dim/2,-1),P5,dim/2,1),P7,dim/2,-1)[i][j];
			}
		}	

		for (int i=0;i<n;i++){
			for (int j=0;j<p;j++){
				MultipleXY1[i][j]=MultipleXY[i][j];
			}
		}
	}
	
	else if(n==1&&m==1&&p==1)
	{
		MultipleXY1[0][0]=X[0][0]*Y[0][0];
	} 
	
	return MultipleXY1;
}


int main(){
	int n;
	int m;
	int p;
	cout<<"Please enter n, m and p for the dimensions of the first n*m matrix and the second m*p matrix!"<<endl;
	cin>>n>> m>>p;
	int **matrix_X=new int*[n];
	int **matrix_Y=new int*[m];
	int **MultipleXY;
	for (int row=0;row<n;row++){
		matrix_X[row]=new int[m];
	}
	for (int row=0;row<m;row++){
		matrix_Y[row]=new int[p];
	}
	cout<<"Please enter the elements of the first n*m matrix:";
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++){
			cin>>matrix_X[i][j];
		}
	}
	cout<<"Please enter the elements of the second m*p matrix:";
	for (int i=0;i<m;i++){
		for (int j=0;j<p;j++){
			cin>>matrix_Y[i][j];
		}
	}
	MultipleXY=Multipl_XY(matrix_X,matrix_Y,n,m,p);
	for (int i=0;i<n;i++){
		for (int j=0;j<p;j++){
			cout<<MultipleXY[i][j]<<"  ";
		}
		cout<<endl;
	}
	return 0;
}
