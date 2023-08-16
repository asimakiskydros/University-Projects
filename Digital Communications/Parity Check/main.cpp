#include <iostream>
#include <vector>

using std::string, std::vector, std::pair;
//done like this for clarity:
using matrix = vector<vector<char>>;
using pairs  = vector<pair<int, int>>;

bool noise_channel(string&, const vector<int>&);
bool noise_channel(matrix&, const pairs&);
bool even_parity_check(string&);
void even_parity_check(matrix&);
void scan_for_flaws(string, const vector<int>&);
void scan_for_flaws(matrix, const pairs&);
void print_matrix(const matrix&);

/**
 * Data given in the project pronunciation:
 * ex1: 10001101011000
 * ex3: 1100111101110101110010101001
 */
/**
     * Parity Check:
     * A simple way to determine whether a received signal is corrupted or not.
     * Arbitrarily decide that an even or odd amount of '1' bits means that the signal is correct.
     * Then, based on what decision was made, check all the '1' in the given signal.
     *
     * Even Parity Check:
     * Given signal holds even amount of '1': signal transmitted without flaws (ideally).
     * Else flaw detected.
     *
     * Odd Parity Check:
     * Invert the above logic.
     *
     * Note that this method isn't very safe or reliable, but it is very simple and cost-effective.
*/
/**
    * 2D-Parity Check:
    * Break apart a big signal into smaller ones and with those create a matrix.
    * Run the desired parity check on the result signals that correspond to the rows and columns of said matrix.
    * The parity bit is added to the end of each row and column, respectively.
    * This method is more powerful than the 1D version, as flaws are now more likely to be detected,
    * either by the corresponding row or column parity bit.
    *
    * It should be noted that even amounts of errors occurring in both rows and columns can eliminate
    * each other, rendering the corruption undetectable.
*/

int main() {
    string signal;
    std::cout << "Exercise 1:\n->Give signal:\n";
    std::cin >> signal;
    if (even_parity_check(signal))
        std::cout << "Signal is correct\n";
    else
        std::cout << "Signal incorrect, corrected: " << signal << "\n";

    std::cout << "\nExercise 2:" << std::endl;
    scan_for_flaws(signal, {});
    scan_for_flaws(signal, {5});
    //undetectable error
    scan_for_flaws(signal, {5, 11});

    signal.clear();
    std::cout << "\nExercise 3:\n->Give signal:\n";
    std::cin >> signal;
    matrix mtrx = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
    };
    for(int i = 0, k = 0; i < 4; i++) for(int j = 0; j < 7; j++)
        mtrx[i][j] = signal[k++];
    even_parity_check(mtrx);
    print_matrix(mtrx);

    std::cout << "\nExercise 4:\n";
    scan_for_flaws(mtrx, {});
    scan_for_flaws(mtrx, {{1, 2}});
    scan_for_flaws(mtrx, {{1, 2}, {1, 4}});
    //undetectable error
    scan_for_flaws(mtrx, {{1, 2}, {1, 4}, {2, 2}, {2, 4}});

    return 0;
}
bool noise_channel(string &signal, const vector<int> &positions){
    for(int index : positions) //scan for out of bounds
        if (index < 0 || index >= (int)signal.size())
            return false;
    for(int index : positions) //flip corresponding bits
        signal[index] = signal[index] == '0' ? '1' : '0';
    return true;
}
bool even_parity_check(string &signal){
    int ones = 0;
    for(char bit : signal) if (bit == '1') ones++;
    signal += ones % 2 == 0 ? '0' : '1';
    return signal[signal.size() - 1] != '1';
}
void scan_for_flaws(string signal, const vector<int> &positions){
    if(noise_channel(signal, positions) &&
       even_parity_check(signal))
         std::cout << "DATA ACCEPTED\n";
    else std::cout << "DATA REJECTED\n";
}
void scan_for_flaws(matrix mtrx, const pairs &positions){
    //no point if positions held wrong inputs
    if(!noise_channel(mtrx, positions)) return;
    //check rows:
    for(auto &row : mtrx){
        string temp;
        for(char bit : row) temp += bit;
        if (!even_parity_check(temp)) {
            std::cout << "DATA REJECTED\n";
            return;
        }
    }
    //check columns:
    for(int i = 0, width = (int)mtrx[0].size(); i < width; i++){
        string temp;
        for(auto &row : mtrx) temp += row[i];
        if (!even_parity_check(temp)){
            std::cout << "DATA REJECTED\n";
            return;
        }
    }
    //if this point is reached, the matrix is presumed correct
    std::cout << "DATA ACCEPTED\n";
}
bool noise_channel(matrix &mtrx, const pairs &positions){
    //scan for out of bounds
    for(const auto &[x, y] : positions)
        if(x < 0 ||  y < 0  ||
           x >= mtrx.size() || y >= mtrx[0].size())
            return false;
    //flip corresponding bits
    for(const auto &[x, y] : positions)
        mtrx[x][y] = mtrx[x][y] == '0' ? '1' : '0';
    return true;
}
void even_parity_check(matrix &mtrx){
    //check rows and add appropriate parity bit in each one
    for(auto &row : mtrx){
        string temp;
        for(char bit : row) temp += bit;
        row[mtrx[0].size() - 1] = even_parity_check(temp) ? '0' : '1';
    }
    //do the same for each column
    for(int i = 0, width = (int)mtrx[0].size(); i < width; i++){
        string temp;
        for(auto &row : mtrx) temp += row[i];
        mtrx[mtrx.size() - 1][i] = even_parity_check(temp) ? '0' : '1';
    }
}
void print_matrix(const matrix &mtrx){
    for(const auto &row : mtrx){
        for(const auto &bit : row)
            std::cout << bit << " ";
        std::cout << "\n";
    }
}



