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
using namespace std;
#define ll long long
#ifndef UNTITLED2_VOLE_H
#define UNTITLED2_VOLE_H
class ALU{
public:
    int to_dec(string s);
    static string hexToDec(const string& hexStr) ;
    static string decToHex(int decimalValue) ;
    unordered_map<char, string> hexToBinMap = {
            {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
            {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
            {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
            {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
    };
    unordered_map<string, char> binToHexMap = {
            {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
            {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
            {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
            {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}
    };
    unordered_map<char, string> decToBinMap = {
            {'0', "000"}, {'1', "001"}, {'2', "010"}, {'3', "011"},
            {'4', "100"}, {'5', "101"}, {'6', "110"}, {'7', "111"},
    };
    unordered_map<string, char> binToDecMap = {
            {"000", '0'}, {"001", '1'}, {"010", '2'}, {"011", '3'},
            {"100", '4'}, {"101", '5'}, {"110", '6'}, {"111", '7'},
    };
    string decimalToBinary(double num) ;
    double binaryToDecimal(const string& binary) ;
    float hexa_to_float(string n);
    string float_to_hexa(float n);
};
class Memory {
    vector<string> cells = vector<string>(256, "00");
public:
    void setMemoryValue(int ind, string val) ;
    string getMemoryValue(int ind) ;
    void show() ;
};
class Register {
    int size = 16;
    vector<string> mm = vector<string>(size, "00");
public:
    void setRegisterValue(int ind, string val) ;
    string getRegisterValue(int ind) ;
    void show() ;
};
class CU {
public:
    void get_instruction(string FN , vector<string>&w);
    void executeInstructions(Register& reg, Memory& mem , int st , vector<string>&instruction , ALU cd , int c) ;
private:
    void transferRegister(const string& code, Register& reg , ALU cd) ;
    void addRegisters(const string& code, Register& reg, ALU cd) ;
    void addFloatRegisters(const string& code, Register& reg , ALU cd) ;
    void jumping(string& code, Register& reg , ALU& cd , int& c ) ;
    void xor_opreation(const string& code, Register& reg , ALU cd ) ;
    void or_opreation(const string& code, Register& reg , ALU cd ) ;
    void and_opreation(const string& code, Register& reg , ALU cd ) ;
    void jumping_D(string& code, Register& reg , ALU& cd , int& c) ;
    void rotate(const string& code, Register& reg, ALU cd) ;
};
#endif //UNTITLED2_VOLE_H
