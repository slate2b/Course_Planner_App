/////////////////////////////////////////////////////////////////////////////////////
//
//  COURSE PLANNER APP:
//  -------------------
//  A Binary Search Tree (BST) Project 
//  ----------------------------------
//  by slate2b
//
//  This program is designed to act as a basic course planning tool for a 
//  theoretical university.  The program reads course information from a CSV file
//  and loads it into a Binary Search Tree (BST) data structure.  Then it allows
//  the user to print a list of all available courses or to request more detailed 
//  information for a specific course.
// 
//  This project was part of a DSA (Data Structure and Algorithms) course I took
//  in pursuit of my Bachelor's Degree in Computer Science at Southern New 
//  Hampshire University.  
// 
//  For this project, I performed runtime complexity analysis and space complexity
//  analysis for multiple data structures.  I chose to use a BST since it had an 
//  average runtime complexity of Theta(log(n)) and because it handled memory 
//  allocation rather well.  I considered a Hash Table as an alternative data 
//  structure, but I utimately chose a BST because it performs better in the memory
//  efficiency arena.  
// 
//  This project provides the following structures and functionality:
// 
//     * Implements a Binary Search Tree data structure
//     * Traverses the BST In Order (left to right) via recursive algorithm
//     * Inserts a new node into the BST
//     * Populates each new node with data for the Course objects used in this 
//       program
//     * Searches for Course objects within the BST
//     * Retrieves and Prints Course information based on project specifications
//     * Reads data from a csv file and loading it into the BST
//     * Implements a text-based user interface based on project specifications
//     * Implements input validation and error handling
//
/////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <vector>
#include <fstream>


// ---------------------------------------
// Course objects store course information
// ---------------------------------------
struct Course {

    // Attributes for Course objects
    std::string courseNumber;
    std::string name;
    std::vector<std::string> coursePrerequisites;

    // Default Constructor
    Course() {
    }
};



// ------------------------------------------------------------------
// Node objects store course objects and node pointers so we can
// traverse the binary search tree and perform required functionality
// ------------------------------------------------------------------
struct Node {

    // Attributes for Node objects
    Course course;
    //Node* parent; // Not used in current implementation, but could be useful in future implementations
    Node* left;
    Node* right;

    // Basic Constructor
    Node() {
        //Node* parent; // Not used in current implementation, but could be useful in future implementations
        left = nullptr;
        right = nullptr;
    }

    // Constructor with a Course argument
    Node(Course aCourse) {
        //Node* parent; // Not used in current implementation, but could be useful in future implementations
        left = nullptr;
        right = nullptr;
        this->course = aCourse;
    }
};



// ----------------------------------------------------------------------------------
// Binary Search Tree Class Definition
// The Binary Search Tree will be the primary data structure used in this application
// ----------------------------------------------------------------------------------
class BinarySearchTree {

private:

    // Node pointer for the root of the Binary Search Tree
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);

public:

    BinarySearchTree();
    virtual ~BinarySearchTree();
    void MainMenu(BinarySearchTree* courses, std::string csvPath);
    void LoadData(std::string csvPath, BinarySearchTree* courses);
    void Insert(Course course);
    Course Search(std::string courseNumber);
    void InsertCourses(std::vector<std::vector<std::string>> fileContent, BinarySearchTree* courses);
    void PrintSampleSchedule();
    void PrintCourseInformation(BinarySearchTree* courses, std::string courseNumber);
};


// Default Constructor for BinarySearchTree class
// ----------------------------------------------
BinarySearchTree::BinarySearchTree() {

    // Initialize the root of the tree with nullptr
    this->root = nullptr;
}


// Destructor 
// ----------
BinarySearchTree::~BinarySearchTree() {

    // Current implementation does not include a destructor. 
    // Need to implement in the future to prevent memory leaks.
}


