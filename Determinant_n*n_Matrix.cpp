#include <iostream>
#include <cmath>

using namespace std;
//This function creates the minor matrix by deleting the specified row and column
int** minor(int **array, int dim, int alongRowi, int alongColj){
	int **minorArr=new int*[dim-1];
	for (int row=0; row<dim-1; row++) {
		minorArr[row] = new int[dim-1];
	}
	int k=0;
	int l;
	for(int i=0;i<dim;i++){
		if(i!=alongRowi){
			l=0;
			for (int j=0;j<dim;j++){	
				if(j!=alongColj){	
					minorArr[k][l]=array[i][j];
					l++;					
				}
			}
			k++;
		}
	}
	return minorArr;
} ;
//This function is used to free the dynamic memory allocated for a 2D array
void freeMinor(int** minorArr, int dim){
	if(minorArr){
		for(int row=0; row<dim-1; row++){
			if(minorArr[row]){ delete[] minorArr[row];
			}
		}
		delete[] minorArr;    
	}
};

// Recursive definition of determinate using expansion by minors
int determinant (int **array, int dim, int alongRowi){
	int det;
	int n=dim;
	if (dim==1){
		det=array[0][0];
	}
	else if(dim>1){
		int det=0;
		for (int j=0;j<n;j++){
			int **minorArr=minor(array,dim,alongRowi,j);//for each column j, first calculates the minor matrix by deleting the "alongRowi" row and "j" column
			det=det+pow(-1,j)*array[alongRowi][j]*determinant(minorArr,dim-1,alongRowi);//determinant for matrix "array" with size n is weighted sum of
			//the determinants of n sub-matrices of minorArr, each of size (n−1) × (n−1) 
			freeMinor(minorArr,dim-1);// here make free the dynamic memory
		}			
		return det;	
	}
};   
//main function asks the user to enter the size of matrix "array" as well as the elements of that matrix row by row 
int main(){
	int n;
	int det;
	cout<<"Please enter the value n"<<endl;
	cin>>n;
	int **array=new int*[n];
	for (int row=0; row<n; row++) {
		array[row] = new int[n];
	}
	cout<<"Please enter the elements of the matrix row by row!"<<endl;
	for(int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			cin>>array[i][j];
		}
	}
	det=determinant(array,n,0);//Calculates the amount of determinant using Laplace expansion along first row
	cout<<"The amount of determinant is: "<< det<<endl;
	return 0;
}
