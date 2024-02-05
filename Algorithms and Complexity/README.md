# Algorithms and Complexity

Project header:

Give mathematically and logically valid answers to the following problems:
1. Prove that the problem of Winner Determination at Combinatorial Auctions is NP-Complete
   (*Algorithm Design*, Kleinberg & Tardos, ex.8.13).
2. Based on the proof of TSP's NP-Completeness by reduction from the Hamiltonian Cycle Problem
   (as seen in *Algorithm Design* by Kleinberg and Tardos) prove that there cannot exist $\rho$-approximation
   for TSP for any $\rho > 1$ unless P = NP.
4. Formulate the Decision Welfare Maximization Problem and prove that it is NP-Complete. You can use reduction from
   the Partition problem.
6. Give a polynomial time algorithm for deciding a winner in *Geography on a graph* when the graph is DAG 
   (*Algorithm Design*, Kleinberg & Tardos, ex.9.3).
8. Given the *Explore(*$\Phi$*, d)* algorithm, prove that it returns true iff there exists a satisfying assignment for 3-SAT
   $\Phi'$ at distance at most d from $\Phi$. Give its time complexity as a function of n and d. Use this algorithm to solve
   3-SAT at O(p(n)$\sqrt{3}^n$) time (*Algorithm Design*, Kleinberg & Tardos, ex.10.2).
10. Give a 3-approximation algorithm for the Load Balancing problem when the machines are split in k twice-as-fast and m normal ones
   (*Algorithm Design*, Kleinberg & Tardos, ex.11.6).
12. *Assume some good at given quantity* $B \geq 0$*, n buyers, each of which will pay* $b_j \geq 0$ *for every unit of good that's assigned to them.*
   *Find the quantity of good each buyer must be assigned such that the minimum pay among all buyers is maximized.*
   Formulate the above as a LPP and find its dual.
13. Based on the analysis of Christofides' algorithm, why does an Euler walk always exist, and why must |W| be even for a perfect match to exist?