// ---------------------------------------------------------------------------------------
// MainMenu
// --------
// Public method to display the main menu and get user input
// 
// @param courses: the pointer to the BinarySearchTree which will hold the course objects
// @param csvPath: the file path for the csv input file which contains the raw course data
// ---------------------------------------------------------------------------------------
void BinarySearchTree::MainMenu(BinarySearchTree* courses, std::string csvPath) {

    // Declare and Initialize variable for main user input
    std::string userMainInput = "0";

    // Declare and initialize a boolean variable to track whether or not the tree has been loaded
    // Implemented to avoid runtime errors for trying to access data which isn't there.
    bool treeLoaded = false;

    // Print application welcome banner
    std::cout
        << "======================================" << std::endl
        << "| Welcome to the ABCU Course Planner |" << std::endl
        << "======================================" << std::endl;

    // The while loop which handles the flow of the program
    while (userMainInput != "9") {

        // Print the main menu
        std::cout << std::endl;
        std::cout << "========================" << std::endl;
        std::cout << "  Menu:" << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << "  1. Load Data Structure" << std::endl;
        std::cout << "  2. Print Course List" << std::endl;
        std::cout << "  3. Print Course" << std::endl;
        std::cout << "  9. Exit" << std::endl;
        std::cout << "========================";
        std::cout << std::endl;
        std::cout << "Enter choice: ";
                
        try {

            // Read user input
            std::cin >> userMainInput;

            // Condition for exception handling
            if (userMainInput != "1" && userMainInput != "2" && userMainInput != "3" && userMainInput != "9") {

                throw char('a');
            }
        }

        // Catch invalid user input exception
        catch (char parameter) {

            // Print invalid selection message
            std::cout << std::endl << "Invalid Selection. Please try again." << std::endl;
        }
        
        //
        // Program routes based on user input
        //

        if (userMainInput == "1") {

            // Instantiate new BinarySearchTree and assign to the courses pointer variable
            courses = new BinarySearchTree();

            // Call the LoadData method, sending the file path and the instantiated Binary Search Tree
            LoadData(csvPath, courses);

            // Once LoadData is finished, print success message
            std::cout << std::endl << "Data Structure loaded successfully." << std::endl;

            // Update treeLoaded variable to true
            treeLoaded = true;
        }

        else if (userMainInput == "2") {

            // If the data structure has already been loaded
            if (treeLoaded) {

                // Call the PrintSampleSchedule method to print the entire course list in alphanumeric order
                courses->PrintSampleSchedule();
            }

            // Otherwise, if the data structure has not been loaded yet
            else {
                
                // Print message to load data structure
                std::cout << std::endl
                    << "Please load the data structure before attempting to print the course list."
                    << std::endl;
            }
        }

        else if (userMainInput == "3") {

            // If the data structure has already been loaded
            if (treeLoaded) {

                // Declare and Instantiate a string variable to hold user input for a particular course
                std::string userCourseInput = "";

                // Prompt user for input
                std::cout << "Enter course number: " << std::endl;

                // Read user input
                std::cin >> userCourseInput;

                // Call the PrintCourseInformation method, sending the Binary Search Tree
                // and the course number from the user.
                PrintCourseInformation(courses, userCourseInput);
            }

            // Otherwise, if the data structure has not been loaded yet
            else {

                // Print message to load data structure
                std::cout << std::endl
                    << "Please load the data structure before attempting to print course information."
                    << std::endl;
            }
        }

        else if (userMainInput == "9") {
            
            // Exit the main menu while loop
            break;
        }
    }
}


// ----------------------------------------------------------------------
// Search
// ------
// Public method to search for a course
// 
// @param courseNumber: the courseNumber for the course we're looking for
// ----------------------------------------------------------------------
Course BinarySearchTree::Search(std::string courseNumber) {

    // Create a node pointer to keep track of the node we're currently looking at
    Node* current = root;

    // While we still have nodes to look at
    while (current != nullptr) {

        // If the node we're looking for matches the node we're looking at
        if (courseNumber == current->course.courseNumber) {

            // Return the node we're looking at
            return current->course;
        }

        // Else if the node we're looking for is less than the node we're looking at
        else if (courseNumber < current->course.courseNumber) {

            // Start looking at the node to the left of the current node (traverse left)
            current = current->left;

            // And go back to the top of the while loop...
        }

        // Else if the node we're looking for is more than the node we're looking at
        else if (courseNumber > current->course.courseNumber) {

            // Start looking at the node to the right of the current node (traverse right)
            current = current->right;

            // And go back to the top of the while loop...
        }
    }

    // If we didn't find the course in the while loop above, then create an empty course
    Course course;

    // And return the empty course
    return course;
}


