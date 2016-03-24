// By KRT girl xiplus
#include <iostream>
#include <fstream>
using namespace std;
int main(){
	fstream in,exe1,exe2;
	in.open("in.in",ios::in);
	exe1.open("exe1.out",ios::in);
	exe2.open("exe2.out",ios::out);
	int A,B,a,b;
	in>>A>>B;
	if(A>B)swap(A,B);
	exe1>>a>>b;
	if(B-A<1){
		if(a==0&&b==0)exe2<<"AC"<<endl;
		else exe2<<"WA 0 0"<<endl;
	}else{
		if(a<A)exe2<<"WA a<A"<<endl;
		else if(a>B)exe2<<"WA a>B"<<endl;
		else if(b<A)exe2<<"WA b<A"<<endl;
		else if(b>B)exe2<<"WA b>B"<<endl;
		else if(!((a&1)^(b&1)))exe2<<"WA not even&odd"<<endl;
		else exe2<<"AC"<<endl;
	}
}
