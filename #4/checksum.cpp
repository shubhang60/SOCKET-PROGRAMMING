  #include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

char binaryToHex(string s){
    if(s == "0000") return '0';
    else if(s == "0001") return '1';
    else if(s == "0010")return '2';
    else if(s == "0011") return'3';
    else if(s == "0100") return '4';
    else if(s == "0101") return '5';
    else if(s == "0110") return '6';
    else if(s == "0111") return '7';
    else if(s == "1000") return '8';
    else if(s == "1001") return '9';
    else if(s == "1010") return 'A';
    else if(s == "1011") return 'B';
    else if(s == "1100") return 'C';
    else if(s == "1101") return 'D';
    else if(s == "1110")return 'E';
    else if(s == "1111") return 'F';
    return '#';
}

string addstrings(string binary[]){
    int n = 5;
    int carry = 0;
    string add = "";
    for(int i=15;i>=0; i--){
        int sum = carry;
        for(int j=0;j<5;j++){
            sum += binary[j][i]-'0'; 
        }
        if( sum < 2) {
            add += char(sum+'0');
            carry = 0;
        }else{
            carry = sum/2;
            sum = sum%2;
            add += char(sum+'0');
        }
    }
    reverse(add.begin(),add.end());
    if(carry){
        bitset<4> b(carry);
        string c = b.to_string();
        carry = 0;
        for(int i=15;i>=12;i--){
            int sum = carry;
            sum += add[i]+'0';
            sum += c[i-12]+'0';
            if(sum < 2){
                add[i] = char(sum+'0');
                carry=0;
            }else{
                carry = sum/2;
                sum = sum%2;
                add[i] = char(sum+'0');
            }
        }
    }
    for(int i=0;i<16;i++){
        if(add[i] == '1') add[i] = '0';
        else add[i] = '1';
    }
    string ans="";
    for(int i=0;i<15;){
        ans += binaryToHex(add.substr(i,4));
        i += 4;
    }
    cout<<"Checksum: 0x"<<ans<<"\n";
    return ans;
}

string hexToBinary(string s){
    // string s = "0xFFFF";
    stringstream ss;
    ss << hex << s;
    unsigned m;
    ss >> m;
    bitset<16> b(m);
    // cout << b.to_string() << endl;
    return b.to_string();
}

string transmitData(string data){
    vector <string> hexdigits(4, "0x");
    for(int i=2,j=0;i<18 && j<4;){
        hexdigits[j++] += data.substr(i,4);
        i += 4;
    }
    string binary[5];
    binary[0] = hexToBinary("0x0");
    for(int i=0;i<4;i++){
        binary[i+1] = hexToBinary(hexdigits[i]);
    }
    string checksum = addstrings(binary);
    return data+checksum;
}

int main() {
    string data = "0x0000F203F4F5F6F7";
    cout<<"Transmitted Data:\n";
    cout<<transmitData(data)<<"\n";
    return 0;
}