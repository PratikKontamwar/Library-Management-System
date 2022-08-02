
#include <iostream> // for std input output
#include <conio.h> //console input output header file have fn clrscr(),getch(),system("CLS");
#include <string.h>
#include <cstring>
#include <iomanip>  // provide setw() fn
#include <fstream> // for file handling

#define ADMINUSER "t"
#define ADMINPASSWORD "t"

using namespace std;

int flag_menu;

void student_menu();
void Librarian_menu();
void get_main_menu();
void cheack_menu();
void student_operation();

int current_id;


class book
{

    char book_number[30];

    char book_name[50];
    char author_name[50];
    char stbmisno[10];  // MIS of student who issued book
    string book_status; // 1->issued book i.e. not available or 0-> not issued book i.e. available
public:

    void create_book() // fn for insert new book details
    {
        //   auto generation Book id code
        
        cout << "\n\n\tBook ID is: ";
        book_number[0]='B';
        book_number[1]='I';
        int temp=current_id++;
        for(int i=5;i>1;i--){
            book_number[i]=temp%10+48;
            temp=temp/10;
        }
        for(int i=0;i<6;i++){
            cout<<book_number[i];
        }

        // cout << "\n\tEnter The Book ID: ";
        // cin >> book_number;
        cout << "\n\tEnter The Name of The Book: ";
        cin.ignore();
        cin.getline(book_name, 50); //take i/p including space max limit 50
        cout << "\n\tEnter The Author's Name: ";
        cin.getline(author_name, 50);
        book_status = "Available"; //
        stbmisno[0] = '\0';        //
        cout << "\t\t\n\n\tBook Created Successfully...";
    }

    void show_book() // fn for printing book details
    {
        cout << "\n\n\tBook ID: " << book_number;
        cout << "\n\tBook Name: " << book_name;
        cout << "\n\tAuthor's Name: " << author_name;
        cout << "\n\tBook status : " << book_status;                        //
        if (book_status == "Unavailable" && flag_menu == 1)                 //
            cout << "\n\tStudent MIS Number who issued book: " << stbmisno; //
    }

    void modify_book() //fn for modifying book details
    {
        cout << "\n\tBook ID : " << book_number;
        cout << "\n\tModify Book Name : ";
        cin.ignore();
        cin.getline(book_name, 50);
        cout << "\n\tModify Author's Name: ";
        // cin.ignore();
        cin.getline(author_name, 50);
    }

    char *getbooknumber()
    {
        return book_number;
    }

    char *getbookname()
    {
        return book_name;
    }

    char *retstbmisno()
    {
        return stbmisno;
    }

    string retbook_status()
    {
        return book_status;
    }

    void addbook_status()
    {
        book_status = "Unavailable";
    }

    void resetbook_status()
    {
        book_status = "Available";
    }

    void getstbmisno(char t[]) //copy MIS of student who issued book no. to i/p char array
    {
        strcpy(stbmisno, t);
    }

    void report()
    {
        cout << "\t" << setw(6) << book_number << setw(40) << book_name << setw(35) << author_name << setw(15) << book_status << endl;
    }
};

class student
{
    char ID_number[20];
    char Student_name[50];
    char stbno[6]; // student issued book no
    string token;     // 1->issued book or 0-> not issued book


public:
    void create_student() // fn for insert new student details
    {
        cout << "\n\n\tEnter Student's MIS Number: ";
        cin >> ID_number;

        // validation to mis number
        int ID_num = stoi(ID_number);
        while (ID_num < 100000000 || ID_num > 999999999)
        {
            cout << "\n\tEntered number is negative or is not a 9 digit number!\nPlease enter a positive 9 digit number!" << endl;
            cout << "\n\tEnter Student's MIS Number: ";
            cin >> ID_num;
        }
        string Temp;
        Temp = to_string(ID_num);
        strcpy(ID_number, Temp.c_str());

        cout << "\n\n\tEnter The Name of The Student: ";
        cin.ignore();
        cin.getline(Student_name, 50);
        token = "0";
        stbno[0] = '\0'; //
        cout << "\t\t\n\n\tStudent Record Created Successfully...";
    }

    void show_student() // fn for printing student details
    {
        cout << "\n\n\tMIS Number: " << ID_number;
        cout << "\n\tStudent Name: ";
        puts(Student_name);
        cout << "\n\tNo of Book issued: " << token;
        if (token == "1")
            cout << "\n\tBook ID: " << stbno;
    }

