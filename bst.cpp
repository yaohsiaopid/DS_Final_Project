// #include "function.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;
extern ofstream fileOut;
BikePtr _BST::search(LicenseType License)
{
  if(root == NULL) return NULL;
  _node *cur = root;
  while(1) {
    if(cur->bike->License == License)
      return cur->bike;
    else if(cur->bike->License < License) {
      if(cur -> right != NULL)
        cur = cur -> right;
      else
        return NULL;
    } else {
      if(cur -> left != NULL)
        cur = cur -> left;
      else
        return NULL;
    }

  }

}

void _BST::ins(BikePtr bike)
{
  if(root == NULL) {
    root = new _node();
    root->bike = bike;
    return;
  }
  _node *cur = root;
  while(1) {
    if(cur->bike->License == bike->License)
      return;
    else if(cur->bike->License < bike->License) {
      if(cur -> right != NULL)
        cur = cur -> right;
      else
        break;
    } else {
      if(cur -> left != NULL)
        cur = cur -> left;
      else
        break;
    }
  }
  if(cur->bike->License < bike->License) {
      cur -> right = new _node();
      cur -> right -> bike = bike;
  } else {
    cur -> left = new _node();
    cur -> left -> bike = bike;
  }

}

void _BST::del(BikePtr bike)
{
  if(root == NULL) return;
  int l = -1;
  _node *cur = root, *p = NULL;
  while(1) {
    if(cur->bike->License == bike->License)
      break;
    else if(cur->bike->License < bike->License) {
      if(cur -> right != NULL){
        p = cur;
        l = 0;
        cur = cur -> right;
      } else
        return; // find no
    } else {
      if(cur -> left != NULL){
        p = cur;
        l = 1;
        cur = cur -> left;
      } else
        return; // find no
    }
  }

  if(cur -> left == NULL && cur -> right == NULL) {
    if(cur == root) {
      root = NULL;
    } else {
      if(l) p -> left  = NULL;
      else  p -> right = NULL;
    }
    delete cur;
    return;
  } else if( cur -> left == NULL && cur -> right != NULL) {
    if(cur == root) {
      root = cur -> right;
      delete cur;
      return;
    } else {
      if(l) p -> left = cur -> right;
      else  p -> right = cur -> right;
      delete cur;
    }

  } else {
    // cur -> left != NULL
    // Replace with the left child which has the largest value case
    if (cur == root) {
      _node *temp = cur -> left, *prev = NULL;
      while(1) {
        if (temp -> right != NULL){ prev = temp; temp = temp -> right;}
        else break;
      }
      if(prev == NULL) {
        root = cur -> left;
        root -> right = cur -> right;
        delete cur;
        return;
      } else {
        prev -> right = NULL;
        temp -> left = cur -> left;
        temp -> right = cur -> right;
        root = temp;
        delete cur;
        return;
      }

    } else {
      _node *temp = cur -> left, *prev = NULL;
      while(1){
        if(temp -> right != NULL) { prev = temp; temp = temp -> right; }
        else break;
      }
      if(prev != NULL) {
        prev -> right = NULL;
        temp -> right = cur -> right;
        temp -> left = cur -> left;
      } else {
        temp -> right = cur -> right;
      }
      if(l) p -> left = temp;
      else  p -> right = temp;
      delete cur;

    }


  }

}
void _BST::show(_node *n)
{
  if(n == NULL) return;
  _node *cur = n;

  std::cout << n->bike->License << " ";
  this->show(n->left);
  this->show(n->right);
}
void _BST::inord() {
  if(root == NULL) return;
  stack<_node*> st;
  st.push(root);
  _node *cur = root;
  while(!st.empty()) {
    while(cur != NULL) {
      if(cur -> left != NULL) {
        st.push(cur->left);
        cur = cur -> left;

      } else
        break;
    }
    cur = st.top();
    st.pop();
    fileOut << cur -> bike -> License;
    if(cur -> right != NULL) {
      st.push(cur->right);
      cur = cur -> right;
    }
    if(!st.empty())
      fileOut << "->";

  }
}
void _BST::preord() {
  if(root == NULL) return;
  stack<_node*> q;
  q.push(root);
  while(!q.empty()) {
    fileOut << q.top()->bike->License;
    _node *temp = q.top();
    q.pop();
    if(temp->right != NULL)
      q.push(temp->right);
    if(temp->left != NULL)
      q.push(temp->left);

    if(!q.empty()) {
      fileOut << "->";
    }


  }
}
