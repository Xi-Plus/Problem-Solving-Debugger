#include<iostream>
#include<sstream>
#include<fstream>
#include<ctime>
#include<conio.h>
using namespace std;
string readPath() {
	string path;
	getline(cin,path);
	while(path.front()==' ')path.erase(path.begin());
	while(path.back()==' ')path.erase(path.end()-1);
	if(path.front()=='"'&&path.back()=='"') {
		path.erase(path.begin());
		path.erase(path.end()-1);
	}
	return path;
}
bool cmpFile(string p1,string p2) {
	fstream f1(p1.c_str());
	fstream f2(p2.c_str());
	char a,b;
	while(true) {
		a=f1.get();
		b=f2.get();
		if(f1.eof()||f2.eof()) break;
		if(a!=b) {
			f1.close();
			f2.close();
			return false;
		}
	}
	if( (!f1.eof()) || (!f2.eof()) ) {
		f1.close();
		f2.close();
		return false;
	} else {
		f1.close();
		f2.close();
		return true;
	}
}
string exe1="",exe2="",exesp="",testdata="",type="",temp="temp.out";
int times=-1;
int changepath(string *path) {
	string temp = readPath();
	if(temp=="") {
		cout<<"No Change"<<endl;
		return 0;
	}
	ifstream ifile(temp);
	if(!ifile.good()) {
		cout<<"File Not Found"<<endl;
		return -1;
	}
	*path = temp;
	return 1;
}
int changeexe1() {
	cout<<"[exe 1] input one executable path: ";
	return changepath(&exe1);
}
int changeexe2() {
	cout<<"[exe 2] input the other executable path: ";
	return changepath(&exe2);
}
int changeexesp() {
	cout<<"[exe sp] input special judge path: ";
	return changepath(&exesp);
}
int changetestdata() {
	cout<<"[testdata] input testdata generator path: ";
	return changepath(&testdata);
}
void changetimes() {
	while(times<0) {
		cout<<"[times] times of test (0 for forever): ";
		cin>>times;
	}
}
int changetype() {
	cout<<"[type] \"cmp\" for compare 2 exe, \"sp\" for special judge: ";
	string temp = readPath();
	if(temp=="") {
		return 0;
	}
	if(temp=="cmp"||temp=="sp") {
		type = temp;
		return 1;
	}
	return -1;
}
int main() {
	stringstream ss;
	string s;
	clock_t start_time,end_time;
	while(changeexe1()!=1);
	while(changetype()!=1);
	if(type=="cmp")
		while(changeexe2()!=1);
	else
		while(changeexesp()!=1);
	while(changetestdata()!=1);
	changetimes();
	while(true) {
		for(int t=1; t<=times||times==0; t++) {
			if(kbhit()) {
				getch();
				break;
			}
			cout<<"test "<<t;
			ss.str("");
			ss<<"\"\""<<testdata<<"\" > \"in.in\"\"";
			system(ss.str().c_str());
			ss.str("");
			ss<<"\"\""<<exe1<<"\" < \"in.in\" > \"exe1.out\"\"";
			start_time=clock();
			system(ss.str().c_str());
			end_time=clock();
			cout<<"\t"<<(end_time-start_time)*1000/CLOCKS_PER_SEC<<"ms";
			if(type=="cmp") {
				ss.str("");
				ss<<"\"\""<<exe2<<"\" < \"in.in\"> \"exe2.out\"\"";
				start_time=clock();
				system(ss.str().c_str());
				end_time=clock();
				cout<<"\t"<<(end_time-start_time)*1000/CLOCKS_PER_SEC<<"ms";
				if(cmpFile("exe1.out","exe2.out")) {
					cout<<"\tAC"<<endl;
				} else {
					cout<<"\tWA"<<endl;
					system("start in.in");
					system("start exe1.out");
					system("start exe2.out");
					break;
				}
			} else {
				ss.str("");
				ss<<"\""<<exe2<<"\"";
				system(ss.str().c_str());
				fstream exe2("exe2.out");
				string s;
				exe2>>s;
				if(s=="AC") {
					cout<<"\tAC"<<endl;
				} else {
					cout<<"\tWA"<<endl;
					system("start in.in");
					system("start exe1.out");
					break;
				}
			}
		}
		cout<<endl;
		cout<<"[exe1] "<<exe1<<endl;
		if(type=="cmp") cout<<"[exe2] "<<exe2<<endl;
		if(type=="sp") cout<<"[exesp] "<<exesp<<endl;
		cout<<"[testdata] "<<testdata<<endl;
		cout<<"[times] "<<times<<endl;
		cout<<"Input exe1, exe2, exesp, testdata, times to change"<<endl;
		cout<<"others to continue."<<endl;
		string cmd="";
		cmd=readPath();
		if(cmd=="exe1")changeexe1();
		else if(type=="cmp"&&cmd=="exe2")changeexe2();
		else if(type=="sp"&&cmd=="exesp")changeexesp();
		else if(cmd=="testdata")changetestdata();
		else if(cmd=="times")changetimes();
	}
}
