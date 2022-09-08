#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <chrono>
#include <ctime>
#include <conio.h>
using namespace std;
void show_help_info();
int main () {
        printf("\033[2J");
        show_help_info();
        ofstream file;
        file.open("file.txt",ios_base::app);
        string str;
        for(int i=0;i<3;i++) file<<endl;
        time_t ttime = time(0);
        tm *local_time = localtime(&ttime);
        char type;
        int notion_id = 83298;
        bool success;
        do{
                type=getch();
                success=1;
                printf("\033[2J\033[H");
                switch(type){
                        case '.':
                                printf("task");
                                break;
                        case 'x':
                                printf("task is done");
                                break;
                        case '>':
                                printf("task is pushed");
                                break;
                        case '<':
                                printf("task is scheduled");
                                break;
                        case '-':
                                printf("task is canceled");
                                break;
                        case '+':
                                printf("note");
                                break;
                        case '*':
                                printf("important task");
                                break;
                        case '&':
                                printf("goal");
                                break;
                        case '$':
                                printf("daily task");
                                break;
                        case '@':
                                printf("historical event");
                                break;
                        default:
                                printf("there is no such type, choose one of suggested!");
                                show_help_info();
                                success=0;
                }
        }while(!success);
        printf("\033[4;1H");
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
        printf("\033[2J\033[60;1Hfile saved!");
        file.close();
        return 0;
}


void show_help_info(){
        printf("\033[18;48HEnter a type of the note:"
                        "\033[20;50H. is a task"
                        "\033[21;50Hx means task is done"
                        "\033[22;50H> task is pushed"
                        "\033[23;50H< task is scheduled"
                        "\033[24;50H- task is canceled"
                        "\033[25;50H+ is note"
                        "\033[26;50H* is some very important task"
                        "\033[27;50H& is a goal"
                        "\033[28;50H$ is daily task"
                        "\033[29;50H@ is historical event");
}