    void modify_student_details() //fn for modifying student details
    {
        cout << "\n\n\tMIS Number: " << ID_number;
        cout << "\n\tModify Student Name: ";
        cin.ignore();
        cin.getline(Student_name, 50);
    }

    char *get_ID_number()
    {
        return ID_number;
    }

    char *retstbno()
    {
        return stbno;
    }

    string rettoken()
    {
        return token;
    }

    void addtoken()
    {
        token = "1";
    }

    void resettoken()
    {
        token = "0";
    }

    void getstbno(char t[]) //copy issued book no. to i/p char array
    {
        strcpy(stbno, t);
    }

    void report()
    {
        cout << "\t" << setw(9) << ID_number << setw(30) << Student_name << setw(15) << token << endl;
    }
};

fstream fp, fp1;
book bk;
student st;
// int flag_menu;

void cheack_menu() // use for identifying menu 0->student or 1->librarian
{
    if (flag_menu == 0)
    {
        system("CLS");
        student_menu();
    }
    else
    {
        system("CLS");
        Librarian_menu();
    }
}

//----Display Books ----Display all books----Display specific books---display book by name----

void display_allb() // fn for displaying all books
{
    system("cls");
    fp.open("book.dat", ios::in);
    if (!fp)
    {
        cout << "\n\n\tERROR!!! FILE COULD NOT BE OPEN ";
        cout << "\n\nPress any key to continue..";
        getch();
        return;
    }
    // cout << "\n\n\t\tBook LIST\n\n";
    cout << "\n\t********************************** BOOK LIST **********************************\n\n";
    cout << "=======================================================================================================================\n";
    cout << "\tBook ID" << setw(40) << "Book Name" << setw(35) << "Author" << setw(15) << "Book Status\n";
    ;
    cout << "=======================================================================================================================\n";
    // for reading book.dat file we use below code
    while (fp.read((char *)&bk, sizeof(book))) //  read( (char *) & ob, sizeof(ob)); ob is an object of class which will be written to a file.
    {
        bk.report();
    }
    fp.close();
    cout << "\n\nPress any key to continue..";
    getch(); //fn will tell to the console wait for some time until a key is hit given after running of program.
    cheack_menu();
}

