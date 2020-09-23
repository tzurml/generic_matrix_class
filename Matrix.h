// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;
} MatrixDims;

// Insert Matrix class here...

/**
 * class that represent matrix as represented in linear algebra 2
 */
class Matrix
{

private:
    MatrixDims *dims;
    /**
     * represent the matrix data
     */
    float *myMat;
public:
    /**
     * Constructs Matrix rows × cols
     * Inits all elements to 0
     */
    Matrix(int rows, int cols);

    /**
     * Constructs 1×1 Matrix
     * Inits the single element to 0
     */
    Matrix();

    /**
     * copy ctor
     * @param m - matrix to copy
     */
    Matrix(const Matrix &m);
    /**
     * destructor - free resources
     */
    ~Matrix();

    /**
     * get num of rows
     */
    int getRows() const;

    /**
    * get num of cols
    */
    int getCols() const;

    /**
     * Prints matrix elements, no return value.
     * prints space after each element (incl. last
     * element in the row)
     * prints newline after each row (incl. last row)
     */
    void plainPrint() const;

    /**
     * Transforms a matrix into a col vector
     * Supports function calling concatenation
     */
    Matrix &vectorize();

    /**
     * override = , put matrix into matrix.
     */
    Matrix &operator=(const Matrix &other);

    /**
     * override * , double 2 matrix as learned in algebra linear
     */
    Matrix operator*(const Matrix &other) const;

    /**
     * override * , every elem in matrix is multiply by c.
     */
    Matrix operator*(const float c) const;
    /**
     * override * , every elem in matrix is multiply by c.
     */
    friend Matrix operator*(const float left, const Matrix &right);

    /**
     * override + , add 2 matrix as learned in algebra linear
     * retrun matrix
     */
    Matrix operator+(const Matrix &other) const;
    /**
     * override + , add 2 matrix as learned in algebra linear
     * retrurn the cur matrix after add
     */
    Matrix &operator+=(const Matrix &other);

    /**
     * override () return the i,j elem in matrix
     */
    float &operator()(int row, int col);

    /**
     * override () return the i,j elem in matrix
     * return & to a float
     */
    const float &operator()(int row, int col) const;

    /**
     * override [] return the i elem in matrix
     * return & to a float
     */
    float &operator[](int i);

    /**
     * override [] return the i elem in matrix
     */
    float operator[](int i) const;

    /**
     *
     * prints matrix into the stream as defined at the instruction
     */
    friend std::ostream &operator<<(std::ostream &out, const Matrix &c);

    /**
     *
     * load values into matrix from a stream
     */
    friend std::istream &operator>>(std::istream &in, Matrix &c);

};


#endif //MATRIX_H
