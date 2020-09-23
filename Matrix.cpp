//
// Created by tzurml on 16/12/2019.
//
#include "Matrix.h"

#define MATRIX_SIZE_ERR "ERROR: invalid operation, error in matrix size."
#define MATRIX_MEM_ERR "ERROR: problem with memory"
#define STREAM_ERR "ERROR: failed in using stream."


/**
 * Constructs Matrix rows & cols Inits all elements to 0
 */
Matrix::Matrix(int rows, int cols)
{
    if (rows <= 0 || cols <= 0 )
    {
        std::cerr << MATRIX_SIZE_ERR << std::endl;
        exit(EXIT_FAILURE);
    }

    dims = new MatrixDims;
    if (dims == nullptr)
    {
        std::cerr << MATRIX_MEM_ERR << std::endl;
        exit(EXIT_FAILURE);
    }

    dims->cols = cols;
    dims->rows = rows;
    myMat = new float[rows * cols];
    if (myMat == nullptr)
    {
        std::cerr << MATRIX_MEM_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows * cols; i++)
    {
        myMat[i] = 0;
    }
}

Matrix::Matrix()
    : Matrix(1, 1)
{}

Matrix::Matrix(const Matrix &m)
    : Matrix(m.getRows(), m.getCols())
{
    for (int i = 0; i < (m.getRows() * m.getCols()); i++)
    {
        myMat[i] = m.myMat[i];
    }
}

Matrix::~Matrix()
{
    delete[] myMat;
    delete dims;

}

int Matrix::getRows() const
{
    return dims->rows;
}

int Matrix::getCols() const
{
    return dims->cols;
}

void Matrix::plainPrint() const
{
    int counterRow = 0;
    for (int i = 0; i < (dims->rows * dims->cols); i++)
    {
        counterRow++;
        std::cout << myMat[i] << " ";
        if (counterRow == dims->cols)
        {
            std::cout << std::endl;
            counterRow = 0;
        }
    }
}

Matrix &Matrix::vectorize()
{
    int x = dims->cols * dims->rows;
    dims->cols = 1;
    dims->rows = x;
    return *this;
}

Matrix &Matrix::operator=(const Matrix &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete[] myMat;
    dims->rows = other.dims->rows;
    dims->cols = other.dims->cols;
    myMat = new float[dims->rows * dims->cols];
    if (myMat == nullptr)
    {
        std::cerr << MATRIX_MEM_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < (dims->rows * dims->cols); i++)
    {
        myMat[i] = other.myMat[i];
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (dims->cols != other.getRows())
    {
        std::cerr << MATRIX_SIZE_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix result(this->getRows(), other.getCols());
    float sum;
    for (int i = 0; i < this->getRows(); i++)
    {
        for (int j = 0; j < other.getCols(); j++)
        {
            sum = 0.0f;
            for (int k = 0; k < this->getCols(); k++)
            {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

Matrix Matrix::operator*(const float c) const
{
    Matrix temp = Matrix(*this);
    for (int i = 0; i < dims->rows * dims->cols; ++i)
    {
        temp.myMat[i] = myMat[i] * c;
    }
    return temp;
}

Matrix operator*(const float left, const Matrix &right)
{
    if (right.dims->rows <= 0 || right.dims->cols <= 0)
    {
        std::cerr << MATRIX_SIZE_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    return right * left;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (dims->cols != other.getCols() || dims->rows != other.getRows())
    {
        std::cerr << MATRIX_SIZE_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix ret(dims->rows, dims->cols);
    for (int i = 0; i < dims->rows * dims->cols; ++i)
    {
        ret.myMat[i] = myMat[i] + other.myMat[i];
    }
    return ret;
}
Matrix &Matrix::operator+=(const Matrix &other)
{
    if (dims->cols != other.getCols() || dims->rows != other.getRows())
    {
        std::cerr << MATRIX_SIZE_ERR << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dims->rows * dims->cols; ++i)
    {
        myMat[i] = myMat[i] + other.myMat[i];
    }
    return *this;
}

float &Matrix::operator()(const int row, const int col)
{
    if ( row >= dims->rows || col >= dims->cols || row < 0 || col < 0)
    {
        std::cerr << MATRIX_SIZE_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    return (myMat[dims->cols * row + col]);
}
float &Matrix::operator[](int i)
{
    if ( i >= dims->cols*dims->rows || i < 0)
    {
        std::cerr << MATRIX_SIZE_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    return myMat[i];
}

float Matrix::operator[](int i) const
{
    if ( i >= dims->cols*dims->rows || i < 0)
    {
        std::cerr << MATRIX_SIZE_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    return myMat[i];
}

const float &Matrix::operator()(const int row, const int col) const
{
    if ( row >= dims->rows || col >= dims->cols || row < 0 || col < 0)
    {
        std::cerr << MATRIX_SIZE_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    return (myMat[dims->cols * row + col]);
}

std::ostream &operator<<(std::ostream &out, const Matrix &c)
{
    if (!out.good())
    {
        std::cerr << STREAM_ERR << std::endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < c.dims->rows; ++i)
    {
        for (int j = 0; j < c.dims->cols; ++j)
        {
            if (c(i, j) - 0.1f <= 0)
            {
                out << "  ";
            }
            else
            {
                out << "**";
            }

        }
        out << std::endl;
    }
    return out;
}

    std::istream &operator>>(std::istream &in, Matrix &c)
    {
        for (int i = 0; i < c.getCols() * c.getRows(); ++i)
        {
            if (!in.good())
            {
                std::cerr << STREAM_ERR << std::endl;
                exit(EXIT_FAILURE);
            }
            in.read((char *) &c[i], sizeof(float));
        }
        if(in.eof())
        {
            std::cerr << STREAM_ERR << std::endl;
            exit(EXIT_FAILURE);
        }
        return in;
    }



