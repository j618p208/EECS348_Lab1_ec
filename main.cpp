#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void assign_programmers(int programmers[5][6], int departments[5][6]) {
    for (int l=0; l<5; l++) {   //programmer choice, this for loop encompasses the entire function because 
                                //we are giving priority to 1st choice over 2nd choice over 3rd choice over 4th choice over 5th choice
        int assign[5][5] = {    //rows = programmer
            {0,0,0,0,0},        //columns is the departments that want the programmer
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        };

        for (int i=0; i<5; i++) {   //department
                if (departments[i][5] != 0) {   //if the department already has someone skip it
                    continue;
                }
                if (programmers[departments[i][l]-1][5] != 0) {   //if the programmer is already assigned to a department skip them
                    continue;
                }
                for (int k=0; k<5; k++) {   //index in assign[][j]
                    if (assign[departments[i][l]-1][k] == 0) {
                        assign[departments[i][l]-1][k] = i+1;    //adds the department i+1 to the programmer row it wants
                        break;
                    }
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
                if (programmers[i][5] != 0) {   //if the current programmer has been assigned to a department continue to the next progammer
                    break;
                }
            }
        }
    }
}

int main() {
    cout << "Please input the file name: ";
    string filename;
    cin >> filename;

    ifstream infile;
    infile.open(filename);
    while (!infile) {
        cout << "File not found" << endl;
        cout << "Please input the file name: ";
        cin >> filename;
        infile.open(filename);
    }

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

    assign_programmers(programmers, departments);

    for (int i=0; i<5; i++) {
        cout << "Department #" << i+1 << " will get Programmer #" << departments[i][5] << endl;
    }

    return 0;
}