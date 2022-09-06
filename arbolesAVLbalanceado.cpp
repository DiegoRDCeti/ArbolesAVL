#include <iostream>
using namespace std;

class Node {
   public:
  int key;
  Node *left;
  Node *right;
  int height;
};

int max(int a, int b);
void preOrder(Node *);
void inOrder(Node *);
void postOrder(Node *);

// Calcular altura del arbol
int height(Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// Creacion de nuevo nodo
Node *newNode(int key) {
  Node *node = new Node();
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Rotacion R
Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  return x;
}

// Rotacion L
Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  return y;
}

// Conseguir el factor de balance de cada nodo
int getBalanceFactor(Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) -
       height(N->right);
}

// Insertar el nodo
Node *insertNode(Node *node, int key) {
  // Encontrar la posicion correcta del nodo y
  // Luego insertarlo
  if (node == NULL)
    return (newNode(key));
  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  // Actualizar el valor de balance de cada nodo y
  // Luego insertarlo 
  node->height = 1 + max(height(node->left),
               height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (key < node->left->key) {
      return rightRotate(node);
    } else if (key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (key > node->right->key) {
      return leftRotate(node);
    } else if (key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  
  return node;
  
}

// Nodo con el valor minimo
Node *nodeWithMimumValue(Node *node) {
  Node *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

// Eliminar un nodo
Node *deleteNode(Node *root, int key) {
  // Encontrar el nodo para luego eliminarlo
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == NULL) ||
      (root->right == NULL)) {
      Node *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      Node *temp = nodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right,
                   temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Actualizar el valor de balance de cada nodo y luego
  // balancear el arbol
  root->height = 1 + max(height(root->left),
               height(root->right));
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1) {
    if (getBalanceFactor(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}

// Imprimir el arbol
void printTree(Node *root, string indent, bool last) {
  if (root != nullptr) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "   ";
    } else {
      cout << "L----";
      indent += "|  ";
    }
    cout << root->key << endl;
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
  }
}

void preOrder(Node *root){
	if(root != NULL){
		cout << root->key << "---*---*";
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(Node *root){
	if(root != NULL){
		inOrder(root->left);
		cout << root->key << "---*---*";
		inOrder(root->right);
	}
}

void postOrder(Node *root){
	if(root != NULL){
		postOrder(root->left);
		postOrder(root->right);
		cout << root->key << "---*---*";
	}
}

int main() {
  Node *root = NULL;
  root = insertNode(root, 100);
  root = insertNode(root, 90);
  root = insertNode(root, 80);
  root = insertNode(root, 70);
  root = insertNode(root, 110);
  root = insertNode(root, 85);
  root = insertNode(root, 75);
  root = insertNode(root, 115);
  printTree(root, "", true);
  cout << "Tree in preOrder: " << endl;
  preOrder(root);
  cout << "\nTree in inOrder: " << endl;
  inOrder(root);
  cout << "\nTree in postOrder: " << endl;
  postOrder(root);
  
  /*root = deleteNode(root, 110);
  cout << "After deleting " << endl;
  printTree(root, "", true);*/

}