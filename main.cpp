/**
  * @brief Programa principal
  * @file main.cpp
  * @name main
  * @version 1.0
  * @author Carlos Enrique Duarte Ortiz
  * @code
    #include "sudoku.h"
    #include <iostream>
    #include <fstream>

    using namespace std;

    int main() {
        ifstream fin("/users/cedo/desktop/top95.txt");
        string linea;
        Sudoku::inicializa();
        Sudoku *S1 = nullptr;
        Sudoku *S2 = nullptr;
        while (getline(fin, linea)) {
            S2 = new Sudoku(linea);
            S1 = sudoku_soluciona(S2);
            if (S1 == nullptr) {
                cerr << "Error" << endl;
                return 1;
            }
            S1->escribe(cout);
            cout << endl << endl;
            delete S1;
        }
        fin.close();
        return 0;
    }
  * @endcode
  */

#include "DuSudoku.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("./top95.txt");
    string linea;
    DuSudoku::inicializa();
    DuSudoku *S1 = nullptr;
    DuSudoku *S2 = nullptr;
    while (getline(fin, linea)) {
        S2 = new DuSudoku(linea);
        S1 = sudoku_soluciona(S2);
        if (S1 == nullptr) {
            cerr << "Error" << endl;
            return 1;
        }
        S1->escribe(cout);
        cout << endl << endl;
        delete S1;
    }
    fin.close();
    return 0;
}
