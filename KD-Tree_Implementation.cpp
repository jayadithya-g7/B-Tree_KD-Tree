#include<iostream>
#include<math.h>
#include<stdio.h>
#include<chrono>

using namespace std;

struct point{
    int x;
    int y;
};

class node{
    public:
       struct point key;
       node *left;
       node *right;
       node(int a,int b){
        key.x=a;
        key.y=b;
        left=NULL;
        right=NULL;
       }
};


class kdtree{
    private:
      node *r;
    
    double distance(struct point val1,struct point val2){
        return sqrt(((val1.x - val2.x)*(val1.x - val2.x)) + ((val1.y - val2.y)*(val1.y - val2.y)));
    }


    public:
    kdtree(int a,int b){
        r=new node(a,b);
    }
    node* getroot(){
        return r;
    }
    void insert(node *root,int val1,int val2,int depth){
            node *newnode=new node(val1,val2);
            if(depth%2==0){
                if(val1<=root->key.x){
                    if(root->left==NULL){
                        root->left=newnode;
                    }
                    else{
                        insert(root->left,val1,val2,depth+1);
                    }
                }
                else{
                    if(root->right==NULL){
                        root->right=newnode;
                    }
                    else{
                        insert(root->right,val1,val2,depth+1);
                    }
                }

            }
            else{
                if(val2<=root->key.y){
                    if(root->left==NULL){
                        root->left=newnode;
                    }
                    else{
                        insert(root->left,val1,val2,depth+1);
                    }
                }
                else{
                    if(root->right==NULL){
                        root->right=newnode;
                    }
                    else{
                        insert(root->right,val1,val2,depth+1);
                    }
                }

            }

    }

    node* findmin(node* root){
         while(root->left==NULL){
            root=root->left;
         }
         return root;
    }

    node* del(node *root,int val1,int val2,int depth){
       if(root==NULL){
        return NULL;
       }
       if(depth%2==0){
          if(val1<root->key.x){
           root->left=del(root->left,val1,val2,depth+1);
          } 
          else if(val1>root->key.x){
           root->right=del(root->right,val1,val2,depth+1);
          }
          else{
               if(root->right==NULL && root->left==NULL){
                node *temp=root;
                delete root;
                temp=NULL;
                root=temp;
              }
              else if(root->right==NULL && root->left!=NULL){
                  node *temp=root->left;
                  delete root;
                  root=temp;
              }
              else if(root->right!=NULL && root->left==NULL){
                  node *temp=root->right;
                  delete root;
                  root=temp;
              }
              else{
                  node *minnode=findmin(root->right);
                  root->key.x=minnode->key.x;
                   root->key.y=minnode->key.y;
                  root->right=del(root->right,minnode->key.x,minnode->key.y,0);
                    
              }
          }
       }
       else{
         if(val2<root->key.y){
           root->left=del(root->left,val1,val2,depth+1);
          } 
          else if(val2>root->key.y){
           root->right=del(root->right,val1,val2,depth+1);
          }
          else{
               if(root->right==NULL && root->left==NULL){
                node *temp=root;
                delete root;
                temp=NULL;
                root=temp;
              }
              else if(root->right==NULL && root->left!=NULL){
                  node *temp=root->left;
                  delete root;
                  root=temp;
              }
              else if(root->right!=NULL && root->left==NULL){
                  node *temp=root->right;
                  delete root;
                  root=temp;
              }
              else{
                  node *minnode=findmin(root->right);
                  root->key.x=minnode->key.x;
                   root->key.y=minnode->key.y;
                  root->right=del(root->right,minnode->key.x,minnode->key.y,0);
                    
              }
          }

       }
       return root;
    }

    void traverse(node *root){
          if(root==NULL){
            return;
          }
          cout<<"x:"<<root->key.x<<" y:"<<root->key.y<<endl;
          traverse(root->left);
          traverse(root->right);

    }
    int search(node *root,int val1,int val2,int depth){
            if(root==NULL){
                return 0;
            }
           
            if(depth%2==0){
             if(val1<root->key.x){
                return search(root->left,val1,val2,depth+1);
             }
             else if(val1>root->key.x){
                return search(root->right,val1,val2,depth+1);
             }  
             else if(val1==root->key.x && val2==root->key.y){
                return 1;
             }
             else{
                return 0;
             }
             
            }
            else{
                 if(val2<root->key.y){
                return search(root->left,val1,val2,depth+1);
             }
             else if(val2>root->key.y){
                return search(root->right,val1,val2,depth+1);
             }  
             else if(val2==root->key.y && val1==root->key.x){
                return 1;
             }
             else{
                return 0;
               } 
            }
    }