// --------------------------------------------------------------------------
// PrintCourseInformation
// ----------------------
// Public method to print the full course information for a given course.
//
// @param courses: a pointer to the binary search tree
// @param courseNumber: the courseNumber for the course we're trying to print
// --------------------------------------------------------------------------
void BinarySearchTree::PrintCourseInformation(BinarySearchTree* courses, std::string courseNumber) {

    // Declare a string which we will use to convert alpha characters to uppercase and assign with courseNumber
    std::string uppercaseCourseNumber = courseNumber;

    // For each character in uppercaseCourseNumber
    for (unsigned k = 0; k < uppercaseCourseNumber.length(); ++k) {

        // Convert the character to uppercase
        uppercaseCourseNumber[k] = toupper(uppercaseCourseNumber[k]);
    }

    // Call the Search method sending the courseNumber we're looking for
    Course courseToPrint = courses->Search(uppercaseCourseNumber);

    // As long as we found a course
    if (!courseToPrint.courseNumber.empty()) {

        // Print courseNumber and name
        std::cout << std::endl << courseToPrint.courseNumber << ", " << courseToPrint.name << std::endl;

        // If there are any prerequisites for the given course
        if (!courseToPrint.coursePrerequisites.empty()) {

            // Print first prerequisite
            std::cout << "Prerequisites: " << courseToPrint.coursePrerequisites.at(0);
            
            // For each additional prerequisite
            for (unsigned i = 1; i < courseToPrint.coursePrerequisites.size(); ++i) {

                // Print the additional prerequisite
                std::cout << ", " << courseToPrint.coursePrerequisites.at(i);
            }
        }
        std::cout << std::endl;
    }

    // Otherwise, if we did not find the course the user entered
    else {

        // Print message
        std::cout << std::endl << "Course Number " << courseNumber << " not found." << std::endl;
    }
}


// -----------------------------------------------------------------------------------
// LoadData
// --------
// Public method to read course data from a csv file, parse it into individual rows
// and strings, and push those rows into a string vector.
//
// @param csvPath: the file path for the csv file to be loaded
// @param courses: the pointer for the BinarySearchTree which will hold course objects
// -----------------------------------------------------------------------------------
void BinarySearchTree::LoadData(std::string csvPath, BinarySearchTree* courses) {

    //
    // Strings and vectors used to read data from file
    //

     // Vector to hold the strings for a single row
    std::vector<std::string> row;
    // Vector to hold all the data from the original file
    std::vector<std::string> originalFile;
    //// Vector to hold the components of the file header as individual strings
    //std::vector<std::string> fileHeader;
    // 2D Vector to hold the main contents of the file as individual strings within individual rows
    std::vector<std::vector<std::string>> fileContent;
    // String variable to hold a single line of data
    std::string line;
    // String variable to hold the data read from the input file stream
    std::string fileData;

    //
    // Read the data from the file into a vector called originalFile,
    // where each element of the vector is a single line of data.
    //

    // Input file stream to read data from file into the fileData string variable
    std::ifstream inputFile(csvPath.c_str());

    try {

        // If the inputFile is open
        if (inputFile.is_open()) {

            // While the status flags for the input file are good (ie. no flagged issues)
            while (inputFile.good()) {

                // Get one line of data from the input file and load into the line string variable
                std::getline(inputFile, line);

                // If line is not an empty string
                if (line != "") {

                    // Push the line into the originalFile vector
                    originalFile.push_back(line);
                }
            }

            // Close the inputFile ifstream
            inputFile.close();

            // If the originalFile vector is empty
            if (originalFile.size() == 0) {

                // Throw an exception for No Data in File
                throw 10;
            }

            // String vector iterator to iterate through each line of the original file
            std::vector<std::string>::iterator it;

            // Assign the iterator with the beginning of the originalFile vector
            it = originalFile.begin();

            // For each line in the originalFile
            for (; it != originalFile.end(); it++) {

                // variable to track where each line begins and ends
                bool quoted = false;
                // variable to track our position as we progress through the characters in each line
                int tokenStart = 0;

                // For all characters in the current line
                for (unsigned int i = 0; i != it->length(); i++) {

                    // If the character we are currently looking at is a double quote
                    if (it->at(i) == '"') {

                        // Toggle the value of the quoted variable
                        quoted = ((quoted) ? (false) : (true));
                    }

                    // Else if the character we are currently looking at is a comma AND quoted is false
                    else if (it->at(i) == ',' && !quoted) {

                        // Create a substring beginning with the character at index of tokenStart
                        // and ending with the character at index we are looking at minus tokenStart,
                        // ie. create a substring from a single cell of data, then add it to the row vector
                        row.push_back(it->substr(tokenStart, i - tokenStart));

                        // Assign tokenStart with the next character so we can capture the next cell of data
                        tokenStart = i + 1;
                    }
                }

                // Add the last cell of data from the line into the row vector
                row.push_back(it->substr(tokenStart, it->length() - tokenStart));

                // Add the row to the 2D fileContent vector
                fileContent.push_back(row);

                // Clear the contents of the row vector so it can be used again in the next loop iteration
                row.clear();
            }

            // Call the InsertCourses method sending the fileContent vector we just completed
            InsertCourses(fileContent, courses);
        }

        // Otherwise, if the file did not open properly
        else {

            // Throw an exception for Unable to Open File
            throw float(1.0);
        }
    }

    // If error thrown because there was no data in the file
    catch (int parameter) {

        std::cout << std::endl << "No data in file: " << csvPath << std::endl << std::endl;
    }

    // If error thrown because file did not open properly
    catch (float parameter) {

        std::cout << std::endl << "Unable to open file: " << csvPath << std::endl << std::endl;
    }
}


