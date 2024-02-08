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
#include <fstream>

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
void CHAIN(Student* &, Student* &, Student**, int, int, int &);
void UNCHAIN(Student* &);
void RANDOM_STUDENT(int, Student**, int);
Student** REHASH(Student**, Student**, int &, int);


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
    
    cout << "What would you like to do? (ADD, DELETE, PRINT Students, RAND [create random students], QUIT program)" << endl;
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

    else if (!strcmp(input, "RAND")) {
      int num;
      cout << "How many random students would you like to add?" << endl;
      cin >> num;
      RANDOM_STUDENT(num, table, size);
      cout << "random students added!" << endl;
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

  if (head == NULL) {//no collision
    array[index] = newStudent;
  }

  else {
    cout << "going to have to chain!" << endl;
    CHAIN(newStudent, head, array, 0, 4, size); //chaining needed
  }
  
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
  float gpa = student -> gpa;
  int id = student -> id;
  
  int sum;

  for (int i = 0; i < strlen(first); i++) {
    sum += (int) toupper(first[i]); //add up sum of chars in first name - average first name lenth around 6 so max around 540
  }

  int num = ((sum + (int)gpa)/6) * (size/100);

  cout << "got a hash of " << (num%size) << endl;
  return ((num%size));
}


void RANDOM_STUDENT(int num, Student** array, int size) {
  //https://www.w3schools.com/cpp/cpp_files.asp
  
  srand(time(0)); //this allows random results to be random every time program runs
  
  ifstream file("firstNames.txt"); //taken from above source, the code
  
  ifstream file2("lastNames.txt");

  //random first name:
  char* firsts[20]; //https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html taught me that I could use >>
  char* lasts[20];
    
  for (int i = 0; i < 20; i++) {
    firsts[i] = new char[20];
    lasts[i] = new char[20];
    file >> firsts[i];
    file2 >> lasts[i];
  }
  
  for (int i = 0; i < num; i++) {
    Student* newStud = new Student;
    
    //https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/ for rand() function paired with modulus:
    strcpy((*newStud).firstName, firsts[rand()%20]);
    strcpy((*newStud).lastName, lasts[rand()%20]);
    newStud -> gpa = rand()%4;
    newStud -> id = i;
    ADD(newStud, array, size);
  }
  return;
}

void CHAIN(Student* &newStudent, Student* &head, Student** oldArray, int current, int limit, int &size) {

  Student* next = head -> nextStudent;
  int cur = current;
  int lim = limit;
  
  if (next == NULL) { //add to end of chain

    head -> nextStudent = newStudent;
    return;
  }

  if (cur == lim) {
    cout << "woah - reached max collisions and going to have to rehash" << endl;
    Student* newPlace[size*2];

    //make sure everthing here is null:
    for (int i = 0; i < size*2; i++) {
      newPlace[i] = NULL;
    }
    cout << "made empty bigger array and entering rehash" << endl;
    cout << "here is the old array address before: " << oldArray << endl;
    oldArray = REHASH(oldArray, newPlace, size, size*2);
    cout << "rehashed!" << "changed address to " << oldArray << endl;
    return;
  }

  cur++;
  
  CHAIN(newStudent, next, oldArray, cur, lim, size); //recurse
  return;
}

void UNCHAIN(Student* &head) {
  return;
}

Student** REHASH(Student** oldArray, Student** newArray, int &currSize, int newSize) {

  cout << "entered rehash function for new size " << newSize << endl;
  for (int i = 0; i < currSize; i++) {

    Student* current = oldArray[i]; //this loop brought from print function above
  
    do {

      if (current != NULL) {
	cout << "going to move " << current -> firstName << endl;
	//cout << "who should be HASH(current, newSize);"
	ADD(current, newArray, newSize); //add to new array
	current = current -> nextStudent; //loop
      }

    }
    while (current != NULL);
    
  }

  cout << "put everything in new array, going to delete old array" << endl;
  
  delete[] oldArray;

  cout << "deleted old array" << endl;
  
  currSize = newSize;
  return newArray;
}
