//C++ Programming: Student List Project With HASH TABLE!
//by Akhil Baidya

//Date of Submission (mm/dd/yy): 02/08/24

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
Initial studentList.cpp file taken from my github at https://github.com/AkhilBaidya/StudentList.git
*/


#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//DEFINING STRUCTS:
struct Student { //a student has a first name, last name, id, gpa, and a following student
  char firstName[20];
  char lastName[20];
  int id;
  float gpa;  
  Student* nextStudent = NULL;
};


//FUNCTION PROTOTYPES:
void ADD(Student* &, Student**, int &); 
void PRINT(Student**, int);
void DELETE(Student* &);
bool QUIT(Student* &);

int HASH(Student* &, int);
void CHAIN(Student* &, Student* &, int, int);
void UNCHAIN(Student* &);
Student* RANDOM_STUDENT();
void REHASH(Student **, Student **);


//MAIN FUNCTION:

int main() { //this is where the user will input commands to edit a student list


  //Variables:
  bool running = true; //loops the student list program
  int size = 100;
  Student* table[size]; // a hash table that will store the students
  for (int i = 0; i < 100; i++) {
    table[i] = NULL; //suggested by Mr. Galbraith - everything is not NULL by default :)
  }

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
      
      char firstN[20]; //new student's first name (taken from input)
      char lastN[20]; //new student's last name (taken from input)
      int ID; // new student's id (taken from input)
      float GPA; // new student's gpa (taken from input)
      Student* stuPnt = new Student; //create a new pointer to a new Struct (a new Student)  
  
      //Ask for new student details:
      cout << "what is the first name of the student?" << endl; //adding new first name
      cin >> firstN;
      strcpy((*stuPnt).firstName, firstN); //need to dereference pointer to set variables in new Struct (new student) equal to inputs (through strcpy())

      cout << "last name?" << endl; //do the same for the new last name
      cin >> lastN;
      strcpy((*stuPnt).lastName, lastN);

      cout << "id?" << endl; //do the same for the new id
      cin >> ID;
      (*stuPnt).id = ID;

      cout << "GPA?" << endl; //do the same for the new gpa
      cin >> GPA;
      (*stuPnt).gpa = GPA;

      ADD(stuPnt, table, size); //add a student
    }

    else if (!strcmp(input, "DELETE")) { //if the character array spells out "DELETE"...
      //DELETE(studVec); //delete a student
    }
    
    else if (!strcmp(input, "PRINT")) { //if the character array spells out "PRINT"...
      PRINT(table, size); //print out the students
    }    
  }
  return 0;
}

//OTHER FUNCTIONS IMPLEMENTED IN MAIN FUNCTION:


/*The ADD() function takes in the current vector of students (student pointers) and
creates a new student (and student pointer that is added to the vector).
 */

void ADD(Student* &newStudent, Student** array, int &size) {

  int index = HASH(newStudent, size); //get the index I should put the student in
  cout << index << endl;
  
  Student* head = new Student;

  head = array[index]; //the thing at that location
 
  cout << "no seg again" << endl;

  if (head == NULL) {//no collision
    array[index] = newStudent;
  }

  else {
    CHAIN(newStudent, head, 0, 4); //chaining needed
  }

  cout << "no seg 2" << endl; 
  cout << "added student" << endl;
  
  return;
}

/* The PRINT() function takes in the current vector of students (student pointers) and
prints out each student registered (and their info).
*/

void PRINT(Student** array, int size) {

  cout.setf(ios::showpoint); //from studentList
  cout.precision(3);
  
  for (int i = 0; i < size; i++) {

    Student* current = array[i];
    
    do {

      if (current != NULL) {

	cout << "Name: " << current -> firstName << " " << current -> lastName << ", ";
	cout << "ID: " << current -> id << ", ";
	cout << "GPA: " << current -> gpa << endl;
	current = current -> nextStudent;
      }

    }
    while (current != NULL);
  }
    return;
}

/* The DELETE() function takes in the current vector of students (student pointers) and
prompts the user for a student id. It then erases the student with that id from the student list.
*/
//void DELETE(vector<Student*> &studVec) {

  //referred to this source for how to delete objects in a vector (with the .erase() command:
  //https://www.geeksforgeeks.org/cpp-stl-cheat-sheet/#T3

  /*This source shows how the .erase() command takes the position of an object
    in a vector and deletes the object at that position.

    The source also shows how the beginning position (of the first element
    in the vector) can be accessed through vectorName.begin())
   */
  
  //int rmID; //the id of the student that will be removed
  //int count = 0; //counts the distance each "student" is away from the beginning
  //int position = -1; //the position of the student needed to be deleted
 
  //cout << "Which student do you want to remove from the student list? (Give ID)" << endl;
  //cin >> rmID; //get the id of the student we want to remove


//for (vector<Student*>::iterator student = studVec.begin(); student != studVec.end(); student++) { //iterate through each student in the vector

//++count; //increase the count (creates a "number" for each students position from studVec.begin())

//if (((*student) -> id) == rmID) { //if the student's id is equal to the id being searched for..
//position = count; //this is the position of the student we want removed!
//delete (*student); //help from Mr. Galbraith for delete command (deletes the Struct pointed to by the student pointer - removes the actual student)

//}
// }
/*
    if (position != -1) { //if there is a student (position) with that id
      studVec.erase(studVec.begin() + position - 1); //remove student pointer at that position from the vector

      cout << "removed student" << endl;
    }

    else {
      cout << "student not found" << endl;
    }
  
  return;
}
*/

bool QUIT(Student* &array) {
  return false;
}

int HASH(Student* &student, int size){

  //https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html

  char* first = student -> firstName;
  
  int sum;

  for (int i = 0; i < strlen(first); i++) {
    sum += (int) toupper(first[i]); //add up sum of chars in first name - average first name lenth around 6 so max around 540
  }

  return (sum/6)%size;
}


Student* RANDOM_STUDENT() {
  Student* bob = new Student();
  return bob;
}

void CHAIN(Student* &newStudent, Student* &head, int current, int limit) {

  Student* next = head -> nextStudent;
  int cur = current;
  int lim = limit;
  
  if (next == NULL) { //add to end of chain

    head -> nextStudent = newStudent;
    return;
  }

  cur++;
  
  CHAIN(newStudent, next, cur, lim); //recurse
  return;
}

void UNCHAIN(Student* &head) {
  return;
}

void REHASH(Student** oldArray, Student** newArray) {
  return;
}
