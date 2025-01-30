#ifndef FUNCTION_H
#define FUNCTION_H
#define SUDOKU_SIZE 9

#include <iostream>     // libraries
#include <fstream>
#include <string>
#include "clui.h"
#include <iomanip> 
#include <thread>
#include <chrono>
#include <ctime>
#include <stack>

using namespace std;

struct c_user_game{  //structures
    string name;
    int score;
    int num_false;
    bool game_stat;
    int remaining_time;
}player;
struct all_game_player{
    string name;
    int total_wins;
    int total_losses;
    all_game_player* next=NULL;
}player_history;

int row = get_window_rows();        //define global variables
int col = get_window_cols() * 5 / 6;
string USERNAME = "";
const int MAX_USERS = 100;
int printer_timer=0;
bool timer=false;
bool stop_timer=false;
bool done = false;
int num_false=0;
int seconds=0;
int final_user=0;
string userr;
char mode_win;
int score_=0;
int game_num;
int hint_num;
stack<int> stack_i;
stack<int> stack_j;


void show_leaderboard();
void write_to_file(const c_user_game& user);
void calculate_total_wins_losses(c_user_game users[], int numUsers);
void print_all_players(all_game_player all_players[], int numUsers);
void load_sudoku(const string&, int**);
void print_sudoku(int**);
void edit_sudoku(int**,double,int,char);
void time_counter(double);
void go_save(char mode,int num_false,int seconds,int** sudoku);
void get_user(string);
int welcom();
int signup();
int check_username(string);
int welcom_page();
int start_game();
int login();
int level();
int save_game();
int get_userprofiles(c_user_game*);
int game(int** sudoku,char mode,int,int);
bool is_true_entry(int i,int j,char mode,int entry);
bool check_save_name(string save_name);
void change_sudoku(int**,char);
int** gen(char);
void select_main_sudoku(char mode);
void hint_sudoku(int**,int**);
c_user_game read_from_file();
c_user_game users[MAX_USERS];
all_game_player* all_players=new all_game_player;






int welcom_page() {
    clear_screen();
    char input;
    welcom();
    do {
        cin >> input;
        switch (input) {
            case '1':
                clear_screen();
                delay(400);
                login();
                break;
            case '2':
                clear_screen();
                delay(400);
                signup();
                break;
            case '3':
                clear_screen();
                delay(400);
                quit();
                break;
            case 'q':
                clear_screen();
                delay(400);
                quit();
                break;
            default:
                clear_screen();
                welcom();
                cursor_to_pos(row / 2 + 3, col / 2 - 1);
                change_color_rgb(121, 140, 209);
                cout << "invalid input try again!";
                reset_color();
                cursor_to_pos(row / 2 + 1, col / 2 + 25);
                change_color_rgb(109, 237, 220);
                break;
        }
    } while (input != '1' && input != '2' && input != '3' && input != 'q');
    return 1;
}

int welcom() {
    cursor_to_pos(row / 2 - 5, col / 2);
    change_color_rgb(109, 237, 220);
    cout << "Welcome To ";
    change_color_rgb(193, 245, 238);
    cout << "9x9";
    change_color_rgb(109, 237, 220);
    cout << " Sudoku Game" << endl;
    reset_color();
    change_color_rgb(121, 140, 209);
    cursor_to_pos(row / 2 - 3, col / 2);
    cout << "1.Login";
    cursor_to_pos(row / 2 - 2, col / 2);
    cout << "2.Sign Up";
    cursor_to_pos(row / 2 - 1, col / 2);
    cout << "3.Exit";
    reset_color();
    cursor_to_pos(row / 2 + 1, col / 2 - 1);
    cout << "Please Enter Your Choice: ";

    return 1;
}

int signup() {
    string username = "";
    while (username.length() == 0) {
        delay(400);
        cursor_to_pos(row / 2 - 5, col / 2);
        change_color_rgb(109, 237, 220);
        cout << "Welcome To ";
        change_color_rgb(193, 245, 238);
        cout << "9x9";
        change_color_rgb(109, 237, 220);
        cout << " Sudoku Game" << endl;
        reset_color();
        change_color_rgb(121, 140, 209);
        cursor_to_pos(row / 2 - 3, col / 2);
        cout << "Enter Your Username: ";
        reset_color();
        getline(cin, username);
    }
    check_username(username);
    return 1;
}

