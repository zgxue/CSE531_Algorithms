#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define M 1001
#define N 1001

using namespace std;

int c[M][N];
int b[M][N]; // 1 means diagnal; 2 means left; 3 means up

int counting = 0;
char res[M];

void LCS(string x, string y); // Longest Common Subsequence
void print_LCS(string x, int i, int j);
void output_LCS();

int main() {

    //ifstream inf("/Users/zhenggangxue/Desktop/input.txt");
    ifstream inf("input.txt");
    string x, y;
    if(inf.is_open()){
        inf >> x;
        inf >> y;
    }
    else
        cerr << "Error when opening input.txt" << endl;
    inf.close();

    //string x = "bacdca";
    //string y = "adbcda";

    cout << "The input strings are: \""<<x <<"\" , \"" << y << "\"" << endl;

    LCS(x, y);

    int m = x.length();
    int n = y.length();

    print_LCS(x, m, n);
    output_LCS();

    return 0;
}

void LCS(string x, string y){

    int m = x.length();
    int n = y.length();


    for (int i = 1; i <= m; ++i) {
        c[i][0] = 0;
    }
    for (int j = 0; j <= n ; ++j) {
        c[0][j] = 0;
    }
    for (int i = 1; i <= m ; ++i) {
        for (int j = 1; j <= n ; ++j) {
            if (x[i-1] == y[j-1]){
                c[i][j] = c[i-1][j-1] +1;
                b[i][j] = 1;
            }
            else if (c[i-1][j] >= c[i][j-1]){
                c[i][j] = c[i-1][j];
                b[i][j] = 3;
            }
            else{
                c[i][j] = c[i][j-1];
                b[i][j] = 2;
            }
        }
    }

}

void print_LCS(string x, int i, int j){

    if (i == 0 || j == 0)
        return;
    if (b[i][j] == 1){
        print_LCS(x, i-1, j-1);
        cout << x[i-1] << " ";
        res[counting++] = x[i-1];
    }
    else if (b[i][j] == 3){
        print_LCS(x, i-1, j);
    }
    else{
        print_LCS(x, i, j-1);
    }
}

void output_LCS(){
    //ofstream outf("/Users/zhenggangxue/Desktop/output.txt");
    ofstream outf("output.txt");
    outf << counting << endl;
    for (int i = 0; i < counting; ++i) {
        outf << res[i];
    }
    outf.close();
}
