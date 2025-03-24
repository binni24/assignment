#include <iostream>
#include <vector>
#include <string>
#include <cctype>


enum TokenType {
    NUM,       
    PLUS,      
    MULTIPLY,  
    LPAREN,    
    RPAREN,    
    EOF_TOKEN  
};


struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value = "") : type(type), value(value) {}
};


class Tokenizer {
public:
    Tokenizer(const std::string &input) : input(input), pos(0) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;

        while (pos < input.length()) {
            char current = input[pos];

            if (std::isspace(current)) {
                pos++;  
                continue;
            } else if (std::isdigit(current)) {
                tokens.push_back(Token(NUM, readNumber()));
            } else if (current == '+') {
                tokens.push_back(Token(PLUS, "+"));
                pos++;
            } else if (current == '*') {
                tokens.push_back(Token(MULTIPLY, "*"));
                pos++;
            } else if (current == '(') {
                tokens.push_back(Token(LPAREN, "("));
                pos++;
            } else if (current == ')') {
                tokens.push_back(Token(RPAREN, ")"));
                pos++;
            } else {
                std::cerr << "Unexpected character: " << current << "\n";
                exit(1);
            }
        }

        tokens.push_back(Token(EOF_TOKEN));  
        return tokens;
    }

private:
    std::string input;
    size_t pos;

    
    std::string readNumber() {
        std::string num;
        while (pos < input.length() && std::isdigit(input[pos])) {
            num += input[pos];
            pos++;
        }
        return num;
    }
};


void printTokens(const std::vector<Token> &tokens) {
    for (const auto &token : tokens) {
        if (token.type == NUM) std::cout << "NUM(" << token.value << ")\n";
        else if (token.type == PLUS) std::cout << "PLUS(+)\n";
        else if (token.type == MULTIPLY) std::cout << "MULTIPLY(*)\n";
        else if (token.type == LPAREN) std::cout << "LPAREN(()\n";
        else if (token.type == RPAREN) std::cout << "RPAREN())\n";
        else if (token.type == EOF_TOKEN) std::cout << "EOF\n";
    }
}

int main() {
    std::string expression = "(12 + 34) * 56";

    Tokenizer tokenizer(expression);
    std::vector<Token> tokens = tokenizer.tokenize();

    printTokens(tokens);

    return 0;
}