int check_username(string username) {
    ifstream file("UserNames/UserNames.txt");
    string line;
    int number_of_lines = 0;
    for(int i;i<username.length();i++){
        if(username[i]==' '){
            cursor_to_pos(row / 2 - 1, col / 2 );
            cout << "Username shoudn't contain spaces" << endl;
            delay(2000);
            welcom_page();
            return 0;
        }
    }
    while (getline(file, line)) {
        number_of_lines++;
        if (line == username) {
            cursor_to_pos(row / 2 - 1, col / 2 - 15);
            cout << "Username already exists. Please choose a different username." << endl;
            delay(2000);
            ifstream game_num_file("game_num.txt");
            string line;
            int game_number;
            int shomar=0;
            while (getline(game_num_file, line)) {
                shomar++;
                if (shomar == number_of_lines) {
                    line = to_string(stoi(line) + 1);
                    break;
                }
            }
            game_num_file.close();
            

            welcom_page();
            return 0;
        }
    }
    file.close();
    ofstream outfile("UserNames/UserNames.txt", ios::app);
    outfile << username << endl;
    outfile.close();
    USERNAME = username;
    clear_screen();
    delay(400);
    cursor_to_pos(row / 2 - 5, col / 2);
    change_color_rgb(109, 237, 220);
    cout << "Welcome To ";
    change_color_rgb(193, 245, 238);
    cout << "9x9";
    change_color_rgb(109, 237, 220);
    cout << " Sudoku Game" << endl;
    reset_color();
    change_color_rgb(121, 140, 209);
    cursor_to_pos(row / 2 - 3, col / 2);
    cout << "Enter Your Password: ";
    reset_color();
    string password;
    getline(cin, password);
    ofstream outfile1("UserNames/UserPassword.txt",ios::app);
    outfile1 << password <<endl;
    outfile1.close();
    start_game();
    return 1;
}

int login() {
    string username = "";
    while (username.length() == 0) {
        delay(400);
        cursor_to_pos(row / 2 - 5, col / 2);
        change_color_rgb(109, 237, 220);
        cout << "Welcome To ";
        change_color_rgb(193, 245, 238);
        cout << "9x9";
        change_color_rgb(109, 237, 220);
        cout << " Sudoku Game" << endl;
        reset_color();
        change_color_rgb(121, 140, 209);
        cursor_to_pos(row / 2 - 3, col / 2);
        cout << "Enter Your Username: ";
        cursor_to_pos(row / 2 - 2, col / 2);
        cout << "Enter Your Password: ";
        reset_color();
        cursor_to_pos(row / 2 - 3, col / 2+ 22);
        getline(cin, username);
    }
    ifstream file("UserNames/UserNames.txt");
    string line;
    int num=0;
    while (getline(file, line)) {
        num++;
        if (line == username) {
            USERNAME = username; //
            string password="";
        
            cursor_to_pos(row / 2 - 2, col / 2+ 22);
            getline(cin,password);
            ifstream file1("UserNames/UserPassword.txt");
            string line2;
            int num1=0;
            while(getline(file1,line2)){
                num1++;

                if(num1==num && line2==password){
                    file1.close();
                    start_game();
                }
                else if(num1==num){
                    file1.close();
                    cursor_to_pos(row / 2 , col / 2);
                    change_color_rgb(255,0,0);
                    cout<<"Wrong Password Please Try Agian";
                    delay(3000);
                    clear_screen();
                    login();
                }
            }

            //start_game();
            
            return 1;
        }
    }
    file.close();
    cursor_to_pos(row / 2 - 1, col / 2 - 4);
    cout << "Username does not exist. Please sign up." << endl;
    delay(2000);
    
    welcom_page();
    return 0;
}

int start_game() {
    get_user(USERNAME); 
    clear_screen();
    cursor_to_pos(row / 2 - 11, col / 2);
    change_color_rgb(240, 255, 31);
    cout << "IN HIS SUBLIME NAME" << endl;
    cursor_to_pos(row / 2 - 10, col / 2 + 1);
    change_color_rgb(28, 240, 17);
    cout << "Let's Play Sudoku" << endl;
    cursor_to_pos(row / 2 - 9, col / 2 + 2);
    change_color_rgb(43, 73, 224);
    cout << "<Game Options>" << endl;

    cursor_to_pos(row / 2 - 7, col / 10);
    change_color_rgb(15, 237, 245);
    cout << "You Logged In As " << USERNAME << endl;
    reset_color();
    cursor_to_pos(row / 2 - 5, col / 10);
    change_color_rgb(121, 140, 209);
    cout << "1. Start Game" << endl;
    cursor_to_pos(row / 2 - 4, col / 10);
    change_color_rgb(121, 140, 209);
    cout << "2. Play Saved Game" << endl;
    cursor_to_pos(row / 2 - 3, col / 10);
    change_color_rgb(121, 140, 209);
    cout << "3. Check LeaderBoard" << endl;
    cursor_to_pos(row / 2 - 2, col / 10);
    change_color_rgb(121, 140, 209);
    cout << "4. Exit Game" << endl;
    char input;
    cursor_to_pos(row / 2 , col / 10);
    cout<<"Please Enter Your Choice: ";
    cin >> input;
    reset_color();
    switch (input) {
        case '1':
            clear_screen();
            delay(400);
            level();
            break;
        case '2':
            clear_screen();
            delay(400);
            save_game();
            break;
        case '3':
            clear_screen();
            delay(400);
            show_leaderboard();
            break;
        case '4':
            clear_screen();
            delay(400);
            quit();
            break;
        default:
            clear_screen();
            start_game();
            break;
    }
    return 1;
}

