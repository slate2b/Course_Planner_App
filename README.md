# Course Planner App:
---------------------
A Binary Search Tree (BST) Project 
----------------------------------
by slate2b

This program is designed to act as a basic course planning tool for a 
theoretical university.  The program reads course information from a CSV file
and loads it into a Binary Search Tree (BST) data structure.  Then it allows
the user to print a list of all available courses or to request more detailed 
information for a specific course.

This project was part of a DSA (Data Structure and Algorithms) course I took
in pursuit of my Bachelor's Degree in Computer Science at Southern New 
Hampshire University.  

For this project, I performed runtime complexity analysis and space complexity
analysis for multiple data structures.  I chose to use a BST since it had an 
average runtime complexity of Theta(log(n)) and because it handled memory 
allocation rather well.  I considered a Hash Table as an alternative data 
structure, but I utimately chose a BST because it performs better in the memory
efficiency arena.  

![main_menu_course_planner](https://user-images.githubusercontent.com/88697660/191091185-6e82e438-b404-4f7f-8425-e323c19c6afd.PNG)
 
This project provides the following structures and functionality:

* Implements a Binary Search Tree data structure
* Traverses the BST In Order (left to right) via recursive algorithm
* Inserts a new node into the BST
* Populates each new node with data for the Course objects used in this 
  program
* Searches for Course objects within the BST
* Retrieves and Prints Course information based on project specifications
* Reads data from a csv file and loading it into the BST
* Implements a text-based user interface based on project specifications
* Implements input validation and error handling
