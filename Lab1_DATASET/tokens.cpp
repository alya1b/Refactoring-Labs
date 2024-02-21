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

// Tokenize function
std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    
    // Define regex patterns
    std::regex keyword_regex("DD1|DD2|OWFLW|BLOCK|RECORD|SIZE|RECFRM|REL|SCAN|DEVICE|RMNAME|FRSPC|SEGM|MINLEN|LOGICAL");
    std::regex real_regex("[+-]?[0-9]+[.][0-9]*"); 
    std::regex integer_regex("[+-]?[0-9]+");
    std::regex string_regex("'(.*?)'");
    std::regex xstring_regex("x'(.*?)'");
    std::regex cstring_regex("c'(.*?)'");
    std::regex identifier_regex("[a-zA-Z_][a-zA-Z0-9_]*"); // Identifiers start with a letter or underscore, followed by letters, digits, or underscores

    // Define token patterns
    std::vector<std::pair<std::regex, TokenType>> token_patterns = {
        { std::regex("\\("), TokenType::LPAREN },
        { std::regex("\\)"), TokenType::RPAREN },
        { std::regex("/"), TokenType::SLASH },
        { std::regex("EMPTY"), TokenType::EMPTY },
        { std::regex("="), TokenType::EQUAL },
        { std::regex("DATASET"), TokenType::DATASET },
        { keyword_regex, TokenType::KEYWORD },
        { real_regex, TokenType::REAL },
        { integer_regex, TokenType::INTEGER },
        { string_regex, TokenType::STRING },
        { xstring_regex, TokenType::XSTRING },
        { cstring_regex, TokenType::CSTRING },
        { std::regex("\\*"), TokenType::STAR },
        { std::regex(","), TokenType::COMMA },
        { std::regex("\\n|\\r"), TokenType::END_OF_LINE },  // End of line
        { std::regex("[\\s]+"), TokenType::WHITESPACE },  // Whitespace

        { identifier_regex, TokenType::IDENTIFIER } // Identifier
    };

    // Iterate through the input string
    size_t pos = 0;
    while (pos < input.length()) {
        // Try to match the input with each token pattern
        bool match_found = false;
        for (const auto& pattern : token_patterns) {
            std::smatch match;
            if (std::regex_search(input.begin() + pos, input.end(), match, pattern.first, std::regex_constants::match_continuous)) {
                match_found = true;
                std::string token_value = match.str();
                pos += token_value.length();
                // Skip whitespace and end of line
                if (pattern.second == TokenType::WHITESPACE) {
                    break;
                }
                // Add token to the list
                tokens.push_back({ pattern.second, token_value });
                break;
                
            }
        }
        if (!match_found) {
            // If no match found, it's an invalid token
            tokens.push_back({ TokenType::INVALID, std::string(1, input[pos]) });
            ++pos;
        }
    }
    
    return tokens;
}

// Helper function to print tokens
void printTokens(const std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        std::cout << "Type: ";
        switch (token.type) {
            case TokenType::LPAREN: std::cout << "LPAREN"; break;
            case TokenType::RPAREN: std::cout << "RPAREN"; break;
            case TokenType::SLASH: std::cout << "SLASH"; break;
            case TokenType::EMPTY: std::cout << "EMPTY"; break;
            case TokenType::EQUAL: std::cout << "EQUAL"; break;
            case TokenType::KEYWORD: std::cout << "KEYWORD"; break;
            case TokenType::IDENTIFIER: std::cout << "IDENTIFIER"; break;
            case TokenType::REAL: std::cout << "REAL"; break;
            case TokenType::INTEGER: std::cout << "INTEGER"; break;
            case TokenType::STRING: std::cout << "STRING"; break;
            case TokenType::XSTRING: std::cout << "XSTRING"; break;
            case TokenType::CSTRING: std::cout << "CSTRING"; break;
            case TokenType::STAR: std::cout << "STAR"; break;
            case TokenType::COMMA: std::cout << "COMMA"; break;
            case TokenType::WHITESPACE: std::cout << "WHITESPACE"; break;
            case TokenType::END_OF_LINE: std::cout << "END_OF_LINE"; break;
            case TokenType::DATASET: std::cout << "DATASET"; break;
            case TokenType::INVALID: std::cout << "INVALID"; break;
        }
        std::cout << ", Value: " << token.value << std::endl;
    }
}

// Function to convert TokenType enum value to string
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::DATASET:
            return "DATASET";
        case TokenType::KEYWORD:
            return "KEYWORD";
        case TokenType::EQUAL:
            return "=";
        case TokenType::LPAREN:
            return "(";
        case TokenType::RPAREN:
            return ")";
        case TokenType::SLASH:
            return "/identifier";
        case TokenType::IDENTIFIER:
            return "identifier";
        case TokenType::INTEGER:
            return "integer";
        case TokenType::REAL:
            return "real";
        case TokenType::STRING:
            return "string";
        case TokenType::XSTRING:
            return "xstring";
        case TokenType::CSTRING:
            return "cstring";
        case TokenType::STAR:
            return "star-value";
        case TokenType::COMMA:
            return ",";
        case TokenType::END_OF_LINE:
            return "EOL";
        case TokenType::EMPTY:
            return "EMPTY";
        default:
            return "UNKNOWN";
    }
}


//RUN TO TEST TOKENS
/*
int main() {
    std::string input = "DATASET DD1 = dataset-dd1 DD2 = dataset-dd2 SIZE = 123 RECFRM = 'abc' LOGICAL\n";
    std::vector<Token> tokens = tokenize(input);
    printTokens(tokens);
    return 0;
}*/
