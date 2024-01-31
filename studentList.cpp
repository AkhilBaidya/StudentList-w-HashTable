//C++ Programming: Student List Project
//by Akhil Baidya

//Date of Submission (mm/dd/yy): 10/16/23

/* Notes: In this program, the user will be able to edit a list of students.
The user can input the commands "ADD," "DELETE," "PRINT" and "QUIT." QUIT
exits the program.

   1. ADD registers a new student in the list. The user inputs the student's names,
   id, and gpa (the id and gpa must be inputted as numbers).

   2. DELETE removes a student from the student list. The user must input a student
   id to identify this student to be removed.

   3. PRINT displays all the students currently registered in the student list and their info.
 */


/* Credits: 

1. In order to understand the syntax of creating vectors and passing them in by reference in function prototypes and functions, Mr. Galbraith's video on Vectors in Canvas was observed: https://www.youtube.com/watch?v=KD_pItB8Ygg&t=1s (video url).

The same video was also referred to in order to understand how to deference pointers (with (*pointerName)) and access aspects of the object the pointer is pointed towards using "->."

The same video was also used to write the iterator when printing out the students in the student vector in the PRINT function.


2. Referred to cplusplus.com (https://cplusplus.com/reference/cctype/toupper/) to find toupper() command which was used to standardize user command inputs (such as "PRINT" or "pRinT") to upper case.


3.Referred to GeeksforGeeks website for learning how to delete objects in a vector (with the .erase() command):https://www.geeksforgeeks.org/cpp-stl-cheat-sheet/#T3

This source shows how the .erase() command takes the position of an object in a vector and deletes the object at that position. The source also shows how the beginning position (of the first element in the vector) can be accessed through vectorName.begin())

4. Code for making Structs was based on Mr. Galbraith's video on Structs in Canvas:https://www.youtube.com/watch?v=vMCKhGuROnk&t=1s

5. Code for adding trailing zeroes and changing the preciseness of numbers when printed out was based on Mr. Galbraith's video on Formatting Outputs in Canvas:
https://www.youtube.com/watch?v=kv8XRxxaD8Q&t=290s

6. Learned how to create pointer, such as Student* stuPnt = new Student;, based on the Double Pointer visualizer provided by 
Mr. Galbraith on Canvas: https://pythontutor.com/visualize.html#mode=display

7. Help from Mr. Galbraith for learning about "delete" command (to remove a student Struct)
*/


#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//DEFINING STRUCTS:
struct Student { //Struct code based on Mr. Galbraith's video on Structs in Canvas (link in heading notes)

  char firstName[20];
  char secondName[20];
  int id;
  float gpa; //a Student has a first name, last name, id, and gpa 
};


//FUNCTION PROTOTYPES:

/*Referred to Mr. Galbraith's videos for understanding how to pass vectors by reference (link in heading notes) */

void ADD(vector<Student*> &); 
void PRINT(vector<Student*> &);
void DELETE(vector<Student*> &);
  

//MAIN FUNCTION:

int main() { //this is where the user will input commands to edit a student list


  //Variables:
  bool running = true; //loops the student list program
  vector<Student*> studVec; //contains pointers to the registered students
  char input[7]; //an array to store the user's inputs (max length is 6)

  while (running) {
    
    cout << "What would you like to do? (ADD, DELETE, PRINT Students, QUIT program)" << endl;
    cin >> input;

    for (int i = 0; i < strlen(input); i++) {
      input[i] = toupper(input[i]); //convert user input to upper case (add and ADD will be considered the same)

      //referred to https://cplusplus.com/reference/cctype/toupper/ for toupper() command.
    }

    if (!strcmp(input, "QUIT")) { //if the character array (user input) spells out "QUIT"...
      cout << "quitting student list program" << endl;
      running = false; //quit the program! (the program continues and loops if running = true)
    }

    else if (!strcmp(input, "ADD")) { //if the character array spells out "ADD"...
      ADD(studVec); //add a student
    }

    else if (!strcmp(input, "DELETE")) { //if the character array spells out "DELETE"...
      DELETE(studVec); //delete a student
    }
    
    else if (!strcmp(input, "PRINT")) { //if the character array spells out "PRINT"...
      PRINT(studVec); //print out the students
    }    
  }
  return 0;
}

