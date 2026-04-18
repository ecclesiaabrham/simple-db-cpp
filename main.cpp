#include<iostream>
#include<sqlite3.h>
#include <string>
using namespace std;

struct student{
  int id;
  string name;
  double gpa;
  string pswrd;
}s;

int main(){
sqlite3 *db;
sqlite3_stmt *stmt;

sqlite3_open("student.db",&db);
    
    
 cout<<"Login(1) or sign in(2)?";
   string button;
    cin>>button;
    
 if(button=="1"){
 cout<<"Password: "; 
 cin>>s.pswrd;
  goto lable1;
  }
    
 else if(button=="2"){
  cout<<"Create account(y/n)?";
    cin>>button;
    if(button=="y"){
  cout<<"ID: ";
   cin>>s.id;
   cin.ignore();
    cout<<"Name: ";
      getline(cin,s.name);
    cout<<"current gpa: ";
      cin>>s.gpa; 
      cout<<"password: ";
        cin>>s.pswrd;
       string insert="INSERT INTO STUDENT VALUES("+to_string(s.id)+", '"+s.name+"', "+to_string(s.gpa)+ ", '"+s.pswrd+"');";
      sqlite3_exec(db, insert.c_str(),NULL,0,NULL);
       sqlite3_exec(db, "COMMIT;", NULL, 0, NULL); cout<<"Account created!\n";
     }
     else{
       cout<<"completed!";
         return 0;
     }
 }
    

      lable1:
      if(s.pswrd=="123"){
      string select="SELECT *FROM STUDENT;";
       sqlite3_prepare_v2(db,select.c_str(),-1,&stmt,NULL);
         cout<<"\nSTUDENT DATABASE\n";
         
        cout<<"id\tname\tgpa\tpassword\n";
         while(sqlite3_step(stmt)==SQLITE_ROW){
           int id=sqlite3_column_int(stmt,0);
           string name=(char*)sqlite3_column_text(stmt,1);
           double gpa=sqlite3_column_double(stmt,2);
           string password=(char*)sqlite3_column_text(stmt,3);
             
             cout<<id<<"\t"<<name<<"\t"<<gpa<<"\t"<<password<<"\t"<<endl;
         
         }
         
           sqlite3_finalize(stmt);
           }
           else {
              string select="SELECT ID,GPA FROM STUDENT;";
       sqlite3_prepare_v2(db,select.c_str(),-1,&stmt,NULL);
         cout<<"\nSTUDENT DATABASE\n";
         
        cout<<"id\tgpa\n";
        while(sqlite3_step(stmt)==SQLITE_ROW){
       int id=sqlite3_column_int(stmt,0);
       double gpa=sqlite3_column_double(stmt,1);
         
             cout<<id<<"\t"<<gpa<<endl;
          
             }
             sqlite3_finalize(stmt);
           }
           
           sqlite3_close(db);

    return 0;
}
