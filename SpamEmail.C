//=========================================================
//Project: SpamEmail
//Your name: Omar Gonzalez
//Contact: omargb22@gmail.com
//Complier:  G++
//File type: main file -> SpamEmail.C
// Purpose: To implement and simulate a finite automata for a given language and identify spam emails given a collection of emails.
//=========================================================

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;
//global variables
int Index=0; // Index for our vector of character words that will contain each character in the email
int message=0; // message counter that will increment each time it goes through
//-----------------------------------
// function prototypes
vector<char> ReadEmails(); // function to read email into a string of vectors
bool FiniteStateMachine(vector<int>&spam,vector<char>&words, int &Index); // function to implement our Finate State Machine
void TransitionFunction(char temp, int state, bool event); // function to record our Our transition functions
bool BeginTransitionFunction(vector<char>&words, int &Index, int &message);
void PrintVector(vector<int> X); // this function will print our vectors that were used
void GetSpam(vector<int>&spam,int &message);// this function should help to keep track of our emails id's containing spam
void SkipSubject(vector<char>words,int &tempIndex); //This function should skip subject of every email
//--------------------------------------------
//Main Function
int main()
{
  bool check=true;      // checkk will be used to check whenever true is return from FiniteStateMachine which means Final State was reached
  vector<char> words;   // Vector contining Emails from messagefile.txt
  vector<int> spam;     // Vecotr containing Final Spam email
  words = ReadEmails(); // calling ReadEmails() too read emails to our vector words

  //FiniteStateMachine Will keep getting called until there is no more emails in messagefile.txt
  do {
    check = FiniteStateMachine(spam,words,Index);
  } while(check==true); //stop when FiniteStateMachine returns false meaning didnt reach reach final state

  if(spam.size()== 0) //if vector spam is 0 then there was no spam email
    {
      cout << "=====================================================" << endl;
      cout << "There was no spam emails!!!" << endl;
    }
  else //Print out total number of emails and Email ID's of emails containg spam emails
    {
      cout << "=====================================================" << endl;
      cout << "Total Number of Emails = " << message << endl;
      cout <<"The Following Emails were spam:" << endl;
      PrintVector(spam);
    }

  return 0; // end of program
}
//------------------------------------------------------------------------------
/*
ReadEmails
Purpose: This Function will read the emails character by charter including spaces and store characters into Vector of characters words
*/
//------------------------------------------------------------------------------
vector<char> ReadEmails()
{
  vector<char>X; // vector V
  char temp; // temp string variable

  ifstream fin;
  fin.open("messagefile.txt"); // open  messagefile.txt file
  fin >> noskipws >> temp;
  while(fin)     // reading string by string and sotring it into vector
    {
      X.push_back(temp);
      fin >> noskipws >> temp;
    }
  fin.close(); // closing messagefile.txt file
  return (X); // return vector after we finish reading everything
}
//------------------------------------------------------------------------------
/*
FiniteStateMachine
-Purpose: This function will check for the following strings character by character to determine Email is a spam:"free access","free sofware","free vacation","free trials","win","winner","winners", "winnings"
This function will also check for string </DOC> when email is not spam to dtermine end of email
return true when final state is reach
return false when there is no more emails
*/
//------------------------------------------------------------------------------
bool FiniteStateMachine(vector<int>&spam,vector<char>& words, int &Index)
{
  bool check=false;   //boolian variable check will be used to check if there is emails to be checked for spam
  bool event= false;  //boolean variable event will help to determine when final state has been reached, if final state is reached then event=true
  int  state=0;        //interger variable state will help to determine state.initial state starting at q0
  char temp;          //character variable temp will hold our characers in the email

  check = BeginTransitionFunction(words,Index,message); //checking for beggining of email if no more emails to be check then variable check=false
  if (check==false)
    {
      cout << "MESSAGE " << message+1 << " was not an email in the file "<< endl;
      return false; //return false to the main when there is no more emails
      cout<< "No more emails to be read" << endl;
    }
  else //there is email to be check
    {
      cout<< "Transition Function to determine if Email is a spam: (where qf is our final state) " << endl;
      cout<< "Note that if </DOC> is reached (qf) is not a spam email" << endl;
    }
  //Finate state to determine if email contains spam
  //-------------------------------------------------
  int tempIndex=Index; // interger variable tempIndex will be used to move through vector words
  while(event!=true && Index<words.size())
    {
      temp=words[tempIndex];
      if(temp=='S')
      {
        SkipSubject(words,tempIndex);
      }
      switch(state)
	      {
        	case 0: if(((temp== 'w' && words[tempIndex-1]==' ')|| (temp=='f' && words[tempIndex-1]==' ')|| temp=='<')&& event==false){event=false; TransitionFunction(temp,state,event); state++;}
                  else{state=0;event=false;}
        	  break;
        	case 1: if((temp== 'i'|| temp=='r'|| temp=='/')&& event==false){event=false; TransitionFunction(temp,state,event); state++;}
                  else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 " << endl;}
        	  break;
        	case 2: //win final state
                  if((temp == 'n' && (words[tempIndex+1]==' ' || words[tempIndex+1]=='"')) && words[tempIndex-2]!='f'){event= true; GetSpam(spam,message); TransitionFunction(temp,state,event);tempIndex++; Index=tempIndex;return true;}
                  if((temp =='n'|| temp=='e' || temp=='D') && event==false){event=false; TransitionFunction(temp,state,event); state++;}
                  else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 "<< endl ;}
        	  break;
          case 3:if((temp =='n'|| temp=='e'|| temp=='O') && event==false){event=false;TransitionFunction(temp,state,event); state++;}
                else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 " << endl;}
            break;
          case 4:if((temp == 'e' || temp=='i'|| temp==' ' || temp=='C')&& event==false){event=false; TransitionFunction(temp,state,event); state++;}
                 else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 "<< endl ;}
            break;
          case 5://winner meaning spam & </DOC> meaning no spam final states
                  if(temp == '>' && event==false){event= true; TransitionFunction(temp,state,event);tempIndex++; Index=tempIndex;return true;}
                  if(temp == 'r' && (words[tempIndex+1]==' ' || words[tempIndex+1]=='"')&& event==false){event= true; GetSpam(spam,message); TransitionFunction(temp,state,event);tempIndex++; Index=tempIndex;return true;}
                  if((temp=='r' || temp=='n' || temp=='a' || temp=='s'|| temp=='v'|| temp=='t') && event==false){event=false;TransitionFunction(temp,state,event); state++;}
                  else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 " << endl;}
              break;
          case 6://winners final states
                  if(temp == 's' && (words[tempIndex+1]==' ' || words[tempIndex+1]=='"')&& event==false){event= true; GetSpam(spam,message); TransitionFunction(temp,state,event);tempIndex++; Index=tempIndex;return true;}
                  if((temp=='g'|| temp=='c' || temp=='o'|| temp=='a'|| temp=='r')&& event==false){event=false; TransitionFunction(temp,state,event); state++;}
                 else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 " << endl;}
               break;
          case 7: //winnings final state
                  if(temp == 's' && (words[tempIndex+1]==' ' || words[tempIndex+1]=='"')){event= true; GetSpam(spam,message); TransitionFunction(temp,state,event);tempIndex++; Index=tempIndex;return true;}
                  if((temp=='c' || temp=='f'||temp=='i')&& event==false){event=false; TransitionFunction(temp,state,event); state++;}
                  else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 " << endl;}
                break;
          case 8: if((temp=='e' || temp=='t'|| temp=='a')&& event==false){event=false; TransitionFunction(temp,state,event); state++;}
                  else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 " << endl;}
                break;
          case 9: if((temp=='s' || temp=='w'|| temp=='t'|| temp=='l')&& event==false){event=false; TransitionFunction(temp,state,event); state++;}
                  else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 "<< endl ;}
                break;
          case 10://Free acesss & free trials final states
                  if(temp == 's' && (words[tempIndex+1]==' ' || words[tempIndex+1]=='"')){event= true; GetSpam(spam,message); TransitionFunction(temp,state,event);tempIndex++; Index=tempIndex;return true;}
                  if((temp=='a'|| temp=='i')&& event==false){event=false; TransitionFunction(temp,state,event); state++;}
                  else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 " << endl;}
                break;
          case 11: if((temp=='r'|| temp=='o')&& event==false){event=false; TransitionFunction(temp,state,event); state++;}
                    else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 " << endl;}
                break;
          case 12://free sofware & free vacation finals state
                  if(temp == 'n' && (words[tempIndex+1]==' ' || words[tempIndex+1]=='"')){event= true; GetSpam(spam,message); TransitionFunction(temp,state,event);tempIndex++; Index=tempIndex;return true;}
                  if(temp == 'e' && (words[tempIndex+1]==' ' || words[tempIndex+1]=='"')){event= true; GetSpam(spam,message); TransitionFunction(temp,state,event);tempIndex++; Index=tempIndex;return true;}
                  else {state=0;event=false;cout << "$(q"<< state  << "," << temp << ")=q0 " << endl;}
                break;
              };
              //anable this if loop if you want to see all the states that will stay at q0
            /*  if (state ==0)
              {
                cout << "$(q"<< state  << "," << temp << ")=q0, " ;
              }*/
        tempIndex++; //incrementing tempIndex to read next character
    }
  Index= tempIndex; //set global Index to tempIndex after done
  //return true;
  }
  //------------------------------------------------------------------------------
  /*
  BeginTransitionFunction
  Purpose: This function will help us to determine the beggining of every email in messagefile.txt
  return true every time string <DOCID> is reached which means starting of the email
  return false when there is no more emails
  */
  //------------------------------------------------------------------------------
  bool BeginTransitionFunction(vector<char>&words,int &Index, int &message)
  {
    bool event=false; //boolean variable event
    char temp;        //character variable temp
    int state=0;      //interger variable state

    //printing out ID for current email
    cout << "-------------------------------------------------------" << endl;
    cout << "Message " << message+1<<":" << endl;
    cout << "Transition functions to determine beggining of email: (where qf is our final state)" << endl;

    //finate state machine to determine the beggining of each email whehre "<DOCID>" is the final state
    while (event!=true && Index<words.size())
      {
	temp=words[Index];
	switch(state)
	  {
	  case 0:
	    if (temp == '<'){event= false;TransitionFunction(temp,state,event);state++; break;}
	    else {event=false;state =0;}
	    break;
	  case 1:
	    if (temp== 'D'){event= false; TransitionFunction(temp,state,event);state++; break;}
	    else
	      {event=false;state =0;}
	    break;
	  case 2:
	    if (temp== 'O'){ event= false; TransitionFunction(temp,state,event); state++; break;}
	    else {event=false;state =0;}
	    break;
	  case 3:
	    if (temp== 'C'){event= false;TransitionFunction(temp,state,event); state++; break;}
	    else
	      {event=false;state =0;}
            break;
	  case 4:
	    if (temp== 'I'){event= false;TransitionFunction(temp,state,event);state++; break;}
	    else {event=false; state =0;}
            break;
	  case 5:
	    if (temp== 'D'){event= false; TransitionFunction(temp,state,event);state++; break;}
	    else {event=false;state =0;}
            break;
	  case 6:
	    if (temp== '>'){event= true; TransitionFunction(temp,state,event); message++;state++;Index++; return true;}
	    else
	      {event=false; state=0;};
            break;
	  default: break;
	  }
	Index++;
      }
    return false;
  }
  //------------------------------------------------------------------------------
  /*
  TransitionFunction
  Purpose: This Function will print out our Transition Function
  */
  //------------------------------------------------------------------------------
  void TransitionFunction(char temp, int state, bool event)
  {
    if (event == false)
      cout << "$(q"<< state  << "," << temp << ")=q" << state +1 << endl;
    if(event == true)
      cout << "$(q"<< state  << "," << temp << ")=qf" << ", ***Final State Has Been Reached" << endl;
  };
  //------------------------------------------------------------------------------
  /*
  GetSpam
  Purpose: This FUnction will help us to keep track of our spam emails ID by storing into a vector when a spam email is detected in FiniteStateMachine function
  */
  //------------------------------------------------------------------------------
  void GetSpam(vector<int>&spam,int &message)
  {
    spam.push_back(message);
  }
  //------------------------------------------------------------------------------
  /*
  PrintVector
  Purpose: This Function Prints out Any Vector
  */
  //------------------------------------------------------------------------------
 void PrintVector(vector<int> X)
 {
     for (int i=0; i<X.size(); i++)//int i= Local counter used for this for loop
     {
      cout << "Email ID's containing spam: " << X[i] << endl; //printing out each Message ID for spam emails
     }
 }
 //------------------------------------------------------------------------------
 /*
 SkipSubject
 Purpose: to Skip subect of every email
 */
 //------------------------------------------------------------------------------
void SkipSubject(vector<char>words,int &tempIndex)
{
  while(words[tempIndex]!='\n')
  {
    tempIndex++;
  }
}