int level() {
    clear_screen();
    delay(400);
    cursor_to_pos(row / 2 - 5, col / 2);
    change_color_rgb(109, 237, 220);
    cout << "Select difficulty level: ";
    reset_color();
    change_color_rgb(121, 140, 209);
    cursor_to_pos(row / 2 - 3, col / 2);
    cout << "1. Easy";
    cursor_to_pos(row / 2 - 2, col / 2);
    cout << "2. Normal";
    cursor_to_pos(row / 2 - 1, col / 2);
    cout << "3. Hard";
    reset_color();
    cursor_to_pos(row / 2 + 1, col / 2 - 1);
    cout << "Please Enter Your Choice: ";
    char input;
    cin >> input;
    //get_user(USERNAME);   
    int** sudoku_e = new int*[SUDOKU_SIZE];
    int** sudoku_n = new int*[SUDOKU_SIZE];
    int** sudoku_h = new int*[SUDOKU_SIZE];
    for (int i = 0; i < SUDOKU_SIZE; ++i) {
        sudoku_e[i] = new int[SUDOKU_SIZE];
        sudoku_n[i] = new int[SUDOKU_SIZE];
        sudoku_h[i] = new int[SUDOKU_SIZE];
    }

    switch (input) {
        case '1':
            clear_screen();
            delay(400);

            select_main_sudoku('e');
            change_sudoku(gen('e'),'e');
            hint_num=5;
            load_sudoku("sudoku tables/easy.txt", sudoku_e);
            //get_user(USERNAME);
            game(sudoku_e,'e',0,300);

            break;
        case '2':
            clear_screen();
            delay(400);
             select_main_sudoku('n');
            hint_num=3;

            change_sudoku(gen('n'),'n');


            load_sudoku("sudoku tables/normal.txt", sudoku_n);
            game(sudoku_n,'n',0,180);

            break;
        case '3':
            clear_screen();
            delay(400);
             select_main_sudoku('h');
            hint_num=2;

            change_sudoku(gen('h'),'h');


            load_sudoku("sudoku tables/hard.txt", sudoku_h);
            game(sudoku_h,'h',0,120);

            break;
        default:
            clear_screen();
            level();
            break;
    }

    for (int i = 0; i < SUDOKU_SIZE; ++i) {
        delete[] sudoku_e[i];
        delete[] sudoku_n[i];
        delete[] sudoku_h[i];
    }
    delete[] sudoku_e;
    delete[] sudoku_n;
    delete[] sudoku_h;
    


    return 1;
}

