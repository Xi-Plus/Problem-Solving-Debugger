#include<iostream>
#include<sstream>
#include<fstream>
#include<ctime>
using namespace std;
string readPath(){
	string path;
	getline(cin,path);
	if(path[0]=='\"'){
		path.erase(0,1);
		path.erase(path.size()-1,1);
	}
	return path;
}
bool cmpFile(string p1,string p2){
	fstream f1(p1.c_str());
	fstream f2(p2.c_str());
	char a,b;
	while(true){
		a=f1.get();
		b=f2.get();
		if(f1.eof()||f2.eof()) break;
		if(a!=b){
			f1.close();
			f2.close();
			return false;
		}
	}
	if( (!f1.eof()) || (!f2.eof()) ){
		f1.close();
		f2.close();
		return false;
	}else{
		f1.close();
		f2.close();
		return true;
	}
}
string exe1="",exe2="",testdata="",type="",temp="temp.out";
int main(){
	stringstream ss;
	string s;
	clock_t start_time,end_time;
	cout<<"your exe path: ";
	exe1=readPath();
	while(type!="cmp"&&type!="sp"){
		cout<<"\"cmp\" for compare 2 exe, \"sp\" for special judge: ";
		cin>>type;
		cin.ignore();
	}
	if(type=="cmp") cout<<"correct exe path: ";
	else cout<<"special judge path: ";
	exe2=readPath();
	cout<<"testdata path or command: ";
	testdata=readPath();
	int times;
	cout<<"times of test (0 for forever): ";
	cin>>times;
	while(true){
		for(int t=1;t<=times||times==0;t++){
			cout<<"test "<<t;
			ss.str("");
			ss<<"\"\""<<testdata<<"\" > \"in.in\"\"";
			system(ss.str().c_str());
			ss.str("");
			ss<<"\"\""<<exe1<<"\" < \"in.in\" > \"exe1.out\"\"";
			start_time=clock();
			system(ss.str().c_str());
			end_time=clock();
			cout<<"  "<<(end_time-start_time)*1000/CLOCKS_PER_SEC<<"ms";
			if(type=="cmp"){
				ss.str("");
				ss<<"\"\""<<exe2<<"\" < \"in.in\"> \"exe2.out\"\"";
				start_time=clock();
				system(ss.str().c_str());
				end_time=clock();
				cout<<"  "<<(end_time-start_time)*1000/CLOCKS_PER_SEC<<"ms";
				if(cmpFile("exe1.out","exe2.out")){
					cout<<"  AC"<<endl;
				}else{
					cout<<"  WA"<<endl;
					system("start in.in");
					system("start exe1.out");
					system("start exe2.out");
					break;
				}
			}else{
				ss.str("");
				ss<<"\""<<exe2<<"\"";
				system(ss.str().c_str());
				fstream exe2("exe2.out");
				string s;
				exe2>>s;
				if(s=="AC"){
					cout<<"  AC"<<endl;
				}else{
					cout<<"  WA"<<endl;
					system("start in.in");
					system("start exe1.out");
					break;
				}
			}
		}
		system("pause");
	}
}
