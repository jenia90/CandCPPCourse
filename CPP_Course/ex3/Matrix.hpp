/**
 * @file Matrix.hpp
 * @author jenia90
 * @version 1.0
 * @date 22 Sep 2016
 *
 * @brief Header file containg the definition of generic Matrix class
 * @section DESCRIPTION:
 * This class represents a Matrix object which supports operations like adding, multiplying and
 * subtracting 2 matrices. Also, it supports getting the transpose of a Matrix, both real and
 * complex numbers.
 * This Matrix object supports both sequential and parallel computation for the addition and
 * multiplication operators.
 */

#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <thread>
#include "Complex.h"

#define CELL_DELIM "\t"
#define DIF_SIZE_ERROR "Cannot perform the operation on matrices of different sizes!"
#define MODE_CHANGE_MSG "Generic Matrix mode changed to"
#define PARALLEL " Parallel "
#define NON_PARALLEL " non-Parallel "
#define MODE "mode"

static bool _isParallel = false;

template <class T>
class Matrix
{
    typedef std::vector<T> Cells;
    size_t _rows, _cols;
    Cells _cells;

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

    /**
     * @brief Template function which applies a given operator method to this matrix and another
     * matrix to update the third matrix
     * @param oper relevant operator method s.a. addition/multiplication
     * @param newMatrix the result matrix object
     * @param matrix other matrix object
     */
    template <typename Func>
    void applyOperator(Func oper, std::reference_wrapper<Matrix<T>> newMatrix,
                            const std::reference_wrapper<const Matrix<T>> matrix) const
    {
        // Check if parallel calculation was enabled
        if(_isParallel)
        {
            // get number of rows and allocate enough threads in the vector
            size_t rows = newMatrix.get()._rows;
            std::vector<std::thread> threads;
            threads.reserve(rows);

            // for each row create a new thread with the given operation on that row
            for (size_t row = 0; row < newMatrix.get()._rows; ++row)
            {
                threads.push_back(std::thread(oper, this, row, newMatrix, matrix));
            }

            // wait for all threads to finish their jobs
            for (std::thread &t : threads)
            {
                t.join();
            }
        }
        else
        {
            // if parallel calculation wasn't enabled, perform the given operation row by row
            for (size_t row = 0; row < _rows; ++row)
            {
                (this->*oper)(row, newMatrix, matrix);
            }
        }
    }

    /**
     * @brief Sums cells in each column of the given row
     * @param row row in which to sum the columns
     * @param newMatrix the result matrix object ref
     * @param matrix other matrix obj ref
     */
    void sumRows(const size_t row, Matrix<T> &newMatrix, const Matrix<T> &matrix) const
    {
        for (size_t c = 0; c < _cols; ++c)
        {
            newMatrix(row, c) = (*this)(row, c) + matrix(row, c);
        }
    }

    /**
     * @brief Multiplies cells in each column of the given row
     * @param row row in which to sum the columns
     * @param newMatrix the result matrix object ref
     * @param matrix other matrix obj ref
     */
    void multRows(size_t row, Matrix<T> &newMatrix, const Matrix<T> &matrix) const
    {
        T sum;
        for (size_t j = 0; j < matrix._cols; ++j)
        {
            sum = 0;
            for (size_t k = 0; k < _cols; ++k)
            {
                sum += (*this)(row, k) * matrix(k, j);
            }
            newMatrix(row, j) = sum;
        }
    }
public:
    typedef typename Cells::const_iterator const_iterator;

    /**
     * @brief Default ctor. Creates a 1x1 Matrix with 0 in its only cell.
     * @return
     */
    Matrix() : _rows(1), _cols(1), _cells(1, T())
    {}

    /**
     * @brief Ctor to init a matrix of size rows x cols with 0 in all its cells
     * @param rows number of rows
     * @param cols number of cols
     * @return
     */
    Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols), _cells(rows * cols, T())
    {}

    /**
     * @brief Ctor to init a matrix of size rows x cols with data contained in the cells vector
     * @param rows number of rows
     * @param cols number of columns
     * @param cells cells data vector
     * @return
     */
    Matrix(size_t rows, size_t cols, const Cells& cells) : _rows(rows), _cols(cols),
                                                                                 _cells(cells)
    {}

    /**
     * @brief copy ctor. copies data from one matrix to the other
     * @param matrix matrix to copy the data from
     * @return
     */
    Matrix(const Matrix<T> &matrix): _rows(matrix._rows), _cols(matrix._cols), _cells(matrix._cells)
    {}

    /**
     * @brief move ctor. moves the data from one matrix to the other
     * @param matrix the matrix to move the data from
     * @return
     */
    Matrix(Matrix<T> &&matrix) : _rows(std::move(matrix._rows)), _cols(std::move(matrix._cols)),
                              _cells(std::move(matrix._cells))
    {}

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
     * @brief Sets the calculation mode of the matrix.
     * @param isParallel true for parallel; false otherwise
     */
    static void setParallel(bool isParallel)
    {
        if(_isParallel != isParallel)
        {
            _isParallel = isParallel;
            std::cout << MODE_CHANGE_MSG; 
            std::cout << (_isParallel ? PARALLEL : NON_PARALLEL) << MODE << std::endl;
        }
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
    Matrix& operator=(const Matrix<T>& matrix)
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
    Matrix operator+(const Matrix<T> &matrix) const
    {
        // if matrices of different sizes, throws an exception
        if(_rows != matrix.rows() || _cols != matrix.cols())
        {
            throw DIF_SIZE_ERROR;
        }

        Matrix<T> m = Matrix(_rows, _cols);
        applyOperator(&Matrix<T>::sumRows, m, std::ref(matrix));

        return m;
    }

    /**
     * @brief Minus operator overload to sum 2 matrices of same size
     * @param matrix Matrix object ref
     * @return new Matrix object which is the difference of 2 matrices
     */
    Matrix operator-(const Matrix<T> &matrix) const
    {
        // if matrices of different sizes, throws an exception
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
    Matrix operator*(const Matrix<T> &matrix) const
    {
        Matrix<T> m = Matrix<T>(_rows, matrix._cols);

        applyOperator(&Matrix::multRows, m, std::ref(matrix));

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