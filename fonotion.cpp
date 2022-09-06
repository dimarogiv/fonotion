#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <chrono>
#include <ctime>
#include <conio.h>
using namespace std;
int main () {
        cout<<"Enter a type of the note:\n\t. is a task\n\tx means task is done\n\t> task is pushed\n\t< task is scheduled\n\t- task is canceled\n\t+ is note\n\t* is some very important task\n\t& is a goal\n\t$ is daily task\n\t@ is historical event"<<endl;
        ofstream file;
        file.open("file.txt",ios_base::app);
        string str;
        string dot = ".";
        for(int i=0;i<3;i++) file<<endl;
        time_t ttime = time(0);
        tm *local_time = localtime(&ttime);
        char type;
        int notion_id = 83298;
        bool success;
        do{
                type=getch();
                success=1;
                switch(type){
                        case '.':
                                cout<<"task"<<endl;
                                break;
                        case 'x':
                                cout<<"task is done"<<endl;
                                break;
                        case '>':
                                cout<<"task is pushed"<<endl;
                                break;
                        case '<':
                                cout<<"task is scheduled"<<endl;
                                break;
                        case '-':
                                cout<<"task is canceled"<<endl;
                                break;
                        case '+':
                                cout<<"note"<<endl;
                                break;
                        case '*':
                                cout<<"important task"<<endl;
                                break;
                        case '&':
                                cout<<"goal"<<endl;
                                break;
                        case '$':
                                cout<<"daily task"<<endl;
                                break;
                        case '@':
                                cout<<"historical event"<<endl;
                                break;
                        default:
                                cout<<"there is no such type, choose one of suggested!"<<endl;
                                success=0;
                }
        }while(!success);
        string note_data;
        note_data.append(1,type);
        if(local_time->tm_mday<10)note_data.append("0");
        note_data.append(to_string(local_time->tm_mday));
        note_data.append("/");
        if(local_time->tm_mon<10)note_data.append("0");
        note_data.append(to_string(1+local_time->tm_mon));
        note_data.append("/");
        note_data.append(to_string(1900+local_time->tm_year));
        note_data.append("_");
        if(local_time->tm_hour<10)note_data.append("0");
        note_data.append(to_string(1+local_time->tm_hour));
        note_data.append(":");
        if(local_time->tm_min<10)note_data.append("0");
        note_data.append(to_string(1+local_time->tm_min));
        note_data.append(":");
        if(local_time->tm_sec<10)note_data.append("0");
        note_data.append(to_string(1+local_time->tm_sec));
        note_data.append("#");
        note_data.append(to_string(notion_id));
        if(type=='<') cout<<"Enter the destination date and time: dd/mm/yy_hh:mm";
        else if(type=='&') cout<<"Enter end date of the goal achieving: dd/mm/yy_hh:mm";
        else if(type=='@') cout<<"Enter a date of the event: dd/mm/yy_hh:mm";
        else if(type=='$') cout<<"Enter end date of the daily task: dd/mm/yy_hh:mm";
        if(type=='<'||type=='&'||type=='@'||type=='$') {
                note_data.append("|");
                printf("\033[14D");
                string to_append;
                cin>>to_append;
                note_data.append(to_append);
                if(type=='$') {
                        cout<<"\nEnter a time when you will do the task: hh:mm";
                        printf("\033[5D");
                        cin>>to_append;
                        note_data.append("\\");
                        note_data.append(to_append);
                }
        }
        file<<note_data<<endl;
        while(getline(cin,str)&&str.compare(".")) file<<"                        "<<str<<endl;
        cout<<"file saved!"<<endl;
        file.close();
        return 0;
}
