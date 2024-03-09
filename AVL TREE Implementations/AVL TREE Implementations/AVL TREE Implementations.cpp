#include <iostream>
using namespace std;

class Node {
public:
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVLtree {
public:
    Node* root;

    AVLtree() {
        root = nullptr;
    }
    int height(Node* n) {
        if (n == nullptr)return 0;
        else
            return n->height;
    }
    int getbalance(Node* n) {
        if (n == nullptr)return 0;
        else return height(n->left) - height(n->right);
       //  return INT_MIN;
    }

    Node* insert(Node* ptr, int k) {
        if (ptr == nullptr) {
            return new Node(k);
        }

        if (k < ptr->key) {
            ptr->left = insert(ptr->left, k);
        }
        else if (k > ptr->key) {
            ptr->right = insert(ptr->right, k);
        }
        else {
            cout << "\nDuplicate: " << k << endl;
            return ptr;
        }

        // Update height and balance factor
        ptr->height = 1 + max(height(ptr->left), height(ptr->right));
        int bf = getbalance(ptr);
        // Return the balanced node
        //LL case
        if (bf > 1 && k<ptr->left->key) {
            return RR(ptr);
        }
        //RR case
        if (bf > -1 && k > ptr->left->key) {
            return LL(ptr);
        }
        //LR case
        if (bf > 1 && k > ptr->left->key) {
            ptr->right = LL(ptr->right);
            return RR(ptr);
        }
        //RL case
        if (bf > -1 && k < ptr->left->key) {
            ptr->left = RR(ptr->left);
            return LL(ptr);
        }
        return ptr;
    }
    Node* RR(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;

        x->height = max(height(root->left),height(root->right));
        y->height = max(height(root->left), height(root->right));
        return x;
    }
    Node* LL(Node* y) {
        Node* x = y->right;
        Node* T2 = x->left;
        x->left = y;
        y->right = T2;

        x->height = max(height(root->left), height(root->right));
        y->height = max(height(root->left), height(root->right));
        return x;
    }

    bool find(Node* root,int k) {

        while (root != NULL) {
            if (root->key == k) {
                cout << "\n YOUR DATA IS FOUND \n";
                return true;
            }
            else if (root->key> k) {
                return find(root->left, k);
            }
            else if (root->key< k) {
                return find(root->right, k);
            }
            else {
                cout << "\n NOT FOUND \n";
                return false;
            }
        }
        return true;
    }
    int minBSTval(Node* root) {
        Node* temp = root;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        int dat;
        dat = temp->key;
        return dat;
    }
   
    Node* deleteNode(Node* root,int k) {
        if (root == NULL) {
            return root;
        }
        if (root->key == k) {
            // 0 child node 
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            // 1 child node left
            if (root->left !=NULL && root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            // 1 child node right
            if (root->left == NULL && root->right != NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            // 2 child node both side
            if (root->left != NULL && root->right != NULL) {
                int mini = minBSTval(root->right);
                root->key = mini;
                root->right = deleteNode(root->right, mini);
                return root;
            }

        }
        else if (k<root->key) {
            root->left = deleteNode(root->left, k);
        }
        else {
            root->right = deleteNode(root->right, k);
        }
        return root;
    }

    void inOrderTraversal(Node* ptr) {
        if (ptr != nullptr) {
            cout << " " << ptr->key;
            inOrderTraversal(ptr->left);
            
            inOrderTraversal(ptr->right);
        }
    }

    void insert(int k) {
        root = insert(root, k);
    }

    void traversal() {
        inOrderTraversal(root);
    }
    void del(int k) {
     //   cout << "oK;";
        root = deleteNode(root, k);
    }
};

int main() {
    AVLtree a;
    a.insert(32);
    a.insert(54);
    a.insert(22);
    a.insert(38);
    a.insert(62);
    a.insert(87);
    a.insert(98);
    a.traversal();
    a.del(67);
    cout << endl;
    a.traversal();
    return 0;
}
