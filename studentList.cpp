//C++ Programming: Student List Project With HASH TABLE!
//by Akhil Baidya

//Date of Submission (mm/dd/yy): 02/08/24

/* Notes: In this program, the user will be able to edit a list of students that are stored in a hash table. The user can input the commands "ADD," RAND," "DELETE," "PRINT" and "QUIT." QUIT exits the program.

   1. ADD registers a new student in the hash table. The user inputs the student's names,id, and gpa (the id and gpa must be inputted as numbers).

   2. RAND creates random students (random names, gpa, id) and adds them to the hash table. The user will be prompted for how many random students they want to generate (ex. 100). 

   3. DELETE removes a student (or multiple) from the student list. The user must input a student id to identify this student to be removed. There will be a final prompt to delete the entry (a y/n prompt) before deletion.

   4. PRINT displays all the students currently registered in the hash table and their info.

 After every ADD or RAND, the code will check whether to rehash the students into a new list of slightly over double-the-size (a max of 3 collisions are allowed, where those students are chained in a linked list - otherwise, rehashing is called) 
*/

/* Additional Note about Project: This project is a reworking of a previous studentList project. The initial studentList.cpp file was taken from my GitHub at at https://github.com/AkhilBaidya/StudentList.git.

  Referred to Mr. Galbraith's explanation of Hash Table (https://www.youtube.com/watch?v=tV3Jsa0_Xm4&t=2s) to better understand what I'm dealing with and what a Hash Function is
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

//User commands (ADD, RAND, PRINT, DELETE, QUIT):
void ADD(Student*, Student** &, int &, bool &); 
void RANDOM_STUDENT(int, Student** &, int &, bool &);
void PRINT(Student**, int);
void DELETE(Student**, int &, int);
bool QUIT(Student**, int &);

//Additional functions (to support :
int HASH(Student*, int &);
void CHAIN(Student*, Student* , Student** &, int, int, int &, bool &);
void REHASH(Student** &, Student** &, int &, int, bool &);


//MAIN FUNCTION:

int main() { //this is where the user will input commands to edit the student list

  //Variables:
  bool running = true; //loops the student list program
  bool rehash = false; //determines whether to rehash (rehash hash table if true)
  int size = 100; //the size of the hash table (will change after every rehash)
  Student* table[size]; // this is the hash table that will store the students
  
  for (int i = 0; i < size; i++) {
    //need to make sure everything in the initial hash table is NULL and empty!
    table[i] = NULL; //loop to set everything null suggested by Mr. Galbraith - everything is not NULL by default in C++ :)
  }
  
  Student** tpntr = new Student*[size]; //this is a pointer "table pointer" that will point to the hash table (help from Mr. Galbraith in realizing I need a Student** and advice from Kevin that I can allocate space for Student*[size] not only Student**)
  
  tpntr = table;

  char input[7]; //an array to store the user's inputs (max length of input is 6)

  while (running) {
    
    cout << "What would you like to do? (ADD, DELETE, PRINT Students, RAND [create random students], QUIT program)" << endl;
    cin >> input;

    for (int i = 0; i < strlen(input); i++) {
      input[i] = toupper(input[i]); //convert user input to upper case
      //Referred to https://cplusplus.com/reference/cctype/toupper/ for toupper() command
    }

    //User inputs "quit":
    if (!strcmp(input, "QUIT")) {
      cout << "quitting student list program" << endl;
      running = QUIT(tpntr, size); //quit the program! (the program continues and loops if running = true)
    }

    //User inputs "add":
    else if (!strcmp(input, "ADD")) {

      char firstN[20]; //new student's first name (taken from input)
      char lastN[20]; //new student's last name (taken from input)
      int ID; // new student's id (taken from input)
      float GPA; // new student's gpa (taken from input)

      Student* stuPnt = new Student(); //create a new pointer to a new Student  
      stuPnt -> nextStudent = NULL; //Just in case - should not have a nextStudent yet
      
      //Ask for new student details:
      cout << "what is the first name of the student?" << endl;
      cin >> firstN;
      strcpy((*stuPnt).firstName, firstN); //set first name

      cout << "last name?" << endl;
      cin >> lastN;
      strcpy((*stuPnt).lastName, lastN); //set last name

      cout << "id?" << endl;
      cin >> ID;
      (*stuPnt).id = ID; //set id

      cout << "GPA?" << endl;
      cin >> GPA;
      (*stuPnt).gpa = GPA; //set gpa

      ADD(stuPnt, tpntr, size, rehash); //add the student!
    }

    //User inputs "delete":
    else if (!strcmp(input, "DELETE")) {

      //Get id of student the user wants to delete:
      int wantedId = 0;
      cout << "Delete student(s) of which ID?" << endl;
      cin >> wantedId;

      DELETE(tpntr, size, wantedId); //delete the student
    }

    //User inputs "print":
    else if (!strcmp(input, "PRINT")) {
      PRINT(tpntr, size); //print out the students
    }

    //User inputs "rand":
    else if (!strcmp(input, "RAND")) {
      
      //Get how many new students the user wants:
      int num;
      cout << "How many random students would you like to add?" << endl;
      cin >> num;

      RANDOM_STUDENT(num, tpntr, size, rehash); //add random students
      cout << "random students added!" << endl;
    }

    //At the end of each "turn" (after add or rand is called and finished), check for rehashing (indicated by boolean "rehash"):

    if (rehash) { //if need to rehash:

      //Need a bigger size for the new array:
      int newSize = (int) size*2.3; // Multiplying by prime number sugestion from my father to help generate more unique values when the size is used to modulus other values  
    
      cout << "woah - we had reached max collisions and will now need to rehash into a new hash table of size " << newSize << endl;
    
      Student** newPlacePntr = new Student*[newSize]; //new hash table
    
      //make sure everthing here is null:
      for (int i = 0; i < newSize; i++) {
	newPlacePntr[i] = NULL;
      }
   
      REHASH(tpntr, newPlacePntr, size, newSize, rehash); //REHASH!
      cout << "rehashed!" << endl;
    }
  }
  return 0;
}


//OTHER FUNCTIONS IMPLEMENTED IN MAIN FUNCTION:

/*The ADD() function takes in the a new student and the hash table. It also takes the current size of the table in order to hash the new student and get an index for where to put it in the table. If the spot at the index is empty, the student is simply added there; if not, chaining is needed and the CHAIN() function is called. ADD also takes in the boolean rehash to be passed into CHAIN() to check for max collisions and the need to rehash the table (which would set the boolean to true).
 */

