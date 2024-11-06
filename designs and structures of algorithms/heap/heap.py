class FibHeapNode:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.degree = 0
        self.parent = None
        self.child = None
        self.marked = False
        self.next = self
        self.prev = self

class FibHeap:
    def __init__(self):
        self.min_node = None
        self.total_nodes = 0

    def insert(self, key, value):
        node = FibHeapNode(key, value)
        self._add_to_root_list(node)
        if self.min_node is None or node.key < self.min_node.key:
            self.min_node = node
        self.total_nodes += 1
        return node

    def extract_min(self):
        z = self.min_node
        if z is not None:
            if z.child is not None:
                children = [x for x in self._iterate(z.child)]
                for child in children:
                    self._add_to_root_list(child)
                    child.parent = None
            self._remove_from_root_list(z)
            if z == z.next:
                self.min_node = None
            else:
                self.min_node = z.next
                self._consolidate()
            self.total_nodes -= 1
        return z

    def decrease_key(self, node, new_key):
        if new_key > node.key:
            raise ValueError("New key is greater than current key")
        node.key = new_key
        parent = node.parent
        if parent and node.key < parent.key:
            self._cut(node, parent)
            self._cascading_cut(parent)
        if node.key < self.min_node.key:
            self.min_node = node

    def _add_to_root_list(self, node):
        if self.min_node is None:
            node.next = node.prev = node
        else:
            node.next = self.min_node
            node.prev = self.min_node.prev
            self.min_node.prev.next = node
            self.min_node.prev = node

    def _remove_from_root_list(self, node):
        node.prev.next = node.next
        node.next.prev = node.prev

    def _consolidate(self):
        import math
        max_degree = int(math.log(self.total_nodes) * math.log(2)) + 1
        A = [None] * max_degree
        nodes = [x for x in self._iterate(self.min_node)]
        for w in nodes:
            x = w
            d = x.degree
            while A[d] is not None:
                y = A[d]
                if x.key > y.key:
                    x, y = y, x
                self._link(y, x)
                A[d] = None
                d += 1
            A[d] = x
        self.min_node = None
        for i in range(max_degree):
            if A[i] is not None:
                if self.min_node is None or A[i].key < self.min_node.key:
                    self.min_node = A[i]

    def _link(self, y, x):
        self._remove_from_root_list(y)
        y.parent = x
        if x.child is None:
            x.child = y
            y.next = y.prev = y
        else:
            y.next = x.child
            y.prev = x.child.prev
            x.child.prev.next = y
            x.child.prev = y
        x.degree += 1
        y.marked = False

    def _cut(self, x, y):
        self._remove_from_child_list(y, x)
        y.degree -= 1
        self._add_to_root_list(x)
        x.parent = None
        x.marked = False

    def _cascading_cut(self, y):
        z = y.parent
        if z is not None:
            if not y.marked:
                y.marked = True
            else:
                self._cut(y, z)
                self._cascading_cut(z)

    def _remove_from_child_list(self, parent, child):
        if parent.child == child:
            if child.next != child:
                parent.child = child.next
            else:
                parent.child = None
        child.prev.next = child.next
        child.next.prev = child.prev

    def _iterate(self, start):
        node = start
        while True:
            yield node
            node = node.next
            if node == start:
                break
