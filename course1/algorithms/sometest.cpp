#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
ifstream fin("C:\\Users\\Egor\\Documents\\QCTF\\neutrino\\content");
//ifstream f;
ofstream fout("C:\\Users\\Egor\\Documents\\QCTF\\neutrino\\out2.txt");

int main() {
    //f.open("C:\\Users\\Egor\\Documents\\QCTF\\neutrino\\content");
    //int n, k;
    //double d;
    //double last = 0;
    char r;
    for(int i = 0; i < 100000; i++) {
        //ostringstream ost;
        //fin >> n >> d;
        for(int j = 0;j<24;j++){
            fin >> r;
            fout << r;
        }
        //cout << r << endl;
        //ost << d;
        //string s = ost.str();
        /*for(int i = 0;i<s.length();i++){
            if(s[i] == '.'){
                s[i] = ',';
            }
        */
        fout<< endl;
    }

    fin.close();
    //f.close();
    fout.close();
    return 0;
}
