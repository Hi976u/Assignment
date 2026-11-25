#include <iostream>
#include <queue>
using namespace std;

class Node
{
    public:
        int data;
        Node* right;
        Node* left;
        int height;

        Node(int data)
        {
            this->data = data;
            this->left = NULL;
            this->right = NULL;
            this->height = 1;
        }
};

int height(Node* root)
{
    if(root == NULL)
    {
        return 0;
    }

    return root->height;
}

int checkBalanceFactor(Node* root)
{
    if(root == NULL)
    {
        return 0;
    }

    return height(root->left) - height(root->right);
}

void updateHeight(Node* root)
{
    if(root == NULL)
    {
        return ;
    }

    root->height =  1 + max(height(root->left),height(root->right));
}

Node* leftRotation(Node* root)
{
    Node* child = root->right;
    Node* temp = child->left;

    child->left = root;
    root->right = temp;

    updateHeight(root);
    updateHeight(child);

    return child;
}

Node* rightRotation(Node* root)
{
    Node* child = root->left;
    Node* temp = child->right;

    child->right = root;
    root->left = temp;

    updateHeight(root);
    updateHeight(child);

    return child;
}

Node* insertToAVL(Node* root, int data)
{
    if(root == NULL)
    {
        return new Node(data);
    }

    if(data < root->data)
    {
        root->left = insertToAVL(root->left,data);
    }
    else if(data > root->data)
    {
        root->right = insertToAVL(root->right,data);
    }
    else
    {
        return root;
    }

    updateHeight(root);

    int balance = checkBalanceFactor(root);

    //LL
    if( balance > 1 && data < root->left->data)
    {
        return rightRotation(root);
    }
    //RR
    if(balance < -1 && data > root->right->data)
    {
        return leftRotation(root);
    }
    //LR
    if(balance > 1 && data > root->left->data)
    {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    //RL
    if(balance < -1 && data < root->right->data)
    {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;

}

void levelOrderTraversal(Node* root)
{
    if(root == NULL)
    {
        return;
    }

    queue<Node*>q;
    q.push(root);
    q.push(NULL);

    while(!q.empty())
    {
        Node* temp = q.front();
        q.pop();

        if(temp == NULL)
        {
            cout<<endl;
            if(!q.empty())
            {
                q.push(NULL);
            }
        }
        else
        {
            cout<<temp->data<<" ";
            if(temp->left)
            {
                q.push(temp->left);
            }
            if(temp->right)
            {
                q.push(temp->right);
            }
        }
    }
}

Node* deleteNode( Node* root,int key)
{
    if( root == NULL)
    {
        return NULL;
    }

    if(key < root->data)
    {
        root->left = deleteNode(root->left,key);
    }
    else if(key > root->data)
    {
        root->right = deleteNode(root->right,key);
    }
    else
    {
        //Leaf Node
        if(root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }

        //One Child
        else if(root->left != NULL && root->right == NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else if(root->right != NULL && root->left == NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else
        {
            Node* curr = root->right;
            while(curr->left)
            {
                curr = curr->left;
            }

            root->data = curr->data;
            root->right = deleteNode(root->right,curr->data);
        }
    }

    root->height = 1 + max(height(root->left),height(root->right));

    int balance = checkBalanceFactor(root);

    if(balance > 1)
    {
        //LL
        if(checkBalanceFactor(root->left) >= 0)
        {
            return rightRotation(root);
        }
        //LR
        else  
        {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
    }
    else if(balance < -1)
    {
        //RR
        if(checkBalanceFactor(root->right) <= 0)
        {
            return leftRotation(root);
        }
        //RL
        else
        {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
    }
    else
    {
        return root;
    }

}

int main()
{
    Node* root = NULL;

    root = insertToAVL(root, 10);
    root = insertToAVL(root, 20);
    root = insertToAVL(root, 30);
    root = insertToAVL(root, 40);
    root = insertToAVL(root, 50);
    root = insertToAVL(root, 60);
    root = insertToAVL(root, 70);
    root = insertToAVL(root, 80);

    levelOrderTraversal(root);
    
    root = deleteNode(root, 10);
    
    cout<<"After Deleting Node : "<<endl;
    levelOrderTraversal(root);


    return 0;
}
