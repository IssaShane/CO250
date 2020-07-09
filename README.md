Hello!

This project is intended as a command-line tool for automating calculations involving fractional
arithmetic, matrix-vector operations, and the Simplex algorithm. At the moment, this project is split
into three separate executables, LibVec for fractional arithmetic and matrix-vector arithmetic, 
Linear for solving linear systems, and Simplex for operations using the simplex method

About Input: 

When giving a vector as input, list all values in order, separated only by spaces, and ending with
a semicolon. When giving a matrix as input, give each row as a vector in order from top to bottom of
the matrix, encased in [].

LibVec Commands:

 - quit/q : ends the process
 - transpose [matrix] : gives the transpose of a matrix
 - matrixmult [A] [B] : multiplies AxB, and prints the result
 - vecmult [A] [v] : multiplies the matrix A by the vector v
 - subset [A] [b] : gives the matrix composed of the columns of the matrix A, given by the entries of
    the vector b, starting at 0; b must be given in ascending order
 - swaprows [A] [i] [j] : swaps the rows i and j in the matrix A, where rows begin at the top of A, 
    starting at 0
 - inverse [A] : gives the inverse of the matrix A
 - innerproduct [v1] [v2] : returns the standard inner product of the vectors v1 and v2
 - multfrac [f1] [f2] : gives the product of the fractions f1 and f2
 - addfrac [f1] [f2] : gives the sum of the fractions f1 and f2
 - divfrac [f1] [f2] : gives the quotient of the fraction f1 by the fraction f2
 - subfrac [f1] [f2] : gives the difference of the fraction f1 from the fraction f2
 - fracequal [f1] [f2] : returns true iff f1 == f2, and false otherwise
 - fracsimplify [f] : returns the simplified fractional version of the fraction f
 
LinearSys Commands:

 - quit/q : ends the process
 - upper [A] : gives the upper triangular matrix of the matrix A
 - lower [A] : gives the lower triangular matrix of the matrix A
 - solve [A] [b] : returns the solution x to the system Ax=b
 - inverse [A] : returns the inverse to the matrix A
 - forwardsub [v] [A] : solves the system Ax=v via forward substitution where A is lower triangular
 - backwardsub [v] [A] : solves the system Ax=v via backward substitution where A is upper triangular

Simplex Commands: 

 - quit/q : ends the process
 - canonicalize [A][b][obj][obj_const][basis] : returns the canonical form of the LP 
    {max x(obj)+obj_const : Ax=b} with the basis basis
 - aux [A][b][obj][obj_const][basis] : gives the auxiliary LP of the LP {max x*obj+obj_const : Ax=b}
    with the basis basis
 - canonform [A][b][obj][obj_const][basis] : returns true iff the given LP is in canonical form
 - solve [A][b][obj][obj_const][basis] : solves the LP
