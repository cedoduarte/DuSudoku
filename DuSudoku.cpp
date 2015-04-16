#include "DuSudoku.h"
#include <cassert>

using namespace std;

/**
 * @brief The Posibles class
 */
class Posibles
{
public:
    /**
     * @brief Posibles
     */
    Posibles() : _b(9, true)
    {
        // constructor
    }

    /**
     * @brief Posibles
     * @param otro
     */
    Posibles(const Posibles &otro) : _b(otro._b)
    {
        // constructor de copia
    }

    /**
     * @brief activo
     * @param v
     * @return true/false
     */
    bool activo(int v) const
    {
        return _b[v - 1];
    }

    /**
     * @brief elimina
     * @param v
     */
    void elimina(int v)
    {
        _b[v - 1] = false;
    }

    /**
     * @brief str
     * @param ancho
     * @return string
     */
    string str(int ancho) const;

    /**
     * @brief num_activos
     * @return cantidad de activos
     */
    int num_activos() const
    {
        return count(_b.begin(), _b.end(), true);
    }

    /**
     * @brief val
     * @return valor
     */
    int val() const
    {
        vector<bool>::const_iterator i;
        i = find(_b.begin(), _b.end(), true);
        return 1 + (i - _b.begin());
    }
private:
    vector<bool> _b;
};

string Posibles::str(int ancho) const
{
    int i, j = 0;
    string s(ancho, ' ');
    for (i = 1; i <= 9; ++i) {
        if (activo(i)) {
            s[j] = ('0' + i);
            ++j;
        }
    }
    return s;
}

Grupo DuSudoku::_grupos(27);
Grupo DuSudoku::_grupos_de(81);
Grupo DuSudoku::_vecinos(81);

void DuSudoku::inicializa()
{
    int i, j, k, x;
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j) {
            const int ka = (i * 9) + j;
            const int gpos[3] = {
                i, 9 + j, 18 + ((i / 3) * 3) + (j / 3)
            };
            for (x = 0; x < 3; ++x) {
                _grupos[gpos[x]].push_back(ka);
                _grupos_de[ka].push_back(gpos[x]);
            }
        }
    }
    for (k = 0; k < 81; ++k) {
        for (x = 0; x < 3; ++x) {
            for (i = 0; i < 9; ++i) {
                if (_grupos[_grupos_de[k][x]][i] != k) {
                    _vecinos[k].push_back(_grupos[_grupos_de[k][x]][i]);
                }
            }
        }
    }
}

DuSudoku::DuSudoku(const string &str) : _celdas(81)
{
    unsigned i, k = 0;
    for (i = 0; i < 81; ++i) {
        _celdas[i] = new Posibles;
    }
    const unsigned tam = str.size();
    for (i = 0; i < tam; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            if (!asigna(k, str[i] - '0')) {
                cerr << "Error en el sudoku de entrada" << endl;
            }
            ++k;
        } else if (str[i] == '0' || str[i] == '.') {
            ++k;
        }
    }
    assert(k == 81);
}

DuSudoku::DuSudoku(const DuSudoku &otro) : _celdas(81)
{
    for (int i = 0; i < 81; ++i) {
        _celdas[i] = new Posibles(*otro._celdas[i]);
    }
}

DuSudoku::~DuSudoku()
{
    for (int i = 0; i < 81; ++i) {
        delete _celdas[i];
    }
}

bool DuSudoku::resuelto() const
{
    const unsigned tam = _celdas.size();
    for (unsigned k = 0; k < tam; ++k) {
        if (_celdas[k]->num_activos() != 1) {
            return false;
        }
    }
    return true;
}

bool DuSudoku::asigna(int k, int val)
{
    for (int i = 1; i <= 9; ++i) {
        if (i != val) {
            if (!elimina(k, i)) {
                return false;
            }
        }
    }
    return true;
}

bool DuSudoku::elimina(int k, int val)
{
    if (!_celdas[k]->activo(val)) {
        return true;
    }
    unsigned i, n, x, k2, kp;
    _celdas[k]->elimina(val);
    const int nactivos = _celdas[k]->num_activos();
    if (nactivos == 0) {
        return false;
    } else if (nactivos == 1) {
        const unsigned tam = _vecinos[k].size();
        for (i = 0; i < tam; ++i) {
            kp = _vecinos[k][i];
            if (!elimina(kp, _celdas[k]->val())) {
                return false;
            }
        }
    }
    for (x = 0; x < 3; ++x) {
        n = 0;
        for (i = 0; i < 9; ++i) {
            kp = _grupos[_grupos_de[k][x]][i];
            if (_celdas[kp]->activo(val)) {
                ++n;
                k2 = kp;
            }
        }
        if (n == 0) {
            return false;
        } else if (n == 1) {
            if (!asigna(k2, val)) {
                return false;
            }
        }
    }
    return true;
}

void DuSudoku::escribe(ostream &out) const
{
    unsigned i, j, k;
    int ancho = 2;
    const unsigned tam = _celdas.size();
    for (k = 0; k < tam; ++k) {
        ancho = max(ancho, 1 + _celdas[k]->num_activos());
    }
    const string sep(3 * ancho, '-');
    for (i = 0; i < 9; ++i) {
        if (i == 3 || i == 6) {
            out << sep << "+-" << sep << "+-" << sep << endl;
        }
        for (j = 0; j < 9; ++j) {
            if (j == 3 || j == 6) {
                out << "| ";
            }
            out << _celdas[(9 * i) + j]->str(ancho);
        }
        out << endl;
    }
}

int DuSudoku::menos_posibilidades() const
{
    unsigned k;
    int min, kmin = -1;
    const unsigned tam = _celdas.size();
    for (k = 0; k < tam; ++k) {
        const int np = _celdas[k]->num_activos();
        if (np > 1) {
            if (kmin == -1 || np < min) {
                min = np;
                kmin = k;
            }
        }
    }
    return kmin;
}

Posibles *DuSudoku::posibles(int k) const
{
    return _celdas[k];
}

DuSudoku *sudoku_soluciona(DuSudoku *S)
{
    if (S == nullptr || S->resuelto()) {
        return S;
    }
    DuSudoku *S2 = nullptr, *S3 = nullptr;
    const int k = S->menos_posibilidades();
    for (int i = 1; i <= 9; ++i) {
        if (S->posibles(k)->activo(i)) {
            S2 = new DuSudoku(*S);
            if (S2->asigna(k, i)) {
                S3 = sudoku_soluciona(S2);
                if (S3 != nullptr) {
                    if (S3 != S2) {
                        delete S2;
                    }
                    return S3;
                }
            }
            delete S2;
        }
    }
    return nullptr;
}
