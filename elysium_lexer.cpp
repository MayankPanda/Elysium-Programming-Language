#include <iostream>
#include <string>
#include <vector>
#include <sstream>

enum TokenType {
    START,
    END,
    PRINT,
    STRING,
    CHAR,
    INT,
    DOUBLE,
    BOOL,
    TRUE,
    FALSE,
    PLUS,
    IDENTIFIER,
    ASSIGN,
    LPAREN,
    RPAREN,
    STRING_LITERAL,
    SEMICOLON,
    EOL, // End of Line token
    INPUT,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string lexeme;
};

class ElysiumLexer {
public:
    ElysiumLexer(const std::string& input) : input_(input), current_pos_(0) {}

    Token getNextToken() {
        skipWhitespace();

        if (current_pos_ >= input_.size()) {
            return {UNKNOWN, ""};
        }

        char current_char = input_[current_pos_];

        if (current_char == 'S') {
            if (matchKeyword("START")) {
                advance(5);
                return {START, "START"};
            }
        } else if (current_char == 'E') {
            if (matchKeyword("END")) {
                advance(3);
                return {END, "END"};
            }
        } 
        else if (current_char == '+') {
            advance(1);
        return {PLUS, "+"};
        }
        else if (current_char == 'I') {
            if (matchKeyword("INT")) {
                advance(3);
                return {INT, "INT"};
            }
        } else if (current_char == 'I') {
            if (matchKeyword("INPUT")) {
                advance(5);
                return {INPUT, "INPUT"};
            }
        } else if (current_char == 'P') {
            if (matchKeyword("PRINT")) {
                advance(5);
                return {PRINT, "PRINT"};
            }
        } else if (current_char == 'C') {
            if (matchKeyword("CHAR")) {
                advance(4);
                return {CHAR, "CHAR"};
            }
        } else if (current_char == 'S') {
            if (matchKeyword("STRING")) {
                advance(6);
                return {STRING, "STRING"};
            }
        } else if (current_char == 'I') {
            if (matchKeyword("INT")) {
                advance(3);
                return {INT, "INT"};
            }
        } else if (current_char == 'T') {
            if (matchKeyword("TRUE")) {
                advance(4);
                return {TRUE, "TRUE"};
            }
        } 
        else if (current_char == 'F') {
            if (matchKeyword("FALSE")) {
                advance(5);
                return {TRUE, "FALSE"};
            }
        }  
        else if (current_char == 'B') {
            if (matchKeyword("BOOL")) {
                advance(4);
                return {TRUE, "BOOL"};
            }
        } 
        else if (current_char == 'D') {
            if (matchKeyword("DOUBLE")) {
                advance(6);
                return {DOUBLE, "DOUBLE"};
            }
        } else if (std::isalpha(current_char)) {
            return getIdentifierOrKeyword();
        } else if (current_char == '=') {
            advance(1);
            return {ASSIGN, "="};
        } else if (current_char == '(') {
            advance(1);
            return {LPAREN, "("};
        } else if (current_char == ')') {
            advance(1);
            return {RPAREN, ")"};
        } else if (current_char == ';') {
            advance(1);
            return {SEMICOLON, ";"};
        } else if (current_char == '"') {
            return getStringLiteral();
        } else if (current_char == '%') {
            advance(1);
            return {EOL, "%"};
        }

        // Unknown token
        advance(1);
        return {UNKNOWN, ""};
    }

private:
    const std::string input_;
    std::size_t current_pos_;

    void skipWhitespace() {
        while (current_pos_ < input_.size() && std::isspace(input_[current_pos_]))
            ++current_pos_;
    }

    bool matchKeyword(const std::string& keyword) {
        return current_pos_ + keyword.size() <= input_.size() &&
               input_.substr(current_pos_, keyword.size()) == keyword;
    }

    void advance(std::size_t count) {
        current_pos_ += count;
    }

    Token getIdentifierOrKeyword() {
        std::size_t start_pos = current_pos_;
        while (current_pos_ < input_.size() && std::isalnum(input_[current_pos_]))
            ++current_pos_;

        std::string lexeme = input_.substr(start_pos, current_pos_ - start_pos);
        return {IDENTIFIER, lexeme};
    }

    Token getStringLiteral() {
        std::size_t start_pos = current_pos_ + 1;
        std::size_t end_pos = input_.find('"', start_pos);
        if (end_pos == std::string::npos)
            return {UNKNOWN, ""};

        std::string value = input_.substr(start_pos, end_pos - start_pos);
        current_pos_ = end_pos + 1;
        return {STRING_LITERAL, value};
    }
};

int main() {
    std::string input = "START%INT d=3;%PRINT(d);%END";

    // Preprocess the input and split it into lines using the '%' delimiter
    std::vector<std::string> lines;
    std::istringstream iss(input);
    std::string line;
    while (std::getline(iss, line, '%')) {
        lines.push_back(line);
    }

    std::vector<Token> tokens;

    // Tokenize each line separately
    for (const std::string& line : lines) {
        ElysiumLexer lexer(line);
        Token token;
        do {
            token = lexer.getNextToken();
            tokens.push_back(token);
        } while (token.type != END && token.type != UNKNOWN);
    }

    // Print the tokens
    for (const Token& t : tokens) {
        std::cout << "Type: " << t.type << ", Lexeme: " << t.lexeme << std::endl;
    }

    return 0;
}