void ADD(Student* newStudent, Student** &arrayPntr, int &size, bool &rehash) {

  int index = HASH(newStudent, size); //Get the index the student should be put in
  
  Student* head = arrayPntr[index]; //Get the thing already at that location

  if (head == NULL) {//If there is nothing there, then there is no collision!

    //Simply place the new student at the location: 
    arrayPntr[index] = newStudent;
    
    arrayPntr[index] -> nextStudent = NULL; //<aking next student null after adding to array just in case something weird occurs with memory
  }

  else { //If there is a collision...
    cout << "going to have to chain!" << endl;
    CHAIN(newStudent, head, arrayPntr, 0, 3, size, rehash); //CHAIN the new student in the array
  }

  //For user's reference;
  cout << "added " << newStudent -> firstName << " " << newStudent -> lastName << endl;
  return;
}

/* The PRINT() function takes in the hash table and its current size and prints out each student registered (and their info).
*/
void PRINT(Student** arrayPntr, int size) {
  
  cout.setf(ios::showpoint); //This formatting code is from my original studentList (linked in the additional notes at the top of this file)
  cout.precision(3);
 
  for (int i = 0; i < size; i++) { //Going through each "row" in the array (if the array is considered rows of linked lists):

    Student* current = arrayPntr[i]; //Start with the first element in the row
    
    do {

      if (current != NULL) { //If the current student exists, print out their info:

	cout << "Name: " << current -> firstName << " " << current -> lastName << ", ";
	cout << "ID: " << current -> id << ", ";
	cout << "GPA: " << current -> gpa << endl;
	current = current -> nextStudent; //Go to the next student down the linked list
      }
    }
    while (current != NULL);

  }
  return;
}

