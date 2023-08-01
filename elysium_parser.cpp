#include <iostream>
#include <vector>

enum TokenType {
    // ... (same enum definitions as before)
    START,
    END,
    PRINT,
    STRING,
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
    ElysiumParser(const std::vector<Token>& tokens) : tokens_(tokens), current_token_index_(0) {}

    // Helper functions to check current token type and advance to the next token
    bool match(TokenType type) const {
        return currentToken().type == type;
    }

    Token consume(TokenType type) {
        if (current_token_index_ < tokens_.size()) {
            if (tokens_[current_token_index_].type == type) {
                return tokens_[current_token_index_++];
            }
        }
        // Return an UNKNOWN token if the expected token type does not match
        return {UNKNOWN, ""};
    }

    // Recursive Descent Parsing function for the given program
    // program -> START statement_list END
    void program() {
        std::cout << "Parsing program...\n";
        consume(START);
        statement_list();
        consume(END);
        std::cout << "Program parsed successfully!\n";
    }

    // statement_list -> statement statement_list | empty
    void statement_list() {
        while (!match(END)) {
            std::cout << "Parsing statement...\n";
            statement();
        }
    }

    // statement -> variable_declaration | input_statement | print_statement
    void statement() {
        if (match(STRING)) {
            variable_declaration();
        } else if (match(INPUT)) {
            input_statement();
        } else if (match(PRINT)) {
            print_statement();
        } else {
            // Handle any other statements here (e.g., assignments, control flow, etc.)
            consume(UNKNOWN); // Skip unknown tokens for now
        }
    }

    // variable_declaration -> STRING IDENTIFIER SEMICOLON
    void variable_declaration() {
        std::cout << "Parsing variable declaration...\n";
        consume(STRING);
        consume(IDENTIFIER);
        consume(SEMICOLON);
        std::cout << "Variable declaration parsed successfully!\n";
    }

    // input_statement -> INPUT LPAREN IDENTIFIER RPAREN SEMICOLON
    void input_statement() {
        std::cout << "Parsing input statement...\n";
        consume(INPUT);
        consume(LPAREN);
        consume(IDENTIFIER);
        consume(RPAREN);
        consume(SEMICOLON);
        std::cout << "Input statement parsed successfully!\n";
    }

    // print_statement -> PRINT LPAREN IDENTIFIER RPAREN SEMICOLON
    void print_statement() {
        std::cout << "Parsing print statement...\n";
        consume(PRINT);
        consume(LPAREN);
        consume(IDENTIFIER);
        consume(RPAREN);
        consume(SEMICOLON);
        std::cout << "Print statement parsed successfully!\n";
    }

private:
    const std::vector<Token>& tokens_;
    std::size_t current_token_index_;

    Token currentToken() const {
        return tokens_[current_token_index_];
    }
};

int main() {
    std::vector<Token> tokens = {
        {START, "START"},
        {STRING, "STRING"},
        {IDENTIFIER, "str"},
        {SEMICOLON, ";"},
        {INPUT, "INPUT"},
        {LPAREN, "("},
        {IDENTIFIER, "str"},
        {RPAREN, ")"},
        {SEMICOLON, ";"},
        {PRINT, "PRINT"},
        {LPAREN, "("},
        {IDENTIFIER, "str"},
        {RPAREN, ")"},
        {SEMICOLON, ";"},
        {END, "END"},
    };

    // Create the parser and parse the program
    ElysiumParser parser(tokens);
    parser.program();

    return 0;
}
