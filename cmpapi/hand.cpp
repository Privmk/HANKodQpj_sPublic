#include <bits/stdc++.h>
using namespace std;

string uid="";
int sid=0;

void getid(){
    fstream f;
    f.open("checknow.log", ios::in);
        f >> uid;
    f.close();
}

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

void exec(){
    string path = "g++ ./submit/" + uid + "/uhankod.cpp -o ./return/uhankod 2> ./log/uohankod.log";
    const char *cmd = path.c_str();
    system(cmd);    
}

bool compareFiles(const std::string& p1, const std::string& p2) {
  std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
  std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

  if (f1.fail() || f2.fail()) {
    return false; //file problem
  }

  if (f1.tellg() != f2.tellg()) {
    return false; //size mismatch
  }

  //seek back to beginning and use std::equal to compare contents
  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}

void resultreturn(int mark){
    ifstream f("./return/" + uid + ".log", ios::out);
        f << mark << endl;
    f.close();
}

void testcase(){
    system("mv ./return/uhankod ./test");
    
    int n;
    int mark=0;
    string test, testid, outpath;
    ifstream f("./test/info.txt");
        f >> n;
    f.close();
    for(int i=1; i<=n; i++){
        testid = to_string(n);
        test = "cp ./inp/" + testid + "/HANKOD.INP ./test";
        const char *cmd = test.c_str();
        system(cmd);
        system("./test/uhankod");
        outpath = "./test/out/" + testid + "/HANKOD.OUT";
        if (compareFiles("./test/HANKOD.OUT" , outpath)){
                mark++;
            }
        }
    resultreturn(mark);
}


void getexec(){
    string r="";
    fstream f("./log/uohankod.log", ios::in);
        f >> r;
    f.close();

    if (r==""){
        testcase();
    }
}

int main(){
    getid();
    exec();
    getexec();
    testcase();
    return 0;   
}