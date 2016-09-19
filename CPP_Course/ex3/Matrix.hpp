//
// Created by jenia on 19/09/2016.
//

#include <vector>
#include <algorithm>
#include <sstream>

#define CELL_DELIM "\t"

template <typename T>
class Matrix
{
    unsigned int _rows, _cols;
    std::vector<T> _cells;

    /**
     * @brief Helper method to check equality of two matrices
     * @param matrix Matrix object ref
     * @return true if all cells are equal; false otherwise
     */
    bool isEqual(const Matrix & matrix)
    {
        if(matrix.cols() != _cols || matrix.rows() != _rows)
        {
            return false;
        }

        for (size_t i = 0; i < _cells.size(); ++i)
        {
            if(_cells[i] != matrix._cells[i])
            {
                return false;
            }
        }
        return true;
    }
public:
    Matrix() : _rows(1), _cols(1), _cells(0)
    {
    }
    Matrix(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols)
    {
    }

    Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells) : _rows(rows),
                                                                                _cols(cols),
                                                                                _cells(cells)
    {
    }

    Matrix(Matrix&& matrix) : _rows(std::move(matrix._rows)), _cols(std::move(matrix._cols)),
                              _cells(std::move(matrix._cells))
    {
    }



    ~Matrix()
    {
        _cells.clear();
    }

    bool isSquareMatrix()
    {
        return _rows == _cols;
    }

    unsigned int rows() const
    {
        return _rows;
    }

    unsigned int cols() const
    {
        return _cols;
    }

    Matrix&operator=(const Matrix & matrix)
    {
        if(this != &matrix)
        {
            _rows = matrix.rows();
            _cols = matrix.cols();
            _cells.clear();
            _cells = matrix._cells;
        }
        return *this;
    }

    Matrix operator+(const Matrix& matrix)
    {
        if(_rows != matrix.rows() || _cols != matrix.cols())
        {
            // TODO: exception
        }
        Matrix m = Matrix(_rows, _cols);
        for (int i = 0; i < _cells.size(); ++i)
        {
            m._cells[i] = _cells[i] + matrix._cells[i];
        }

        return m;
    }

    Matrix operator-(const Matrix& matrix)
    {
        if(_rows != matrix.rows() || _cols != matrix.cols())
        {
            // TODO: exception
        }
        Matrix m = Matrix(_rows, _cols);
        for (int i = 0; i < _cells.size(); ++i)
        {
            m._cells[i] = _cells[i] - matrix._cells[i];
        }

        return m;
    }

    Matrix operator*(const Matrix& matrix)
    {
        //TODO: Implement
    }

    bool operator==(const Matrix& matrix)
    {
        return isEqual(matrix);
    }

    bool operator!=(const Matrix& matrix)
    {
        return !isEqual(matrix);
    }

    std::ostream& operator<<(std::ostream &os, const Matrix& matrix)
    {
        for (size_t r = 0; r < _rows; ++r)
        {
            for (size_t c = 0; c < _cols; ++c)
            {
                os << (*this)(r, c) << CELL_DELIM;
            }
            os << std::endl;
        }

        return os;
    }

    T operator()(const unsigned int r, const unsigned int c) const
    {
        return _cells[_cols * r + c];
    }

    T& operator()(const unsigned int r, const unsigned int c)
    {
        return _cells[_cols * r + c];
    }

    T begind()
    {
        return _cells.begin();
    }
    T end()
    {
        return _cells.end();
    }
};