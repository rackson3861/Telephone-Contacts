#include <bits/stdc++.h>

using namespace std;

# define SIZE 26

// directory node
struct directory {
    struct directory* children[SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    string phone_num;
    bool is_end_of_name;
};

// Returns new directory node (initialized to NULLs)
struct directory* getNode(void)
{
    struct directory* pNode = new directory;

    pNode->is_end_of_name = false;
    pNode->phone_num = "NA";
    for (int i = 0; i <SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts name into directory
// If the name is prefix of directory node, just
// marks leaf node
void insertNode(struct directory* root, string name,string num)
{
    struct directory* name_iter = root;

    for (int i = 0; i < name.length(); i++) {
        int index = name[i] - 'a';
        if (!name_iter->children[index])
            name_iter->children[index] = getNode();

        name_iter = name_iter->children[index];
    }

    // mark last node as leaf
    name_iter->is_end_of_name = true;
    name_iter->phone_num = num;
}

// Returns true if name presents in directory, else
// false
string searchContact(struct directory* root, string name)
{

    struct directory* name_iter = root;

    for (int i = 0; i < name.length(); i++) {
        int index = name[i] - 'a';
        if (!name_iter->children[index])
            return "NA";

        name_iter = name_iter->children[index];
    }

    return (name_iter != NULL && name_iter->is_end_of_name ? name_iter->phone_num : "NA");
}

// Returns true if root has no children, else false
bool isEmpty(directory* root)
{
    for (int i = 0; i < SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// Recursive function to delete a name from given directory
directory* deleteContact(directory* root, string name, int depth = 0)
{
    // If tree is empty
    if (!root)
        return NULL;

    // If last character of name is being processed
    if (depth == name.size()) {

        // This node is no more end of word after
        // removal of given name
        if (root->is_end_of_name)
            root->is_end_of_name = false;

        // If given is not prefix of any other word
        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        }

        return root;
    }

    // If not last character, recur for the child
    // obtained using ASCII value
    int index = name[depth] - 'a';
    root->children[index] =
          deleteContact(root->children[index], name, depth + 1);

    // If root does not have any child (its only child got
    // deleted), and it is not end of another word.
    if (isEmpty(root) && root->is_end_of_name == false) {
        delete (root);
        root = NULL;
    }

    return root;
}

// Driver
int main()
{   system ("color 65");
    cout<<endl<<endl;
    for(int i=0;i<120;i++)
        cout<<"*";
    cout<<endl<<endl;
    cout<<"\t\t\t\t\tWELCOME TO THE WORLD OF DICTIONARY...\n\n";
    cout<<"\t\t 1) ADD CONTACT\n\n";
    cout<<"\t\t 2) DELETE CONTACT\n\n";
    cout<<"\t\t 3) SEARCH CONTACT\n\n";
    cout<<"\t\t 4) EXIT\n\n";
    struct directory* root = getNode();
    cout<<"\n\n\n";
  X:  cout<<"Select your choice : ";
    int c;
    cin>>c;
    string name,exp;
    string num;
    switch(c)
    {
    case 1:  cout<<"\n\n\tEnter the name: ";

             cin>>name;
             cout<<"\n\n\tEnter the contact no: ";

             cin>>num;
             insertNode(root, name,num);
             cout<<"\n\n\t\t\tNumber added successfully\n\n";
             goto X;
             break;

    case 2:  cout<<"\n\n\tEnter the name: ";

             cin>>name;
             deleteContact(root,name);
             cout<<"\n\n\t\t\tNumber deleted successfully\n\n";
             goto X;
             break;

    case 3:  cout<<"\n\n\tEnter the name: ";

             cin>>name;
             exp =searchContact(root,name);
             if(exp=="NA")
                cout<<"\n\n\tContact Not Found..."<<endl;
             else
                cout<<"contact Number is : "<<exp<<endl<<endl;
                goto X;
            break;
    case 4:  goto Y;
             break;

    }

   Y:
    return 0;
}
