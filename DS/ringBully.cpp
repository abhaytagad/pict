#include <iostream>
#include <vector>
using namespace std;


void ringElection(vector<int> processes) {
    int n = processes.size();
    int initiator;
    cout << "\n[RING ALGORITHM] Enter the process that initiates the election: ";
    cin >> initiator;

    
    int current = initiator;
    int maxID = processes[current];  

    cout << "Election started by process: P" << initiator << endl;

    do {
        int next = (current + 1) % n;
        cout << "Process P" << current << " sends message to process P" << next << endl;
        
        if (processes[next] > maxID) {
            maxID = processes[next]; 
        }
        current = next;
    } while (current != initiator);

   
    cout << "Process P" << maxID << " becomes the new coordinator in Ring Algorithm." << endl;
}


void bullyElection(vector<int> processes, int initiator) {
    int n = processes.size();
    cout << "\n[BULLY ALGORITHM] Election initiated by process P" << initiator << endl;

    
    int maxID = processes[initiator];
    bool hasHigher = false;

    for (int i = initiator + 1; i < n; ++i) {
        cout << "Process P" << initiator << " sends election message to process P" << i << endl;
        if (processes[i] > maxID) {
            cout << "Process P" << i << " responds to election message." << endl;
            maxID = processes[i];
            hasHigher = true;
        }
    }

    if (!hasHigher) {
        cout << "Process P" << initiator << " becomes the new coordinator in Bully Algorithm." << endl;
    } else {
        cout << "Process P" << maxID << " becomes the new coordinator in Bully Algorithm." << endl;
    }
}

int main() {
   
    vector<int> processes = {1, 2, 3, 4, 5}; 

    int choice, initiator;

    
    do {
        cout << "\nChoose Election Algorithm:\n";
        cout << "1. Ring Election Algorithm\n";
        cout << "2. Bully Election Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                ringElection(processes);  
                break;

            case 2:
                cout << "\n[BULLY ALGORITHM] Enter the process that initiates the election: ";
                cin >> initiator;
                bullyElection(processes, initiator);  
                break;

            case 3:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice! Please enter again.\n";
        }
    } while (choice != 3);

    return 0;
}
