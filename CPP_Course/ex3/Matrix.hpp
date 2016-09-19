//
// Created by jenia on 19/09/2016.
//

#include <vector>
#include <algorithm>
#include <sstream>

#define CELL_DELIM "\t"

template <typename T>
class Matrix<>
{
    size_t _rows, _cols;
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
    /**
     * @brief Default ctor. Creates a 1x1 Matrix with 0 in its only cell.
     * @return
     */
    Matrix<>() : _rows(1), _cols(1), _cells(1, 0)
    {
    }

    /**
     * @brief Ctor to init a matrix of size rows x cols with 0 in all its cells
     * @param rows number of rows
     * @param cols number of cols
     * @return
     */
    Matrix<>(size_t rows, size_t cols) : _rows(rows), _cols(cols), _cells(rows * cols, 0)
    {
    }

    /**
     * @brief Ctor to init a matrix of size rows x cols with data contained in the cells vector
     * @param rows number of rows
     * @param cols number of columns
     * @param cells cells data vector
     * @return
     */
    Matrix<>(size_t rows, size_t cols, const std::vector<T>& cells) : _rows(rows), _cols(cols),
                                                                                 _cells(cells)
    {
    }

    /**
     * @brief copy ctor. copies data from one matrix to the other
     * @param matrix matrix to copy the data from
     * @return
     */
    Matrix<>(const Matrix &matrix) : _rows(matrix._rows), _cols(matrix._cols), _cells(matrix._cells)
    {
    }

    /**
     * @brief move ctor. moves the data from one matrix to the other
     * @param matrix the matrix to move the data from
     * @return
     */
    Matrix<>(Matrix &&matrix) : _rows(std::move(matrix._rows)), _cols(std::move(matrix._cols)),
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
        int sum;
        Matrix m = Matrix(_rows, matrix._cols);

        for (size_t i = 0; i < _rows; ++i)
        {
            for (size_t j = 0; j < matrix._cols; ++j)
            {
                sum = 0;
                for (size_t k = 0; k < _cols; ++k)
                {
                    sum += (*this)(i, k) * matrix(k, j);
                }
                m(i, j) = sum;
            }
        }

        return m;
    }

    bool operator==(const Matrix& matrix)
    {
        return isEqual(matrix);
    }

    bool operator!=(const Matrix& matrix)
    {
        return !isEqual(matrix);
    }

    friend std::ostream& operator<<(std::ostream &os, const Matrix& matrix)
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

    T operator()(const unsigned int r, const unsigned int c) const
    {
        return _cells[_cols * r + c];
    }

    T& operator()(const unsigned int r, const unsigned int c)
    {
        return _cells[_cols * r + c];
    }

    T begin()
    {
        return _cells.begin();
    }
    T end()
    {
        return _cells.end();
    }
};