#include <bits/stdc++.h>
using namespace std;

string uid="";
int kodid=0;
int sid=0;

void getid(){
    fstream f;
    f.open("checknow.log", ios::in);
        f >> uid >> kodid;
    f.close();
}

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

void exec(){
    /*
        path = "py3 ./submit/" + uid + "uhankod.py 2> ./log/uohankod.log";
        path = "mono ./submit/" + uid + "uhankod.cs 2> ./log/uohankod.log";
        path = "fpc ./submit/" + uid + "uhankod.pas 2> ./log/uohankod.log";
        path = "gcc ./submit/" + uid + "uhankod.c -o ./return/uhankod 2> ./log/uohankod.log";
        path = "py2 ./submit/" + uid + "uhankod.py 2> ./log/uohankod.log";
        path = "javac ./submit" + uid + "uhankod.java 2> ./log/uohankod.log";
        path = "g++ ./submit/" + uid + "/uhankod.cpp -o ./return/uhankod 2> ./log/uohankod.log";
      */
    string path;
    
    switch (kodid){
            case 1:
            path = "gcc ./submit/" + uid + "uhankod.c -o ./return/uhankod 2> ./log/uohankod.log";
        break;
             case 2:
             path = "g++ ./submit/" + uid + "/uhankod.cpp -o ./return/uhankod 2> ./log/uohankod.log";
        break;
             case 3:
             path = "py2 ./submit/" + uid + "uhankod.py 2> ./log/uohankod.log";
        break;
             case 4:
             path = "py3 ./submit/" + uid + "uhankod.py 2> ./log/uohankod.log";
        break;
             case 5:
            path = "mono ./submit/" + uid + "uhankod.cs 2> ./log/uohankod.log";
        break;
             case 6:
             path = "javac ./submit" + uid + "uhankod.java 2> ./log/uohankod.log";
        break;
             case 7:
             path = "fpc ./submit/" + uid + "uhankod.pas 2> ./log/uohankod.log";
        break;
        default:
        break;
    }
    
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
