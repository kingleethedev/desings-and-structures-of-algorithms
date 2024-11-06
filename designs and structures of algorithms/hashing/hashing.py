class UserHashTable:
    def __init__(self, size=100):
        # Initialize hash table with a fixed size of empty lists for chaining
        self.size = size
        self.table = [[] for _ in range(size)]

    def _hash(self, username: str) -> int:
        """Compute hash index based on the username."""
        return hash(username) % self.size

    def add_user(self, username: str, profile_data: dict):
        """Add a user profile to the hash table."""
        index = self._hash(username)
        
        # Check if username already exists in the chain to update it
        for i, (stored_username, _) in enumerate(self.table[index]):
            if stored_username == username:
                self.table[index][i] = (username, profile_data)
                return
        
        # Append new entry if username does not exist
        self.table[index].append((username, profile_data))

    def get_user(self, username: str) -> dict:
        """Retrieve the profile data for a given username."""
        index = self._hash(username)
        
        # Look through the chain at this index for the matching username
        for stored_username, profile_data in self.table[index]:
            if stored_username == username:
                return profile_data

        # Return None if user not found
        return None
