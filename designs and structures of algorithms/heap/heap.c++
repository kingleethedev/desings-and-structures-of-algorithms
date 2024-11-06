#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct FibHeapNode {
    int key;
    string value;
    FibHeapNode* parent = nullptr;
    FibHeapNode* child = nullptr;
    FibHeapNode* next;
    FibHeapNode* prev;
    int degree = 0;
    bool marked = false;

    FibHeapNode(int k, string v) : key(k), value(v), next(this), prev(this) {}
};

class FibHeap {
public:
    FibHeap() : minNode(nullptr), totalNodes(0) {}

    FibHeapNode* insert(int key, const string& value) {
        FibHeapNode* node = new FibHeapNode(key, value);
        addToRootList(node);
        if (!minNode || node->key < minNode->key) {
            minNode = node;
        }
        totalNodes++;
        return node;
    }

    FibHeapNode* extractMin() {
        FibHeapNode* z = minNode;
        if (z) {
            if (z->child) {
                vector<FibHeapNode*> children = getChildren(z->child);
                for (auto child : children) {
                    addToRootList(child);
                    child->parent = nullptr;
                }
            }
            removeFromRootList(z);
            if (z == z->next) {
                minNode = nullptr;
            } else {
                minNode = z->next;
                consolidate();
            }
            totalNodes--;
        }
        return z;
    }

    void decreaseKey(FibHeapNode* x, int newKey) {
        if (newKey > x->key) return;
        x->key = newKey;
        FibHeapNode* y = x->parent;
        if (y && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->key < minNode->key) {
            minNode = x;
        }
    }

private:
    FibHeapNode* minNode;
    int totalNodes;

    void addToRootList(FibHeapNode* node) {
        if (!minNode) {
            minNode = node->next = node->prev = node;
        } else {
            node->next = minNode;
            node->prev = minNode->prev;
            minNode->prev->next = node;
            minNode->prev = node;
        }
    }

    void removeFromRootList(FibHeapNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    vector<FibHeapNode*> getChildren(FibHeapNode* start) {
        vector<FibHeapNode*> children;
        FibHeapNode* node = start;
        do {
            children.push_back(node);
            node = node->next;
        } while (node != start);
        return children;
    }

    void consolidate() {
        int maxDegree = log2(totalNodes) + 1;
        vector<FibHeapNode*> A(maxDegree, nullptr);
        vector<FibHeapNode*> nodes = getChildren(minNode);

        for (FibHeapNode* w : nodes) {
            FibHeapNode* x = w;
            int d = x->degree;
            while (A[d]) {
                FibHeapNode* y = A[d];
                if (x->key > y->key) swap(x, y);
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
       
