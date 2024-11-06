#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct Node {
    string isbn;
    string bookData;
    Node* left;
    Node* right;

    Node(string i, string bd) : isbn(i), bookData(bd), left(nullptr), right(nullptr) {}
};

class BookBST {
public:
    BookBST() : root(nullptr) {}

    void insert(const string& isbn, const string& bookData) {
        root = insertRecursive(root, isbn, bookData);
    }

    string search(const string& isbn) const {
        Node* result = searchRecursive(root, isbn);
        return result ? result->bookData : "Book not found";
    }

    void deleteNode(const string& isbn) {
        root = deleteRecursive(root, isbn);
    }

private:
    Node* root;

    Node* insertRecursive(Node* node, const string& isbn, const string& bookData) {
        if (!node) return new Node(isbn, bookData);

        if (isbn < node->isbn)
            node->left = insertRecursive(node->left, isbn, bookData);
        else if (isbn > node->isbn)
            node->right = insertRecursive(node->right, isbn, bookData);
        else
            node->bookData = bookData; // Update if ISBN exists

        return node;
    }

    Node* searchRecursive(Node* node, const string& isbn) const {
        if (!node || node->isbn == isbn)
            return node;

        if (isbn < node->isbn)
            return searchRecursive(node->left, isbn);

        return searchRecursive(node->right, isbn);
    }

    Node* deleteRecursive(Node* node, const string& isbn) {
        if (!node) return node;

        if (isbn < node->isbn)
            node->left = deleteRecursive(node->left, isbn);
        else if (isbn > node->isbn)
            node->right = deleteRecursive(node->right, isbn);
        else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;

            Node* successor = minValueNode(node->right);
            node->isbn = successor->isbn;
            node->bookData = successor->bookData;
            node->right = deleteRecursive(node->right, successor->isbn);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }
};
