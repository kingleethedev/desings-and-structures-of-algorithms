class BTreeNode:
    def __init__(self, leaf=False):
        self.leaf = leaf
        self.keys = []
        self.children = []

class BTree:
    def __init__(self, t):
        self.root = BTreeNode(True)
        self.t = t  # Minimum degree (defines the range for number of keys)

    def search(self, key, node=None):
        """Search for a key in the B-tree and return the location if found."""
        if node is None:
            node = self.root
        
        i = 0
        while i < len(node.keys) and key > node.keys[i][0]:
            i += 1
        
        if i < len(node.keys) and key == node.keys[i][0]:
            return node.keys[i][1]
        
        if node.leaf:
            return None
        
        return self.search(key, node.children[i])

    def insert(self, key, location):
        """Insert a file name and location into the B-tree."""
        root = self.root
        if len(root.keys) == 2 * self.t - 1:
            new_root = BTreeNode()
            self.root = new_root
            new_root.children.append(root)
            self.split_child(new_root, 0)
            self._insert_non_full(new_root, key, location)
        else:
            self._insert_non_full(root, key, location)

    def split_child(self, parent, index):
        """Split the child of a parent node at the given index."""
        t = self.t
        node = parent.children[index]
        new_node = BTreeNode(node.leaf)
        parent.keys.insert(index, node.keys[t - 1])
        parent.children.insert(index + 1, new_node)
        
        new_node.keys = node.keys[t:(2 * t - 1)]
        node.keys = node.keys[0:(t - 1)]
        
        if not node.leaf:
            new_node.children = node.children[t:(2 * t)]
            node.children = node.children[0:t]

    def _insert_non_full(self, node, key, location):
        """Insert a key into a non-full node."""
        i = len(node.keys) - 1
        if node.leaf:
            node.keys.append((None, None))
            while i >= 0 and key < node.keys[i][0]:
                node.keys[i + 1] = node.keys[i]
                i -= 1
            node.keys[i + 1] = (key, location)
        else:
            while i >= 0 and key < node.keys[i][0]:
                i -= 1
            i += 1
            if len(node.children[i].keys) == 2 * self.t - 1:
                self.split_child(node, i)
                if key > node.keys[i][0]:
                    i += 1
            self._insert_non_full(node.children[i], key, location)
