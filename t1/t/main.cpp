#include "traffic_signal.hpp"
#include <iostream>

void showMenu() {
    std::cout << "\n--- Traffic Signal Control ---\n";
    std::cout << "1. Rotate Signals\n";
    std::cout << "2. Add Signal to VIP Stack\n";
    std::cout << "3. Display All Signals\n";
    std::cout << "4. Display VIP Stack\n";
    std::cout << "5. Remove Signal from VIP Stack\n";
    std::cout << "6. Delete VIP Stack\n";
    std::cout << "7. Exit\n";
    std::cout << "Choose an option (1-7): ";
}

int main() {
    SignalList signalList;
    VIPStack vipStack;

    // Initialize with 4 signals
    signalList.addSignal(1); // a1
    signalList.addSignal(2); // a2
    signalList.addSignal(3); // a3
    signalList.addSignal(4); // a4

    // Ensure the first signal is green
    signalList.updateSignalColorsBasedOnVIP(vipStack);

    int choice;
    bool running = true;

    while (running) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Rotate signals
                signalList.rotateSignals();
                signalList.updateSignalColorsBasedOnVIP(vipStack);
                std::cout << "Signals rotated.\n";
                break;
            }
            case 2: {
                // Add signal to VIP stack
                int id;
                std::cout << "Enter Signal ID to add to VIP Stack: ";
                std::cin >> id;

                SignalNode* temp = signalList.getHead();
                while (temp && temp->id != id) {
                    temp = temp->next;
                }

                if (temp) {
                    vipStack.pushSignal(temp);
                    signalList.updateSignalColorsBasedOnVIP(vipStack);
                } else {
                    std::cout << "Signal ID not found.\n";
                }
                break;
            }
            case 3: {
                // Display all signals
                signalList.displaySignals();
                break;
            }
            case 4: {
                // Display VIP stack
                vipStack.displayStack();
                break;
            }
            case 5: {
                // Remove signal from VIP stack
                vipStack.popSignal();
                signalList.updateSignalColorsBasedOnVIP(vipStack);
                break;
            }
            case 6: {
                // Delete VIP stack
                while (!vipStack.isEmpty()) {
                    vipStack.popSignal();
                }
                signalList.updateSignalColorsBasedOnVIP(vipStack);
                std::cout << "VIP Stack cleared.\n";
                break;
            }
            case 7: {
                // Exit the program
                running = false;
                std::cout << "Exiting program...\n";
                break;
            }
            default: {
                std::cout << "Invalid option. Please try again.\n";
                break;
            }
        }
    }

    return 0;
}
