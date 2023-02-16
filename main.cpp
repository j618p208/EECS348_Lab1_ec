#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void print_array(string header, int array[5][5]) {
    for (int i=0; i<5; i++) {
        cout << header << " " << i+1 << ": ";
        for (int j=0; j<5; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    ifstream infile;
    infile.open("matching-data.txt");

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

    int temp_assign[5] = {0, 0, 0, 0, 0};   //Programmer i+1 will go to department temp_assign[i]

    int dupes[5][5] = { //rows = programmer
        {0,0,0,0,0},    //columns is the departments that want the programmer
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    for (int i=0; i<5; i++) {   //department
        for (int j=0; j<5; j++) {   //index in dupes[][j]
            if (dupes[departments[i][0]-1][j] == 0) {
                dupes[departments[i][0]-1][j] = i+1;    //adds the department i+1 to the programmer row it wants
                break;
            }
        }
    }

    print_array("Programmer", dupes);

    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            if (dupes[i][j] == 0) {
                if (j == 1) {
                    temp_assign[i] = dupes[i][0];
                }
                break;
            }
        }
    }

    for (int i=0; i<5; i++) {
        cout << temp_assign[i] << " ";
    }

    return 0;
}