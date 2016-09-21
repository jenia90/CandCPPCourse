//
// Created by jenia on 19/09/2016.
//

#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include "Complex.h"

#define CELL_DELIM "\t"

#define DIF_SIZE_ERROR "Cannot perform the operation on matrices of different sizes!"

template <class T>
class Matrix
{
    size_t _rows, _cols;
    std::vector<T> _cells;

    /**
     * @brief Helper method to check equality of two matrices
     * @param matrix Matrix object ref
     * @return true if all cells are equal; false otherwise
     */
    bool isEqual(const Matrix<T>& matrix)
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
    typedef typename std::vector<T>::const_iterator const_iterator;

    /**
     * @brief Default ctor. Creates a 1x1 Matrix with 0 in its only cell.
     * @return
     */
    Matrix() : _rows(1), _cols(1), _cells(1, T())
    {
    }

    /**
     * @brief Ctor to init a matrix of size rows x cols with 0 in all its cells
     * @param rows number of rows
     * @param cols number of cols
     * @return
     */
    Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols), _cells(rows * cols, T())
    {
    }

    /**
     * @brief Ctor to init a matrix of size rows x cols with data contained in the cells vector
     * @param rows number of rows
     * @param cols number of columns
     * @param cells cells data vector
     * @return
     */
    Matrix(size_t rows, size_t cols, const std::vector<T>& cells) : _rows(rows), _cols(cols),
                                                                                 _cells(cells)
    {
    }

    /**
     * @brief copy ctor. copies data from one matrix to the other
     * @param matrix matrix to copy the data from
     * @return
     */
    Matrix(const Matrix<T> &matrix): _rows(matrix._rows), _cols(matrix._cols), _cells(matrix._cells)
    {
    }

    /**
     * @brief move ctor. moves the data from one matrix to the other
     * @param matrix the matrix to move the data from
     * @return
     */
    Matrix(Matrix<T> &&matrix) : _rows(std::move(matrix._rows)), _cols(std::move(matrix._cols)),
                              _cells(std::move(matrix._cells))
    {
    }

    /**
     * @brief dtor
     */
    ~Matrix()
    {
        _cells.clear();
    }

    /**
     * @brief Checks if this matrix is square (if its row number equal to columns number)
     * @return true if square; false otherwise
     */
    bool isSquareMatrix()
    {
        return _rows == _cols;
    }

    /**
     * @brief Getter for the rows number
     * @return number of rows
     */
    size_t rows() const
    {
        return _rows;
    }

    /**
     * @brief Getter for the columns number
     * @return number of columns
     */
    size_t cols() const
    {
        return _cols;
    }

    /**
     * @brief finds the transpose of the matrix
     * @return transposed Matrix
     */
    Matrix trans()
    {
        Matrix<T> tMatrix = Matrix<T>(_cols, _rows);
        for (size_t r = 0; r < _cols; ++r)
        {
            for (size_t c = 0; c < _rows; ++c)
            {
                tMatrix(r, c) =  (*this)(c, r);
            }
        }

        return tMatrix;
    }

    /**
     * @brief Assignment operator overload
     * @param matrix Matrix object ref
     * @return updated Matrix object
     */
    Matrix&operator=(const Matrix<T>& matrix)
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

    /**
     * @brief Plus operator overload to sum 2 matrices of same size
     * @param matrix Matrix object ref
     * @return new Matrix object which is the sum of 2 matrices
     */
    Matrix operator+(const Matrix<T>& matrix)
    {
        if(_rows != matrix.rows() || _cols != matrix.cols())
        {
            throw DIF_SIZE_ERROR;
        }
        Matrix<T> m = Matrix(_rows, _cols);
        for (int i = 0; i < _cells.size(); ++i)
        {
            m._cells[i] = _cells[i] + matrix._cells[i];
        }

        return m;
    }

    /**
     * @brief Minus operator overload to sum 2 matrices of same size
     * @param matrix Matrix object ref
     * @return new Matrix object which is the difference of 2 matrices
     */
    Matrix operator-(const Matrix<T>& matrix)
    {
        if(_rows != matrix.rows() || _cols != matrix.cols())
        {
            throw DIF_SIZE_ERROR;
        }
        Matrix<T> m = Matrix(_rows, _cols);
        for (int i = 0; i < _cells.size(); ++i)
        {
            m._cells[i] = _cells[i] - matrix._cells[i];
        }

        return m;
    }

    /**
     * @brief Multiplication operator overload to multiply 2 matrices
     * @param matrix Matrix object ref
     * @return new Matrix object which is the multiplication result of 2 matrices
     */
    Matrix operator*(const Matrix<T>& matrix)
    {
        T sum;
        Matrix<T> m = Matrix<T>(_rows, matrix._cols);

        for (size_t i = 0; i < _rows; ++i)
        {
            for (size_t j = 0; j < matrix._cols; ++j)
            {
                sum = 0;
                for (size_t k = 0; k < _cols; ++k)
                {
                    sum = sum + (*this)(i, k) * matrix(k, j);
                }
                m(i, j) = sum;
            }
        }

        return m;
    }

    /**
     * @brief Equality operator overload to check if 2 matrices are equal
     * @param matrix Matrix object ref
     * @return true if equal; false otherwise
     */
    bool operator==(const Matrix<T>& matrix)
    {
        return isEqual(matrix);
    }

    /**
     * @brief Non-equality operator overload to check if 2 matrices are not equal
     * @param matrix Matrix object ref
     * @return true if not equal; false otherwise
     */
    bool operator!=(const Matrix<T>& matrix)
    {
        return !isEqual(matrix);
    }

    /**
     * Out stream operator overload to get a stream representation of the matrix
     * @param os Ostream object ref
     * @param matrix Matrix object ref
     * @return updated stream of the Matrix's cells
     */
    friend std::ostream& operator<<(std::ostream &os, const Matrix<T>& matrix)
    {
        for (size_t r = 0; r < matrix._rows; ++r)
        {
            for (size_t c = 0; c < matrix._cols; ++c)
            {
                os << matrix(r, c) << CELL_DELIM;
            }
            os << std::endl;
        }

        return os;
    }

    /**
     * @brief Direct a access operator given a row and column returns the data stored in that cell
     * @param r Row number
     * @param c Column number
     * @return value stored in the requested cell
     */
    T operator()(const size_t r, const size_t c) const
    {
        return _cells[_cols * r + c];
    }

    /**
     * @brief Direct a access operator. Given a row and column returns the reference to the data
     * stored in that cell
     * @param r Row number
     * @param c Column number
     * @return reference to the data stored in the requested cell
     */
    T& operator()(const size_t r, const size_t c)
    {
        return _cells[_cols * r + c];
    }

    /**
     * @brief Const iterator begin function.
     * @return Const iterator begin
     */
    const_iterator begin()
    {
        return _cells.begin();
    }

    /**
     * @brief Const iterator end function.
     * @return Const iterator end
     */
    const_iterator end()
    {
        return _cells.end();
    }
};

/**
 * @brief Specialization of the transpose method for the case where the matrix is filled with
 * Complex values
 * @return transposed Matrix object
 */
template <>
Matrix<Complex> Matrix<Complex>::trans()
{
    Matrix<Complex> tMatrix = Matrix<Complex>(_cols, _rows);
    for (size_t r = 0; r < _cols; ++r)
    {
        for (size_t c = 0; c < _rows; ++c)
        {
            tMatrix(r, c) = _cells[_cols * c + r].conj();
        }
    }

    return tMatrix;
}