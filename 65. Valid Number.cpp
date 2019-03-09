题目链接：https://leetcode.com/problems/valid-number/description/
非常硬核的一道题。建议不要根据test case来debug。这样面试的时候是过不了关的。

楼主总结了几条规律：
如果s[i]不是数字：
s[i]==’e’ 之前不能出现e，之前必须有数字。并且判断下一个数是否为’+’ or  ‘-‘
s[i]==’.’   .之前不能有. ， 并且 e没有出现（否则为如5e6.5这种形式）
不能出现e以外的字母，也只能有一个e，e之后不能有其他代表表达式了只能是数字，数字之间不能有空格，e的指数不能有小数 只能是整数或者负号+数字 数字签名不能出现双重符号
e后面必须有数字 e前面也必须要有数字 但前面的数字可以是2. 然后接e => "5.e1" true

class Solution {
public:
    bool isNumber(string s) {
        if(s.empty()) return false;
        bool e = false;
        bool digit_before_e = false;
        bool dot = false;
        bool digit_after_e = false;
        bool sign_before_e = false;
        bool sign_after_e = false;
        int i = 0;
        int n = s.size() - 1;
        while(i < n && s[i] == ' '){i++;}
        while(n >= i && s[n] == ' '){n--;}
        while(i <= n){
            if(s[i] == 'e'){
                if(e || !digit_before_e) return false;
                e = true;
            }else if(isdigit(s[i])){
                if(!e){
                    digit_before_e = true;
                }else{
                    digit_after_e = true;
                }
            }else if(s[i] == '.'){
                if(e || dot) return false;
                dot = true;
            }else if(s[i] == '+' || s[i] == '-'){
                if((!e && dot) || (!e && digit_before_e) || (sign_before_e && !e ) || sign_after_e || digit_after_e) return false;
                if(e){
                    sign_after_e = true;
                }else{
                    sign_before_e = true;
                }
            }else{
                return false;
            }
            i++;
        }
        return digit_before_e && (e == digit_after_e);
    }
};
