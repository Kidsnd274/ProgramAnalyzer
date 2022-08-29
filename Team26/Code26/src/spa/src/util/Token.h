#include <string>

class Token {
private:
    std::string tokenString;
public:
    Token(std::string s) {
        tokenString = s;
    }
    static Token createTerminal(std::string s);
    static Token createNonTerminal(std::string s);
    static Token createConstToken(std::string s);
};