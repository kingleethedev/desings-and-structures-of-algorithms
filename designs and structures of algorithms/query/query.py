from collections import deque

class PatientQueue:
    def __init__(self):
        self.queue = deque()

    def enqueue(self, patient):
        """Add a patient to the end of the queue."""
        self.queue.append(patient)

    def dequeue(self):
        """Remove and return the patient at the front of the queue."""
        if not self.is_empty():
            return self.queue.popleft()
        else:
            return "No patients in queue"

    def is_empty(self):
        """Check if the queue is empty."""
        return len(self.queue) == 0

class EmergencyStack:
    def __init__(self):
        self.stack = []

    def push(self, patient):
        """Add an emergency patient to the top of the stack."""
        self.stack.append(patient)

    def pop(self):
        """Remove and return the patient from the top of the stack."""
        if not self.is_empty():
            return self.stack.pop()
        else:
            return "No emergency patients"

    def is_empty(self):
        """Check if the stack is empty."""
        return len(self.stack) == 0