     void twodprint(node *root, int space, int dim){
        const int COUNT=10;
        if (root == NULL)
            return;

        space += COUNT;

        twodprint(root->right, space, dim);

        cout<<endl;
        for (int i = COUNT; i < space; i++)
            cout<<" ";
        cout<<root->key.x<<" "<<root->key.y;
        cout<<endl;

        twodprint(root->left, space, dim);
    }


    
};

int main(){
   int i=0;
   kdtree *tree;
   node *root;
   while(1){
    if(i==0){
        cout<<"1-CREATE"<<endl;
        cout<<"2-INSERT"<<endl;
        cout<<"3-DELETE"<<endl;
        cout<<"4-TRAVERSE"<<endl;
      cout<<"5-SEARCH"<<endl;
      cout<<"6-PRINT 2D"<<endl;
      cout<<"7-EXIT"<<endl;
       cout<<"ENTER YOUR CHOICE:";
       int ch;
       cin>>ch;
       if(ch==1){
          int a,b;
          cout<<"enter values:";
          cin>>a>>b;
          tree=new kdtree(a,b);
          auto start = std::chrono::high_resolution_clock::now();
          root=tree->getroot();
          auto end = std::chrono::high_resolution_clock::now();
          double time_taken_create = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
          time_taken_create *= 1e-9; 
          printf("Time taken for creation of root node %d,%d is %.8f nanoseconds\n",a,b,time_taken_create);
       }
       else if(ch==7){
         break;
       }

       else{
         cout<<"CREATE A TREE FIRST"<<endl;
         i--;
       }
    
    
    
    }
    else{
        cout<<"1-INSERT"<<endl;
        cout<<"2-DELETE"<<endl;
        cout<<"3-TRAVERSE"<<endl;
        cout<<"4-SEARCH"<<endl;
        cout<<"5-PRINT 2D"<<endl;
        cout<<"6-EXIT"<<endl;

      cout<<"ENTER YOUR CHOICE:";
      int ch;
      cin>>ch;

      if(ch==1){
         int a,b;
         cout<<"enter values:";
         cin>>a>>b;
         auto start = std::chrono::high_resolution_clock::now();
         tree->insert(root,a,b,0);
         auto end = std::chrono::high_resolution_clock::now();
         double time_taken_insertion = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
         time_taken_insertion *= 1e-9; 
         printf("Time taken for insertion of node  %d,%d is %f nanoseconds\n",a,b,time_taken_insertion);
      }
      else if(ch==2){
         int a,b;
         cout<<"enter values:";
         cin>>a>>b;
         auto start = std::chrono::high_resolution_clock::now();
         root=tree->del(root,a,b,0);
         auto end = std::chrono::high_resolution_clock::now();
         double time_taken_delete = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
         time_taken_delete *= 1e-9; 
         printf("Time taken for deletion of node %d,%d is %f nanoseconds\n",a,b,time_taken_delete);

      }
      else if(ch==3){
         auto start = std::chrono::high_resolution_clock::now();
         tree->traverse(root);
         auto end = std::chrono::high_resolution_clock::now();
         double time_taken_traverse = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
         time_taken_traverse *= 1e-9; 
         printf("Time taken for traversal of tree is %f nanoseconds\n",time_taken_traverse);
      }
      else if(ch==4){
           int a,b;
         cout<<"enter values:";
         cin>>a>>b;
         auto start = std::chrono::high_resolution_clock::now();   
         int s=tree->search(root,a,b,0);
         auto end = std::chrono::high_resolution_clock::now();
         double time_taken_search = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
         time_taken_search *= 1e-9; 
         printf("Time taken for searching node %d,%d is %f nanoseconds\n",a,b,time_taken_search);
         if(s){
            cout<<"VALUE FOUND"<<endl;
         }
         else{
            cout<<"VALUE NOT FOUND"<<endl;
         }

      }
      else if(ch==5){
        auto start = std::chrono::high_resolution_clock::now();  
         tree->twodprint(root,0,2);
         auto end = std::chrono::high_resolution_clock::now();
         double time_taken_print = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
         time_taken_print *= 1e-9;
         printf("Time taken for printing tree in 2D is %f nanoseconds\n",time_taken_print);
      }
      else if(ch==6){
        break;
      }
    }
    i++;
   }
   
 return 0;
}


