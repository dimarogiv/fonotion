void edit_note() {
        go_to_pos(1,1);
                                         // man tcgetattr; man TERMIOS;
        clear();
        refresh();
        go_to_pos(1,1);
        vector<string> note=get_note("Home");
        for(int i=0;i<note.size();i++) printw("%s\n",note[i].c_str());
        char pressed;
        short x,y;
        x=1;
        y=1;
        go_to_pos(1,1);
        keypad(stdscr, TRUE);
        while(!(
                                nodelay(stdscr, TRUE),
                                (pressed=getch())==27&&
                                (getch()==-1)
               )){   // if ESC pressed exit of the loop 
                nodelay(stdscr, FALSE);
                switch(pressed){
                        case KEY_UP:
                                if(y>1){
                                        if(x>=note[--y].size()) x=note[y].size()-1;
                                }
                                break;
                        case KEY_DOWN:
                                if(y<note.size()){
                                        if(x>=note[++y].size()) x=note[y].size()-1;
                                }
                                break;
                        case KEY_RIGHT:
                                if(x<note[y].size()-1) x++;
                                break;
                        case KEY_LEFT:
                                if(x>1) x--;
                                else if(y>1) x=note[--y].size()-1;
                                break;
                        case KEY_BACKSPACE:
                                if(x>1) note[y].erase(note[y].begin()+(--x)); 
                                else{
                                        note.erase(note.begin()+y);
                                        x=note[--y].size()-1;
                                }
                                break;
                        case KEY_ENTER:
                                note.insert(note.begin()+(x=1,++y),"");
                                break;
                        default:
                                note[y].insert(note[y].begin()+(x++),pressed);
                }
                clear();
                refresh();
                go_to_pos(1,1);
                for(int i=0;i<note.size();i++) printw("%s\n",note[i].c_str());
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
                if("Home"==db[i].substr(27,db[i].size()-26)&&db[i][0]!=' '&&db[i][0]!='\0') {
                        ybpos=(++i);
                }
                if(ybpos>-1&&db[i][0]=='\0') yepos=i;
        }
        db.erase(db.begin()+ybpos,db.begin()+yepos);
        for(int i=ybpos;i<yepos;i++) db.insert(db.begin()+ybpos+i,note[i]);
        for(int a=ybpos;a<yepos;a++) for(int i=0;i<24;i++) db[a].insert(db[a].begin(),' ');
        ofstream file1;
        file1.open("file.txt");
        for(int i=0;i<db.size();i++) file1<<db[i]<<endl;
        file1.close();
}
