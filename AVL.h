#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED
#include "dySeaTab.h"
template <class KEY, class OTHER>
class AvlTree: public dynamicSearchTable<KEY, OTHER> {
    struct AvlNode
    {        SET<KEY, OTHER>   data;
              AvlNode           *left;
             AvlNode           *right;
             int               height; //�����ĸ߶�

             AvlNode( const SET<KEY, OTHER> &element ,
                                         AvlNode *lt, AvlNode *rt, int h=1)
              : data(element), left( lt ), right( rt ), height(h) { }
     };

    AvlNode *root;

    struct StNode
    {
      AvlNode *node;
      int TimesPop;
      StNode(AvlNode *N=NULL):node(N),TimesPop(0){}
    };

  public:
    AvlTree() { root = NULL; }
    ~AvlTree() { makeEmpty( root); }
    SET<KEY, OTHER> *find( const KEY & x ) const;
    void insert( const SET<KEY, OTHER> & x ) ;
    void remove( const KEY & x );
    bool check ();
    void search(int i);
    void out(KEY m);
private:
    void insert( const SET<KEY, OTHER> & x, AvlNode * & t ) ;
    bool remove( const KEY & x, AvlNode * & t ) ;
    void makeEmpty( AvlNode *t );
    int height( AvlNode *t ) const { return t == NULL ? 0 : t->height;}
    void LL( AvlNode * & t );
    void LR( AvlNode * & t );
    void RL( AvlNode * & t );
    void RR( AvlNode * & t );
    int max(int a, int b) {return (a>b)?a:b;}
    bool adjust(AvlNode *&t, int subTree);
};

template <class KEY, class OTHER>
SET<KEY, OTHER> *AvlTree<KEY, OTHER>::find(const KEY & x ) const
{
    AvlNode *t = root;
    while (t!=NULL && t->data.key != x)
		if (t->data.key > x) t = t->left; else t = t->right;
    if (t==NULL) return NULL;
      else return (SET<KEY, OTHER> *) t;
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert( const SET<KEY, OTHER> & x, AvlNode * & t )
{
       if( t == NULL )              //�ڿ����ϲ���
	         t = new AvlNode( x, NULL, NULL);
       else if( x.key < t->data.key) {                          //���������ϲ���
	        insert( x, t->left );
	        if ( height( t->left ) - height( t->right ) == 2 )    //tʧ��
		       if( x.key < t->left->data.key ) LL( t ); else LR(t);
        }
       else if( t->data.key < x.key )  {                        //���������ϲ���
	        insert( x, t->right );
	        if( height( t->right ) - height( t->left ) == 2 )     //tʧ��
		   if( t->right->data.key < x.key ) RR(t); else RL(t);
       }
      //���¼���t�ĸ߶�
      t->height = max( height( t->left ) , height( t->right ) ) + 1;
}

template <class KEY,class OTHER>
void AvlTree<KEY, OTHER>::insert( const SET<KEY, OTHER> & x)
{
  insert(x,root);
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LL( AvlNode * & t )
{
   AvlNode *t1 = t->left;       // δ��������
   t->left = t1->right;
   t1->right = t;
   t->height = max( height( t->left ),  height( t->right ) ) + 1;
   t1->height = max( height( t1->left ), height(t)) + 1;
   t = t1;
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR( AvlNode * & t )
{
   AvlNode *t1 = t->right;
   t->right = t1->left;
   t1->left = t;
   t->height = max( height( t->left ),  height( t->right ) ) + 1;
   t1->height = max( height( t1->right ), height(t)) + 1;
   t = t1;
 }

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LR( AvlNode * & t )
{
      RR( t->left );
      LL( t );
}
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL( AvlNode * & t )
{
      LL( t->right );
     RR( t );
}

template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::remove( const KEY & x, AvlNode * & t )
{
      if( t == NULL )     return true;
	    if (x == t->data.key) {                           // ɾ��������
		     if ( t->left == NULL || t->right == NULL ) {
			    AvlNode *oldNode = t;
			    t = ( t->left != NULL ) ? t->left : t->right;
			    delete oldNode;
			    return false;
		    }
		    else {     AvlNode *tmp = t->right;
			    while(tmp->left != NULL) tmp = tmp->left;
			    t->data = tmp->data;
			    if (remove(tmp->data.key, t->right)) return true;
			    return adjust(t, 1);
		    }
	    }
	    if( x < t->data.key )   {                          // ����������ɾ��
		    if (remove( x, t->left )) return true;
		    return adjust(t, 0);
	 }
     else  {                                        // ����������ɾ��
		    if (remove( x, t->right )) return true;
	 	    return adjust(t, 1);
  	 }
 }

 template <class KEY, class OTHER>
 void AvlTree<KEY, OTHER>::remove( const KEY & x)
 {
   remove(x,root);
 }

 template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::adjust(AvlNode * &t, int subTree)
{     if (subTree) {                           //  ����������ɾ����ʹ�������䰫
 	         if (height(t->left) - height(t->right) == 1 ) return true;            // ����a
	    	if (height(t->right) == height(t->left)) { --t->height; return false;} // ����b
		if (height(t->left->right) > height(t->left->left))                 // ����d
		   {  LR(t);	return false;  }
		LL(t);
		if (height(t->right) == height(t->left)) return false; else return true;
	   }
	   else {      // ��������ɾ��
		if (height(t->right) - height(t->left) == 1 ) return true;             // ����a
		if (height(t->right) == height(t->left)) { --t->height; return false;} // ����b
		 if (height(t->right->left) > height(t->right->right))               // ����d
		    { RL(t);	return false;  }
		 RR(t);
		 if (height(t->right) == height(t->left)) return false; else return true;
	  }
}

template<class KEY,class OTHER>
bool AvlTree<KEY, OTHER>::check()
{
    linkQueue<AvlNode*> s;
    AvlNode *current;
    s.enQueue(root);
    while(!s.isEmpty())
    {
      current=s.deQueue();
      //检查大小关系
      if(current->left!=NULL) {s.enQueue(current->left);if(current->left->data.key>current->data.key) return false;};
      if(current->right!=NULL) {s.enQueue(current->right);if(current->right->data.key<current->data.key) return false;};
      //检查高度关系
      if(current->left!=NULL&&current->right!=NULL)
      {
         if((current->left->height-current->right->height)>=2||(current->right->height-current->left->height)>=2)
         return false;
      }
    }
    return true;
}

template<class KEY,class OTHER>
void AvlTree<KEY, OTHER>::search(int i)
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
void AvlTree<KEY, OTHER>::out(KEY m)
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

template<class KEY,class OTHER>
void AvlTree<KEY,OTHER>::makeEmpty(AvlNode *t)
{
    if(t==NULL) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

#endif // AVL_H_INCLUDED