/* The DELETE() function takes in the hash table, its size, and the id of the student the user wants to delete. It then prompts the user, for each student with the id, whether to delete the student. If yes, the student is deleted.
*/
void DELETE(Student** array, int &size, int wantedId) {
  
  for (int i = 0; i < size; i++) {

    Student* head = array[i]; //This is the head of the linked list in this "row" of the table
    
    Student* current = head; //The current student being looked at is the head
    
    Student* next = new Student();

    while (current != NULL) { //For a current student:

      next = current -> nextStudent;
      
      if (next != NULL) { 

	if (next -> id == wantedId) { //If the next student has the id wanted, delete the next student:

	  char answer;
	  cout << "Would you like to delete this student with the specified id? (y/n)" << endl; 
	  cout << "Name: " << next -> firstName << " " << next -> lastName << ", ";
	  cout << "ID: " << next -> id << ", ";
	  cout << "GPA: " << next -> gpa << endl;

	  cin >> answer;
	  if (answer == 'y') {

	    //First disconnect the nextStudent from the linked list:
	    current -> nextStudent = NULL;
	    current -> nextStudent = next -> nextStudent;
	    next -> nextStudent = NULL;

	    //Then delete:
	    delete next;
	    cout << "Deleted!" << endl;
	  }
	}
      }
      current = current -> nextStudent; //Move down the linked list
    }

    //After all that, check the first element in the linked list for deletion:
    if (head != NULL) {
      if (head -> id == wantedId) {

	cout << "head" << endl;
	char answer;
	cout << "Would you like to delete this student with the specified id? (y/n)" << endl\
;
        cout << "Name: " << head -> firstName << " " << head -> lastName << ", ";
        cout << "ID: " << head -> id << ", ";
        cout << "GPA: " << head -> gpa << endl;
	cin >> answer;

	if (answer == 'y') {
	
	  array[i] = head -> nextStudent; //delete it by setting its place in the array equal to its nextStudent

	}
      }
    }
  }
}


/* The QUIT() function takes in the current hash table and its size and deletes all the elements from the hash table. It returns false, signalling that the program should end.
 */
bool QUIT(Student** array, int &size) {

  for (int i = 0; i < size; i++) {

    Student* head = array[i]; //Head of each linked list in the array
    
    Student* current = head; //The current student being looked at is the head
    
    Student* next = new Student();

    while (current != NULL) {//For each current student:

      next = current -> nextStudent;
      
      if (next != NULL) { //Check if there is a next student:

	//Disconnect the next student from the linked list: 
	current -> nextStudent = NULL;
	current -> nextStudent = next -> nextStudent;
	next -> nextStudent = NULL;

	//Then delete it:
	delete next;  
      }
      current = current -> nextStudent; //Move down the linked list
    }

    //Now delete the head of the linked list if it exists:
    if (head != NULL) {
	array[i] = head -> nextStudent;
    }
  }
  return false;
}


/* The HASH() function takes in a student and the current size of the hash table and returns a number that will be the student's index position in the hash table. Ideally, the possible values from the function should be spread out within the current size.
 */

int HASH(Student* student, int &size){

  //Refered to Carnegie Mellon School of CS ASCII Chart at https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html (for predicting max integer sum of chars in the students' names)

  //Get the student's info:
  char* first = student -> firstName;
  char* last = student -> lastName;
  float gpa = student -> gpa;
  int id = student -> id;
  
  int sum;

  //Add the sum of the ASCII values of the first and last name chars of the student:
  
  for (int i = 0; i < strlen(first); i++) {
    sum += (int) ((toupper(first[i]))*17); //Multiplied each ASCII value, first, by a prime number, to possibly help spread out the resulting values (suggestion from my father)
    }

  for (int i = 0; i < strlen(last); i++) {
    sum += (int) ((toupper(last[i]))*97);
  }
  
  return (sum)%(size * 97/100); //Should mod by the size to keep values within possible indices for the array
  //Adding a flavor of randomness with * 97/100 to possibly help with spreading out hash values 
}

