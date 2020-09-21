/* */
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <bitset>
#include <map>
#include <set>
const int MAX_LEN = 1010;
#define GETLINE(x) fgets(x,MAX_LEN,stdin)
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef pair<double, double> dd;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<ll> vll;
#ifdef XVENOM
    #define errp(...) fprintf(stderr, __VA_ARGS__)
    #define dbg(...) errp("[%s]: ", #__VA_ARGS__), dbg_str(__VA_ARGS__)
#else
    #define errp(...)
    #define dbg(...)
#endif
template <typename U, typename V> string to_string (pair<U, V>);
string to_string (const string& e_) { return "\"" + e_ + "\""; }
string to_string (char e_) { return "\'" + string(1, e_) + "\'"; }
string to_string (bool e_) { return e_ ? "true" : "false"; }
template <typename T> string to_string (T e_) {
    string s_ = "[ ";
    for (const auto& x_ : e_) s_ += to_string(x_) + " ";
    return s_ + "]";
}
template <typename U, typename V> string to_string (pair<U, V> e_) {
    return "(" + to_string(e_.first) + ", " + to_string(e_.second) + ")";
}
void dbg_str () { errp(" \n"); }
template <typename U, typename... V> void dbg_str (U u, V... v) {
     errp(" %s", to_string(u).c_str()); dbg_str(v...);
}
/* --- */
string inputfile;
string outputfile;
string filename;
map<string,string> RAMaddr={
    {"local","LCL"},
    {"argument","ARG"},
    {"this","THIS"},
    {"that","THAT"},
    {"temp","5"}
    //set static manually
    //temp bhi alag
    //pointer bhi alag
};
string pntr[]={"THIS","THAT"};
char s[100];
int arthJumpFlag;
map<string,string> flagsel={
    {"gt","JLE"},
    {"lt","JGE"},
    {"eq","JNE"}
};
string jumpin(string type){
    return "@SP\n" 
                "AM=M-1\n" 
                "D=M\n" 
                "A=A-1\n" 
                "D=M-D\n" 
                "@FALSE" + to_string(arthJumpFlag) + "\n" 
                "D;" + type + "\n" 
                "@SP\n" 
                "A=M-1\n" 
                "M=-1\n" 
                "@CONTINUE" + to_string(arthJumpFlag) + "\n" 
                "0;JMP\n" 
                "(FALSE" + to_string(arthJumpFlag) + ")\n" 
                "@SP\n" 
                "A=M-1\n" 
                "M=0\n" 
                "(CONTINUE" + to_string(arthJumpFlag) + ")\n";                
}
void processpush(string seg,int index){
    printf("//push %s %d\n",seg.data(),index);
    if(seg.compare("constant")==0){
        printf("@%d\n",index);
        printf("D=A\n");
    }
    else if(seg.compare("pointer")==0){
        printf("@%s\n",pntr[index].data());
        printf("D=M\n");
    }
    else if(seg.compare("static")==0){
        printf("@%s.%d\n",filename.data(),index);
        printf("D=M\n");
    }
    else if(seg.compare("temp")==0){
        printf("@5\n");
        printf("D=A\n");
        printf("@%d\n",index);
        printf("A=D+A\n");
        printf("D=M\n");
    }
    else {
        printf("@%d\n",index);
        printf("D=A\n");
        printf("@%s\n",RAMaddr[seg].data()); 
        printf("A=D+M\n");
        printf("D=M\n");
    }
    printf("@SP\n");
    printf("A=M\n");
    printf("M=D\n");
    printf("@SP\n");
    printf("M=M+1\n");
}
void processpop(string seg,int index){
    printf("//pop %s %d\n",seg.data(),index);
    printf("@SP\n");
    printf("M=M-1\n");
    printf("A=M\n");
    printf("D=M\n");
    printf("@R13\n");
    printf("M=D\n");
    if(seg.compare("pointer")==0){
        printf("@%s\n",pntr[index].data());
        printf("M=D\n");
    }
    else if(seg.compare("static")==0){
        printf("@%s.%d\n",filename.data(),index);
        printf("M=D\n");
    }
    else {
        printf("@%s\n",RAMaddr[seg].data()); 
        if(seg.compare("temp")==0)printf("D=A\n");
        else printf("D=M\n");
        printf("@%d\n",index);
        printf("D=D+A\n");
        printf("@R14\n");
        printf("M=D\n");
        printf("@R13\n");
        printf("D=M\n");
        printf("@R14\n");
        printf("A=M\n");
        printf("M=D\n");
    }
}
void processops(string operatn){
    printf("//start operation\n");
    if(operatn.compare("not")==0){
        printf("@SP\nA=M-1\nM=!M\n");
    }
    else if(operatn.compare("neg")==0){
        printf("D=0\n@SP\nA=M-1\nM=D-M\n");
    }
    else if(operatn.compare("gt")==0 || operatn.compare("lt")==0 || operatn.compare("eq")==0){
        printf("%s",jumpin(flagsel[operatn]).data());
        arthJumpFlag++;
    }
    else {
        printf("@SP\n");
        printf("M=M-1\n");
        printf("A=M\n");
        printf("D=M\n");
        printf("@SP\n");
        printf("M=M-1\n");
        printf("A=M\n");
        if(operatn.compare("add")==0)printf("M=D+M\n");
        if(operatn.compare("sub")==0)printf("M=M-D\n");
        if(operatn.compare("and")==0)printf("M=D&M\n");
        if(operatn.compare("or")==0)printf("M=D|M\n");
        printf("@SP\n");
        printf("M=M+1\n");
    }
}
char t[100];
char q[100];
char segment[100];
vector<string> filepath;
set<string> ops={"add","sub","neg","eq","gt","lt","and","or","not"};
int n;
int main ( int argc, char *argv[]) { 
    inputfile=string(argv[1]);
    char* tch;
    tch= strtok (argv[1],".");
    filename=tch;
    outputfile=filename+".asm";
    dbg(outputfile);
    char *pch;
    pch= strtok (argv[1],"./");
    while (pch != NULL)
    {
        string x=pch;
        filepath.push_back(pch);
        pch = strtok (NULL, "./");
    }
    dbg(filepath);
    filename=filepath[filepath.size()-1];
    freopen(inputfile.c_str(), "r", stdin);
    freopen(outputfile.c_str(), "w", stdout);
   while(scanf("%s",s)==1){
        if(strcmp(s,"push")==0){
            scanf("%s %d",segment,&n);
            processpush(segment,n);
            
        }
        if(strcmp(s,"pop")==0){
            scanf("%s %d",segment,&n);
            processpop(segment,n);
        }
        if(ops.count(string(s))==1){
            processops(string(s));
        }
        if(s[0]=='/'){GETLINE(t);}
   }
}