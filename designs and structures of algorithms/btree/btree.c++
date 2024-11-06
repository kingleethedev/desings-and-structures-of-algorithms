#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class BTreeNode {
public:
    vector<pair<string, string>> keys;  // Pair of (file name, location)
    vector<BTreeNode*> children;
    bool leaf;

    BTreeNode(bool isLeaf) : leaf(isLeaf) {}
};

class BTree {
public:
    BTree(int t) : t(t) {
        root = new BTreeNode(true);
    }

    string search(const string& key) {
        return search(root, key);
    }

    void insert(const string& key, const string& location) {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);
            root = newRoot;
            insertNonFull(newRoot, key, location);
        } else {
            insertNonFull(root, key, location);
        }
    }

private:
    BTreeNode* root;
    int t;  // Minimum degree

    string search(BTreeNode* node, const string& key) {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i].first) i++;

        if (i < node->keys.size() && key == node->keys[i].first)
            return node->keys[i].second;

        if (node->leaf)
            return "File not found";

        return search(node->children[i], key);
    }

    void splitChild(BTreeNode* parent, int i) {
        BTreeNode* child = parent->children[i];
        BTreeNode* newChild = new BTreeNode(child->leaf);
        parent->keys.insert(parent->keys.begin() + i, child->keys[t - 1]);
        parent->children.insert(parent->children.begin() + i + 1, newChild);

        newChild->keys.assign(child->keys.begin() + t, child->keys.end());
        child->keys.resize(t - 1);

        if (!child->leaf) {
            newChild->children.assign(child->children.begin() + t, child->children.end());
            child->children.resize(t);
        }
    }

    void insertNonFull(BTreeNode* node, const string& key, const string& location) {
        int i = node->keys.size() - 1;

        if (node->leaf) {
            node->keys.push_back({ "", "" });
            while (i >= 0 && key < node->keys[i].first) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = { key, location };
        } else {
            while (i >= 0 && key < node->keys[i].first) i--;

            i++;
            if (node->children[i]->keys.size() == 2 * t - 1) {
                splitChild(node, i);
                if (key > node->keys[i].first) i++;
            }
            insertNonFull(node->children[i], key, location);
        }
    }
};

int main() {
    // Create a B-tree of minimum degree 2
    BTree btree(2);

    // Insert file names and locations
    btree.insert("file1.txt", "/folder/file1.txt");
    btree.insert("file2.txt", "/folder/file2.txt");
    btree.insert("file3.txt", "/folder/file3.txt");

    // Search for file locations
    cout << btree.search("file1.txt") << endl;  // Output: /folder/file1.txt
    cout << btree.search("file4.txt") << endl;  // Output: File not found

    return 0;
}
