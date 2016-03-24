#include<iostream>
#include<sstream>
#include<fstream>
#include<ctime>
#include<map>
#include<dirent.h>
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
string exe="",folder="",temp="temp.out";
void judge(string name){
	cout<<"testdata "<<name<<"  ";
	clock_t start_time,end_time;
	stringstream ss;
	ss<<"\"\""<<exe<<"\" < \""<<folder<<name<<".in\" > \""<<temp<<"\"\"";
	start_time=clock();
	system(ss.str().c_str());
	end_time=clock();
	ss.str("");
	ss<<folder<<name<<".out";
	if(cmpFile(temp,ss.str())) cout<<"AC";
	else cout<<"WA";
	cout<<"  "<<(end_time-start_time)*1000/CLOCKS_PER_SEC<<"ms ";
	cout<<endl;
}
int main(){
	stringstream ss;
	string s;
	int e;
	while(true){
		if(exe==""){
			cout<<"exe path: ";
			exe=readPath();
		}
		if(folder==""){
			cout<<"testdata folder path: ";
			folder=readPath();
			folder+="\\";
			s="";
			while(s!="all"&&atoi(s.c_str())==0){
				cout<<"First testdata index or Type \"all\": ";
				cin>>s;
				cin.ignore();
			}
			e=0;
			while(s!="all"&&e==0){
				cout<<"Last testdata index: ";
				cin>>e;
				cin.ignore();
			}
		}
		if(s=="all"){
			DIR *dir;
		    struct dirent *dirp;
		    if((dir = opendir(folder.c_str())) != NULL){
		    	map<string,bool> in,out;
		    	while((dirp = readdir(dir)) != NULL){
		    		string name=dirp->d_name;
		    		string ext=name.substr(name.find_last_of(".")+1);
		    		string main=name.substr(0,name.find_last_of("."));
		    		if(ext=="in"){
		    			in[main]=true;
					}else if(ext=="out"){
						out[main]=true;
					}
			    }
				closedir(dir);
				for(auto i:in){
					if(out[i.first]){
						judge(i.first);
					}else{
						cout<<"Missing file: "<<i.first<<".out"<<endl;
					}
				}
		    }else {
		    	cout<<"Judge fail."<<endl;
			}
		}else{
			for(int i=atoi(s.c_str());i<=e;i++){
				judge(to_string(i));
			}
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
