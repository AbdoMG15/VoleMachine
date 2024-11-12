//
// Created by dell on 11/4/2024.
//

#include "vole.h"
#include <iostream>
#include <map>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <fstream>
#include <vector>
using namespace std;
int ALU :: to_dec(string s){
    int v;
    stringstream ss;
    ss << hex << s;
    ss >> v;
    return v;
}
string ALU :: hexToDec(const string& hexStr) {
    int decimalValue;
    stringstream ss;
    ss << hex << hexStr;
    ss >> decimalValue;
    return to_string(decimalValue);
}
string ALU :: decToHex(int decimalValue) {
    stringstream ss;
    ss << hex << uppercase << decimalValue;
    return ss.str();
}
string ALU :: decimalToBinary(double num) {
    int integerPart = static_cast<int>(num);
    double fractionalPart = num - integerPart;
    string integerBinary = "";
    if (integerPart == 0) {
        integerBinary = "0";
    } else {
        while (integerPart > 0) {
            integerBinary = std::to_string(integerPart % 2) + integerBinary;
            integerPart /= 2;
        }
    }
    string fractionalBinary = ".";
    int precision = 10; // Limit the fractional part to 10 binary places
    while (fractionalPart > 0 && precision > 0) {
        fractionalPart *= 2;
        int bit = static_cast<int>(fractionalPart);
        fractionalBinary += std::to_string(bit);
        fractionalPart -= bit;
        precision--;
    }
    return integerBinary + fractionalBinary;
}
double ALU :: binaryToDecimal(const string& binary) {
    size_t pointPos = binary.find('.');
    double decimalValue = 0.0;
    int power = (pointPos == std::string::npos) ? binary.size() - 1 : pointPos - 1;
    for (size_t i = 0; i < (pointPos == std::string::npos ? binary.size() : pointPos); i++) {
        if (binary[i] == '1') {
            decimalValue += pow(2, power);
        }
        power--;
    }
    if (pointPos != std::string::npos) {
        power = -1;
        for (size_t i = pointPos + 1; i < binary.size(); i++) {
            if (binary[i] == '1') {
                decimalValue += pow(2, power);
            }
            power--;
        }
    }
    return decimalValue;
}
float ALU :: hexa_to_float(string n){
    int sign = 1;
    if(n[0]-'0' > 7){
        sign = -1;
    }
    int dec1 = 0 , counter = 0;
    string f = hexToBinMap[n[0]];
    dec1 = binToDecMap[f.substr(1,3)] - '0';
    dec1-=4;
    string floating ;
    floating=hexToBinMap[n[1]];
    if(dec1 > 0){
        floating = floating.substr(0,dec1) + "." + floating.substr(dec1) ;
    }
    else if(dec1 < 0){
        floating = "0." + string(abs(dec1),'0') + floating ;
    }
    return sign * binaryToDecimal(floating);
}
string ALU :: float_to_hexa(float n){
    string binary;
    int counter = 0 , temp;
    float mantissa ;
    binary = decimalToBinary(abs(n));
    if(stod(binary) < 1){
        for(auto i = 2 ; i < binary.length();i++){
            if(binary[i]!='0'){
                break;
            }
            else{
                counter+=1;
            }
            if(counter == 4){
                break;
            }
        }
        temp = -counter ;
        binary = "0." + binary.substr(2+counter);
    }
    else{
        for(auto i = 0 ; i < binary.length();i++){
            if(binary[i]=='.'){
                break;
            }
            counter+=1;
        }
        temp = counter;
        while(counter > 0){
            swap(binary[counter],binary[counter-1]);
            counter-=1;
        }
        binary = "0" + binary ;
    }
    mantissa = stof(binary);
    temp+=4;
    binary = decimalToBinary(temp);
    if(binary[binary.length()-1] == '.'){
        binary.pop_back();
    }
    while(binary.length()<3){
        binary = "0"+binary;
    }
    if(n < 0){
        binary = "1" + binary;
    }
    else{
        binary = "0" + binary;
    }
    string res = "";
    res+=binToHexMap[binary.substr(0,4)];
    res+=binToHexMap[to_string(mantissa).substr(2,4)];
    return res;
}
void Memory:: setMemoryValue(int ind, string val) {
    cells[ind] = val;
}

string Memory:: getMemoryValue(int ind) {
    return cells[ind];
}

void Memory:: show() {
    cout << "Memory Contents:" << endl;

    // Display header with hexadecimal addresses for columns
    cout << "   ";
    for (int i = 0; i < 16; ++i) {
        cout << "  " << hex << uppercase << i;
    }
    cout << endl;
    for (int row = 0; row < 16; ++row) {
        cout << hex << uppercase << ((row)) << " |";
        for (int col = 0; col < 16; ++col) {
            int index = row * 16 + col;
            cout << " " << hex << uppercase << cells[index];
        }
        cout << endl;
    }
}
void Register :: setRegisterValue(int ind, string val) {
    mm[ind] = val;
}

string Register :: getRegisterValue(int ind) {
    return mm[ind];
}

