#include <string>
#include <vector>

class Token {
private:
    std::string tokenString;
public:
    static Token createTerminal(std::string s);
    static Token createNonTerminal(std::string s);
};