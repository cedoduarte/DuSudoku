#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <iostream>
#include <algorithm>

class Posibles;

/**
 * @brief Grupo
 */
using Grupo = std::vector<std::vector<int>>;

/**
 * @brief The Sudoku class
 */
class DuSudoku
{
public:
    /**
     * @brief inicializa
     */
    static void inicializa();

    /**
     * @brief Sudoku
     * @param str
     */
    DuSudoku(const std::string &str);

    /**
     * @brief Sudoku
     * @param otro
     */
    DuSudoku(const DuSudoku &otro);

    /**
      * @brief Destructor
      */
    ~DuSudoku();

    /**
     * @brief resuelto
     * @return true/false
     */
    bool resuelto() const;

    /**
     * @brief asigna
     * @param k
     * @param val
     * @return true/false
     */
    bool asigna(int k, int val);

    /**
     * @brief elimina
     * @param k
     * @param val
     * @return true/false
     */
    bool elimina(int k, int val);

    /**
     * @brief escribe
     * @param o
     */
    void escribe(std::ostream &o) const;

    /**
     * @brief menos_posibilidades
     * @return cantidad de posibilidades
     */
    int menos_posibilidades() const;

    /**
     * @brief posibles
     * @param k
     * @return Posibles valores
     */
    Posibles *posibles(int k) const;
private:
    std::vector<Posibles *> _celdas;
    static Grupo _grupos;
    static Grupo _grupos_de;
    static Grupo _vecinos;
};

/**
 * @brief sudoku_soluciona
 * @param S
 * @return Sudoku
 */
DuSudoku *sudoku_soluciona(DuSudoku *S = nullptr);

#endif // SUDOKU_H
