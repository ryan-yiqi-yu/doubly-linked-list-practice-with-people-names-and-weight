
#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

class nameandweightdll{ //This class creates a doubly linked list sorting weight and names
private:
    struct node{ //this struct creates a node which stores a person's name and weight and pointers pointing to ascending name and weight
        int weight;
        string name;
        node *heavierweight = NULL, *alphaname = NULL; //pointers pointing to heavier weight and alphabetical name initialized as NULL
    };
    int count = 0; //this keeps count of the number of people in the list
    node *alphahead=NULL, *weighthead=NULL, *ptr=NULL, *trailingptr=NULL; //these pointers keep track of the head of the sorted weight and name list. ptr and trailingptr are used to sort the list later on.
    
public:
    void pushdll(int NewWeight, string NewName){ //this function pushes a new person into the list, in sorted name and weight order
     
        node *NewPerson=new node; //A new node is created for the new person pushed into the list
        NewPerson->weight=NewWeight; //Setting the weight for the new person
        NewPerson->name=NewName; //setting the name for the new person
        if (IsEmpty()){ //If IsEmpty() is true, the new person pushed will be the only in the list
            alphahead=NewPerson; //the lone person in the list will be the head of alphabetical names
            weighthead=NewPerson; //the lone person in the list will be the head of ascending weight
        }
        else{ //in this else, when the list is not empty, this program traverses the list and finds a position to place the new person, keeping the list sorted
           
            ptr=alphahead; //ptr will be started off at the head of the alphabetical order, which will then be traversed
            trailingptr=NULL; //the trailingptr will first be started off at null
            while(true){ //to add the new person in sorted order, the new person will enter this while loop to iterate over the list of exisiting people
                
                if (ptr == NULL){ //if the ptr traverses to the end of the list(NULL), the person will be appended to the end of the list
              
                    trailingptr->alphaname=NewPerson; //appending the person to the end of the list, the previous last person in the list will have its name pointer pointing to the new person
                    break; //once the person is pushed into the list, the loop will be broken out of
                }
                else if (NewName<ptr->name){ //this else if suite is for a person who has a name who goes before the current person in the list. they will be pushed into the list
                    
                    NewPerson->alphaname=ptr; //to be pushed into the list, the new person's alphabretical pointer will point to the current person in the list
                    if(trailingptr!=NULL){ // if the trailingptr is not NULL, that indicates that the new person is somewhere in the middle of the list
                        trailingptr->alphaname=NewPerson; //The trailingptr will have its name pointer assigned to the new person, in order to push the new person in sorted order
                    }
                    else{ //if the trailingptr is NULL, that indicates that the new person will be pushed to the top of the list as their name is the the earliest in the alphabet
                        alphahead=NewPerson; //the head of the names list will be assigned to the new person
                    }
                    
                    break;//once the person is pushed into the list, the loop will be broken
                }
                else{ //this keeps the ptr traversing the list if neither of the suites before were satisfied
                    trailingptr=ptr; //in order to continue traversing, the trailingptr will be assigned the current pointer's node
                    ptr=ptr->alphaname; //the current pointer will be assigned to the next node in the list
                }
                }
            
             
            ptr=weighthead;//ptr will be started off at the head of the alphabetical order, which will then be traversed
            trailingptr=NULL;//the trailingptr will first be started off at null
            while(true){//to add the new person in sorted weight order, the new person will enter this while loop to iterate over the list of exisiting people and their weights
                
                if (ptr == NULL){//if the ptr traverses to the end of the list(NULL), the person will be appended to the end of the list
                    trailingptr->heavierweight=NewPerson;//appending the person to the end of the list, the previous last person of the list will have its weight pointer assigned to the new person
                    break;//once the person is pushed into the list, the loop will be broken out of
                }
                else if (NewWeight<ptr->weight){//this else-if suite is for a person who has a weight who goes less than the current person in the list. they will be pushed somewhere onto the exisitng list
                    
                    NewPerson->heavierweight=ptr;//to be pushed into the list, the new person's weight pointer will point to the current person in the list
                    if(trailingptr!=NULL){// if the trailingptr is not NULL, that indicates that the new person's weight is somewhere in the middle of the list
                        trailingptr->heavierweight=NewPerson;//The trailingptr will have its weight pointer assigned to the new person, in order to push the new person in sorted order
                        
                    }
                    else{//if the trailingptr is NULL, that indicates that the new person will be pushed to the top of the list as they are the heaviest person in the list
                        weighthead=NewPerson;//the head of the weight list will now be assigned to the new person
                       
                    }
                    
                    break;//once the person is pushed into the list, the loop will be broken
                }
                else{//this keeps the ptr traversing the list if neither of the suites before were satisfied
                    trailingptr=ptr; //in order to continue traversing, the trailingptr will be assigned the current pointer's node
                    ptr=ptr->heavierweight;//the current pointer will be assigned to the next node in the list
                }
                }
             
             
            
        }
        count++; //once all the operaitons to push a person are complete, the total count of people in the list will be incremented
    }
    
