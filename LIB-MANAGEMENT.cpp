#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>  

using namespace std;

int main() {
    char data[16]; // Increased size for safety
    int n = 0, option = 0, count_n = 0;
    string empty = "00", proctor;
    ifstream f("Example.txt");
    string line;

    while (getline(f, line)) count_n++;
    f.close();

    while (option != 6) {
        cout << "\nAvailable operations: \n1. Add New Students\n2. Student Login\n3. Faculty Login\n4. Proctor Login\n5. Admin View\n6. Exit\nEnter option: ";
        cin >> option;

        if (option == 1) {
            cout << "Enter the number of students: ";
            cin >> n;
            count_n += n;
            ofstream outfile("Example.txt", ios::app);

            for (int i = 0; i < n; i++) {
                cout << "Enter your registration number: ";
                cin >> data;
                outfile << data << "\t";
                
                cout << "Enter your name: ";
                cin >> data;
                outfile << left << setw(15) << data << "\t"; // Ensure fixed-width
                
                outfile << empty << "\t" << empty << "\t";
                
                cout << "Enter your proctor ID: ";
                cin >> proctor;
                outfile << proctor << endl;
            }
            outfile.close();
        }

        else if (option == 2) {
            string regno;
            cout << "Enter your registration number: ";
            cin >> regno;
            ifstream infile("Example.txt");
            bool found = false;
            
            while (infile >> data) {
                if (regno == data) {
                    found = true;
                    cout << "\nRegistration Number: " << data << endl;
                    infile >> data;
                    cout << "Name: " << data << endl;
                    infile >> data;
                    cout << "CSE1001 mark: " << data << endl;
                    infile >> data;
                    cout << "CSE1002 mark: " << data << endl;
                    infile >> data;
                    cout << "Proctor ID: " << data << endl;
                    break;
                }
            }
            infile.close();
            if (!found) cout << "No such registration number found!\n";
        }

        else if (option == 3) {
            string subcode, mark;
            cout << "Enter your subject code: ";
            cin >> subcode;
            
            if (subcode != "CSE1001" && subcode != "CSE1002") {
                cout << "No such subject code found!\n";
                continue;
            }
            
            cout << "\nAvailable operations:\n1. Add marks\n2. View marks\nEnter option: ";
            cin >> option;
            
            if (option == 1) {
                cout << "Warning! You need to enter marks for all students!\n";
                fstream file("Example.txt", ios::in | ios::out);
                for (int i = 0; i < count_n; i++) {
                    int pos = (subcode == "CSE1001") ? (26 + 37 * i) : (29 + 37 * i);
                    file.seekp(pos, ios::beg);
                    cout << "Enter the mark of student#" << (i + 1) << " : ";
                    cin >> mark;
                    file.write(mark.c_str(), 2);
                }
                file.close();
            } else if (option == 2) {
                ifstream infile("Example.txt");
                cout << "Registration number - Marks\n";
                while (infile >> data) {
                    cout << data;
                    infile >> data >> data;
                    if (subcode == "CSE1001") cout << " - " << data << endl;
                    infile >> data;
                    if (subcode == "CSE1002") cout << " - " << data << endl;
                    infile >> data;
                }
                infile.close();
            }
        }

        else if (option == 4) {
            string procid;
            cout << "Enter your proctor ID: ";
            cin >> procid;
            ifstream infile("Example.txt");
            bool found = false;
            string temp1, temp2, temp3, temp4, id;
            
            while (infile >> temp1 >> temp2 >> temp3 >> temp4 >> id) {
                if (id == procid) {
                    cout << "\nRegistration Number: " << temp1 << endl;
                    cout << "Name: " << temp2 << endl;
                    cout << "CSE1001 Mark: " << temp3 << endl;
                    cout << "CSE1002 Mark: " << temp4 << endl;
                    found = true;
                }
            }
            infile.close();
            if (!found) cout << "No such proctor ID found!\n";
        }

        else if (option == 5) {
            string password;
            cout << "Enter the admin password: ";
            cin >> password;
            
            if (password == "admin") {
                ifstream infile("Example.txt");
                cout << "Reg No.\tName\tCSE1001\tCSE1002\tProctor ID\n";
                while (infile >> data) {
                    cout << data << "\t";
                    infile >> data;
                    cout << data << "\t";
                    infile >> data;
                    cout << data << "\t";
                    infile >> data;
                    cout << data << "\t";
                    infile >> data;
                    cout << data << endl;
                }
                infile.close();
            } else {
                cout << "Incorrect password!\n";
            }
        }
    }
    return 0;
}
