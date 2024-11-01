#include <iostream>
#include <map>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <fstream>
#include <vector>
using namespace std;

class ALU{
public:
    int to_dec(string s){
        int v;
        stringstream ss;
        ss << hex << s;
        ss >> v;
        return v;
    }
    static string hexToDec(const string& hexStr) {
        int decimalValue;
        stringstream ss;
        ss << hex << hexStr;
        ss >> decimalValue;
        return to_string(decimalValue);
    }
    static string decToHex(int decimalValue) {
        stringstream ss;
        ss << hex << uppercase << decimalValue;
        return ss.str();
    }
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
    string decimalToBinary(double num) {
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
    double binaryToDecimal(const string& binary) {
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
    float hexa_to_float(string n){
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
    string float_to_hexa(float n){
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
};
class Memory{
    int size = 256;
    vector<string> cells = vector<string>(size,"00");
public:
    void setMemoryValue(int ind , string val){
        cells[ind] = val;
    }
    string getMemoryValue(int ind){
        return cells[ind];
    }
    void show(){
        for (auto i : cells) {
            cout << i << endl;
        }
    }
};
class Register{
    int size = 16;
    vector<string> mm = vector<string>(size,"00");
public:
    void setRegisterValue(int ind , string val){
        mm[ind] = val;
    }
    string getRegisterValue(int ind){
        return mm[ind];
    }
    void show(){
        for (auto i : mm) {
            cout << i << endl;
        }
    }
};
class CU {
public:
    void get_instruction(string FN , vector<string>&w){
        ifstream f(FN);
        char ch;string s="";
        while (!f.eof()) {
            f.get(ch);
            if(ch != '\n'){
                s+=ch;
            }
            if (s.length()==4){
                w.push_back(s);
                if(s == "C000"){
                    break;
                }
                s = "";
            }
        }
        f.close();
    }
    void executeInstructions(Register& reg, Memory& mem , int st , vector<string>&instruction , ALU cd , int c) {
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

private:
    void transferRegister(const string& code, Register& reg , ALU cd) {
        string s1, s2;
        s1 = reg.getRegisterValue(cd.to_dec(code.substr(2,1)));
        s2 = reg.getRegisterValue(cd.to_dec(code.substr(3, 1)));
        swap(s1, s2);
        reg.setRegisterValue(cd.to_dec(code.substr(2, 1)), s1);
        reg.setRegisterValue(cd.to_dec(code.substr(3, 1)), s2);
    }

    void addRegisters(const string& code, Register& reg , ALU cd ) {
        string s3 = reg.getRegisterValue(cd.to_dec(code.substr(2, 1))), s4 = reg.getRegisterValue(
                cd.to_dec(code.substr(3, 1)));
        int n = cd.to_dec(s3) + cd.to_dec(s4);
        reg.setRegisterValue(cd.to_dec(code.substr(1, 1)), cd.decToHex(n));
    }

    void addFloatRegisters(const string& code, Register& reg , ALU cd) {
        string s3 = reg.getRegisterValue(cd.to_dec(code.substr(2, 1))), s4 = reg.getRegisterValue(
                cd.to_dec(code.substr(3, 1)));
        float f3 = cd.hexa_to_float(s3) + cd.hexa_to_float(s4);
        reg.setRegisterValue(cd.to_dec(code.substr(1, 1)), cd.float_to_hexa(f3));
    }

    void jumping(string& code, Register& reg , ALU& cd , int& c ) {
        if(reg.getRegisterValue(cd.to_dec(code.substr(1, 1))) == reg.getRegisterValue(0)){
            c = cd.to_dec(code.substr(2));
        }
    }
};

int main() {
    int c = 1;
    int st = 0;
    Register reg;
    Memory mem;
    CU processor;
    ALU cd;
    vector<string>instructions;
    processor.get_instruction("file1.txt" , instructions);
    processor.executeInstructions(reg, mem , st , instructions , cd , c);
    cout << "memory : " << endl;
    mem.show();
    cout << "Register : " << endl;
    reg.show();
    return 0;
}
