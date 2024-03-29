# Numerical Analysis - Project #1

Project header\*:

Complete the following tasks in C++ or Python:

1. Given the function $f(x) = 14xe^{x-2} - 12e^{x-2} - 7x^3 + 20x^2 - 26x + 12, x \in [0, 3]$
   provide its graph and approximate its roots using the standard bisection method,
   the Newton-Raphson method and the secant method.
2. Given the function $f(x) = 54x^6 + 45x^5 - 102x^4 - 69x^3 + 35x^2 + 16x - 4, x \in [-2, 2]$
   provide its graph and approximate its roots using a randomized version of the bisection method,
   the Newton-Raphson method that uses the following algorithm: $x_{n+1} = x_n - (\frac{f'(x_n)}{f(x_n)} - \frac{f''(x_n)}{2f'(x_n)})^{-1}$
   and the variant of the secant method that is shown in the header\*.
3. Compare the above variants based on the results they return. 
4. Given these two matrices $A_{n\times n} = \lbrace 5 \text{ if } i=j, -2 \text{ if } |i-j|=1, 0 \text{ otherwise}\rbrace$, $B_{n\times 1} = \lbrace 3, 1, 1, ..., 1, 3\rbrace$,
   perform Gauss, Gauss-Seidel on them and Cholesky on A, after making sure A satisfies the appropriate conditions.
5. Given the adjacency table found in the header\*, and assuming jump probability $q = 0.15$:
      1. Build the Google matrix and prove it is stochastic
      2. Find the eigenvector of the Google matrix using the power method
      3. Compare the probabilites of the user jumping to page 14 before and after increasing traffic to it by removing
         one of its connections and adding another 4. Do that however you like. 
      4. Find the eigenvectors of the Google matrix, again using the power method, but assuming new jump probabilities
         $q = 0.02$ and $q = 0.6$. Comparing these 3 vectors, decide how a q metric can describe a specific user in the real world. 
      5. Increase the values $(8, 11)$ and $(12, 11)$ of the adjacency table to 3. Comment on the impact this change had on the
         eigenvalue of page 11.
      6. Delete node 10 from the adjacency table and rebuild the Google matrix. Comment on the impact this change had on the
         eigenvalues of the pages that pointed on page 10 and those that were pointed to by page 10.
      
*\*I've lost the original header. Project courtesy of Aristotle University of Thessalonica, CSD.*
