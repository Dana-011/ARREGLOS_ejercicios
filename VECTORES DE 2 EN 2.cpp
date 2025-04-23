#include <iostream>
using namespace std;
int main(){
	setlocale(LC_ALL, "SPANISH");
	int A[10],n;
	cout<<"ingrese la cantidad de números: ";
	cin>>n;
	for (int i=1;i<=n;i++){
		cout<<"ingrese los elementos del vector: ";
		cin>>A[i];
	}
	
	cout<<"Los valores almacenados en las posiciones pares son : ";
	for (int i=2;i<=n;i=i+2){
		cout<<A[i]<<endl;
	}
	return 0;
}