void display_spb(char n[]) // fn for Displaying specific books taking book no as i/p
{
    cout << "\n\t************* BOOK DETAILS *************\n";
    int flag = 0;
    fp.open("book.dat", ios::in);
    while (fp.read((char *)&bk, sizeof(book)))
    {
        if (strcmpi(bk.getbooknumber(), n) == 0) //strcmpi() function compare string but is not case sensitive
        {
            bk.show_book();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\n\tBook does not exist";

    cout << "\n\nPress any key to continue..";
    getch();
    cheack_menu();
}

void display_book_byname(char n[]) // fn for Displaying specific books taking book name as i/p
{
    cout << "\n\t************ BOOK DETAILS ************\n";
    int flag = 0;
    fp.open("book.dat", ios::in);
    while (fp.read((char *)&bk, sizeof(book)))
    {
        if (strcmpi(bk.getbookname(), n) == 0)
        {
            bk.show_book();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\n\tBook does not exist";

    cout << "\n\nPress any key to continue..";
    getch();
    cheack_menu();
}

//----search book---modify book---///

void search_book() // fn for searching book
{
    system("cls");
    cout << "\n\t************ SEARCH BOOK ************\n";
    cout << "\n\n\t\t>>Please Choose One Option:\n\n";

    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\tPress 1 to SEARCH BOOK BY BOOK NAME";
    cout << "\n\t\tPress 2 to SEARCH BOOK BY BOOK ID";
    cout << "\n\t\tPress 3 to GO BACK TO PREVIOUS MENU";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    int i;
    cout << "\n\t\tEnter valid option: ";
    cin >> i;
    switch (i)
    {
    case 1:
        char num1[50];
        system("cls");
        cout << "\n\n\tPlease Enter The book Name: ";
        cin.ignore();
        cin.getline(num1, 50);
        display_book_byname(num1);
        break;
    case 2:
        char num[6];
        system("cls");
        cout << "\n\n\tPlease Enter The Book ID: ";
        cin >> num;
        display_spb(num);
        break;
    case 3:
        system("CLS");
        cheack_menu();
        break;

    default:
        cout << "\n\t\tPlease enter correct option :(";
        cout << "\n\nPress any key to continue..";
        getch();
        system("cls");
        search_book();
    }
}

void modify_book() // fn for modifying book details
{
    system("cls");
    char n[20];
    int found = 0;
    cout << "\n\t************ MODIFY BOOK ************\n";
    cout << "\n\n\tEnter The Book ID: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read((char *)&bk, sizeof(book)) && found == 0)
    {
        if (strcmpi(bk.getbooknumber(), n) == 0)
        {
            bk.show_book();
            cout << "\n\n\tEnter The New Details of book\n"
                 << endl;
            bk.modify_book();
            long long unsigned int pos = -1 * sizeof(bk); //
            fp.seekp(pos, ios::cur);   // seekp() function is used to set the position of put pointer in a file while writing.
            fp.write((char *)&bk, sizeof(book));
            cout << "\n\n\t Record Updated Successfully...";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\n\tRecord Not Found ";

    cout << "\n\nPress any key to continue..";
    getch();
    cheack_menu();
}

// ----isssue book----

void issue_book() // fn for performing book issue operation
{
    system("cls");
    char sn[20], bn[20];
    int found = 0, flag = 0;
    cout << "\n\t************ BOOK ISSUE ************\n";
    cout << "\n\n\tEnter student's MIS number: ";
    cin >> sn;

    // validation to mis number
    int ID_num = stoi(sn);
    while (ID_num < 100000000 || ID_num > 999999999)
    {
        cout << "\n\tEntered number is negative or is not a 9 digit number!\nPlease enter a positive 9 digit number!" << endl;
        cout << "\n\tEnter Student's MIS Number: ";
        cin >> ID_num;
    }
    string Temp;
    Temp = to_string(ID_num);
    strcpy(sn, Temp.c_str());

    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmpi(st.get_ID_number(), sn) == 0)
        {
            found = 1;
            if (st.rettoken() == "0")
            {
                cout << "\n\n\tEnter Book ID: ";
                cin >> bn;
                while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
                {
                    const char *c = bk.retbook_status().c_str();
                    if ((strcmpi(bk.getbooknumber(), bn) == 0 && strcmpi(c, "Available") == 0)) //
                    {
                        bk.show_book();
                        flag = 1;
                        st.addtoken();
                        st.getstbno(bk.getbooknumber());
                        long long unsigned int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char *)&st, sizeof(student));

                        bk.addbook_status();                  //
                        bk.getstbmisno(st.get_ID_number());   //
                        long long unsigned int pos1 = -1 * sizeof(bk);           //
                        fp1.seekp(pos1, ios::cur);            //
                        fp1.write((char *)&bk, sizeof(book)); //
                        cout << "\n\n\t Book issued successfully...";
                    }
                }
                if (flag == 0)
                    cout << "\n\tBook is Unavailable !";
            }
            else
                cout << "\n\tYou have not returned the last book ";
        }
    }
    if (found == 0)
        cout << "\n\tStudent record not exist...";
    fp.close();
    fp1.close();
    cout << "\n\nPress any key to continue..";
    getch();
    system("cls");
    cheack_menu();
}

//----create student profile -----display all students

void write_student() // fn for write new student details in student.dat file
{
    system("cls");
    int more_or_main;
    fp.open("student.dat", ios::out | ios::app);
    do
    {
        st.create_student();
        fp.write((char *)&st, sizeof(student));


        cout << "\n\n\tPress 1 to add more students.";
        cout << "\n\tPress 2 to return to librarian menu.\n";
        cout << "\n\tEnter: ";
        cin >> more_or_main;

    } while (more_or_main == 1);

    fp.close();
    if (more_or_main == 2)
    {
        system("CLS");
        Librarian_menu();
    }
}

void display_all_students() // fn for displaying all students list
{
    system("cls");
    fp.open("student.dat", ios::in);
    if (!fp)
    {
        cout << "\n\n\tERROR!!! FILE COULD NOT BE OPEN ";
        cout << "\n\nPress any key to continue..";
        getch();
        return;
    }
    cout << "\n\t************ STUDENTS LIST ************\n\n";
    cout << "======================================================================================\n";
    cout << "\tMIS Number." << setw(25) << "Name" << setw(25) << "Book Issued\n";
    cout << "======================================================================================\n";
    while (fp.read((char *)&st, sizeof(student)))
    {
        st.report();
    }
    fp.close();
    cout << "\n\nPress any key to continue...";
    getch();
    student_operation();
}

//---Display a student----modify student-----

void display_a_student(char n[]) // fn for displaying specific student details
{
    system("cls");
    cout << "\n\t************ STUDENTS DETAILS ************\n\n";
    int check = 0;
    fp.open("student.dat", ios::in);
    while (fp.read((char *)&st, sizeof(student)))
    {
        if ((strcmpi(st.get_ID_number(), n) == 0))
        {
            st.show_student();
            check = 1;
        }
    }
    fp.close();
    if (check == 0)
        cout << "\n\n\tStudent does not exist";

    cout << "\n\nPress any key to continue...";
    getch();
    student_operation();
}

void modify_student() // fn for write new  details of student in student.dat file
{
    system("cls");
    char n[20];
    int found = 0;
    cout << "\n\t************ MODIFY STUDENTS RECORD ************\n\n";
    cout << "\n\n\tEnter Student's MIS number: ";
    cin >> n;

    // validation to mis number
    int ID_num = stoi(n);
    while (ID_num < 100000000 || ID_num > 999999999)
    {
        cout << "\n\tEntered number is negative or is not a 9 digit number!\nPlease enter a positive 9 digit number!" << endl;
        cout << "\n\tEnter Student's MIS Number: ";
        cin >> ID_num;
    }
    string Temp;
    Temp = to_string(ID_num);
    strcpy(n, Temp.c_str());

    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmpi(st.get_ID_number(), n) == 0)
        {
            st.show_student();
            cout << "\n\n\tEnter The New Details of student: " << endl;
            st.modify_student_details();
            long long unsigned int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&st, sizeof(student));
            cout << "\n\n\tRecord Updated Successfully...";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\n\tRecord Not Found ";

    cout << "\n\nPress any key to continue...";
    getch();
    student_operation();
}

//----student section---

void student_operation() // fn for printing student operation
{
    system("cls");
    int option;
    cout << "\n\t\t>>Please Choose One Option:\n\n";

    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\tPress 1 to CREATE STUDENT RECORD";
    cout << "\n\t\tPress 2 to DISPLAY ALL STUDENTS RECORD";
    cout << "\n\t\tPress 3 to DISPLAY SPECIFIC STUDENT RECORD";
    cout << "\n\t\tPress 4 to MODIFY STUDENT RECORD";
    cout << "\n\t\tPress 5 to GO BACK TO LIBRARIAN MENU";
    cout << "\n\t\tPress 6 to GO BACK TO MAIN MENU";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";

    cout << "\n\t\tEnter your choice : ";
    cin >> option;
    switch (option)
    {
    case 1:
        system("cls");
        write_student();
        break;
    case 2:
        system("cls");
        display_all_students();
        break;
    case 3:
    {
        char num[20];
        system("cls");
        cout << "\n\n\tPlease Enter The MIS Number: ";
        cin >> num;

        // validation to mis number
        int ID_num = stoi(num);
        while (ID_num < 100000000 || ID_num > 999999999)
        {
            cout << "\n\tEntered number is negative or is not a 9 digit number!\nPlease enter a positive 9 digit number!" << endl;
            cout << "\n\tEnter Student's MIS Number: ";
            cin >> ID_num;
        }
        string Temp;
        Temp = to_string(ID_num);
        strcpy(num, Temp.c_str());

        display_a_student(num);
        break;
    }
    case 4:
        system("cls");
        modify_student();
        break;
    case 5:
        system("cls");
        Librarian_menu();
        break;
    case 6:
        system("cls");
        get_main_menu();
        break;
    default:
        system("cls");
        student_operation();
    }
}

//-----write book----book return
void write_book() // fn for write new book details in book.dat file
{
    system("cls");
    int more_or_main;
    fp.open("book.dat", ios::out | ios::app);
    do
    {
        bk.create_book();
        fp.write((char *)&bk, sizeof(book));
        FILE *f=fopen("current_book_id.txt","w");
    if(!f){
        cout<<"could not open current_id.txt"<<endl;
    }
    else{
        fprintf(f,"%d",current_id);
        fclose(f);
    }
        cout << "\n\tPress 1 to add more books.";
        cout << "\n\tPress 2 to return to previous menu.\n";
        cout << "\n\tEnter: ";
        cin >> more_or_main;
    } while (more_or_main == 1);
    fp.close();
    if (more_or_main == 2)
    {
        Librarian_menu();
    }
}

void book_return()
{
    system("cls");
    char sn[20], bn[20];
    int found = 0, flag = 0, day, fine;
    cout << "\n\t************ RETURN BOOKS ************\n\n";
    cout << "\n\n\tEnter The students MIS Number: ";
    cin >> sn;

    // validation to mis number
    int ID_num = stoi(sn);
    while (ID_num < 100000000 || ID_num > 999999999)
    {
        cout << "\n\tEntered number is negative or is not a 9 digit number!\nPlease enter a positive 9 digit number!" << endl;
        cout << "\n\tEnter Student's MIS Number: ";
        cin >> ID_num;
    }
    string Temp;
    Temp = to_string(ID_num);
    strcpy(sn, Temp.c_str());

    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmpi(st.get_ID_number(), sn) == 0)
        {
            found = 1;
            if (st.rettoken() == "1")
            {
                while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
                {
                    if (strcmpi(bk.getbooknumber(), st.retstbno()) == 0)
                    {
                        bk.show_book();
                        flag = 1;
                        cout << "\n\n\tBook returned in no. of days: ";
                        cin >> day;
                        if (day > 15)
                        {
                            fine = (day - 15) * 10; // late return fine: rs 10 fine per day
                            cout << "\n\n\tYou are returning book late. You have to pay a fine of Rs " << fine;
                        }
                        st.resettoken();
                        int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char *)&st, sizeof(student));

                        bk.resetbook_status();                //
                        int pos1 = -1 * sizeof(bk);           //
                        fp1.seekp(pos1, ios::cur);            //
                        fp1.write((char *)&bk, sizeof(book)); //
                        cout << "\n\n\t Book returned successfully...";
                    }
                }
                if (flag == 0)
                    cout << "\n\tBook ID does not exist";
            }
            else
                cout << "\n\tNo book is issued..please check!!";
        }
    }
    if (found == 0)
        cout << "\n\tStudent record not exist...";

    fp.close();
    fp1.close();
    cout << "\n\nPress any key to continue..";
    getch();
    system("cls");
    cheack_menu();
}

