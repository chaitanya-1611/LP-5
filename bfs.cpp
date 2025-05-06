#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

class node{
    public:
    int data;
    node* left;
    node* right;
};

class Breathfs{
    private:
    node*root;

    public:
    Breathfs(){
        root = NULL;
    };
    node* insert(int);
    void bfs();

};

node *Breathfs::insert(int data){
    if(!root){
        root = new node;
        root->data=data;
        root->left=NULL;
        root->right=NULL;

        return root;
    }

    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        node* temp = q.front();
        q.pop();
        if(temp->left==NULL){
           temp->left  =new node;
           temp->left->data=data;
           temp->left->left=NULL;
           temp->left->right=NULL;
           return root; 
        }else{
            q.push(temp->left);
        }

        if(temp->right==NULL){
            temp->right=new node;
            temp->right->data=data;
            temp->right->left=NULL;
            temp->right->right=NULL;
            return root;
        }else{
            q.push(temp->right);
        }
    }

    return root;
}

void Breathfs::bfs(){
    if(!root){
        cout<<"Tree is empty"<<endl;
        return;
    }
    queue<node*> q;
    q.push(root);
    int size;
    while(!q.empty()){
        size = q.size();
        #pragma omp parallel for
        for(int i=0;i<size;i++){
            node* currentNode;
            #pragma omp critical
            {
                currentNode=q.front();
                q.pop();
                cout<<"Thread "<<omp_get_thread_num()<<currentNode->data<<endl;
            }

            #pragma omp critical
            {
                if(currentNode->left!=NULL){
                    q.push(currentNode->left);
                }
                if(currentNode->right!=NULL){
                    q.push(currentNode->right);
                }
            }
        }
    }    
}

int main(){
    Breathfs tree;
    int data;
    char ans;

    do{
        cout<<"Enter data: ";
        cin>>data;
        tree.insert(data);
        cout<<"Do you want to insert more data? (y/n): ";
        cin>>ans;
    }while(ans=='y'||ans=='Y');

    cout<<"Breadth First Search Traversal: ";
    tree.bfs();

    return 0;
}