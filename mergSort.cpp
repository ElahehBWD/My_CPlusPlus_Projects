#include <iostream>
#include <cmath>

using namespace std;
//merge function merges two sorted sub-arrays namely aLeft and aRigh
void merge(int aLeft[],int aRight[],int a[],int lL,int lR,int n){
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
};
//mergeSort function recursively sorts and merges sub arrays 
void mergeSort(int a[],int n){
	int i,j,mid=n/2;
	int aLeft[n/2];
	int aRight[n-mid];

	 for (i=0;i<mid;i++){
		(aLeft[i])=a[i];
	 }
	 for (j=0;j<n-mid;j++){
		(aRight[j])=a[j+mid];
	 }
	 
	int lL=sizeof(aLeft) / sizeof(aLeft[0]);
	int lR=sizeof(aRight) / sizeof(aRight[0]);
	
	if (lL>=2){
	mergeSort(aLeft,lL);
	}
	if(lR>=2){
	mergeSort(aRight,lR);
	}
	merge(aLeft,aRight,a,lL,lR,n);
}


int main(){
	int n;
    cout<< "Please enter the size of your array:";
	cin>>n;
	int a[n];
	cout<<"Please enter "<<n<<" numbers of the unsorted array"<<endl;
	for (int i=0;i<n;i++){
	cin>>a[i];
	}
	mergeSort(a, sizeof(a) / sizeof(a[0]));
	cout<<"Sorted array is:"<<endl;
	for (int l=0;l<n;l++){
		cout<<a[l]<<" ";
	}
	cout<<endl;
	return 0;

}
