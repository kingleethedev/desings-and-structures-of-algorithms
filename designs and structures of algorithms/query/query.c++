#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

class PatientQueue {
public:
    void enqueue(const string& patient) {
        queue.push(patient);
    }

    string dequeue() {
        if (!isEmpty()) {
            string patient = queue.front();
            queue.pop();
            return patient;
        } else {
            return "No patients in queue";
        }
    }

    bool isEmpty() const {
        return queue.empty();
    }

private:
    queue<string> queue;
};

class EmergencyStack {
public:
    void push(const string& patient) {
        stack.push(patient);
    }

    string pop() {
        if (!isEmpty()) {
            string patient = stack.top();
            stack.pop();
            return patient;
        } else {
            return "No emergency patients";
        }
    }

    bool isEmpty() const {
        return stack.empty();
    }

private:
    stack<string> stack;
};