// ----modify or add book ----
void modify_or_add_book()
{
    system("cls");
    cout << "\n\t************ MODIFY OR ADD BOOKS ************\n\n";
    cout << "\n\n\t\t>>Please Choose One Option:\n\n";

    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\tPress 1 to MODIFY BOOK DETAILS";
    cout << "\n\t\tPress 2 to ADD NEW BOOK DETAILS";
    cout << "\n\t\tPress 3 to GO BACK TO PREVIOUS MENU";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    int i;
    cout << "\n\t\tEnter your choice : ";
    cin >> i;

    switch (i)
    {
    case 1:
        modify_book();
        break;
    case 2:
        write_book();
        break;
    case 3:
        cheack_menu();
        break;
    default:
        cout << "\n\t\tPlease enter correct option :(";
        cout << "\n\nPress any key to continue..";
        getch();
        system("cls");
        modify_or_add_book();
        break;
    }
}

void issue_book_info()
{
    cout << "\n\t\t****************** HOW TO ISSUE A BOOK ? *************************\n\n";
    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\t1) Search for book and notedown book ID.";
    cout << "\n\t\t2) Tell Librarian your MIS number and Book ID of the book.";
    cout << "\n\t\t3) Complete the process.";
    cout << "\n\n\t\t REMEMBER:\n";
    cout << "\n\t\t* You can issue only one book at time.";
    cout << "\n\t\t* You have to return a book within 15 days from issued date. ";
    cout << "\n\t\t* If you fail to return book within 15 days from issued date.";
    cout << "\n\t\t  You have to pay fine of Rs 10 per day";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    cout << "\n\nPress any key to continue..";
    getch();
    system("cls");
    student_menu();
}