//OTHER FUNCTIONS IMPLEMENTED IN MAIN FUNCTION:


/*The ADD() function takes in the current vector of students (student pointers) and
creates a new student (and student pointer that is added to the vector).
 */

void ADD(vector<Student*> &studVec) {

  //Variables:
  char firstN[20]; //new student's first name (taken from input)
  char lastN[20]; //new student's last name (taken from input)
  int ID; // new student's id (taken from input)
  float GPA; // new student's gpa (taken from input)
  Student* stuPnt = new Student; //create a new pointer to a new Struct (a new Student)
  //(learned how to create pointer from Double Pointer visualizer provided in Canvas at https://pythontutor.com/visualize.html#mode=display)  
  
  //Ask for new student details:
  cout << "what is the first name of the student?" << endl; //adding new first name
  cin >> firstN;
  strcpy((*stuPnt).firstName, firstN); //need to dereference pointer to set variables in new Struct (new student) equal to inputs (through strcpy())

  cout << "last name?" << endl; //do the same for the new last name
  cin >> lastN;
  strcpy((*stuPnt).secondName, lastN);

  cout << "id?" << endl; //do the same for the new id
  cin >> ID;
  (*stuPnt).id = ID;

  cout << "GPA?" << endl; //do the same for the new gpa
  cin >> GPA;
  (*stuPnt).gpa = GPA;

  studVec.push_back(stuPnt); //puts new pointer (pointing to new student created) in the vector of pointers
  cout << "added student" << endl;
  
  return;
}

/* The PRINT() function takes in the current vector of students (student pointers) and
prints out each student registered (and their info).
*/
void PRINT(vector<Student*> &studVec) {

  cout << "Students:" << endl;
  
  for (vector<Student*>::iterator student = studVec.begin(); student != studVec.end(); student++) { //iterate through each student in the vector

    /*referred to Mr. Galbraith's video on Vectors in Canvas to learn about using "->" to access aspects of an object pointed at
     (link in heading comments)*/

    cout << (*student) -> firstName << " "; //print out the first and last name of the student
    cout << (*student) -> secondName << ", ";

    cout << "ID: " << (*student) -> id << ", "; //print out the student's id

    /*referred to Mr. Galbraith's video on Formatting Outputs in Canvas to learn about .setf() and .precision()
      (link in heading comments)*/
    
    cout.setf(ios::showpoint); //want trailing zeroes in gpa (5 as 5.00)
    cout.precision(3); //restrict precision to three, allowing two decimal places for gpa
    cout << "GPA: " << (*student) -> gpa << endl; //print out the student's gpa
  }
  
  return;

}

/* The DELETE() function takes in the current vector of students (student pointers) and
prompts the user for a student id. It then erases the student with that id from the student list.
*/
void DELETE(vector<Student*> &studVec) {

  //referred to this source for how to delete objects in a vector (with the .erase() command:
  //https://www.geeksforgeeks.org/cpp-stl-cheat-sheet/#T3

  /*This source shows how the .erase() command takes the position of an object
    in a vector and deletes the object at that position.

    The source also shows how the beginning position (of the first element
    in the vector) can be accessed through vectorName.begin())
   */
  
  int rmID; //the id of the student that will be removed
  int count = 0; //counts the distance each "student" is away from the beginning
  int position = -1; //the position of the student needed to be deleted
 
  cout << "Which student do you want to remove from the student list? (Give ID)" << endl;
  cin >> rmID; //get the id of the student we want to remove


    for (vector<Student*>::iterator student = studVec.begin(); student != studVec.end(); student++) { //iterate through each student in the vector

    ++count; //increase the count (creates a "number" for each students position from studVec.begin())

    if (((*student) -> id) == rmID) { //if the student's id is equal to the id being searched for..
      position = count; //this is the position of the student we want removed!
      delete (*student); //help from Mr. Galbraith for delete command (deletes the Struct pointed to by the student pointer - removes the actual student)

    }
  }

    if (position != -1) { //if there is a student (position) with that id
      studVec.erase(studVec.begin() + position - 1); //remove student pointer at that position from the vector

      cout << "removed student" << endl;
    }

    else {
      cout << "student not found" << endl;
    }
  
  return;
}
