void show_list(){
        char key;
        int pos;
        pos=0;
        printw("get list of the notes");
        move(0,0);
        refresh();
        printw("Enter a number of first strings to be showed: ");
        int n;
        while(!((n=(getch()-'0'))>=0&&n<=9));
        vector <string> list=get_list_of_notes(n);
        for(int i=pos;i<pos+60;i++) printw("%s\n",list[i].c_str());
        while((key=getch())!='q'){
                if(key==KEY_DOWN) pos++;
                else if(key==KEY_UP&&pos>0) pos--;
                for(int i=pos;i<pos+60;i++) printw("%s\n",list[i].c_str());
        }
        n=0;
        clear();
        refresh();
        go_to_pos(1,1);
        list=get_note("Home");
        for(int i=0;i<list.size();i++) printw("%s\n",list[i].c_str());
}
