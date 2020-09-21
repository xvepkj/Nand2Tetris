/* */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <sstream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <bitset>
#include <map>
#include <set>
const int MAX_LEN = 10100;
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
char s[100];
char t[100];
char p[100];
vector<string> instructions;
int noofinstructions;
map<string,int> symbols={
    {"R0",0},
    {"R1",1},
    {"R2",2},
    {"R3",3},
    {"R4",4},
    {"R4",4},
    {"R5",5},
    {"R6",6},
    {"R7",7},
    {"R8",8},
    {"R9",9},
    {"R10",10},
    {"R11",11},
    {"R12",12},
    {"R13",13},
    {"R14",14},
    {"R15",15},
    {"SP",0},
    {"LCL",1},
    {"ARG",2},
    {"THIS",3},
    {"THAT",4},
    {"SCREEN",16384},
    {"KBD",24576}
};
map<string,string> jumps={{"JGT","001"},{"JEQ","010"},{"JGE","011"},{"JLT","100"},{"JNE","101"},{"JLE","110"},{"JMP","111"}};
map<string,string> dests={{"M","001"},{"D","010"},{"MD","011"},{"A","100"},{"AM","101"},{"AD","110"},{"AMD","111"}};
map<string,string> comp={
    {"0","0101010"},
    {"1","0111111"},
    {"-1","0111010"},
    {"D","0001100"},
    {"A","0110000"},
    {"M","1110000"},
    {"!D","0001101"},
    {"!A","0110001"},
    {"!M","1110001"},
    {"-D","0001111"},
    {"-A","0110001"},
    {"-M","1110011"},
    {"D+1","0011111"},
    {"A+1","0110111"},
    {"M+1","1110111"},
    {"D-1","0001110"},
    {"A-1","0110010"},
    {"M-1","1110010"},
    {"D+A","0000010"},
    {"D+M","1000010"},
    {"D-A","0010011"},
    {"D-M","1010011"},
    {"A-D","0000111"},
    {"M-D","1000111"},
    {"D&A","0000000"},
    {"D&M","1000000"},
    {"D|A","0010101"},
    {"D|M","1010101"}
};
bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
void binary(int cur){
    vi bin;
    for(int i=0;i<15;i++){
        bin.push_back(cur%2);
        cur=cur>>1;
    }
    reverse(bin.begin(),bin.end());
    for(int i=0;i<15;i++)
        printf("%d",bin[i]);
    printf("\n");
}
int varno=16;
int main(){
    // freopen("inp.txt", "r", stdin);
    // freopen("pong.hack", "w", stdout);
    while(scanf("%s",s)==1){
        if(s[0]!='/' && s[0]!='('){
            instructions.push_back(string(s));
            noofinstructions++;
        }
        if(s[0]=='('){
            int i=1;
            while(s[i]!=')'){t[i-1]=s[i];i++;}
            t[i-1]='\0';
            symbols[string(t)]=noofinstructions;
        }
        if(s[0]=='/'){
            GETLINE(p);
        }
    }
    // dbg(instructions);
    // dbg(symbols);
    int n=(int)instructions.size();
    for(int in=0;in<n;in++){
        string x=instructions[in];
        if(x[0]=='@'){
            //A instruction
            printf("0");
            int num;
            string y=x.substr(1,x.length()-1);
            if(!is_number(y)){
            if(symbols.count(y)==0){
                symbols[y]=varno++;
            }
            num=symbols[y];
            }
            else num=stoi(y);
            binary(num);
        }
        else {
            int i=0;
            int len=x.length();
            while(x[i]!='=' && x[i]!=';')i++;
            len-=(i+1);
            string y=x.substr(0,i);
            string z=x.substr(i+1,len);
            printf("111");
            if(x[i]=='='){
                printf("%s",comp[z].data());
                printf("%s",dests[y].data());
                printf("000\n");
            }
            else {
                printf("%s",comp[y].data());
                printf("000");
                printf("%s\n",jumps[z].data());

            }
        }
    }
}