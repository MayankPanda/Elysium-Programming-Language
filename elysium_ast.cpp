#include <iostream>
#include <vector>

enum TokenType {
    START,
    END,
    PRINT,
    STRING,
    CHAR,
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

class ElysiumParser {
public:
    ElysiumParser(const std::vector<Token>& tokens) : tokens_(tokens), current_index_(0) {}

    void program() {
        consume(START);
        statement_list();
        consume(END);
    }

private:
    const std::vector<Token>& tokens_;
    size_t current_index_;

    void consume(TokenType expected_type) {
        if (current_index_ < tokens_.size()) {
            if (tokens_[current_index_].type == expected_type) {
                current_index_++;
            } else {
                std::cerr << "Error: Expected token type: " << expected_type << ", but got: "
                          << tokens_[current_index_].type << " with lexeme: "
                          << tokens_[current_index_].lexeme << std::endl;
                exit(1);
            }
        }
    }

    void statement_list() {
    while (current_index_ < tokens_.size() && tokens_[current_index_].type != END) {
        if (tokens_[current_index_].type == STRING || tokens_[current_index_].type == CHAR) {
            variable_declaration();
        } else if (tokens_[current_index_].type == INPUT) {
            input_statement();
        } else if (tokens_[current_index_].type == PRINT) {
            print_statement();
        } else {
            std::cerr << "Error: Invalid statement type: " << tokens_[current_index_].type
                      << " with lexeme: " << tokens_[current_index_].lexeme << std::endl;
            exit(1);
        }
    }
}

    void variable_declaration() {
        TokenType type = tokens_[current_index_].type;
        consume(type); // Consume the variable type (STRING or CHAR)

        std::string variable_name = tokens_[current_index_].lexeme;
        consume(IDENTIFIER);
        consume(ASSIGN);
        std::string value = tokens_[current_index_].lexeme;
        if (type == STRING) {
            consume(STRING_LITERAL);
        } else if (type == CHAR) {
            consume(STRING_LITERAL);
            // Extract the first character from the CHAR string literal
            value = value.substr(1, 1);
        }
        consume(SEMICOLON);

        std::cout << "Variable Declaration: " << variable_name << ", Type: " << type << ", Value: " << value << std::endl;
    }

    void input_statement() {
        consume(INPUT);
        consume(LPAREN);
        std::string variable_name = tokens_[current_index_].lexeme;
        consume(IDENTIFIER);
        consume(RPAREN);
        consume(SEMICOLON);
        std::cout << "Input Statement: " << variable_name << std::endl;
    }

    void print_statement() {
        consume(PRINT);
        consume(LPAREN);
        std::string variable_name = tokens_[current_index_].lexeme;
        consume(IDENTIFIER);
        consume(RPAREN);
        consume(SEMICOLON);
        std::cout << "Print Statement: " << variable_name << std::endl;
    }
};

int main() {
    std::vector<Token> tokens = {
    {START, "START"},
    {CHAR, "CHAR"},
    {IDENTIFIER, "c"},
    {ASSIGN, "="},
    {STRING_LITERAL, "'x'"},
    {SEMICOLON, ";"},
    {PRINT, "PRINT"},
    {LPAREN, "("},
    {IDENTIFIER, "c"},
    {RPAREN, ")"},
    {SEMICOLON, ";"},
    {END, "END"},
};


    ElysiumParser parser(tokens);
    parser.program();

    return 0;
}