void Register :: show() {
    cout << "Register Contents:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "Register " << hex << toupper(i) << ": " << mm[i] << endl;
    }
}
void CU :: get_instruction(string FN , vector<string>&w){
    std::ifstream f(FN);
    char ch;
    std::string s = "";
    bool foundC000 = false; // To check if "C000" is found

    while (f.get(ch)) {
        ch = std::toupper(ch); // Convert character to uppercase
        if (ch != '\n') {
            s += ch;
        }
        if (s.length() == 4) {
            w.push_back(s);
            if (s == "C000") {
                foundC000 = true;
                break;
            }
            s = "";
        }
    }
    f.close();
    if (!foundC000) {
        w.push_back("C000");
    }
}
void CU :: executeInstructions(Register& reg, Memory& mem , int st , vector<string>&instruction , ALU cd , int c) {
    string code = instruction[st] ;
    while (code != "C000" && c < 256 ){
        string currentInstruction = code;
        char operation_code = currentInstruction[0];
        switch (operation_code) {
            case '1':
                reg.setRegisterValue(cd.to_dec(code.substr(1,1)),mem.getMemoryValue(cd.to_dec(code.substr(2,2))));
                break;
            case '2':
                reg.setRegisterValue(cd.to_dec(code.substr(1,1)),code.substr(2,2));
                break;
            case '3':
                mem.setMemoryValue(cd.to_dec(code.substr(2,2)),reg.getRegisterValue(cd.to_dec(code.substr(1,1))));
                break;
            case '4':
                transferRegister(code , reg , cd);
                break;
            case '5':
                addRegisters(code , reg ,cd);
                break;
            case '6':
                addFloatRegisters(code , reg , cd);
                break;
            case 'B':
                jumping(code , reg , cd , c);
                break;
            case '7':
                or_opreation(code , reg ,cd);
                break;
            case '8':
                and_opreation(code , reg ,cd);
                break;
            case '9':
                xor_opreation(code , reg ,cd);
                break;
            case 'A':
                rotate( code,  reg,  cd);
                break;
            case 'D':
                jumping_D(code , reg , cd , c);
                break;
            default:
                cout << "";
        }
        mem.setMemoryValue(c,code.substr(0,2));
        c+=1;
        mem.setMemoryValue(c,code.substr(2));
        c+=1;
        st+=1;
        code = instruction[st] ;
    }
}
void CU :: transferRegister(const string& code, Register& reg , ALU cd) {
    string s1, s2;
    s1 = reg.getRegisterValue(cd.to_dec(code.substr(2,1)));
    s2 = reg.getRegisterValue(cd.to_dec(code.substr(3, 1)));
    swap(s1, s2);
    reg.setRegisterValue(cd.to_dec(code.substr(2, 1)), s1);
    reg.setRegisterValue(cd.to_dec(code.substr(3, 1)), s2);
}

void CU :: addRegisters(const string& code, Register& reg, ALU cd) {
    string s3 = reg.getRegisterValue(cd.to_dec(code.substr(2, 1)));
    string s4 = reg.getRegisterValue(cd.to_dec(code.substr(3, 1)));
    int n1 = cd.to_dec(s3);
    int n2 = cd.to_dec(s4);
    if (n1 > 127)
    {
        n1 -= 256;
    }
    if (n2 > 127)
    {
        n2 -= 256;
    }
    int result = n1 + n2;
    if (result > 127) {
        result -= 256;
    }
    else if (result < -128) {
        result += 256;
    }
    reg.setRegisterValue(cd.to_dec(code.substr(1, 1)), cd.decToHex(result));
}


void CU :: addFloatRegisters(const string& code, Register& reg , ALU cd) {
    string s3 = reg.getRegisterValue(cd.to_dec(code.substr(2, 1)));
    string s4 = reg.getRegisterValue(cd.to_dec(code.substr(3, 1)));
    float f3 = cd.hexa_to_float(s3) + cd.hexa_to_float(s4);
    reg.setRegisterValue(cd.to_dec(code.substr(1, 1)), cd.float_to_hexa(f3));
}

void CU :: jumping(string& code, Register& reg , ALU& cd , int& c ) {
    if(reg.getRegisterValue(cd.to_dec(code.substr(1, 1))) == reg.getRegisterValue(0)){
        c = cd.to_dec(code.substr(2));
    }
}
void CU :: xor_opreation(const string& code, Register& reg , ALU cd ) {
    string s3 = reg.getRegisterValue(cd.to_dec(code.substr(2, 1)));
    string s4 = reg.getRegisterValue(cd.to_dec(code.substr(3, 1)));
    int n = (cd.to_dec(s3) ^ cd.to_dec(s4));
    reg.setRegisterValue(cd.to_dec(code.substr(1, 1)), cd.decToHex(n));
}
void CU :: or_opreation(const string& code, Register& reg , ALU cd ) {
    string s3 = reg.getRegisterValue(cd.to_dec(code.substr(2, 1)));
    string s4 = reg.getRegisterValue(cd.to_dec(code.substr(3, 1)));
    int n = (cd.to_dec(s3) | cd.to_dec(s4));
    reg.setRegisterValue(cd.to_dec(code.substr(1, 1)), cd.decToHex(n));
}
void CU :: and_opreation(const string& code, Register& reg , ALU cd ) {
    string s3 = reg.getRegisterValue(cd.to_dec(code.substr(2, 1)));
    string s4 = reg.getRegisterValue(cd.to_dec(code.substr(3, 1)));
    int n = (cd.to_dec(s3) & cd.to_dec(s4));
    reg.setRegisterValue(cd.to_dec(code.substr(1, 1)), cd.decToHex(n));
}
void CU :: jumping_D(string& code, Register& reg , ALU& cd , int& c) {
    if(reg.getRegisterValue(cd.to_dec(code.substr(1, 1))) > reg.getRegisterValue(0)){
        c = cd.to_dec(code.substr(2));
    }

}
void CU :: rotate(const string& code, Register& reg, ALU cd) {
    int steps = cd.to_dec(code.substr(2, 1)); // Assuming the number of steps is in the second position
    int regIndex = cd.to_dec(code.substr(1, 1)); // The register to rotate is indicated in the first position
    string regValue = reg.getRegisterValue(regIndex);
    int val = cd.to_dec(regValue);
    int result = (val >> steps) | (val << (8 - steps)) & 0xFF;
    reg.setRegisterValue(regIndex, cd.decToHex(result));

}