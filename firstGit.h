#include <iostream>

using namespace std;



//a Node that that can store any type of data in it
template<typename T>
struct Node{

    // pointer to left and right children
    struct Node<T>* left;
    struct Node<T>* right;
    // data that holds any type
    T data;
    //int variable that holds the frequency of the node
    int count;
    //constructor that initalizes the data variable and sets the count to 0
    Node<T>(T data){
        left = right = nullptr;
        this->data = data;
        this->count = 0;
    }
};




template<typename T>
class bst{

public:

    // below is a node poiinter that points to the root node
    // This pointer is how I chose to interact and modify the tree
    struct Node<T>* root;
    
    // Defalt constructor
    bst(){
        root = nullptr;
    }

    // Constructor that creates the root node. (first node in the tree)
    bst(T data){
        root = create_Node(data);
    }

    // Defalt destructor
    ~bst(){
        cout<<"Destructor has executed.";
    }

    // Method below creates a new node and assigns values to the non-static members of struct node
    // returns a pointer to the newly created node
    Node<T>* create_Node(T data){
        struct Node<T>* new_Node = new Node<T>(data);
        
        return new_Node;
    }

    // Method below uses recursion to place a string in the correct spot on the BST
    Node<T>* insert(Node<T>* root, T data){ 
        
        // Base case
        if(root == nullptr){
            root = create_Node(data);
        }

        // If the word has already been added to the tree then incriments the "count" variable that every node holds
        // returns pointer to the node that it matches
        if(root->data == data){
            root->count = root->count + 1;
            return root;
        }

        // Uses recursion
        // inserts to right of tree or subtree
        else if(root->data < data){
            root->right = insert(root->right, data);
        }

        // Uses recursion
        // inserts to left of tree or subtree
        else if(root->data > data){
            root->left = insert(root->left, data);
        }

        // returns pointer to the inserted node
        return root;
    }

    // The method uses recursion to search the tree if there is a node that holds a string matching the string being searched for.
    // returns NULL if the node doesn't exsist
    // returns pointer to the node if it was found
    Node<T>* search(Node<T>* root, T data){
        
        if(root == NULL){
            return NULL;
        }

        else if(root->data < data){
           return search(root->right, data);
        }

        else if(root->data > data){
            return search(root->left, data);
        }
        
        else{
            return root;
        }

    }

    // Returns the frquency (or "count" variable) of the node holding the corresponding string data
    int frequency(Node<T>* root, T data){
        
        //Checks if Node exists
        struct Node<T>* found_at = search(root, data);
        
        //If it doesnt exist then returns 0
        if(found_at == nullptr){
            return 0;
        }
        
        //if the node exists then returns the count of the node
        else{
            return found_at->count;
        }
    }

    // Deletes a Node
    Node<T>* deleteNode(struct Node<T>* root, T data){
        
        // Base case
        if(root == NULL){
            return root;
        }

        // Uses recursion to find then delete node right of subtree
        if(root->data < data){
            root->right = deleteNode(root->right, data);
        }

        // Uses recursion to find then delete node left of subtree
        else if(root->data > data){
            root->left = deleteNode(root->left, data);
        }

        // Once the node is found
        else{
            
            // deletes if the node doesnt have a left child
            if (root->left == nullptr){
                struct Node<T> *temp = root->right;
                delete root;
                return temp;
            }
            
            // deletes if the node doesnt have a right child
            else if (root->right == nullptr){
                struct Node<T> *temp = root->left;
                delete root;
                return temp;
            }
            
            // if node has 2 childrren
            // uses "helper" method to find the min value the the subtree where the desired node is the root
            // The min node will replace the node being deleted
            // then we delete the leaf node that holds the same data as the temp node
            struct Node<T>* temp = findMinNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        
        return root;
    }

    // find the minimum node on tree or subtree
    Node<T>* findMinNode(Node<T>* node){
        struct Node<T>* current = node;

        while(current != nullptr && current->left != nullptr){
            current = current->left;
        }

        return current;
    }

    // returns a boolean value representing the nodes existence
    bool exists(T data){
        struct Node<T>* item = search(root, data);

        if(item != nullptr){
            return true;
        }

        return false;

    }

    // Counts how many nodes are in the tree
    int size(Node<T>* root){
        if(root==nullptr){
            return 0;
        }

        else{
            return size(root->left) + 1 + size(root->right);
        }
    }

    //deletes the BST node by node
    void deleteTree(Node<T>* root){
        if(root==nullptr){
            return;
        }

        deleteTree(root->left);
        deleteTree(root->right);

        delete root;
    }

    // Function below uses recursion to print the nodes from the tree in alphebetical order (smallest to largest)
    void printInorder(struct Node<T>* root){
    
        if (root == nullptr){
            return;
        }
 
        printInorder(root->left);
 
        cout << root->data << " ";
 
        printInorder(root->right);
    }
};