/* RANDOM_STUDENT() function takes in a number of students to generate, the hash table, and its size. From this, it adds that number of randomly generated students using ADD(). It passes in the bool rehash into ADD() which passes into CHAIN() to check for rehashing. 
*/
void RANDOM_STUDENT(int num, Student** &array, int &size, bool &rehash) {
  //Referred to w3schools in understanding that ifstream is a class that I can initialize to read in a file, and that I need to include <fstream> at the top of my .cpp file (source at https://www.w3schools.com/cpp/cpp_files.asp)

  //Referred to GeeksforGeeks to understand that I need srand() and need to set a seed to truly get randomized results every time rand() is called (source at https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/)
  srand(time(0)); //This allows random results to be random every time program runs
  
  ifstream file("firstNames.txt"); //Referenced from above w3schools source
  ifstream file2("lastNames.txt");

  //Random first and last name:
  char* firsts[20];
  char* lasts[20]; //these are arrays of names

  //Referred to Udacity.com and the blog by their Udacity team (https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html) to learn that I can read in files using >> (which stops after encountering a space " ")
  
  for (int i = 0; i < 20; i++) { //for each line in the files (20 lines each)
    firsts[i] = new char[20];
    lasts[i] = new char[20];
    file >> firsts[i]; //read in name from file line into array 
    file2 >> lasts[i];
  }
  
  for (int i = 0; i < num; i++) {
    Student* newStud = new Student();
    
    //Referred to GeeksforGeeks again in realizing that in order to set a range for rand(), there isn't an argument, but I need modulus instead (https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/):
    strcpy((*newStud).firstName, firsts[rand()%20]); //set random first name
    strcpy((*newStud).lastName, lasts[rand()%20]); //last name
    newStud -> gpa = rand()%4; //gpa
    newStud -> id = i; //id just increments
    
    ADD(newStud, array, size, rehash); //add random student
  }
  return;
}

/*CHAIN() function takes in a new student, the head of the linked list where we want to add that student, the hash table, and a limit for the number of collisions allowed (length of linked list). It goes to the end of the list and adds the student, but sees whether the length of the list exceeds the limit. That is why it also takes in the rehash bool, which is set to true if the limit is exceeded (rehashing is needed!)
 */
void CHAIN(Student* newStudent, Student* head, Student** &oldArrayPntr, int c, int limit, int &size, bool &rehash) {

  Student* current = new Student();
  current = head;
  int count = 1; 

  while (current -> nextStudent != NULL) { //continue going through linked list until next student is null (meaning the ending is reached)
    current = current -> nextStudent;
    count++; //count the length
  }

  if (count == limit) {
    rehash = true; //we're going to later rehash if the limit was exceeded
  }

  current -> nextStudent = newStudent; //add the student to the end of the linked list
  current -> nextStudent -> nextStudent = NULL; //Suggestion by father: just in case, set the next student after the new addition as null after having added it to the end of the linked list, since it is the end of the list
 
  return;
}

/* REHASH() function takes in the original hash table, the space for the new one, the current size of the original hash table, and the size for the new hash table. It then rehashes each member of the original hash table using the new size and puts them into the new hash table. The function also takes in the bool rehash to set it to false at the end, since rehashing is complete.
*/

void REHASH(Student** &oldArrayPntr, Student** &newArrayPntr, int &currSize, int newSize, bool &rehash) {
  
  for (int i = 0; i < currSize; i++) {

    Student* current = oldArrayPntr[i]; //this is the head of each linked list in the original array
    
    do {

      if (current != NULL) {
	
	cout << "At position "<<i<<", going to move " << current -> firstName << current -> lastName << endl;

	//Copy the info of the current student into new student:
	Student* newStudent = new Student();
	strcpy(newStudent -> firstName, current -> firstName);
	strcpy(newStudent -> lastName, current -> lastName);
	newStudent -> gpa = current -> gpa;
	newStudent -> id = current -> id;
	newStudent -> nextStudent = NULL; //but set the next student to null
	
	ADD(newStudent, newArrayPntr, newSize, rehash); //add this new, fresh, but copied student to the new array
     
	current = current -> nextStudent; //Go down the linked list
      }
    }
    while (current != NULL);
  }
  
  oldArrayPntr = newArrayPntr; //The original array will now become the new array (it has beenreborn as a bigger hash table)
  currSize = newSize; //So has its size been reborn
  
  rehash = false; //No more need to rehash this turn, since it was already done
  return;
}
