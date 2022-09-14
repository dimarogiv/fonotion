#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <vector>
using namespace std;
void show_help_info();
void init_notes();
vector<string> get_list_of_notes(short int n);
int last_note_id();
vector<string> get_note_by_id(int id);
void new_note(char type);
int main () {
        printf("\033[2J");
        show_help_info();
        bool exit_of_program;
        short int n=0;
        do{
                char type=getch();
                exit_of_program=1;
                printf("\033[2J\033[H");
                vector<string> note;
                switch(type){
                        case '.':
                                printf("task");
                                new_note(type);
                                break;
                        case 'x':
                                printf("task is done");
                                new_note(type);
                                break;
                        case '>':
                                printf("task is pushed");
                                new_note(type);
                                break;
                        case '<':
                                printf("task is scheduled");
                                new_note(type);
                                break;
                        case '-':
                                printf("task is canceled");
                                new_note(type);
                                break;
                        case '+':
                                printf("note");
                                new_note(type);
                                break;
                        case '*':
                                printf("important task");
                                new_note(type);
                                break;
                        case '&':
                                printf("goal");
                                new_note(type);
                                break;
                        case '$':
                                printf("daily task");
                                new_note(type);
                                break;
                        case '@':
                                printf("historical event");
                                new_note(type);
                                break;
                        case 'r':
                                printf("get a note by id\n\nenter an id: ");
                                int id;
                                cin>>id;
                                note=get_note_by_id(id);
                                for(int i=0;i<note.size();i++) cout<<note[i]<<endl;
                                getch();
                                break;
                        case 's':
                                printf("get list of the notes");
                                note=get_list_of_notes(n);
                                for(int i=0;i<note.size();i++) cout<<note[i]<<endl;
                                n=0;
                                getch();
                                break;
                        case 'q':
                                printf("exit");
                                exit_of_program=0;
                                break;
                        default:
                                if(type<='9'&&type>='0') n=type-48;
                                else printf("there is no such type, choose one of suggested!");
                                show_help_info();
                }
        }while(exit_of_program);
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
                        "\033[29;50H@ is historical event"
                        "\033[29;50Hr to read note by id"
                        "\033[25;50Hq to exit"
                        "\033[25;50Hs to show notes list");
}

int last_note_id(){
        string tmp,num;
        tmp=get_list_of_notes(0)[get_list_of_notes(0).size()-1];
        for (int i=0;i<5;i++)num[i]=tmp.c_str()[21+i];
        return stoi(num);
}

vector<string> get_list_of_notes(short int n){
        ifstream file;
        file.open ("file.txt");
        vector<string> somestring;
        string tmp;
        while(getline(file,tmp)) if(tmp[0]!=' '&&tmp[0]!='\0') for(int i=0;i<=n&&tmp[0]!='\0';i++) {
                somestring.push_back(tmp);
                getline(file,tmp);
        }
        file.close();
        return somestring;
}

vector<string> get_note_by_id(int id){
        ifstream file;
        file.open ("file.txt");
        string tmp,num="0";
        while(getline(file,tmp) && stoi(num)!=id) if(tmp!=""&&tmp[0]=='.') for(int i=0;i<5;i++) num[i]=tmp[21+i];     // replace tmp[0]=='.' by tmp[0]!=' ' after emptying the db
        vector<string> note;
        for(int i=0;tmp!="";i++){
                note.push_back(tmp);
                getline(file,tmp);
        }
        return note;
}

void new_note(char type){
        printf("\033[4;1H");
        string note_data;
        note_data.append(1,type);
        time_t ttime = time(0);
        tm *local_time = localtime(&ttime);
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
        int notion_id = last_note_id()+1;
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
        ofstream file;
        file.open("file.txt",ios_base::app);
        string str;
        for(int i=0;i<3;i++) file<<endl;
        file<<note_data<<endl;
        while(getline(cin,str)&&str.compare(".")) file<<"                        "<<str<<endl;
        printf("\033[2J\033[60;1Hfile saved!");
        file.close();
}
