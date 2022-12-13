/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Caroline LaVersa
 * Version     : 1.0
 * Date        :
 * Description : Implements fast multiplication Karatsuba method
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <unordered_map>

using namespace std;
string add(const string& a, const string& b){
    int m = max(a.size(), b.size()); // max of sizes
    string tempa = string(m-a.size(), '0') + a; // prepend max-size 0s 
    string tempb = string(m-b.size(), '0') + b; // prepend max-size 0s 
    string sum = ""; //accumulate sum bit by bit
    int carry =0;
    for(int i = tempa.size()-1; i>=0; i--){ // runs through whole length of a and b
        int bitsum = (tempa[i] - '0')+ (tempb[i]-'0')+carry; // add a[i], b[i], carry
        string bit = to_string(bitsum); // int to string
        if(bit.size()>1){ //more than 1 digit
            carry = bitsum/10; // carry bit
            bitsum%=10; // remainder is what want to add to sum
        }
        else{
            carry = 0; // resets carry bit 
        }
        sum = to_string(bitsum)+sum; // adds ith bits of a and b and puts into sum
    }
    sum = to_string(carry) + sum;
    size_t i = 0;
    while(i<sum.size()-1 && sum[i]=='0'){
        i++;
    }
    return sum.substr(i);
}
string subtract(const string& a, const string& b){
    int m = max(a.size(), b.size()); // max of sizes
    string tempa = string(m-a.size(), '0') + a; // prepend max-size 0s 
    string tempb = string(m-b.size(), '0') + b; // prepend max-size 0s
    string difference = ""; //accumulate difference bit by bit
    int borrow = 0;
    for(int i = tempa.size()-1; i>=0; i--){ // runs through whole length of a and b
        int bitdiff = (tempa[i] - '0') - (tempb[i]-'0') + borrow; // sub a[i], b[i], and borrow (-1 if borrowed in previous, else 0)
        if(bitdiff<0){ //if difference is negative
            bitdiff += 10; //add 10
            borrow = -1; // subtracts 1 next time to compensate borrow
        }
        else{
            borrow = 0; // reset borrow if no borrow took place
        }
        difference = to_string(bitdiff)+difference; // adds ith bits of a and b and puts into sum
    }
    size_t i = 0;
    while(i<difference.size()-1 && difference[i]=='0'){
        i++;
    }
    return difference.substr(i); 
}

unordered_map<string,string> thing = {}; // dictionary for key value strings
//multiplies integers, returns as string
string multiply(const string& a, const string& b){ 
    //memoize 
    string tempa = a; // temporary string for a
    string tempb = b; // temporary string for b
    if(tempa.size()>1||tempb.size()>1){
        if(a.size()>b.size()){ // a longer than b
            tempb= string(a.size()-b.size(), '0') + b; //pad 0s to b
        }
        else if (a.size()<b.size()){ // b longer than a 
            tempa = string(b.size()-a.size(), '0') +a; // pad 0s to a
        }
        if((tempa.size()%2)!=0){ //not even num digits
            tempa = '0' +tempa;
            tempb = '0' +tempb;
        }
        //now tempa and tempb are even and the same length
        string thingthing = tempa +"x"+ tempb; // make string to test for in dictionary
        if(thing.find(thingthing)!=thing.end()){ // if in dictionary
            return thing[thingthing]; // return value
        }
        thingthing = tempb +"x"+ tempa; // make string to test for in dictionary (commutative)
        if(thing.find(thingthing)!=thing.end()){ // if in dictionary
            return thing[thingthing]; // return value
        }
        int siz = tempa.size();
        string a1 = tempa.substr(0, (siz/2)); // a1 is first half of a
        string a0 = tempa.substr(siz/2, siz/2); // a0 is second half of a
        string b1 = tempb.substr(0, (siz/2)); // b1 is first half of b
        string b0 = tempb.substr(siz/2, (siz/2)); // b0 is second half of b
        string c0 = multiply(a0, b0); // a0*b0
        string c1 = multiply(add(a1, a0), add(b1, b0)); // (a1+a0)*(b1+b0)
        string c2 = multiply(a1, b1); // a1*b1
        string first = c2; // store original value of c2
        first+=string(siz, '0'); // c2*B^n
        string second = subtract(subtract(c1, c2), c0); // c1-c2-c0
        second+= string(siz/2, '0'); // (c1-c2-c0)*B^n/2
        string fourth = add(first, second); // c2*B^n + (c1-c2-c0)*B^n/2
        string fifth = add(fourth, c0); // c2*B^n + (c1-c2-c0)*B^n/2 +c0
        thing[thingthing] = fifth; // add to dictionary
        return fifth; // a*b expression using my methods
    }

    //general single digit multiplication method
    int a1 = a[0] - '0'; // convert to int
    int b1 = b[0] - '0'; // convert to int
    int prod = a1*b1; // multiply
    string ans = to_string(prod); // convert to string
    return ans;
}


int main(int argc, char *argv[]) {
    cout<<multiply(argv[1],argv[2]) << '\n'; // implement fast multiplication on two arguments
    return 0;
}