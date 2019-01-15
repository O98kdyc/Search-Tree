#ifndef BINSEATRE_H_INCLUDED
#define BINSEATRE_H_INCLUDED
#include "dySeaTab.h"
#include "linkQueue.h"
#include <vector>
#include "seqStack.h"


template <class KEY, class OTHER>
class BinarySearchTree: public dynamicSearchTable<KEY, OTHER>
{ private:
    struct BinaryNode
    {
          SET<KEY, OTHER> data;
          BinaryNode *left;
          BinaryNode *right;

          BinaryNode( const SET<KEY, OTHER> &thedata,BinaryNode *lt=NULL,  BinaryNode *rt=NULL )
          :data( thedata ), left( lt ), right( rt ) { }
    };

    struct StNode
   {
      BinaryNode *node;
      int TimesPop;
      StNode(BinaryNode *N=NULL):node(N),TimesPop(0){}
   };

    BinaryNode *root;
  public:
    BinarySearchTree( ) ;
    ~BinarySearchTree( );
    SET<KEY, OTHER> *find(const KEY &x) const;
    void insert( const SET<KEY, OTHER> &x );
    void remove( const KEY & x );
    bool check ();
    void search(int i);
    void out(KEY m);
  private:
    void insert( const SET<KEY, OTHER> & x, BinaryNode * & t );
    void remove( const KEY & x, BinaryNode * & t );
    SET<KEY, OTHER> *find(const KEY &x, BinaryNode *t ) const;
    void makeEmpty( BinaryNode *t );
};

template <class KEY, class OTHER>
SET<KEY, OTHER> * BinarySearchTree<KEY, OTHER>::find(
                                        const KEY &x ) const
{ return find( x, root );}

template <class KEY, class OTHER>
SET<KEY, OTHER> *BinarySearchTree<KEY, OTHER>::find(
                                         const KEY & x, BinaryNode *t ) const
{     if  ( t == NULL || t->data.key == x )
           return (SET<KEY, OTHER> *) t;
       if( x < t->data.key )   return find( x, t->left );
       else return find( x, t->right );
}

template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::insert( const SET<KEY,OTHER> & x )
{    insert( x, root );    }

template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::insert( const SET<KEY,OTHER> & x, BinaryNode *&t )
{
    //cout<<1<<" ";
    if( t == NULL )
		   {t = new BinaryNode( x, NULL, NULL );}//cout<<t->data.key;}
    else if( x.key < t->data.key )
		   insert( x, t->left );
    else if( t->data.key < x.key )
		   insert( x, t->right );
}

template <class KEY, class OTHER>
void BinarySearchTree<KEY,
         OTHER>::remove( const KEY & x )
{
   remove( x, root );
}

template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::remove( const KEY & x, BinaryNode * & t )
{	    if( t == NULL ) return;
	    if ( x < t->data.key )   remove( x, t->left );
	    else if( t->data.key < x )    remove( x, t->right );
	    else if( t->left != NULL && t->right != NULL ) {    //����������
		    BinaryNode *tmp = t->right;
		    while (tmp->left != NULL) tmp = tmp->left;
		    t->data = tmp->data;
		    remove( t->data.key, t->right );
	    }
	    else  {                                          //��ɾ������Ҷ������ֻ��һ������
		    BinaryNode *oldNode = t;
		    t = ( t->left != NULL ) ? t->left : t->right;
		    delete oldNode;
	    }
}

template <class KEY,class OTHER>
BinarySearchTree<KEY,OTHER>::BinarySearchTree()
{
    root=NULL;
}

template<class KEY,class OTHER>
void BinarySearchTree<KEY,OTHER>::makeEmpty(BinaryNode *t)
{
    if(t==NULL) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

template<class KEY,class OTHER>
BinarySearchTree<KEY,OTHER>::~BinarySearchTree()
{
    makeEmpty(root);
}

template<class KEY,class OTHER>
bool BinarySearchTree<KEY,OTHER>::check()
{
    linkQueue<BinaryNode*> s;
    BinaryNode *current;
    s.enQueue(root);
    while(!s.isEmpty())
    {
      current=s.deQueue();
      if(current->left!=NULL) {s.enQueue(current->left);if(current->left->data.key>current->data.key) return false;};
      if(current->right!=NULL) {s.enQueue(current->right);if(current->right->data.key<current->data.key) return false;};
    }
    return true;
}

template<class KEY,class OTHER>
void BinarySearchTree<KEY,OTHER>::search(int i)
{
  vector<KEY> v;
  seqStack<StNode> s;
  StNode current(root);
  s.push(current);
    while(!s.isEmpty())
    {
        current = s.pop();
        if(++current.TimesPop == 2)         //第二次出栈，可以被访问
        {
            //cout<<  current.node -> data  <<' ';
            v.push_back(current.node->data.key);
            current.node->data;
        }
        else                                //第一次出栈，不能访问，重新入栈
        {
            if(current.node -> right != NULL)
                s.push(StNode(current.node -> right));
            s.push(current);
            if(current.node -> left != NULL)
                s.push(StNode(current.node -> left));
        }
    }
  SET<KEY,OTHER> *p;
  p=find(v[i-1]);
  if(p) cout<<p->key<<" "<<p->other<<endl;
}

template<class KEY,class OTHER>
void BinarySearchTree<KEY,OTHER>::out(KEY m)
{
  vector<KEY> v;
  seqStack<StNode> s;
  StNode current(root);
  s.push(current);
    while(!s.isEmpty())
    {
        current = s.pop();
        if(++current.TimesPop == 2)         //第二次出栈，可以被访问
        {
            //cout<<  current.node -> data  <<' ';
            v.push_back(current.node->data.key);
            current.node->data;
        }
        else                                //第一次出栈，不能访问，重新入栈
        {
            if(current.node -> right != NULL)
                s.push(StNode(current.node -> right));
            s.push(current);
            if(current.node -> left != NULL)
                s.push(StNode(current.node -> left));
        }
    }
  for(int i=0;i<v.capacity();i++)
  {
    if(v[i]<m) remove(v[i]);
    if(v[i]>=m) break;
  }
}

#endif // BINSEATRE_H_INCLUDED