void return_book_info()
{
    cout << "\n\t\t******************** HOW TO RETURN A BOOK ? ***********************\n\n";
    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\t1) Go to Librarian desk.";
    cout << "\n\t\t2) Tell Librarian your MIS number and Book ID of the book.";
    cout << "\n\t\t3) Complete the process.";
    cout << "\n\n\t\t REMEMBER:\n";
    cout << "\n\t\t* You have to return previous issued book to issue new one.";
    cout << "\n\t\t* You have to return a book within 15 days from issued date. ";
    cout << "\n\t\t* If you fail to return book within 15 days from issued date.";
    cout << "\n\t\t  You have to pay fine of Rs 10 per day";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    cout << "\n\nPress any key to continue..";
    getch();
    system("cls");
    student_menu();
}

//----Librarian --section

void Librarian_menu()
{
    system("cls");
    flag_menu = 1;
    int i;
    cout << "\n\t************ WELCOME LIBRARIAN ************\n\n";
    cout << "\n\t\t>>Please Choose One Option:\n\n";

    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\tPress 1 to VIEW BOOKLIST";
    cout << "\n\t\tPress 2 to SEARCH FOR A BOOK";
    cout << "\n\t\tPress 3 to MODIFY OR ADD BOOKS";
    cout << "\n\t\tPress 4 to ISSUE BOOK";
    cout << "\n\t\tPress 5 to RETURN BOOK";
    cout << "\n\t\tPress 6 to STUDENT MENU";
    cout << "\n\t\tPress 7 to GO BACK TO MAIN MENU";
    cout << "\n\t\tPress 8 to CLOSE APPLICATION";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";

    cout << "\n\t\tEnter your choice : ";
    cin >> i;
    switch (i)
    {
    case 1:
        system("CLS");
        display_allb();
        break;
    case 2:
        system("CLS");
        search_book();
        break;
    case 3:
        system("CLS");
        modify_or_add_book();
        break;
    case 4:
        system("CLS");
        issue_book();
        break;
    case 5:
        system("CLS");
        book_return();
        break;
    case 6:
        system("CLS");
        student_operation();
        break;
    case 7:
        system("cls");
        get_main_menu();
        break;
    case 8:
        exit(0);
    default:
        cout << "\n\t\tPlease enter correct option :(";
        cout << "\n\nPress any key to continue..";
        getch();
        system("cls");
        Librarian_menu();
    }
}

