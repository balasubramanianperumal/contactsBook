#include<iostream>
#include<vector>
using namespace std;

class Node
{
	public:
	long int key;
	Node *left;
	Node *right;
    string name;
	int height;
};
class BNode{
    public:
        Node *contact;
        BNode *left;
        BNode *right;
};
class BST{
    public:
        BNode* head;
    BNode* buildTree(BNode* root,Node* contact){
        if (root==NULL) {
            BNode* newNode = new BNode();
            newNode->contact = contact;
            newNode->left = NULL;
            newNode->right = NULL;
            return newNode;
        }
        if (contact->name > root->contact->name) {
            //cout<<"heading to right "<<contact->name<<endl;
            root->right = buildTree(root->right, contact);
        }
        else {
            //cout<<"heading to left "<<contact->name<<endl;
            root->left = buildTree(root->left, contact);
        }
        return root;
    }
    void printPhoneNumber(Node* contact){
        string stuff(29, '-');
        string space1(5,' ');
        string space2(16,' ');
        cout<<stuff<<endl;
        for(int i=0;i<2;i++){
            if(i == 0){
                cout<<"|"<<space1<<"Name:"<<contact->name<<space2<<"|"<<endl;
                cout<<"|"<<space1<<"Number:"<<contact->key<<space1<<"|"<<endl;
            }
        }
    }
    void printHelper(BNode* root){
        if(root != NULL){
            printHelper(root->left);
            printPhoneNumber(root->contact);
            printHelper(root->right);
        }
    }
    void printBST(BNode* root){
            string stuff(29, '-');
            printHelper(root);
            cout<<stuff<<endl;
    }
};
class NumberArranger{
    public: 
    int height(Node *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int max(int a, int b)
    {
        return (a > b)? a : b;
    }

    Node* newNode(long int key,string name)
    {
        Node* node = new Node();
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 1; 
        node->name = name;
        return(node);
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left),
                        height(y->right)) + 1;
        x->height = max(height(x->left),
                        height(x->right)) + 1;
        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left),
                        height(x->right)) + 1;
        y->height = max(height(y->left),
                        height(y->right)) + 1;

        return y;
    }

    int getBalance(Node *N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) -
            height(N->right);
    }

    Node* insert(Node* node,string name,long int key)
    {
        if (node == NULL)
            return(newNode(key,name));

        if (key < node->key)
            node->left = insert(node->left,name, key);
        else if (key > node->key)
            node->right = insert(node->right,name, key);
        else 
            return node;

        node->height = 1 + max(height(node->left),
                            height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node * minValueNode(Node* node)
    {
        Node* current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }

    Node* deleteNode(Node* root,long int key){
        
        if (root == NULL)
            return root;

        if ( key < root->key )
            root->left = deleteNode(root->left, key);

        else if( key > root->key )
            root->right = deleteNode(root->right, key);

        else
        {
            if( (root->left == NULL) ||
                (root->right == NULL) )
            {
                Node *temp = root->left ?
                            root->left :
                            root->right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else 
                *root = *temp;
                free(temp);
            }
            else
            {
                Node* temp = minValueNode(root->right);

                root->key = temp->key;

                root->right = deleteNode(root->right,
                                        temp->key);
            }
        }

        if (root == NULL)
        return root;

        root->height = 1 + max(height(root->left),
                            height(root->right));

        int balance = getBalance(root);

        if (balance > 1 &&
            getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 &&
            getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 &&
            getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 &&
            getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
    BNode* treeSort(Node* root)
    {
        BST bst;
        BNode* head = NULL;
        vector<Node*> contactArray;
        contactArray = buildBst(root,contactArray);
        cout<<"size:"<<contactArray.size()<<endl;
        for(int i=0;i<contactArray.size();i++){
            Node* current = contactArray[i];
            head = bst.buildTree(head,current);
        }
        return head;
    }
    vector<Node*> buildBst(Node* root,vector<Node*> contact){
        if(root != NULL)
        {
            contact.push_back(root);
            contact = buildBst(root->left,contact);
            contact = buildBst(root->right,contact);
            return contact;
        }
        else{
            return contact;
        }
    }
    void preOrder(Node *root)
    {
        if(root != NULL)
        {
            printHelper(root);
            preOrder(root->left);
            preOrder(root->right);
        }
    }
    void printHelper(Node* contact){
        string stuff(29, '-');
        string space1(5,' ');
        string space2(16,' ');
        cout<<stuff<<endl;
        for(int i=0;i<2;i++){
            if(i == 0){
                cout<<"|"<<space1<<"Name:"<<contact->name<<space2<<"|"<<endl;
                cout<<"|"<<space1<<"Number:"<<contact->key<<space1<<"|"<<endl;
            }
        }
    }
    void printPhoneNumber(Node* contact){
            string stuff(29, '-');
            preOrder(contact);
            cout<<stuff<<endl;
    }
    // Node* search(Node* root,long int key){
    //     Node* searchNode;
    //     cout<<"SEARCH_NUMBER"<<endl;
    //     if (root == NULL)
    //         cout<<"No contact available"<<endl; 
    //         return root;
    //     if ( key < root->key ){
    //         searchNode = search(root->left, key);
    //     }
    //     else if( key > root->key ){
    //         searchNode = search(root->right, key);
    //     }
    //     else{

    //         cout<<"number found"<<endl;
    //         Node* current = root;
    //         current->left = NULL;
    //         current->right = NULL;
    //         printPhoneNumber(current);
    //         //cout<<current->name<< current->key<<endl;
    //         return current;
    //     }
    // }
    Node* searchNode(Node* root,long int key){
        if(root != NULL)
        {
            if(root->key == key){
                Node* temp = root;
                temp->left = NULL;
                temp->right = NULL;
                printPhoneNumber(temp);
                return temp;
            }
            else if(root->key > key){
                return searchNode(root->left,key);
            }
            else{
                return searchNode(root->right,key);
            }
        }
        cout<<"No contacts Available"<<endl;
        return root;
    }
    Node* updateNode(Node* root, long int key,string newName,long int newKey){
        
        if (root == NULL)
            return root;

        if ( key < root->key )
            root->left = updateNode(root->left, key,newName,newKey);

        else if( key > root->key )
            root->right = updateNode(root->right, key,newName,newKey);

        else
        {
            root->name = newName;
            root->key = newKey;
        }

        if (root == NULL)
        return root;

        int balance = getBalance(root);

        if (balance > 1 && key < root->left->key)
            return rightRotate(root);

        if (balance < -1 && key > root->right->key)
            return leftRotate(root);

        if (balance > 1 && key > root->left->key)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && key < root->right->key)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
};
class NameArranger{
    public: 
    int height(Node *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int max(int a, int b)
    {
        return (a > b)? a : b;
    }

    Node* newNode(string key,long int phone)
    {
        Node* node = new Node();
        node->key = phone;
        node->left = NULL;
        node->right = NULL;
        node->height = 1; 
        node->name = key;
        return(node);
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left),
                        height(y->right)) + 1;
        x->height = max(height(x->left),
                        height(x->right)) + 1;
        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left),
                        height(x->right)) + 1;
        y->height = max(height(y->left),
                        height(y->right)) + 1;

        return y;
    }

    int getBalance(Node *N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) -
            height(N->right);
    }

    Node* insert(Node* node, string key,long int phone)
    {
        if (node == NULL)
            return(newNode(key,phone));

        if (key < node->name)
            node->left = insert(node->left, key,phone);
        else if (key > node->name)
            node->right = insert(node->right, key,phone);
        else 
            return node;

        node->height = 1 + max(height(node->left),
                            height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->name)
            return rightRotate(node);

        if (balance < -1 && key > node->right->name)
            return leftRotate(node);

        if (balance > 1 && key > node->left->name)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->name)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node * minValueNode(Node* node)
    {
        Node* current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }

    Node* deleteNode(Node* root, string key){
        
        if (root == NULL)
            return root;

        if ( key < root->name )
            root->left = deleteNode(root->left, key);

        else if( key > root->name )
            root->right = deleteNode(root->right, key);

        else
        {
            if( (root->left == NULL) ||
                (root->right == NULL) )
            {
                Node *temp = root->left ?
                            root->left :
                            root->right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else 
                *root = *temp;
                free(temp);
            }
            else
            {
                Node* temp = minValueNode(root->right);

                root->name = temp->name;

                root->right = deleteNode(root->right,
                                        temp->name);
            }
        }

        if (root == NULL)
        return root;

        root->height = 1 + max(height(root->left),
                            height(root->right));

        int balance = getBalance(root);

        if (balance > 1 &&
            getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 &&
            getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 &&
            getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 &&
            getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
    Node* updateNode(Node* root, string key,string newName,long int newKey){
        
        if (root == NULL)
            return root;

        if ( key < root->name )
            root->left = updateNode(root->left, key,newName,newKey);

        else if( key > root->name )
            root->right = updateNode(root->right, key,newName,newKey);

        else
        {
            root->name = newName;
            root->key = newKey;
        }

        if (root == NULL)
        return root;

        int balance = getBalance(root);

        if (balance > 1 && key < root->left->name)
            return rightRotate(root);

        if (balance < -1 && key > root->right->name)
            return leftRotate(root);

        if (balance > 1 && key > root->left->name)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && key < root->right->name)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
    Node* search(Node* root,string key){
        if (root == NULL)
            cout<<"Zero contact"<<endl; 

        if ( key < root->name ){
            return search(root->left, key);
        }
        else if( key > root->name ){
            return search(root->right, key);
        }
        else if(key == root->name)
        {   
            cout<<"number found"<<endl;
            Node* current = root;
            current->left = NULL;
            current->right = NULL;
            printPhoneNumber(root);
            return root;
        }
        return root;
    }
    Node* searchNode(Node* root,string key){
        if(root != NULL)
        {
            if(root->name == key){
                Node* temp = root;
                temp->left = NULL;
                temp->right = NULL;
                printPhoneNumber(temp);
                return temp;
            }
            else if(root->name > key){
                return searchNode(root->left,key);
            }
            else{
                return searchNode(root->right,key);
            }
        }
        cout<<"No contacts Available"<<endl;
        return root;
    }
    void printHelper(Node* contact){
        string stuff(29, '-');
        string space1(5,' ');
        string space2(16,' ');
        cout<<stuff<<endl;
        for(int i=0;i<2;i++){
            if(i == 0){
                cout<<"|"<<space1<<"Name:"<<contact->name<<space2<<"|"<<endl;
                cout<<"|"<<space1<<"Number:"<<contact->key<<space1<<"|"<<endl;
            }
        }
    }
    void printPhoneNumber(Node* contact){
            string stuff(29, '-');
            preOrder(contact);
            cout<<stuff<<endl;
    }
    BNode* treeSort(Node* root)
    {
        BST bst;
        BNode* head = NULL;
        vector<Node*> contactArray;
        contactArray = buildBst(root,contactArray);
        cout<<"size:"<<contactArray.size()<<endl;
        for(int i=0;i<contactArray.size();i++){
            Node* current = contactArray[i];
            head = bst.buildTree(head,current);
        }
        return head;
    }
    vector<Node*> buildBst(Node* root,vector<Node*> contact){
        if(root != NULL)
        {
            contact.push_back(root);
            contact = buildBst(root->left,contact);
            contact = buildBst(root->right,contact);
            return contact;
        }
        else{
            return contact;
        }
    }
    void preOrder(Node *root)
    {
        if(root != NULL)
        {
            printHelper(root);
            preOrder(root->left);
            preOrder(root->right);
        }
    }
};

int main(){
    long int newNumber;
    string searchName;
    string newName;
    string delName;
    long int searchNo;
    long int delNo;
    Node* searchDel = NULL;
    Node* x;
    Node* y;
    long int updateNo;
    long int newNoupdate;
    string newNameUpdate;
    string updateName;
    string stuff(29, '-');
    NumberArranger contactBook1;
    NameArranger contactBook2;
    Node* root1 = NULL;
    Node* root2 = NULL;

    BST binaryTree;
    BNode* bst;
	
    root1 = contactBook1.insert(root1,"b",9940661358);
	root1 = contactBook1.insert(root1,"s" ,9442585822);
	root1 = contactBook1.insert(root1,"k",9940135866);
	root1 = contactBook1.insert(root1,"m", 4146259699);
	root1 = contactBook1.insert(root1,"n", 7397063193);
	root1 = contactBook1.insert(root1,"p", 9442234397);
	root1 = contactBook1.insert(root1,"t", 9080891358);
	root1 = contactBook1.insert(root1,"a", 9442159699);
	root1 = contactBook1.insert(root1,"i", 9487419569);

    root2 = contactBook2.insert(root2,"b",9940661358);
	root2 = contactBook2.insert(root2,"s" ,9442585822);
	root2 = contactBook2.insert(root2,"k",9940135866);
	root2 = contactBook2.insert(root2,"m", 4146259699);
	root2 = contactBook2.insert(root2,"n", 7397063193);
	root2 = contactBook2.insert(root2,"p", 9442234397);
	root2 = contactBook2.insert(root2,"t", 9080891358);
	root2 = contactBook2.insert(root2,"a", 9442159699);
	root2 = contactBook2.insert(root2,"i", 9487419569);

	// contactBook1.printPhoneNumber(root1);

	// root1 = contactBook1.deleteNode(root1,7397063193);

	// contactBook1.printPhoneNumber(root1);
    // cout<<"\n";
    // BST binaryTree;
    // BNode* bst  = contactBook1.treeSort(root1);
    // cout<<"after inserting all values"<<endl;
    // binaryTree.printBST(bst);
    // cout<<"searching for value "<<"b"<<endl;
    //Node* searchedNode = contactBook1.search(root1,9940661358);
    // contactBook1.updateNode(root1,9442585822,"mano",8904561358);

	// contactBook1.printPhoneNumber(root1);
    //cout<<searchedNode->key<<searchedNode->name<<endl;
    int ch;
    int updateCheckParams;
    cout<<"1.insert new contact"<<endl;
    cout<<"2.delete contact by Name"<<endl;
    cout<<"3.delete contact by Number"<<endl;
    cout<<"4.search by Number"<<endl;
    cout<<"5.search by Name"<<endl;
    cout<<"6.update contact by Name"<<endl;
    cout<<"7.update contact by Number"<<endl;
    cout<<"8.print contact"<<endl;
    cout<<"9.preorderTraversal of Trees"<<endl;
    cout<<"0.exit"<<endl;
    while(1){
        cout<<"Enter the choice:";
        cin>>ch;
        switch (ch)
        {
            case 1:
                cout<<"enter Name:";
                cin>>newName;
                cout<<endl;
                cout<<"enter Number:";
                cin>>newNumber;
                root1 = contactBook1.insert(root1,newName,newNumber);
                root2 = contactBook2.insert(root2,newName,newNumber);
                break;
            case 2:
                cout<<"enter name to be deleted:";
                cin>>delName;
                searchDel = contactBook2.searchNode(root2,delName);
                root1 = contactBook1.deleteNode(root1,searchDel->key);
                root2 = contactBook2.deleteNode(root2,delName);
                break;  
            case 3:
                cout<<"enter number to be deleted:";
                cin>>delNo;
                x = contactBook1.searchNode(root1,delNo);
                cout<<"Name:"<<x->name<<" no:"<<x->key<<endl;
                root1 = contactBook1.deleteNode(root1,delNo);
                root2 = contactBook2.deleteNode(root2,x->name);
                break;
            case 4:
                //y = NULL;
                cout<<"enter number to be search:";
                cin>>searchNo;
                y = contactBook1.searchNode(root1,searchNo);
                //cout<<"Name:"<< y->key <<" NO:"<< y->name <<endl;
                break;
            case 5:
                cout<<"enter number to be search:";
                cin>>searchName;
                x = contactBook2.searchNode(root2,searchName);
                //contactBook2.printHelper(x);
                //cout<<stuff<<endl;
                //cout<<"Name:"<< y->key <<" NO:"<< y->name <<endl;
                break;
            case 6:
                cout<<"enter name to update"<<endl;
                cin>>updateName;
                cout<<"Enter 1 to update only Number"<<endl;
                cout<<"Enter 2 to update only Name"<<endl;
                cout<<"Enter 0 to update both Number and Name"<<endl;
                cin>>updateCheckParams;
                if(updateCheckParams == 1){
                    cout<<"enter New No to update:";
                    cin>>newNoupdate;
                    x = contactBook2.searchNode(root2,updateName);
                    if(x !=NULL){
                        newNameUpdate = x->name;
                    
                        root1 = contactBook1.deleteNode(root1,x->key);
                        root2 = contactBook2.deleteNode(root2,x->name);
                        
                        root1 = contactBook1.insert(root1,newNameUpdate,newNoupdate);
                        root2 = contactBook2.insert(root2,newNameUpdate,newNoupdate);
                    }
                } 
                if(updateCheckParams == 2){
                    cout<<"enter New Name to update:";
                    cin>>newNameUpdate;
                    x = contactBook2.searchNode(root2,updateName);
                    if(x != NULL){
                        newNoupdate = x->key;
                        root1 = contactBook1.deleteNode(root1,x->key);
                        root2 = contactBook2.deleteNode(root2,x->name);
                        
                        root1 = contactBook1.insert(root1,newNameUpdate,newNoupdate);
                        root2 = contactBook2.insert(root2,newNameUpdate,newNoupdate);
                    }
                }
                if(updateCheckParams == 0){
                    cout<<"enter New Name to update:";
                    cin>>newNameUpdate;
                    cout<<"enter number to update:";
                    cin>>newNoupdate;
                    x = contactBook2.searchNode(root2,updateName);
                    if(x != NULL){

                        root1 = contactBook1.deleteNode(root1,x->key);
                        root2 = contactBook2.deleteNode(root2,x->name);
                        
                        root1 = contactBook1.insert(root1,newNameUpdate,newNoupdate);
                        root2 = contactBook2.insert(root2,newNameUpdate,newNoupdate);
                    }
                }
                break;
            case 7:
                cout<<"enter number to update"<<endl;
                cin>>updateNo;
                cout<<"Enter 1 to update only Number"<<endl;
                cout<<"Enter 2 to update only Name"<<endl;
                cout<<"Enter 0 to update both Number and Name"<<endl;
                cin>>updateCheckParams;
                if(updateCheckParams == 1){
                    cout<<"enter New No to update:";
                    cin>>newNoupdate;
                    y = contactBook1.searchNode(root1,updateNo);
                    if(y!=NULL){
                        newNameUpdate = y->name;
                    
                        root1 = contactBook1.deleteNode(root1,y->key);
                        root2 = contactBook2.deleteNode(root2,y->name);
                        
                        root1 = contactBook1.insert(root1,newNameUpdate,newNoupdate);
                        root2 = contactBook2.insert(root2,newNameUpdate,newNoupdate);
                    }
                } 
                if(updateCheckParams == 2){
                    cout<<"enter New Name to update:";
                    cin>>newNameUpdate;
                    y = contactBook1.searchNode(root1,updateNo);
                    newNoupdate = updateNo;
                    if(y!=NULL){

                        root1 = contactBook1.deleteNode(root1,y->key);
                        root2 = contactBook2.deleteNode(root2,y->name);
                        
                        root1 = contactBook1.insert(root1,newNameUpdate,newNoupdate);
                        root2 = contactBook2.insert(root2,newNameUpdate,newNoupdate);
                    }
                }
                if(updateCheckParams == 0){
                    cout<<"enter New Name to update:";
                    cin>>newNameUpdate;
                    cout<<"enter number to update:";
                    cin>>newNoupdate;
                    y = contactBook1.searchNode(root1,updateNo);
                    
                    if(y!=NULL){

                        root1 = contactBook1.deleteNode(root1,y->key);
                        root2 = contactBook2.deleteNode(root2,y->name);
                        
                        root1 = contactBook1.insert(root1,newNameUpdate,newNoupdate);
                        root2 = contactBook2.insert(root2,newNameUpdate,newNoupdate);
                    }
                }
                break;
            case 8:
                bst = contactBook1.treeSort(root1);
                binaryTree.printBST(bst);  
                //contactBook1.printPhoneNumber(root1);//contactBook for number
                //cout<<"space"<<endl;
                //contactBook2.printPhoneNumber(root2);//contactBook for name
                break;
            case 9:
                contactBook1.preOrder(root1);
                cout<<stuff<<endl;
                cout<<endl;
                contactBook2.preOrder(root2);
                cout<<stuff<<endl;
                break;
            case 0:
                exit(1);
        }
    }
    return 0;
}

