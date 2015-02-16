#include<iostream>
#include <fstream>

using namespace std;
//The input array contains some numbers in an arbitrary order. The goal of this code is counting the number of inversions in this array. 
//In fact, the number of inversions is the number of pairs (i,j)  of array indices with i<j and A[i]>A[j].(Tim Roughgarden)


//For counting the number of inversions in an array, we use the merge sort algorithm by counting the number of split inversions
int merge(int aLeft[],int aRight[],int a[],int lL,int lR,int n,double S){
	int i=0;int j=0;int k=0;
	for (k=0;k<n;k++){
		if (i<lL&&j<lR){
			if ((aLeft[i])<=(aRight[j])){
				a[k]=(aLeft[i]);
				i++;
			}
			else{
				a[k]=(aRight[j]);
				j++; 
				S+=lL-i;//Here we count the number of split inversions. In fact, when elements of right array gets copied to the output, the value of S is incremented by the number of elements remaining in the left array. 
			}
		}
		else if(i<lL){
			a[k]=(aLeft[i]);
			i++; 
		}
		else if(j<lR){
			a[k]=(aRight[j]);
			j++;  
		}        	   
	}
	cout<<S<<endl;
	return S;
};
//mergeSort function first split the array a into two sub-arrays aLeft 
//and aRight and recursively sorts and merges the sub-arrays 
int mergeSort(int a[],int n){
	int i,j,mid=n/2;
	int aLeft[n/2];
	int aRight[n-mid];
	double static S=0;//The static variable S counts the number of conversions 

	for (i=0;i<mid;i++){
		(aLeft[i])=a[i];
	}
	for (j=0;j<n-mid;j++){
		(aRight[j])=a[j+mid];
	}

	if (mid>=2){
		mergeSort(aLeft,mid);
	}
	if(n-mid>=2){
		mergeSort(aRight,n-mid);
	}
	S=merge(aLeft,aRight,a,mid,n-mid,n,S);
	return S;
}

//Here, we ask the user to enter its array, then the number of inversions is calculated recursively and using merge sort
int main(){
	int n;
	int NoInversions;
	cout<<"Please enter the length of your array!"<<endl;
	cin>>n;
	int array[n];
	cout<<"Please enter the elements of your array:";
	for (int i=0;i<n;i++){
		cin>>array[i];
	}
	NoInversions=mergeSort(array,n);
	cout<<"Number of inversions in array is "<<NoInversions<<endl;
	return 0;
}
