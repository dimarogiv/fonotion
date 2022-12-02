#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>
#include <ncurses.h>
using namespace std;
void clear_screen() {printf("\033[2J\033[H");}
void go_to_pos(int x, int y) {printf("\033[%d;%dH",y,x);}
void move_up(int n) {printf("\033[%dA",n);}
void move_down(int n) {printf("\033[%dB",n);}
void move_left(int n) {printf("\033[%dD",n);}
void move_right(int n) {printf("\033[%dC",n);}

void show_help_info();
void init_notes();
vector<string> get_list_of_notes(short int n);
int last_note_id();
vector<string> get_note(int id);
vector<string> get_note(string);
void new_note(char type);
#include "list.h"
#include "edit.h"

int main () {
        initscr();
        keypad(stdscr, TRUE);
        noecho();
        cbreak();
        refresh();

        bool exit_of_program;
        short int n=0;
        vector<int> branch;
        vector<string> note = get_note("Home");
        for(int i=0;i<note.size();i++) printw("%s%c",note[i].c_str(),'\n');
        do{
                char command=getch();
                exit_of_program=1;
                clear();
                move(0,0);
                refresh();
                string remove_spaces_tmp;
                int id;
                switch(command){
                        case KEY_UP:
                                move_up(1);
                                break;
                        case KEY_DOWN:
                                move_down(1);
                                break;
                        case KEY_RIGHT:
                                move_right(1);
                                break;
                        case KEY_LEFT:
                                move_left(1);
                                break;
                        case 's':
                                show_list();
                                break;
                        case 'e':                                                      // it should be an edit feature!
                                edit_note(); 
                        case 'q':
                                exit_of_program=0;
                                break;
                        default:
                                if(command<='9'&&command>='0') n=command-'0';
                                else printw("%c %d there is no such command, choose one of suggested!", command, (int)command);
                }
        }while(exit_of_program);
        endwin();
        return 0;
}

void show_help_info(){
        go_to_pos(48,18);
        printf("Enter a type of the note:");
        go_to_pos(50,20);
        printf(".is a task");
        go_to_pos(50,21);
        printf("x means task is done");
        go_to_pos(50,22);
        printf("> task is pushed");
        go_to_pos(50,23);
        printf("< task is scheduled");
        go_to_pos(50,24);
        printf("- task is canceled");
        go_to_pos(50,25);
        printf("+ is a note");
        go_to_pos(50,26);
        printf("*is some very important task");
        go_to_pos(50,27);
        printf("&is a goal");
        go_to_pos(50,28);
        printf("$is a daily task");
}

int last_note_id(){
        string tmp,num;
        tmp=get_list_of_notes(0)[get_list_of_notes(0).size()-1];
        for (int i=0;i<5;i++)num[i]=tmp.c_str()[22+i];
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

vector<string> get_note(int id){
        ifstream file;
        file.open ("file.txt");
        string tmp,num="00000";
        while(getline(file,tmp) && stoi(num)!=id) {
                if(tmp!=""&&tmp[0]!=' ') 
                        for(int i=0;i<5;i++) num[i]=tmp[21+i];     // replace tmp[0]=='.' by tmp[0]!=' ' after emptying the db
        }
        vector<string> note;
        for(int i=0;tmp!="";i++){
                note.push_back(tmp);
                getline(file,tmp);
        }
        for(int i=0;i<note.size();i++) note[i].erase(note[i].begin(),note[i].begin()+24);
        return note;
}

vector<string> get_note(string name){
        ifstream file;
        file.open ("file.txt");
        string tmp,current_name="0";
        while(getline(file,tmp) && current_name!=name) {
                current_name.erase();
                if(tmp!=""&&tmp[0]!=' '&&tmp.size()>26) current_name=tmp.substr(27,tmp.size()-26);
        }
        vector<string> note;
        for(int i=0;tmp!="";i++){
                note.push_back(tmp);
                getline(file,tmp);
        }
        for(int i=0;i<note.size();i++) note[i].erase(note[i].begin(),note[i].begin()+24);
        return note;
}

void new_note(char type){
        go_to_pos(1,4);
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
                move_left(14);
                string to_append;
                cin>>to_append;
                note_data.append(to_append);
                if(type=='$') {
                        cout<<"\nEnter a time when you will do the task: hh:mm";
                        move_left(5);
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
        clear();
        refresh();
        go_to_pos(1,60);
        printf("file saved!");
        file.close();
}
