#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>

// Token types
enum class TokenType {
    LPAREN, RPAREN, SLASH, EMPTY, EQUAL, KEYWORD, IDENTIFIER, REAL, INTEGER, STRING, XSTRING, CSTRING, STAR, COMMA, WHITESPACE, END_OF_LINE, DATASET, INVALID
};

// Token structure
struct Token {
    TokenType type;
    std::string value;
};

// Tokenize function declaration
std::vector<Token> tokenize(const std::string& input);

std::string tokenTypeToString(TokenType type);

// Helper function to print tokens
void printTokens(const std::vector<Token>& tokens);

#endif /* TOKENIZER_H */
