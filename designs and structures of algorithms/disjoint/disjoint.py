class DisjointSet:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # Path compression
        return self.parent[x]

    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)

        if rootX != rootY:
            if self.rank[rootX] > self.rank[rootY]:
                self.parent[rootY] = rootX
            elif self.rank[rootX] < self.rank[rootY]:
                self.parent[rootX] = rootY
            else:
                self.parent[rootY] = rootX
                self.rank[rootX] += 1

# Example usage:
dsu = DisjointSet(10)  # Initialize 10 elements
dsu.union(1, 2)
dsu.union(2, 3)
print(dsu.find(1) == dsu.find(3))  # Output: True (connected)
print(dsu.find(1) == dsu.find(4))  # Output: False (not connected)