// -----------------------------------------------------------------------------------
// InsertCourses
// -------------
// Private method to take the contents of the csv file (sent from the LoadData method)
// and create Course Objects, then send them to the Insert method in order to insert
// them into the Binary Search Tree.
//
// @param node: the node in the tree which we are currently reviewing
// @param course: the Course object to be added
// -----------------------------------------------------------------------------------
void BinarySearchTree::InsertCourses(std::vector<std::vector<std::string>> fileContent, BinarySearchTree* courses) {

    // Variable to keep track of the rows in the fileContent vector
    unsigned int i = 0;
    // Variable to keep track of the cells of data in each row
    unsigned int j = 0;
    // Variable to keep track of any prerequisite data in each row
    unsigned int k = 0;

    try {

        // For each row in the fileContent vector
        for (i; i < fileContent.size(); ++i) {

            // Vector to temporarily store prerequisites for the course to be added
            std::vector<std::string> prerequisites;
            // Course object to temporarily store the course data to be added
            Course course;

            // Assign j with 0 to look at the first cell in the current row
            j = 0;
            // Assign courseNumber with the data in the first cell of the current row
            course.courseNumber = fileContent[i][j];

            // Assign j with 1 to look at the second cell in the current row
            j = 1;
            // Assign name with the data in the second cell of the current row
            course.name = fileContent[i][j];

            // If there are additional cells of data in the current row
            if (fileContent.at(i).size() > 2) {

                // For any additional cells of data
                for (k = 2; k < fileContent.at(i).size(); ++k) {

                    // Add the cell of data to the temporary prerequisites vector
                    prerequisites.push_back(fileContent[i][k]);
                }
            }

            // Assign coursePrerequisites with the 
            course.coursePrerequisites = prerequisites;

            // Insert the new course into the courses binary search tree
            courses->Insert(course);
        }
    }

    // Catch standard runtime errors
    catch (std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
    }
}


// -------------------------------------------------------------
// Insert
// ------
// Public method to insert a course into the Binary Search Tree.
//
// In this implementation of the program, Insert is only called
// from the InsertCourses method which is called from the
// LoadData method.
//
// @param course: the Course object we're trying to insert
// -------------------------------------------------------------
void BinarySearchTree::Insert(Course course) {

    // If the tree is empty (if the root node is null) 
    if (root == nullptr) {

        // Create a new Node with the course we are given and assign it to the tree's root
        root = new Node(course);
    }

    // Otherwise if the tree is NOT empty
    else {

        // Call addNode and send in the root node as the starting point along with the course we want to insert
        this->addNode(root, course);
    }
}


