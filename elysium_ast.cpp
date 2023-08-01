#include <iostream>
#include <vector>

enum TokenType {
    START,
    END,
    PRINT,
    STRING,
    CHAR,
    INT,
    INT_LITERAL,
    CHAR_LITERAL,
    DOUBLE_LITERAL,
    DOUBLE,
    BOOL,
    TRUE,
    FALSE,
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
        if (tokens_[current_index_].type == STRING || tokens_[current_index_].type == CHAR ||
            tokens_[current_index_].type == INT || tokens_[current_index_].type == DOUBLE ||
            tokens_[current_index_].type == BOOL) {
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
    consume(type); // Consume the variable type (STRING, CHAR, INT, DOUBLE, or BOOL)

    std::string variable_name = tokens_[current_index_].lexeme;
    consume(IDENTIFIER);
    consume(ASSIGN);
    std::string value = tokens_[current_index_].lexeme;
    if (type == STRING || type == CHAR) {
        consume(STRING_LITERAL);
        if (type == CHAR) {
            // Extract the first character from the CHAR string literal
            value = value.substr(1, 1);
        }
    } else if (type == INT || type == DOUBLE) {
        if (tokens_[current_index_].type == INT_LITERAL || tokens_[current_index_].type == DOUBLE_LITERAL) {
            value = tokens_[current_index_].lexeme;
            consume(tokens_[current_index_].type);
        } else {
            std::cerr << "Error: Expected INT_LITERAL or DOUBLE_LITERAL, but got: "
                      << tokens_[current_index_].type << " with lexeme: "
                      << tokens_[current_index_].lexeme << std::endl;
            exit(1);
        }
    } else if (type == BOOL) {
        if (tokens_[current_index_].type == TRUE || tokens_[current_index_].type == FALSE) {
            value = tokens_[current_index_].lexeme;
            consume(tokens_[current_index_].type);
        } else {
            std::cerr << "Error: Expected True or False, but got: "
                      << tokens_[current_index_].type << " with lexeme: "
                      << tokens_[current_index_].lexeme << std::endl;
            exit(1);
        }
    }
    consume(SEMICOLON);

    std::cout << "Variable Declaration: " << variable_name << ", Type: " << type << ", Value: " << value << std::endl;
}


    void factor() {
        if (tokens_[current_index_].type == IDENTIFIER) {
            // Generate AST node for variable or constant
            std::cout << "Factor: " << tokens_[current_index_].lexeme << std::endl;
            consume(IDENTIFIER);
        } else if (tokens_[current_index_].type == INT_LITERAL || tokens_[current_index_].type == DOUBLE_LITERAL ||
                   tokens_[current_index_].type == STRING_LITERAL || tokens_[current_index_].type == CHAR_LITERAL ||
                   tokens_[current_index_].type == TRUE || tokens_[current_index_].type == FALSE) {
            // Generate AST node for constant
            std::cout << "Factor: " << tokens_[current_index_].lexeme << std::endl;
            consume(tokens_[current_index_].type);
        } else {
            std::cerr << "Error: Invalid factor type: " << tokens_[current_index_].type
                      << " with lexeme: " << tokens_[current_index_].lexeme << std::endl;
            exit(1);
        }
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
        {INT, "INT"},
        {IDENTIFIER, "a"},
        {ASSIGN, "="},
        {INT_LITERAL, "2"},
        {SEMICOLON, ";"},
        {DOUBLE, "DOUBLE"},
        {IDENTIFIER, "b"},
        {ASSIGN, "="},
        {DOUBLE_LITERAL, "3.14"},
        {SEMICOLON, ";"},
        {BOOL, "BOOL"},
        {IDENTIFIER, "flag"},
        {ASSIGN, "="},
        {TRUE, "True"},
        {SEMICOLON, ";"},
        {PRINT, "PRINT"},
        {LPAREN, "("},
        {IDENTIFIER, "c"},
        {RPAREN, ")"},
        {SEMICOLON, ";"},
        {PRINT, "PRINT"},
        {LPAREN, "("},
        {IDENTIFIER, "a"},
        {RPAREN, ")"},
        {SEMICOLON, ";"},
        {PRINT, "PRINT"},
        {LPAREN, "("},
        {IDENTIFIER, "b"},
        {RPAREN, ")"},
        {SEMICOLON, ";"},
        {PRINT, "PRINT"},
        {LPAREN, "("},
        {IDENTIFIER, "flag"},
        {RPAREN, ")"},
        {SEMICOLON, ";"},
        {END, "END"},
    };


    ElysiumParser parser(tokens);
    parser.program();

    return 0;
}