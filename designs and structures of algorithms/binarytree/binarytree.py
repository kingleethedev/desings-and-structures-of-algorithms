class Node:
    def __init__(self, isbn, book_data):
        self.isbn = isbn
        self.book_data = book_data
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def insert(self, isbn, book_data):
        """Insert a new book record into the BST."""
        if self.root is None:
            self.root = Node(isbn, book_data)
        else:
            self._insert_recursive(self.root, isbn, book_data)

    def _insert_recursive(self, node, isbn, book_data):
        if isbn < node.isbn:
            if node.left is None:
                node.left = Node(isbn, book_data)
            else:
                self._insert_recursive(node.left, isbn, book_data)
        elif isbn > node.isbn:
            if node.right is None:
                node.right = Node(isbn, book_data)
            else:
                self._insert_recursive(node.right, isbn, book_data)
        else:
            node.book_data = book_data  # Update book data if ISBN already exists

    def search(self, isbn):
        """Search for a book by ISBN and return its data if found."""
        return self._search_recursive(self.root, isbn)

    def _search_recursive(self, node, isbn):
        if node is None:
            return None
        if isbn == node.isbn:
            return node.book_data
        elif isbn < node.isbn:
            return self._search_recursive(node.left, isbn)
        else:
            return self._search_recursive(node.right, isbn)

    def delete(self, isbn):
        """Delete a book by ISBN from the BST."""
        self.root = self._delete_recursive(self.root, isbn)

    def _delete_recursive(self, node, isbn):
        if node is None:
            return node

        if isbn < node.isbn:
            node.left = self._delete_recursive(node.left, isbn)
        elif isbn > node.isbn:
            node.right = self._delete_recursive(node.right, isbn)
        else:
            # Node with only one child or no child
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left

            # Node with two children: Get the inorder successor
            successor = self._min_value_node(node.right)
            node.isbn, node.book_data = successor.isbn, successor.book_data
            node.right = self._delete_recursive(node.right, successor.isbn)

        return node

    def _min_value_node(self, node):
        """Get the node with the minimum ISBN in a subtree."""
        current = node
        while current.left is not None:
            current = current.left
        return current
