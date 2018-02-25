/* David Haltinner
 * C++ undoubtly. Used as a base for both assembly versions.
 */
#include <iostream>
using namespace std;
int main() {
	int B;
	cout<<"Give me B: ";
	cin>>B;
	int A[20];
	for (int i=0; i<20; i++) {
		A[i]=i*2;
	}
	int count=0;
	for (int i=0; i<20; i++) {
		if (A[i]==B) {
			count=count + 1;
		}
	}
	cout<<B<<" occurs "<<count<<" times in A."<<endl;
}	
