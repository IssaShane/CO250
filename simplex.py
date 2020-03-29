## aux returns the initial solution to the auxiliary LP to the LP described by 
##   obj, constraints, and b
## Efficiency: O(n^2)
## aux: vec, listof -> vec
def aux(constraints, b):
    new_constraints = []
    for i in range(0, len(constraints)):
        row = []
        for j in range(0, len(constraints[0])):
            row.append(constraints[i][j])
        new_constraints.append(row)
            
    ## get the size of the identity matrix to be appended to constraints
    identity_size = len(b)
    j = 0
    for i in range(0, identity_size):
        for k in range(0, j):
            new_constraints[k].append(0)
        
        new_constraints[i].append(1)
        for t in range(j, identity_size):
            new_constraints[t].append(0)
        j += 1

    x = []
    for i in range(0, len(constraints[0])):
        x.append(0)
    for i in range(0, len(b)):
        x.append(b[i])

    return x

## canonicalize alters constraints, obj, and obj_const to be in canonical form
##   for basis
## requirements: constraints is a valid nxm matrix
##               basis is a valid vector in R(n)
##               obj is a valid vector in R(n)
##               obj_const is a valid int const
## canonicalize: vec, matrix, vec, int -> None
def canonicalize(basis, constraints, obj, obj_const):
    ## TODO: Write this bitch
