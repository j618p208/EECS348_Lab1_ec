#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void print_array(string header, int array[5][6]) {
    for (int i=0; i<5; i++) {
        cout << header << " " << i+1 << ": ";
        for (int j=0; j<6; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

void print_array(string programmer, string department, int array[5][5]) {
    for (int i=0; i<5; i++) {
        cout << programmer << " " << i+1 << " wants " << department << ": ";
        for (int j=0; j<5; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

void rec_assign_programmers(int programmers[5][6], int departments[5][6]) {
    int assign[5][5] = { //rows = programmer
        {0,0,0,0,0},    //columns is the departments that want the programmer
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    for (int i=0; i<5; i++) {   //department
        for (int j=0; j<5; j++) {   //programmer the department wants
            if (departments[i][5] != 0) {   //if the department already has someone skip it
                break;
            }
            if (programmers[departments[i][j]-1][5] != 0) {   //if the programmer is already assigned to a department skip them
                continue;
            }
            for (int k=0; k<5; k++) {   //index in assign[][j]
                if (assign[departments[i][j]-1][k] == 0) {
                    assign[departments[i][j]-1][k] = i+1;    //adds the department i+1 to the programmer row it wants
                    break;
                }
            }
            break;
        }
    }

    for (int i=0; i<5; i++) {   //programmer in dupes
        for (int j=0; j<5; j++) {   //department that the programmer wants
            for (int k=0; k<5; k++) {   //departments that want them
                if (programmers[i][j] == assign[i][k]) {    //if the department the programmer wants is the department that wants them
                    programmers[i][5] = assign[i][k];       //assign them to each other
                    departments[assign[i][k]-1][5] = i+1;
                    break;
                }
            }
            if (programmers[i][5] != 0) {
                break;
            }
        }
    }

    bool finished = true;
    for (int i=0; i<5; i++) {
        if (programmers[i][5] == 0 || departments[i][5] == 0) {
            finished = false;
        }
    }

    if (!finished) {
        rec_assign_programmers(programmers, departments);
    }
}

int main() {
    ifstream infile;
    infile.open("testing-data.txt");

    int departments[5][6];
    int programmers[5][6];

    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            infile >> departments[j][i];
        }
        departments[i][5] = 0;
    }

    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            infile >> programmers[j][i];
        }
        programmers[i][5] = 0;
    }

    infile.close();

    print_array("Programmers", programmers);
    cout << endl;
    print_array("Departments", departments);

    rec_assign_programmers(programmers, departments);

    for (int i=0; i<5; i++) {
        cout << "Department #" << i+1 << " will get Programmer #" << departments[i][5] << endl;
    }

    return 0;
}