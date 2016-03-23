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
	ifstream f1(p1.c_str());
	ifstream f2(p2.c_str());
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
int main(){
	string exe="",folder="",temp="temp.out";
	stringstream ss;
	int s,e;
	while(true){
		if(exe==""){
			cout<<"exe path: ";
			exe=readPath();
		}
		if(folder==""){
			cout<<"testdata folder path: ";
			folder=readPath();
			folder+="\\";
			cout<<"First testdata index: ";
			cin>>s;
			cout<<"Last testdata index: ";
			cin>>e; cin.ignore();
		} 
		for(int i=s;i<=e;i++){
			cout<<"testdata "<<i<<"  ";
			clock_t start_time,end_time;
			ss.str("");
			ss<<"run.bat \""<<exe<<"\" \""<<folder<<i<<".in\" \""<<temp<<"\"";
			start_time=clock();
			system(ss.str().c_str());
			end_time=clock();
			ss.str("");
			ss<<folder<<i<<".out";
			if(cmpFile(temp,ss.str())) cout<<"AC";
			else cout<<"WA";
			cout<<"  "<<(end_time-start_time)*1000/CLOCKS_PER_SEC<<"ms ";
			cout<<endl;
		}
		ss.str("");
		ss<<"del "<<temp;
		system(ss.str().c_str());
		cout<<"Press \"Enter\" for rejudge, Input \"exe\" \"testdata\" \"exit\""<<endl;
		string command;
		getline(cin,command);
		if(command=="exe") exe="";
		else if(command=="testdata") folder=""; 
		else if(command=="exit") break;
	}
}
