#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <chrono>
#include <ctime>
using namespace std;
int main () {
        cout<<"Write some text and it will be written to file:"<<endl;
        ofstream file;
        file.open("file.txt",ios_base::app);
        string *str = new string [4095];
        string dot = ".";
        for(int i=0;i<3;i++) file<<endl;
        auto end = chrono::system_clock::now();
        time_t end_time = chrono::system_clock::to_time_t(end);
        file<<ctime(&end_time)<<endl;
        for(int i=0;getline(cin, str[i]),str[i].compare(".");i++) {
                file<<str[i]<<endl;
        }
        cout<<"file saved!"<<endl;
        file.close();
        return 0;
}
