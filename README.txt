//=========================================================
//Project: SpamEmail
//Your name: Omar Gonzalez
//Contact: omargb22@gmail.com
//Complier:  G++
//File type: README.txt
//=========================================================

-program file name:
 "SpamEmail.C"

-Programming Language:
 C++

-Purpose Of Program:
 To implement and simulate a finite automata for a given language and identify spam emails given a collection of emails.

------HOW TO COMPILE-------
g++ -o Gonzalez_proj1  Gonzalez_proj1.C

-------HOW TO RUN-------
./main

*messagefile.txt should contain emails*


Output:
-Out Puts will display Transition functions of our FA determining beggining of email and also Transition Functions of our FA determining if email is a spam
-it should show the total amount of emails in messsagefile.txt and display the email ID's of the emails containing spam

Task:
Suppose you want to use pattern matching to identify email messages that are spam email given a collection of emails.
Specifications: Your programming assignment is to design and implement an FA that accepts strings such as “free access”, “free software”, “free vacation”, “free trials”, and “win/winner(s)”. These strings must be in the body of the message not the subject. Thus, the language to be accepted by your automaton is as follows.
     L = { w = “free access”, w = “free software”,
           w = “free vacation”, w = “free trials”, w = “win”,
           w = “winner”, w = “winners”, w = “winnings”}
The body of the message may or may not have these strings within “ “. Your automaton must accept these strings within “ “ and without “ “.
The implementation of the FA must simulate the FA by reading an input symbol, computing the transition function and displaying the state or set of states the FA reaches when processing this symbol. Your FA must process one symbol at a time, not words or phrases at a time.
Input: A text file named messagefile.txt with xml tags as shown below. Each message is a document identified by msgN, where N is a number starting with 1.
<DOC>
<DOCID> msgN </DOCID> Subject
... body of the email ... </DOC>
 
The entire text of the email is normalized; that is, all characters are lower case, and there is a space in between words and punctuation.
Output: Display each state reached when your FA process one input symbol.
When your program finishes processing all the emails display the emails’ IDs of those
messages identified as spam.


