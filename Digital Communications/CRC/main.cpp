#include <iostream>
#include <random>
#include <ctime>
#define TESTS 1000000000

using std::string;

string add_xor(const string&,const string&);
string division_mod2(const string&,const string&);
string noise_channel(string, double, std::mt19937&);

int main() {
    int alterations = 0, detections = 0, k;
    unsigned long long p;
    double BER;
    string P;

    std::cout << "Give k, P, BER:\n";
    std::cin >> k >> p >> BER;
    P = std::to_string(p); //done like this to avoid '\n' related complications
    std::cout << "Wait...\n";

    std::mt19937 engine(time(nullptr) + 1);
    std::uniform_int_distribution<int> uid(0, 1);

    for(int i = 0, length = (int)P.length(); i < TESTS; i++){
        string D;
        //generate random D
        for(int j = 0; j < k; j++) D += std::to_string(uid(engine));
        //shift left by n - k == len(P) - 1
        for(int j = 1; j < length; j++) D += '0';
        //create T as instructed
        string T = add_xor(D, division_mod2(D, P));
        string dirty_T = noise_channel(T, BER, engine);
        if (T != dirty_T){ //if altered
            alterations++;
            if (division_mod2(dirty_T, P) != "0") detections++;
        }
    }
    //DP: detections percentage, AP: alterations percentage (normalized in [0, 1])
    double DP = (double)detections / alterations, AP = (double)alterations / TESTS;
    std::cout << "Results from " <<    TESTS    <<    " random cases:\n"
              << "   -> Signals altered: "      << AP*100       << "%\n"
              << "   -> Alterations detected: " << DP*100       << "%\n"
              << "   -> Alterations missed: "   << (1 - DP)*100 << "%\n";
    return 0;
}
string add_xor(const string &bigger, const string &smaller){
    int difference = (int)bigger.length() - (int)smaller.length(), i = 0;
    //make sure the bigger parameter is first
    if (difference < 0) return add_xor(smaller, bigger);

    string sum;
    for(char bit : bigger)
        //bigger signal's starting bits will not participate in the addition
        if(difference-- > 0) sum += bit;
        else sum += (bit == smaller[i++]) ? '0' : '1';
    return sum;
}
string division_mod2(const string &dividend, const string &divisor){
    int length = (int)divisor.length(), end = length;
    string remainder;

    for(char bit: dividend)
        if (length-- > 0) remainder += bit; //remainder initialization
        else{
            //perform addition only if remainder is normalized
            if (remainder.front() != '0')
                remainder = add_xor(remainder, divisor);
            for(int i = 1; i < end; i++) //shift left by one
                remainder[i - 1] = remainder[i];
            remainder[end - 1] = bit; //add the next bit of dividend
        }
    for(char bit : remainder) if (bit != '0') return remainder;
    //if remainder describes decimal zero, return only 0
    return "0";
}
string noise_channel(string clean_string, double bit_error_rate, std::mt19937 &engine){
    std::uniform_real_distribution<double> urd(0, 1);

    for(char &bit : clean_string) if (urd(engine) < bit_error_rate) //flip bits with bit_error_rate odds
        bit = (bit == '0') ? '1' : '0';
    return clean_string;
}