//-----student---main---menu
void student_menu()
{
    system("cls");
    flag_menu = 0;
    int i;
    cout << "\n\t************ WELCOME STUDENT ************\n\n";
    cout << "\n\t\t>>Please Choose One Option:\n\n";

    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\tPress 1 to VIEW BOOKLIST";
    cout << "\n\t\tPress 2 to SEARCH FOR A BOOK";
    cout << "\n\t\tPress 3 to HOW TO ISSUE A BOOK ?";
    cout << "\n\t\tPress 4 to HOW TO RETURN A BOOK ?";
    cout << "\n\t\tPress 5 to GO BACK TO MAIN MENU";
    cout << "\n\t\tPress 6 to CLOSE APPLICATION";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";

    cout << "\n\t\tEnter your choice : ";
    cin >> i;

    if (i == 1)
    {
        system("CLS");
        display_allb();
    }
    else if (i == 2)
    {
        system("CLS");
        search_book();
    }
    else if (i == 3)
    {
        system("CLS");
        issue_book_info();
    }
    else if (i == 4)
    {
        system("CLS");
        return_book_info();
    }
    else if (i == 5)
    {
        system("cls");
        get_main_menu();
    }
    else if (i == 6)
        exit(0);
    else
    {
        cout << "\n\t\tPlease enter correct option :(";
        cout << "\n\nPress any key to continue..";
        getch();
        system("cls");
        student_menu();
    }
}

//----Main---Menu-----
void get_main_menu()
{
    int i;
    current_id=0;
    FILE *f=fopen("current_book_id.txt","r");
    if(!f){
        cout<<"could not open current_id.txt"<<endl;
    }
    else{
        fscanf(f,"%d",&current_id);
        fclose(f);
    }

    cout << "\n\t*********** ELECTRICAL STUDENT ASSOCIATION LIBRARY ***********\n"
         << "\n\t\t\tCOLLEGE OF ENGINEERING, PUNE \n";

    cout << "\n\n\t\t>>Please Choose any One Option to login:\n\n";

    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\tPress 1 to STUDENT LOGIN";
    cout << "\n\t\tPress 2 to LIBRARIAN LOGIN";
    cout << "\n\t\tPress 3 to CLOSE APPLICATION";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";

    cout << "\n\t\tEnter your choice : ";
    cin >> i;
    if (i == 1)
    {
        system("cls");
        student_menu();
    }
    else if (i == 2)
    {
        system("cls");
        char adminuser[10];
        char adminpass[10];
        cout << "\n\t************ LIBRARIAN LOGIN ************\n\n";
        cout << "\n\n Please Enter User name :- ";
        cin >> adminuser;
        cout << "\n\n Please Enter Password :- ";
        cin >> adminpass;
        if ((strcmp(adminuser, ADMINUSER) == 0) && (strcmp(adminpass, ADMINPASSWORD) == 0))
        {
            system("CLS");
            Librarian_menu();
        }
    }
    else if (i == 3)
        exit(0);
    else
    {
        cout << "\n\t\tPlease enter correct option :(";
        cout << "\n\nPress any key to continue..";
        getch();
        system("CLS");
        get_main_menu();
    }
}

int main()
{
    system("CLS");
    get_main_menu();
    return 0;
}
