// By KRT girl xiplus
#include <iostream>
#include <ctime>
using namespace std;
int main(){
/*****************************************************/
/* Question: Output 2 dissimilar numbers betewn a,b. */
/* one is even, another is odd.                      */
/* output 0 0 for no answer.                         */
/*****************************************************/
	srand(time(NULL));
	int a=rand()%100;
	int b=a+rand()%10;
	if(rand()%20)cout<<a<<" "<<b<<endl;
	else cout<<b<<" "<<a<<endl;
}
