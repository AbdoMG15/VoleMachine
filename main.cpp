#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <vector>
#include <numeric>
#include <climits>
#include <bitset>
#include <cmath>
#include <utility>
#include <chrono>
#include <unordered_map>
#include "vole.h"
#include "vole.cpp"
using namespace std;
#define ll long long
//class ALU{
//public:
//    unordered_map<char, string> hexToBinMap = {
//            {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
//            {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
//            {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
//            {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
//    };
//    unordered_map<string, char> binToHexMap = {
//            {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
//            {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
//            {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
//            {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}
//    };
//    unordered_map<char, string> decToBinMap = {
//            {'0', "000"}, {'1', "001"}, {'2', "010"}, {'3', "011"},
//            {'4', "100"}, {'5', "101"}, {'6', "110"}, {'7', "111"},
//    };
//    unordered_map<string, char> binToDecMap = {
//            {"000", '0'}, {"001", '1'}, {"010", '2'}, {"011", '3'},
//            {"100", '4'}, {"101", '5'}, {"110", '6'}, {"111", '7'},
//    };
//    string decimalToBinary(double num) {
//        // Separate the integer and fractional parts
//        int integerPart = static_cast<int>(num);
//        double fractionalPart = num - integerPart;
//
//        // Convert the integer part to binary
//        std::string integerBinary = "";
//        if (integerPart == 0) {
//            integerBinary = "0";
//        } else {
//            while (integerPart > 0) {
//                integerBinary = std::to_string(integerPart % 2) + integerBinary;
//                integerPart /= 2;
//            }
//        }
//
//        // Convert the fractional part to binary
//        string fractionalBinary = ".";
//        int precision = 10; // Limit the fractional part to 10 binary places
//        while (fractionalPart > 0 && precision > 0) {
//            fractionalPart *= 2;
//            int bit = static_cast<int>(fractionalPart);
//            fractionalBinary += std::to_string(bit);
//            fractionalPart -= bit;
//            precision--;
//        }
//
//        return integerBinary + fractionalBinary;
//    }
//    double binaryToDecimal(const string& binary) {
//        size_t pointPos = binary.find('.');
//        double decimalValue = 0.0;
//
//        // Convert integer part
//        int power = (pointPos == std::string::npos) ? binary.size() - 1 : pointPos - 1;
//        for (size_t i = 0; i < (pointPos == std::string::npos ? binary.size() : pointPos); i++) {
//            if (binary[i] == '1') {
//                decimalValue += pow(2, power);
//            }
//            power--;
//        }
//
//        // Convert fractional part
//        if (pointPos != std::string::npos) {
//            power = -1;
//            for (size_t i = pointPos + 1; i < binary.size(); i++) {
//                if (binary[i] == '1') {
//                    decimalValue += pow(2, power);
//                }
//                power--;
//            }
//        }
//
//        return decimalValue;
//    }
//    float hexa_to_float(string n){
//        int sign = 1;
//        if(n[0]-'0' > 7){
//            sign = -1;
//        }
//        int dec1 = 0 , counter = 0;
//        string f = hexToBinMap[n[0]];
//        dec1 = binToDecMap[f.substr(1,3)] - '0';
//        dec1-=4;
//        string floating ;
//        floating=hexToBinMap[n[1]];
//        if(dec1 > 0){
//            floating = floating.substr(0,dec1) + "." + floating.substr(dec1) ;
//        }
//        else if(dec1 < 0){
//            floating = "0." + string(abs(dec1),'0') + floating ;
//        }
//        return sign * binaryToDecimal(floating);
//    }
//    string float_to_hexa(float n){
//        string binary;
//        int counter = 0 , temp;
//        float mantissa ;
//        binary = decimalToBinary(abs(n));
//        if(stod(binary) < 1){
//            for(auto i = 2 ; i < binary.length();i++){
//                if(binary[i]!='0'){
//                    break;
//                }
//                else{
//                    counter+=1;
//                }
//                if(counter == 4){
//                    break;
//                }
//            }
//            temp = -counter ;
//            binary = "0." + binary.substr(2+counter);
//        }
//        else{
//            for(auto i = 0 ; i < binary.length();i++){
//                if(binary[i]=='.'){
//                    break;
//                }
//                counter+=1;
//            }
//            temp = counter;
//            while(counter > 0){
//                swap(binary[counter],binary[counter-1]);
//                counter-=1;
//            }
//            binary = "0" + binary ;
//        }
//        mantissa = stof(binary);
//        temp+=4;
//        binary = decimalToBinary(temp);
//        if(binary[binary.length()-1] == '.'){
//            binary.pop_back();
//        }
//        while(binary.length()<3){
//            binary = "0"+binary;
//        }
//        if(n < 0){
//            binary = "1" + binary;
//        }
//        else{
//            binary = "0" + binary;
//        }
//        string res = "";
//        res+=binToHexMap[binary.substr(0,4)];
//        res+=binToHexMap[to_string(mantissa).substr(2,4)];
//        return res;
//    }
//};
//class Memory{
//    int size = 258;
//    vector<string> cells = vector<string>(size,"00");
//public:
//    void setcell(int ind , string val){
//        cells[ind] = val;
//    }
//    string getcell(int ind){
//        return cells[ind];
//    }
//    void show() {
//        cout << "Memory Contents:" << endl;
//        cout << "   ";
//        for (int i = 0; i < 16; ++i) {
//            cout << "  " << hex << uppercase << i;
//        }
//        cout << endl;
//        for (int row = 0; row < 16; ++row) {
//            cout << hex << uppercase << ((row)) << " |";
//            for (int col = 0; col < 16; ++col) {
//                int index = row * 16 + col;
//                cout << " " << hex << uppercase << cells[index];
//            }
//            cout << endl;
//        }
//    }
//
//};
//class Register{
//    int size = 16;
//    vector<string> mm = vector<string>(size,"00");
//public:
//    void setreg(int ind , string val){
//        mm[ind] = val;
//    }
//    string getcell(int ind){
//        return mm[ind];
//    }
//    void show() {
//        cout << "Register Contents:" << endl;
//        for (int i = 0; i < size; ++i) {
//            cout << "Register " << hex << toupper(i) << ": " << mm[i] << endl;
//        }
//    }
//};
//void read_file(string FN , vector<string>&w){
//    ifstream f(FN);
//    char ch;string s="";
//    while (!f.eof()) {
//        f.get(ch);
//        if(ch != '\n'){
//            s+=ch;
//        }
//        if (s.length()==4){
//            w.push_back(s);
//            if(s == "C000"){
//                break;
//            }
//            s = "";
//        }
//    }
//    f.close();
//}
//int to_dec(string s){
//    int v;
//    stringstream ss;
//    ss << hex << s;
//    ss >> v;
//    return v;
//}
int main(){
    int c = 1 , st = 0;
    vector<string>bay;
    Memory m1;
    ALU fun;
    Register r1;
    CU div;
    string code;
    div.get_instruction("codes.txt",bay);
    div.executeInstructions(r1,m1,0,bay,fun,0);
    cout << "memory : " << endl;
    m1.show();
    cout << "Register : " << endl;
    r1.show();
}
