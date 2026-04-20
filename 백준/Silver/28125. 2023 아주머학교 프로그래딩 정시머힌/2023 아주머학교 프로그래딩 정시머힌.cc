#include <iostream>
#include <string>
using namespace std;
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin>>n;
	while(n--){
		string s,r="";
		cin>>s;
		int c=0;
		for(int i=0;i<s.size();++i){
			if(s[i]=='@'){r+='a';c++;}
			else if(s[i]=='['){r+='c';c++;}
			else if(s[i]=='!'){r+='i';c++;}
			else if(s[i]==';'){r+='j';c++;}
			else if(s[i]=='^'){r+='n';c++;}
			else if(s[i]=='0'){r+='o';c++;}
			else if(s[i]=='7'){r+='t';c++;}
			else if(s[i]=='\\'){
				if(s[i+1]=='\\'){r+='w';c++;i+=2;}
				else{r+='v';c++;i++;}
			}
			else r+=s[i];
		}
		if(c*2>=r.size())cout<<"I don't understand\n";
		else cout<<r<<'\n';
	}
}