// ------------------------------------------------------------------------------
// addNode
// -------
// Private method to add a course to a node in the Binary Search Tree (recursive)
//
// @param node: the node in the tree which we are currently reviewing
// @param course: the Course object to be added
// ------------------------------------------------------------------------------
void BinarySearchTree::addNode(Node* node, Course course) {

    // ==============================================================================================
    // NOTE: The node argument for this method is used as a potential parent for the node to be added
    // ==============================================================================================

    // If the root of the tree is null (if the tree is empty)
    // NOTE: Under normal circumstances, this program should never enter this condition
    if (root == nullptr) {

        // Assign the node to the root of the tree
        root = node;
    }

    // Otherwise if the root of the tree is NOT null (the tree is not empty)
    else {

        // If the node we're trying to add is less than the current node we're looking at
        if (course.courseNumber.compare(node->course.courseNumber) < 0) {

            // If the current node's left child is null
            if (node->left == nullptr) {

                // Instantiate a new node with the given course and assign to the current node's left child pointer
                node->left = new Node(course);
            }

            // Otherwise if the current node already has a left child node...
            else {

                // Assign the left child as the next node to look at and call addNode again
                this->addNode(node->left, course);
            }
        }

        // Otherwise if the node we're trying to add is greater than or equal to the current node
        else {

            // If the current node's right child is null
            if (node->right == nullptr) {

                // Instantiate a new node with the given course and assign to the current node's right child pointer
                node->right = new Node(course);
            }

            // Otherwise if the current node already has a right child node...
            else {

                // Assign the right child as the next node to look at and call addNode again
                this->addNode(node->right, course);
            }
        }
    }
}


// --------------------------------------------------------------------------------------
// PrintSampleSchedule
// -------------------
// Public method sends the tree's root to the private inOrder method to traverse the tree
// --------------------------------------------------------------------------------------
void BinarySearchTree::PrintSampleSchedule() {

    std::cout << std::endl;

    // Call the private inOrder method and send the root node as the starting point
    this->inOrder(root);
}


// ----------------------------------------------------------------------------
// inOrder
// -------
// Private recursive method to traverse a binary search tree from left to right
// and print basic course information for each node along the way.
//
// @param node: the node in the tree which we are currently reviewing
// ----------------------------------------------------------------------------
void BinarySearchTree::inOrder(Node* node) {

    // If the node we're starting from is null, there's nothing to traverse
    if (node == nullptr) {

        // Return
        return;
    }

    // Otherwise there is something to traverse, so...
    else {

        // Traverse one level down and left from the node we're currently looking at
        // by calling inOrder again from the left child of the node we're currently looking at.
        // NOTE: These calls will continue until we reach the end of the current leftwise traversal.
        inOrder(node->left);

        // Once we're traversed as far as we can to the left, 
        // print the courseNumber and name stored in the node we're currently looking at.
        // NOTE: The program will print the nodes from left to right
        std::cout << node->course.courseNumber << ": " << node->course.name << std::endl;

        // Traverse one level down and right from the node we're currently looking at
        // by calling inOrder again from the right child of the node we're currently looking at.
        // NOTE: These calls will continue until we reach the end of the current rightwise traversal
        inOrder(node->right);
    }
};


// --------------------------------------------------------------
// The Main Method
// ---------------
// The main method for the program. 
// * Defines the file path for the csv input file
// * Declares the BinarySearchTree courses pointer 
// * Initializes the BinarySearchTree courses pointer to nullptr
// * Declares an empty course object
// * Calls the MainMenu method
// --------------------------------------------------------------
int main()
{
    std::string csvPath = "ABCU_Advising_Program_Input.csv";
    BinarySearchTree* courses = nullptr;
    Course course;

    // Call the MainMenu method which handles program flow
    courses->MainMenu(courses, csvPath);

    // When user chooses to exit the program through the MainMenu method, 
    // Print the farewell banner
    std::cout << std::endl
        << "===========================================" << std::endl
        << "| Thank you for using the course planner! |" << std::endl
        << "===========================================" << std::endl
        << std::endl;

    // End program
    return 0;
}

