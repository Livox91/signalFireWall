#include "traffic_signal.hpp"

// SignalList Implementation
SignalList::SignalList() : head(nullptr), greenSignal(nullptr) {}

void SignalList::addSignal(int id) {
    SignalNode* newNode = new SignalNode(id);
    if (!head) {
        head = newNode;
        head->next = head; // Circular linked list points to itself
        greenSignal = head; // First signal is green by default
        head->color = "Green";
    } else {
        SignalNode* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head; // Maintain circular property
    }
}

void SignalList::rotateSignals() {
    if (!greenSignal) return; // No signals to rotate

    // Set the current green signal to red
    greenSignal->color = "Red";

    // Move the green signal pointer to the next signal
    greenSignal = greenSignal->next;

    // Set the new green signal
    greenSignal->color = "Green";
}

void SignalList::displaySignals() const {
    if (!head) {
        std::cout << "No signals in the list.\n";
        return;
    }
    SignalNode* temp = head;
    do {
        std::cout << "Signal " << temp->id << ": " << temp->color << "\n";
        temp = temp->next;
    } while (temp != head);
}

void SignalList::updateSignalColorsBasedOnVIP(const VIPStack& vipStack) {
    if (!head) return; // No signals in the list

    bool vipActive = !vipStack.isEmpty(); // Check if VIP stack has signals

    SignalNode* temp = head;
    do {
        if (vipActive && vipStack.containsSignal(temp)) {
            // VIP signals remain green
            temp->color = "Green";
        } else if (vipActive) {
            // All non-VIP signals turn red
            temp->color = "Red";
        } else if (temp == greenSignal) {
            // Ensure the green signal remains green if no VIP is active
            temp->color = "Green";
        } else {
            // All other signals are red
            temp->color = "Red";
        }
        temp = temp->next;
    } while (temp != head);
}

SignalNode* SignalList::getHead() const {
    return head;
}

// VIPStack Implementation
VIPStack::VIPStack() : top(nullptr) {}

void VIPStack::pushSignal(SignalNode* signal) {
    if (containsSignal(signal)) {
        std::cout << "Signal " << signal->id << " is already in the VIP Stack.\n";
        return;
    }

    StackNode* newNode = new StackNode();
    newNode->signal = signal;
    newNode->next = top;
    top = newNode;

    // Make the signal green permanently
    signal->color = "Green";
}

void VIPStack::popSignal() {
    if (!top) {
        std::cout << "VIP Stack is empty.\n";
        return;
    }
    StackNode* temp = top;
    SignalNode* signal = top->signal;
    top = top->next;

    // Restore the signal's color to red
    signal->color = "Red";

    delete temp;
}

void VIPStack::displayStack() const {
    if (!top) {
        std::cout << "VIP Stack is empty.\n";
        return;
    }
    StackNode* temp = top;
    std::cout << "VIP Stack (Top to Bottom):\n";
    while (temp) {
        std::cout << "Signal " << temp->signal->id << "\n";
        temp = temp->next;
    }
}

bool VIPStack::isEmpty() const {
    return top == nullptr;
}

bool VIPStack::containsSignal(SignalNode* signal) const {
    StackNode* temp = top;
    while (temp) {
        if (temp->signal == signal) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
