#ifndef TRAFFIC_SIGNAL_HPP
#define TRAFFIC_SIGNAL_HPP

#include <iostream>

// SignalNode represents each traffic signal
struct SignalNode {
    int id;                      // Signal ID
    std::string color;           // Current signal color (Green/Red)
    SignalNode* next;            // Pointer to the next signal

    SignalNode(int id) : id(id), color("Red"), next(nullptr) {}
};

// SignalList represents the circular linked list of signals
class SignalList {
private:
    SignalNode* head;            // Head of the circular linked list
    SignalNode* greenSignal;     // Pointer to the current green signal
public:
    SignalList();

    void addSignal(int id);      // Add a new signal to the list
    void rotateSignals();        // Rotate the green signal pointer
    void displaySignals() const; // Display all signals and their states

    void updateSignalColorsBasedOnVIP(const class VIPStack& vipStack); // Update signal colors based on VIP stack
    SignalNode* getHead() const; // Getter for the head node
};

// Stack for VIP-selected signals
class VIPStack {
private:
    struct StackNode {
        SignalNode* signal;      // Pointer to the signal in the list
        StackNode* next;         // Next element in the stack
    };

    StackNode* top;              // Top of the stack
public:
    VIPStack();

    void pushSignal(SignalNode* signal); // Push a signal onto the stack
    void popSignal();                    // Pop the top signal off the stack
    void displayStack() const;           // Display all signals in the stack
    bool isEmpty() const;                // Check if the stack is empty
    bool containsSignal(SignalNode* signal) const; // Check if a signal is already in the stack
};

#endif