int save_game() {
    char mode;
    int num_false;
    int seconds;
    cursor_to_pos(row / 2 - 5, col / 2);
    change_color_rgb(109, 237, 220);
    cout << "Select ";
    change_color_rgb(193, 245, 238);
    cout << "Save";
    change_color_rgb(109, 237, 220);
    cout << " Game" << endl;
    reset_color();
    int i=0;
    int input;
    ifstream save_name_bar("save game/name.txt");
    string line;
    while (getline(save_name_bar, line)) {
        i++;
        cursor_to_pos(row / 2 + 1 + i, col / 2 - 1);
        cout<<i<<". "<<line<<endl;
    }
    cursor_to_pos(row / 2 + 1 + i+1, col / 2 - 1);
    cout<<"press 100 to back";
        if(i==0){
        clear_screen();
        delay(400);
        cursor_to_pos(row / 2 + 1, col / 2 - 1);
        cout<<"There is no saved game"<<endl;
        delay(2000);
        start_game();
        return 0;
    }
    cursor_to_pos(row / 2 + 1 + i + 2, col / 2 - 1);
    cout << "Please Enter Your Choice: ";
    cin>>input;
    if(input==100){
        start_game();
        return 1;
    }
    input-=1;
    i=0;
    save_name_bar.close();
    ifstream mode_bar("save game/mode.txt");
    while (getline(mode_bar, line)) {
        
        if(i==input){
            mode=line[0];
        }
        i++;
    }
    mode_bar.close();
    ifstream remain_time_bar("save game/remain_time.txt");
    i=0;

    while (getline(remain_time_bar, line)) {
        
        if(i==input){
            seconds=stoi(line);
        }
        i++;
    }
    remain_time_bar.close();
    string userrr;
    
    ifstream save_user_bar("save game/username.txt");
    i=0;
    while (getline(save_user_bar, line)) {
        
        if(i==input){
            // cout<<line<<endl;
            // cout<<i;
            // delay(10000);
            userrr=line;
        }
        i++;
    }



    if(userrr!=USERNAME){
        save_game();
    }

    ifstream save_hint_bar("save game/hint.txt");
    i=0;
    while (getline(save_hint_bar, line)) {
        
        if(i==input){
            // cout<<line<<endl;
            // cout<<i;
            // delay(10000);
            hint_num=stoi(line);
        }
        i++;
    }



    save_hint_bar.close();
    // cout<<userrr<<endl;
    // cout<<USERNAME<<endl;
    // delay(10000);

    ifstream mistakes_bar("save game/mistakes.txt");
    i=0;
    int j=0;
    while (getline(mistakes_bar, line)) {
        if(i==input){
            num_false=stoi(line);
        }
                i++;

    }
    mistakes_bar.close();

    int** sudoku = new int*[SUDOKU_SIZE];
    for (int i = 0; i < SUDOKU_SIZE; ++i) {
        sudoku[i] = new int[SUDOKU_SIZE];
    }
    ifstream soduku_bar("save game/sudoku.txt");
    i=0;
    j=0;
//game_num//line
// line
    while (getline(soduku_bar, line)) {
        if(i-1==input){
            if(j!=9){
                for (int k = 0; k < SUDOKU_SIZE*2; k+=2) {
                    // cout<<line[k]-48;
                    sudoku[j][k/2]=line[k]-'0';
                    // cout<<line[k];
                }
                // cout<<endl;
                j++;
            }
            }
            if(line[0]=='s'){
            i++;
        }
        }
    soduku_bar.close();

    
    string mode_name;
    switch(mode){
        case 'e':
            mode_name="easy";
            break;
        case 'n':
            mode_name="normal";
            break;
        case 'h':
            mode_name="hard";
            break;
        default:
            break;
    }

    string file_name="sudoku tables/"+mode_name+"_a.txt";
    ifstream sourceFile("save game/sudoku_a.txt");
    ofstream destinationFile(file_name,ios::trunc);
    char ch;
    while (sourceFile.get(ch)) {
        destinationFile.put(ch);
    }
    sourceFile.close();
    destinationFile.close();

    

    game(sudoku,mode,num_false,seconds);
    return 1;
    }








