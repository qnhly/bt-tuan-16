//Cài đặt cây AVL để nhập một dãy số cho trước (dãy cho trên lớp) thành một cây AVL 
// 17 23 201 98 67 83 13 23 10 191 84 58
#include <iostream>
#include <algorithm>
using namespace std;
//Khai báo cấu trúc Node
struct avlNode{
    int data;
    avlNode* left;
    avlNode* right;
    int height;
    avlNode(int x, avlNode* l, avlNode* r, int h){
        data = x;
        left = l;
        right = r;
        height = h;
    }
};
int isEmty(avlNode* root){
    return root == NULL;
}
//hàm trả về chiều cao của cây
int height(avlNode* root){
    return root == NULL ? -1 : root->height;
}
//Cài đặt hàm xoay đơn/kép
void rotateWithLeftChild(avlNode* &k2){
    avlNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;  //ham max tra ve gia tri lon hon
    k1->height = max(height(k1->left), k2->height) + 1; //cap nhat lai chieu cao
    k2 = k1;    //dat k1 lam goc moi
}
void rotateWithRightChild(avlNode* &k2){
    avlNode* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->right), k2->height) + 1;
    k2 = k1;
}
void doubleWithLeftChild(avlNode* &k3){
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}
void doubleWithRightChild(avlNode* &k3){
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}
//Cài đặt hàm kiểm tra cân bằng
void balance(avlNode* &root){ //& de cap nhat lai root neu khong thi phai dung ham tra ve avlNode*
    if(root == NULL) return;
    if(height(root->left) - height(root->right) > 1){
        if(height(root->left->left) >= height(root->left->right)){
            rotateWithLeftChild(root);
        }else{
            doubleWithLeftChild(root);
        }
    }else if(height(root->right) - height(root->left) > 1){
        if(height(root->right->right) >= height(root->right->left)){
            rotateWithRightChild(root);
        }else{
            doubleWithRightChild(root);
        }
    }
    root->height = max(height(root->left), height(root->right)) + 1;
}//Cài đặt hàm thêm node mới vào cây
avlNode* insert(avlNode* root, int x){
    if(isEmty(root)){
        return new avlNode(x, NULL, NULL, 0);
    }
    if(x <= root->data){
        root->left = insert(root->left, x);
    }else if(x > root->data){
        root->right = insert(root->right, x);
    }
    balance(root);
    return root;
}
//Cài đặt hàm nhập node mới
avlNode* input(avlNode* root){
    int n;
    cout << "Nhap so luong node: ";
    cin >> n;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        root = insert(root, x);
    }
    return root;
}
//Cài đặt hàm in cây AVL (theo thứ tự duyệt)
void print(avlNode* root){
    if(isEmty(root)) return;
    print(root->left);
    cout << root->data << " ";
    print(root->right);
}
int main(){
    avlNode* root = NULL;
    root = input(root); // 17 23 201 98 67 83 13 23 10 191 84 58
    print(root);
    return 0;
}