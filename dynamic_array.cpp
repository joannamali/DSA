// used: AVL tree with modifications

#include<iostream>
using namespace std; 


// An AVL tree node 
class Node 
{ 
	public: 
	int val; 
    int q; // quantity
	Node *left; 
	Node *right; 
	int height; 
    int onLeft;
}; 


int height(Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 



Node* newNode(int val, int quantity) 
{ 
	Node* node = new Node(); 
	node->val = val; 
    node->q = quantity;
    node->onLeft = 0; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; 
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

    y->onLeft = y->onLeft - x->onLeft - x->q;

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

    y->onLeft = y->onLeft + x->onLeft + x->q;
	return y; 
} 

int getBalance(Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

int find(Node* node, int pos)
{ 

    int start = node->onLeft + 1;
    int end = start + node->q - 1; 

	if (pos < start) {
		return find(node->left, pos); 
    }
	else if (pos > end) 
		return find(node->right, pos - end); 

    else 
        return node->val;

    
} 

Node* insert(Node* node, int pos, int val, int quantity) 
{ 
	if (node == NULL) 
		return(newNode(val, quantity)); 

    int start = node->onLeft + 1;
    int end = start + node->q - 1; 

    if (node->val == val && pos >= start && pos <= end + 1){
            node->q += quantity; 
            return node; 
    }

	if (pos <= start) {
		node->left = insert(node->left, pos, val, quantity); 
        node->onLeft += quantity; 
    }
	else if (pos > end) 
		node->right = insert(node->right, pos - end, val, quantity); 

    else {
        int q_left = pos - 1 - start + 1; 
        node->left = insert(node->left, node->onLeft + 1, node->val, q_left);
        node->right = insert(node->right, 0, node->val, node->q - q_left); 

        node->onLeft += q_left; 
        node->val = val; 
        node->q = quantity;

        node->height = 1 + max(height(node->left), 
                            height(node->right)); 

        int balance = getBalance(node); 
        
        if (balance > 1) 
        { 
            node->left = leftRotate(node->left); 
            return rightRotate(node); 
        } 

      
        if (balance < -1) 
        { 
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        } 
            
        return node; 
    }
    
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

                    
	int balance = getBalance(node); 

    if (balance > 1){

        if (node->left->left != NULL && 
        (node->left->right == NULL || node->left->left->height > node->left->right->height))
		    return rightRotate(node); 

        if ( node->left->right != NULL && 
        (node->left->left == NULL || node->left->right->height > node->left->left->height))
	    { 
		    node->left = leftRotate(node->left); 
		    return rightRotate(node); 
	    } 
    }
    
    if (balance < -1){
        if (node->right->right != NULL && 
        (node->right->left == NULL || node->right->right->height > node->right->left->height))	
            return leftRotate(node); 
    
        if (node->right->left != NULL &&
            (node->right->right == NULL || node->right->left->height > node->right->right->height))
        { 
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        } 
    }
	return node; 
} 

void inOrder(Node *root) 
{ 
	if(root != NULL) 
	{ 
        inOrder(root->left);
    	cout << root->val << " "<<root->q<<" "<<root->onLeft<<", "; 
		 
		inOrder(root->right); 
	} 
} 

int main() 
{ 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


	Node *root = NULL; 
	int m; cin>>m; 
   
    char l; 
    int w = 0, x, j, k, n = 0; 

    for (int i = 0; i < m; i++){
        cin>>l>>j;
        if (l == 'g'){
            j = (j + w) % n;
            w = find(root, j+1);
            cout<<w<<endl;  
        }
        else {
            j = (j + w) % (n + 1);
            cin>>x>>k;
            n += k;
            root = insert(root, j+1, x, k);
        }
 
    }
	
	
} 