void show_leaderboard() {
    int numUsers = get_userprofiles(users);
    // Sort the array of profiles by score in descending order
    for (int i = 0; i < numUsers - 1; i++) {
        for (int j = i + 1; j < numUsers; j++) {
            if (users[i].score < users[j].score) {
                c_user_game temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
            else if( users[i].score == users[j].score && users[i].remaining_time < users[j].remaining_time){
                c_user_game temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }

    // Print the leaderboard
    cout << "Leaderboard:" << endl;
    cout << "----------" << endl;
    for (int i = 0; i < numUsers; i++) {
        cout << (i + 1) << ". " << users[i].name << endl;
        cout << "  Score: " << users[i].score << endl;
        cout <<"  Num False: " << users[i].num_false << endl;
        cout << "  Game Stat: " << (users[i].game_stat ? "Win": "Lose") << endl;
        cout <<"  Remaining Time: "<< users[i].remaining_time << endl;
        cout <<endl;
    }
    calculate_total_wins_losses(users,numUsers);
    // cout<<"sa";
    // delay(10000);
    print_all_players(all_players,final_user);
    delete all_players;
    all_players=new all_game_player;
    int input;
    input=getch();
    switch(input){
        case 27:
        quit();
        break;
        case 109:
        start_game();
        break;
        default:
        quit();
        break;
        
    }
}

void load_sudoku(const string& filename, int** sudoku) {
    ifstream file(filename);
    for (int i = 0; i < SUDOKU_SIZE; ++i) {
        for (int j = 0; j < SUDOKU_SIZE; ++j) {
            file >> sudoku[i][j];
        }
    }
    file.close();
}


void print_sudoku(int** sudoku) {
    
    const int padding = 40;
    string padding_str(padding, ' ');
    cout << "\n\n\n\n\n\n" << endl;
    cout << padding_str << "-------------------------" << endl;
    for (int i = 0; i < SUDOKU_SIZE; ++i) {
        cout << padding_str;
        for (int j = 0; j < SUDOKU_SIZE; ++j) {
            if (j % 3 == 0) cout << "| ";
            if (sudoku[i][j] == 0)
                cout << "  ";
            else{
                change_color_rgb(121, 140, 209);
                cout << sudoku[i][j] << " ";
                reset_color();
            }
                
        }
        cout << "|" << endl;
        if ((i + 1) % 3 == 0 && i != SUDOKU_SIZE - 1)
            cout << padding_str << "|-------|-------|-------|" << endl;
    }
    cout << padding_str << "-------------------------" << endl;
    cursor_to_pos(4,46);
    cout<<"Hint Left: "<<hint_num<<endl;
    if (timer==true){
        int seconds=printer_timer;
        int mins = seconds / 60;
        int secs = seconds % 60; 
        cursor_to_pos(5,46);
        cout << "Time left: " << setw(2) << setfill('0') << mins
                  << ":" << setw(2) << setfill('0') << secs << "\n";}
}

void edit_sudoku(int** sudoku,double timee,int num_falses,char mode) {
    int** answer;
    answer=new int*[SUDOKU_SIZE];
    for (int i = 0; i < SUDOKU_SIZE; ++i) {
        answer[i]=new int[SUDOKU_SIZE];
    }
    switch (mode) {
        case 'e':
            load_sudoku("sudoku tables/easy_a.txt", answer);
            break;
        case 'n':
            load_sudoku("sudoku tables/normal_a.txt", answer);
            break;
        case 'h':
            load_sudoku("sudoku tables/hard_a.txt", answer);
            break;
        default:
            break;
    }


    int row = 0, col = 0;
    char input;
    done = false;
    stop_timer=true;
    num_false=num_falses;
    timer=true;
    while (!done && num_false<=5) {
        int winner=0;
        for(int i=0;i<SUDOKU_SIZE;i++){
            for(int j=0;j<SUDOKU_SIZE;j++){
                if(sudoku[i][j]<=9 && sudoku[i][j]>=1){
                    winner++;
                    
                }
        }}
        if(winner==81){
            done=true;
            stop_timer=false;
            clear_screen();
            print_sudoku(sudoku);
            change_color_rgb(0,255,0);
            cursor_to_pos(6,42);
            cout<<"CONGRATULATIONS YOU WON!!";
            player.name=userr;
            player.score=score_;
            player.num_false=num_false;
            player.game_stat=true;
            player.remaining_time=seconds;
            write_to_file(player);
            reset_color();
            delay(1500);
            show_leaderboard();
            break;
        }
        if(input!=72 && input!=80 && input!=75 || input!=77){
        clear_screen();
        print_sudoku(sudoku);}
        if(num_false>0){
                    change_color_rgb(255,0,0);
                    cursor_to_pos(6,42);
                    cout<<"MISSED ONE!!!! remains:"<<5-num_false;
                    reset_color();
        }

        if(row>=6 && col>=6){
            
            change_character_background(9 + row + 2, 43 + col *2 + 4,255,255,0);
            cout<<".";
            reset_background_colors();
        }
        else if(row>=6 && col>=3){
            change_character_background(9 + row + 2, 43 + col *2+2,255,255,0);
            cout<<".";
            reset_background_colors();

        }
        else if(row>=6 && col>=0){
            change_character_background(9 + row + 2 , 43 + col *2,255,255,0);
            cout<<".";
            reset_background_colors();

        }
        else if(row>=3 && col>=6){
            change_character_background(9 + row + 1 , 43 + col *2 +4,255,255,0);
            cout<<".";
            reset_background_colors();
        }
        else if(row>=3 && col>=3){
            change_character_background(9 + row + 1 , 43 + col *2+2,255,255,0);
            cout<<".";
            reset_background_colors();


        }
        else if(row>=3 && col>=0){
            change_character_background(9 + row + 1 , 43 + col *2,255,255,0);
            cout<<".";
            reset_background_colors();

        }
        else if(row>=0 && col>=6){
            change_character_background(9 + row  , 43 + col *2+4,255,255,0);
            cout<<".";
            reset_background_colors();

        }
        else if(row>=0 && col>=3){
            change_character_background(9 + row  , 43 + col *2+2,255,255,0);
            cout<<".";
            reset_background_colors();

        }
        else if(row>=0 && col>=0){
            change_character_background(9 + row  , 43 + col *2+0,255,255,0); //(int row, int col, int r, int g, int b)
            cout<<".";
            reset_background_colors();
        
        }

        input = getch();

        switch (input) {
            case 72: // Up arrow key
                if (row > 0) {
                    row--;
                    
                }
                break;
            case 80: // Down arrow key
                if (row <SUDOKU_SIZE -1) {
                    row++;
                }
                break;
            case 75: // left arrow key
                if (col > 0) {
                    col--;
                }
                break;
            case 77: // right arrow key
                if (col < SUDOKU_SIZE-1) {
                    col++;
                }
                break;
            case '0' ... '9': // number keys
                if (sudoku[row][col] == 0 && is_true_entry(row,col,mode,input-'0')) {
                    sudoku[row][col] = input - '0';
                    score_++;
                    stack_i.push(row);
                    stack_j.push(col);
                }
                else if(!is_true_entry(row,col,mode,input-'0') && sudoku[row][col] == 0){
                    num_false++;
                    score_--;
                }
                break;
            case 104 : //h key:
                if(hint_num>0){
                hint_num--;
                hint_sudoku(sudoku,answer);   ////
                cursor_to_pos(4,46);
                cout<<"Hint Left: "<<hint_num<<endl;}
                break;
            case 27: // escape key
                input=0;
                timer=false;
                while(input!= 27){
                clear_screen();
                int rows = get_window_rows();
                int cols = get_window_cols() * 5 / 6;
                change_color_rgb(255,0,0);
                cursor_to_pos(rows/2,cols/2);
                cout<<"YOU PAUSED THE GAME!";
                cursor_to_pos(rows/2+1,cols/2);
                cout<<"Press ESC to continue";
                reset_color();
                input = getch();
                if(input==27){
                    timer=true;
                    break;
                }
                }
                break;
            case 115: // s for save
                timer=false;
                stop_timer=false;
                delay(400);
                go_save(mode,num_false,seconds,sudoku);
                break;
            case 117: // u for undo
                row=stack_i.top();
                col=stack_j.top();
                sudoku[row][col]=0;
                stack_i.pop();
                stack_j.pop();
                score_--;
                break;
            default:
                break;
        }
    }
    timer=false;
    clear_screen();
    player.name=userr;
    player.score=score_;
    player.num_false=num_false;
    player.game_stat=false;
    player.remaining_time=seconds;
    write_to_file(player);
    delay(400);
    int rowss = get_window_rows();
    int colss = get_window_cols() * 5 / 6;
    change_color_rgb(255,0,0);
    cursor_to_pos(rowss/2,colss/2);
    cout<<"YOU LOST THE GAME!";
    cursor_to_pos(rowss/2+1,colss/2);
    cout<<"Press ESC to EXIT";
    reset_color();
    delay(5000);

    start_game();
}


int game(int** sudoku,char mode,int num_falses,int timee) {
    print_sudoku(sudoku);

    thread edit_sudoku_thread([sudoku, timee,num_falses,mode]() {
        edit_sudoku(sudoku, timee,num_falses,mode);
    });   
    thread print_time_thread([timee]() {
        time_counter(timee);
    });
    edit_sudoku_thread.join();
    print_time_thread.join();

    return 1;
}

void time_counter(double minutes) {
    seconds =(int)( minutes );
    delay(300);
    while (seconds >= 0 && stop_timer==true) {
        if(timer==true){
        int mins = seconds / 60;
        int secs = seconds % 60; 
        printer_timer=seconds;
        cursor_to_pos(5,46);
        cout << "Time left: " << setw(2) << setfill('0') << mins
                  << ":" << setw(2) << setfill('0') << secs << "\n";

        this_thread::sleep_for(chrono::seconds(1)); 
        seconds--;
        printer_timer=seconds;
        if(seconds==0){
            stop_timer=false;
            done=true;
        }
                    }
                    
    }
    if(seconds>0){
    done=true;
        
    }

}
bool is_true_entry(int i,int j,char mode,int entry){
    int** answer;
    answer=new int*[SUDOKU_SIZE];
    for (int i = 0; i < SUDOKU_SIZE; ++i) {
        answer[i]=new int[SUDOKU_SIZE];
    }
    switch (mode) {
        case 'e':
            load_sudoku("sudoku tables/easy_a.txt", answer);
            break;
        case 'n':
            load_sudoku("sudoku tables/normal_a.txt", answer);
            break;
        case 'h':
            load_sudoku("sudoku tables/hard_a.txt", answer);
            break;
        default:
            break;
    }
    if(answer[i][j]==entry){
        for (int i = 0; i < SUDOKU_SIZE; ++i) {
        delete answer[i];
        }
        delete[] answer;
        return true;
    }
    else{
        for (int i = 0; i < SUDOKU_SIZE; ++i) {
        delete answer[i];
        }
        delete[] answer;
        return false;
    }
}
void go_save(char mode,int num_falses,int seconds,int** sudoku){
    string save_name="";
    clear_screen();
    int row = get_window_rows();
    int col = get_window_cols() ;
    change_color_rgb(121, 140, 209);
    cursor_to_pos(row / 2 , col / 2);
    cout<<"Please Select Save Name For Your Game:";
    cin.ignore();
    getline(cin,save_name);
    if (!(check_save_name(save_name))){
        delay(4000);
        go_save(mode,num_falses,seconds,sudoku);
        return;
    }
    else{
        ofstream mo("save game/mode.txt", ios::app);
        mo << mode << endl;
        mo.close();

        ofstream ho("save game/hint.txt", ios::app);
        ho << hint_num << endl;
        ho.close();
        // ofstream outfile("save game/remain_time.txt", ios::app);
        ofstream rem("save game/remain_time.txt", ios::app);
        rem << seconds << endl;
        rem.close();
        
        ofstream mis("save game/mistakes.txt", ios::app);
        mis << num_false << endl;
        mis.close();

        
        ofstream save_username("save game/username.txt", ios::app);
        save_username << userr << endl;
        save_username.close();

        ofstream score_save("save game/score.txt", ios::app);
        score_save << score_ << endl;
        score_save.close();

        ofstream sudo("save game/sudoku.txt", ios::app);
        for (int i = 0; i < SUDOKU_SIZE; ++i) {
            for (int j = 0; j < SUDOKU_SIZE; ++j) {
                sudo << sudoku[i][j] << " ";
            }
            sudo << endl;


        }
            sudo << "s";
            sudo << endl;
        sudo.close();

        
        
    string mode_name;
    switch(mode){
        case 'e':
            mode_name="easy";
            break;
        case 'n':
            mode_name="normal";
            break;
        case 'h':
            mode_name="hard";
            break;
        default:
            break;
    }
    string file_name="sudoku tables/"+mode_name+"_a.txt";
    ifstream sourceFile(file_name);
    ofstream destinationFile("save game/sudoku_a.txt",ios::trunc);
    char ch;
    while (sourceFile.get(ch)) {
        destinationFile.put(ch);
    }
    sourceFile.close();
    destinationFile.close();

        quit();
        return;
    }


}
bool check_save_name(string save_name) {
    ifstream file("save game/name.txt");
    string line;
    int row = get_window_rows();
    int col = get_window_cols() * 5 / 6;

    while (getline(file, line)) {
        if (line == save_name) {
            cursor_to_pos(row / 2 , col / 2);
            cout << "This Name already exists. Please choose a different Name." << endl;
            delay(2000);
            file.close();
            return false;
        }
    }
    file.close();
    ofstream outfile("save game/name.txt", ios::app);
    outfile << save_name << endl;
    outfile.close();
    return true;
}

int get_userprofiles(c_user_game* users) {
    int numUsers = 0;

    ifstream leader("user_profiles.txt");
    if (leader.is_open()) {
        ifstream user_profile_R("user_profiles.txt");
        while (user_profile_R.peek() != EOF && numUsers < MAX_USERS) {
            c_user_game user;
            if (user_profile_R.is_open() && leader.peek() != EOF) {

                user_profile_R >> user.name;


                user_profile_R >> user.score;
                user_profile_R >> user.num_false;
                int temp;
                user_profile_R >> temp;
                user.game_stat = (temp == 1); 
                user_profile_R >> user.remaining_time;
                
            }

            users[numUsers] = user;
            numUsers++;

            user_profile_R.ignore(2); // Ignore the empty line
        }
        numUsers--;
        // user_profile_R.close();
        leader.close();
        
    }
    return numUsers;
}

void get_user(string a){
    userr=a;
}

void write_to_file(const c_user_game& user) {
    ofstream user_profile("user_profiles.txt", ios_base::app);
    if (user_profile.is_open()) {
        user_profile << user.name << "\n";
        user_profile << user.score << "\n";
        user_profile << user.num_false << "\n";
        user_profile << user.game_stat << "\n";
        user_profile << user.remaining_time << "\n\n\n";
        user_profile.close();
    }
}


c_user_game read_from_file() {
    c_user_game user;
    ifstream user_profile_R("user_profiles.txt");
    if (user_profile_R.is_open()) {
        user_profile_R >> user.name;
        user_profile_R >> user.score;
        user_profile_R >> user.num_false;
        int temp;
        user_profile_R >> temp;
        user.game_stat = (temp == 1); 
        user_profile_R >> user.remaining_time;
        user_profile_R.close();
    }
    return user;
}

void calculate_total_wins_losses(c_user_game userss[], int s) {
    all_game_player* temp=all_players;
    for (int i=0; i <s;i++) {
        bool found= false;
        while (temp->next!=NULL) {
            if (temp->name == userss[i].name) {
                found = true;
                if (userss[i].game_stat) {
                    temp->total_wins++;
                } else {
                    temp->total_losses++;
                }
                break;
            }
            temp=temp->next;
        }
        if (!found) {
          //  cout<<"s"<<endl;
            temp->name = userss[i].name;            
            int winn= userss[i].game_stat? 1:0;
            int losss= userss[i].game_stat? 0:1;
            temp->total_wins = winn;
            temp->total_losses = losss;
            temp->next = new all_game_player;
            final_user++;
        }
        temp=all_players;
    }

}

void print_all_players(all_game_player* all_players, int player_num) {
    delay(5000);
    all_game_player* temp=all_players;
    clear_screen();
    while (temp->next != NULL){
        // cursor_to_pos(i,30);
        cout << "Name: " << temp->name << endl;
        // cursor_to_pos(i,30 + 20);
        cout << "Total Wins: " << temp->total_wins << endl;
        // cursor_to_pos(i,30+ 40);
        cout << "Total Losses: " << temp->total_losses << endl;
        cout << endl;
        delay(2000);
        temp=temp->next;
    }
}

int** gen(char mode){
    int emtpy_entrys=0;
    int ** sudoku=new int*[SUDOKU_SIZE];
    for(int i=0;i<SUDOKU_SIZE;i++){
        sudoku[i]=new int[SUDOKU_SIZE];
    }
    switch(mode){
        case 'e':
            emtpy_entrys=35;
            break;
        case 'n':
            emtpy_entrys=45;
            break;
        case 'h':
            emtpy_entrys=50;
            break;
        default:
            break;
    }
    string mode_name;
    switch(mode){
        case 'e':
            mode_name="easy";
            break;
        case 'n':
            mode_name="normal";
            break;
        case 'h':
            mode_name="hard";
            break;
        default:
            break;
    }
    string file_name="sudoku tables/"+mode_name+"_a.txt";
    ifstream f(file_name);
    for(int i=0;i<SUDOKU_SIZE;i++){
        for(int j=0;j<SUDOKU_SIZE;j++){
            f>>sudoku[i][j];
        }
    }
    f.close();
    int i_c,j_c;
    srand(time(NULL));
    for(int counter=0;counter<emtpy_entrys;counter++){
        i_c=rand()%8+0;
        j_c= rand()%8+0;
        // cout<<i_c<<" "<<j_c<<" ";
        if(sudoku[i_c][j_c]==0){
            counter--;
        }
        sudoku[i_c][j_c]=0;
    }
    return sudoku;

    }
void change_sudoku(int** sudoku,char mode){
    string mode_name;
    switch(mode){
        case 'e':
            mode_name="easy";
            break;
        case 'n':
            mode_name="normal";
            break;
        case 'h':
            mode_name="hard";
            break;
        default:
            break;
    }
    string file_name="sudoku tables/"+mode_name+".txt";
    ofstream f(file_name,ios::trunc);
    for(int i=0;i<SUDOKU_SIZE;i++){
        for(int j=0;j<SUDOKU_SIZE;j++){
            f<<sudoku[i][j]<<" ";
        }
        f<<"\n";
    }
    f.close();
}

void select_main_sudoku(char mode){
    int ** sudoku=new int*[SUDOKU_SIZE];
    for(int i=0;i<SUDOKU_SIZE;i++){
        sudoku[i]=new int[SUDOKU_SIZE];
    }
    srand(time(NULL));
    int randommm=rand()%8+1;
    string random;
    switch(randommm){
        case(1):
            random="1";
            break;
        case(2):
            random="2";
            break;

        case(3):
            random="3";
            break;

        case(4):
            random="4";
            break;

        case(5):
            random="5";
            break;

        case(6):
            random="6";
            break;

        case(7):
            random="7";
            break;

        case(8):
            random="8";
            break;

        
    }
    string mode_name;
    switch(mode){
        case 'e':
            mode_name="easy";
            break;
        case 'n':
            mode_name="normal";
            break;
        case 'h':
            mode_name="hard";
            break;
        default:
            break;
    }
    string file_name="sudoku generator/"+random+".txt";
    ifstream f2(file_name);
    for(int i=0;i<SUDOKU_SIZE;i++){
        for(int j=0;j<SUDOKU_SIZE;j++){
            f2>>sudoku[i][j];
        }
    }
    f2.close();
    file_name="sudoku tables/"+mode_name+"_a.txt";
    ofstream f3(file_name, ios::trunc);

    for(int i=0;i<SUDOKU_SIZE;i++){
        for(int j=0;j<SUDOKU_SIZE;j++){
            f3<<sudoku[i][j]<<" ";
        }
        f3<<"\n";
    }
    f3.close();

}

void hint_sudoku(int** sudoku,int** answer){
    int i_c,j_c;
    srand(time(NULL));
        do{
        i_c=rand()%8+0;
        j_c= rand()%8+0;
        }while(sudoku[i_c][j_c]!=0);
        sudoku[i_c][j_c]=answer[i_c][j_c];
    
}




#endif