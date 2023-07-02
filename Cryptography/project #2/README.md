# Project 2: Public Key Cryptography

project headers:

1. Implement the Diffie-Hellman protocol using $g = 3, p = 101, a = 77, b = 91$ in code.
2. Implement the modular exponentiation algorithm and use it to find $5^{77}\text{ mod }19$.
3. Prove that the inequality $p_n < 2^{2^n}$ holds for the n-th prime $p_n$.
4. Let $a, b \in \mathbb{N} \ni gcd(a, b) = 1.$ Prove that:
    - $gcd(ac, b) = gcd(c, b) \forall c\in\mathbb{Z}$.
    - $gcd(a + b, a - b)\in\{1,2\} \text{ and if } a, b \text{ odd then that it's exactly }2$.
    - $gcd(2^a - 1, 2^b - 1) = 1$.
    - $gcd(M_p, M_q) = 1, text{ where } p, q \text{ Mersenne primes }(p\not=q)$.
5. Let $a, b, c \in \mathbb{Z} \text{ and } \delta = a^2 - 4bc^2 \not= 0$. Prove that $gcd(\delta, 4c^2)$ is a perfect square.
6. Verify experimentally that the inequality $\frac{\sigma(n)}{n} < \frac{e^{\gamma}}{2}ln(ln(n)) + \frac{0.74}{ln(ln(n))}$ holds for all odd integers $< 2^{20}$, where $\gamma$ the Euler constant.
7. Prove that the given integers are Carmichael numbers and attempt to find a larger one.
8. Examine whether the given integer pair satisfies the Fermat test.
9. Implement the trial division algorithm and use it to factorize $2^{62} - 1, 2^{102} - 1$.
10. Implement Lehman's factorization algorithm. Test it as follows: assume success if the algorithm completes the factorization of an 100-bit integer in 10 seconds or less. Give the success ratio for 1000 iterations of this test.
11. Use Pollard's algorithm in combination with Floyd's algorithm to factorize $2^{257} - 1$. Assume $F(X) = (X^2 + 1) \text{ mod }N$ and check $1 < gcd(|X - Y|, N) < N$.
12. Given the RSA public key $(N, e) = (11413, 19)$, decrypt the given message with brute force.
13. Decrypt the given message that was encrypted with the given RSA public key and then encoded in Base64. Implement the Wiener attack to find $d$.
14. Let $(N, e) = (899, 839)$ be the key of a naive RSA digital signature. Examine whether the signature is valid, if the signing of message $m = 3$ is $s = 301$.
15. Send an encrypted message to 0xEB1185F82713D6DF (the professor) using GPG.

*Original headers can be found in the PDF along with the task solutions. Courtesy of Aristotle University of Thessalonica, CSD.*