    bool IsEmpty(){ //this boolean function checks if the list is empty
        if (count==0){ //if the count of the list is 0, that indicates that the list is empty
            return true; //function returns true if empty
        }
        else{ //the program will enter this else suite if the list is not empty
            return false; //function returns false if the list is not empty
        }
    }
    
    void readandpush(){ //this void function reads the given "Names.txt" text file and pushes each person into the sorted list
        ifstream names; //creating an instream object
        names.open("Names.txt"); //opens the given file on canvas to be read
        int weight; //creates a variable that will be the weight of each person
        string name, x; //these string variables will be used to read names and weight from teh text file
      
        if(names.is_open()){ //this if suite will be executed if the file object is open
            while(names>>x){ //this iterates the text file line by line

                if(stringstream(x)>>weight){ //once the weight of the person is entered, this if suite will be executed
                    pushdll(weight, name); //since the name and weight have been assigned, they will be pushed inot the list
                }
                else{ //this else suite will be exexuted if the line is not an integer
                    name=x; // assigns the name taken from the text file to the name variable
                }
            }
            names.close(); //once the text file is read through, it is closed
        }
        else{
            cout<<"UNABLE TO OPEN FILE"<<endl; //this else suite is executed if the file could not be opened
        }
    }
    void printalpha(){ //this function prints the people in the list in alphabetical order
        ptr=alphahead; //this sets the ptr to the head of the alphabetical ordered people, and it will iterate over th elist and print each person
        cout<<"In alphabetical order: ";
        while(ptr!=NULL){ //this while statement iterates over the list in alphabetical order until it reaches the very end
            cout<<ptr->name<<" - "; //print person's name
            cout<<ptr->weight<<", "; //print person's weight
            ptr=ptr->alphaname; //the ptr is moved to the next peron in the list to continue traversing
        }
        cout<<endl<<endl;
    }
    void printweight(){//this function prints the people in the list in ascending weight order
        ptr=weighthead;//this sets the ptr to the head of the weight ordered people, and it will iterate over the list and print each person
        cout<<"In ascending weight: ";
        while(ptr!=NULL){//this while statement iterates over the list in weighted order until it reaches the very end of the list
            cout<<ptr->name<<" - ";//print person's name
            cout<<ptr->weight<<", ";//print person's weight
            ptr=ptr->heavierweight;//the ptr is moved to the next heaviest peron in the list to continue traversing
        }
        cout<<endl<<endl;
    }
};

int main(){ //this is where the test code will be executed
    nameandweightdll test; //creating an weight and name doubly linked list object
    test.readandpush(); //running this function allows the program to read people from the given text file and push the people into the sorted linked list
    test.printalpha(); //this prints the people in the sorted linked list in alphabetical order
    test.printweight();//this prints the people in the sorted linked list in ascending weight order
    
}

/* THE FOLLOWING FROM LINES 155 TO 159 IS THE OUTPUT:
 
 In alphabetical order: Abe - 199, Annabelle - 99, April - 117, Bob - 156, Bobby - 109, Brian - 150, Chris - 175, Claire - 124, Jason - 182, Jim - 150, Kevin - 145, Michael - 174, Richard - 200, Steven - 164, Tom - 212, .

 In ascending weight: Annabelle - 99, Bobby - 109, April - 117, Claire - 124, Kevin - 145, Jim - 150, Brian - 150, Bob - 156, Steven - 164, Michael - 174, Chris - 175, Jason - 182, Abe - 199, Richard - 200, Tom - 212, .

 Program ended with exit code: 0
 
 */
