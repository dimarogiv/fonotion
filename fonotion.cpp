#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <vector>
using namespace std;
void clear_screen() {printf("\033[2J");}
void go_to_pos(int x, int y) {printf("\033[%d;%dH",y,x);}
void move_up(int n) {printf("\033[%dA",n);}
void move_down(int n) {printf("\033[%dB",n);}
void move_left(int n) {printf("\033[%dD",n);}
void move_right(int n) {printf("\033[%dC",n);}

void show_help_info();
void init_notes();
vector<string> get_list_of_notes(short int n);
int last_note_id();
vector<string> get_note_by_id(int id);
void new_note(char type);

int main () {
        clear_screen();
        show_help_info();
        bool exit_of_program;
        short int n=0;
        do{
                char type=getch();
                exit_of_program=1;
                clear_screen();
                go_to_pos(1,1);
                vector<string> note;
                string remove_spaces_tmp;
                int id;
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
                                cin>>id;
                                note=get_note_by_id(id);
                                for(int i=0;i<note.size();i++) cout<<note[i]<<endl;
                                getch();
                                break;
                        case 's':
                                char key;
                                int pos;
                                pos=0;
                                printf("get list of the notes");
                                note=get_list_of_notes(n);
                                for(int i=pos;i<pos+60;i++) cout<<note[i]<<endl;
                                while((key=getch())!='q'){
                                        if(key=='j') pos++;
                                        else if(key=='k'&&pos>0) pos--;
                                        for(int i=pos;i<pos+60;i++) cout<<note[i]<<endl;
                                }
                                n=0;
                                clear_screen();
                                go_to_pos(1,1);
                                show_help_info();
                                break;
                        case 'e':{                                                      // it should be an edit feature!
                                         go_to_pos(1,1);
                                         printf("edit note by id\n\nenter an id: ");   // man tcgetattr; man TERMIOS; conio.h->kbhit; firefox :tab 4
                                         cin>>id;
                                         clear_screen();
                                         go_to_pos(1,1);
                                         note=get_note_by_id(id);
                                         for(int i=0;i<note.size();i++) cout<<note[i]<<endl;
                                         char pressed;
                                         short x,y;
                                         x=1;
                                         y=1;
                                         go_to_pos(1,1);
                                         while(!((pressed=getch())==27&&kbhit()==0)){   // if ESC pressed exit of the loop 
                                                 if(kbhit()){
                                                         getch();
                                                         pressed=getch();
                                                         switch(pressed){
                                                                 case 'A':
                                                                         if(y>1){
                                                                                 if(x>=note[--y].size()) x=note[y].size()-1;
                                                                         }
                                                                         break;
                                                                 case 'B':
                                                                         if(y<note.size()){
                                                                                 if(x>=note[++y].size()) x=note[y].size()-1;
                                                                         }
                                                                         break;
                                                                 case 'C':
                                                                         if(x<note[y].size()-1) x++;
                                                                         break;
                                                                 case 'D':
                                                                         if(x>1) x--;
                                                                         else if(y>1) x=note[--y].size()-1;
                                                         }
                                                 } else if(pressed==127) {
                                                         if(x>1) note[y].erase(note[y].begin()+(--x)); 
                                                         else{
                                                                 note.erase(note.begin()+y);
                                                                 x=note[--y].size()-1;
                                                         }
                                                 } else if(pressed==10) note.insert(note.begin()+(x=1,++y),"");
                                                 else note[y].insert(note[y].begin()+(x++),pressed);
                                                 clear_screen();
                                                 go_to_pos(1,1);
                                                 for(int i=0;i<note.size();i++) printf("%s%c",note[i].c_str(),'\n');
                                                 go_to_pos(x,y);
                                         }
                                         ifstream file;
                                         file.open("file.txt");
                                         vector<string> db;
                                         string tmp;
                                         while(!file.eof()){
                                                 file>>tmp;
                                                 db.push_back(tmp);
                                         }
                                         file.close();
                                         int ybpos=-1,yepos;
                                         for(int i=0;i<db.size();i++){
                                                 if(id==stoi(db[i].substr(21,5))&&db[i][0]!=' '&&db[i][0]!='\0') {
                                                         ybpos=(++i);
                                                 }
                                                 if(ybpos>-1&&db[i][0]=='\0') yepos=i;
                                         }
                                         db.erase(db.begin()+ybpos,db.begin()+yepos);
                                         for(int i=0;i<yepos;i++) db.insert(db.begin()+ybpos+i,note[i]);
                                         for(int a=ybpos;a<yepos;a++) for(int i=0;i<24;i++) db[a].insert(db[a].begin(),' ');
                                         ofstream file1;
                                         file1.open("file.txt");
                                         for(int i=0;i<db.size();i++) file1<<db[i]<<endl;
                                         file1.close();
                                         show_help_info();
                                         break;
                                 }
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
        clear_screen();
        go_to_pos(1,60);
        printf("file saved!");
        file.close();
}
