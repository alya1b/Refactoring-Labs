#include <iostream>
#include <vector>
#include <memory>
#include "tokens.h" // Include the header file containing token definitions

// Forward declaration of the TreeNode class
class TreeNode;

// Alias for shared_ptr of TreeNode
using TreeNodePtr = std::shared_ptr<TreeNode>;

// TreeNode class representing a node in the parse tree
class TreeNode {
public:
    TokenType type;
    std::string value;
    std::vector<TreeNodePtr> children;

    TreeNode(TokenType type, const std::string& value) : type(type), value(value) {}

    // Add child node to the current node
    void addChild(TreeNodePtr child) {
        children.push_back(child);
    }
};

// Parser class for parsing commands
class Parser {
public:
// Recursive function to parse a list
static TreeNodePtr parseList(const std::vector<Token>& tokens, size_t& pos) {
    // Ensure that the current token is an opening parenthesis
    if (pos >= tokens.size() || tokens[pos].type != TokenType::LPAREN) {
        std::cerr << "Error: Expected opening parenthesis." << std::endl;
        return nullptr;
    }

    // Create a list node
    TreeNodePtr listNode = std::make_shared<TreeNode>(TokenType::KEYWORD, "LIST");
    pos++; // Move past the opening parenthesis

    // Parse list elements
    while (pos < tokens.size() && tokens[pos].type != TokenType::RPAREN) {
        // Parse list element
        if (tokens[pos].type == TokenType::LPAREN) {
            // Nested list
            TreeNodePtr nestedListNode = parseList(tokens, pos);
            if (!nestedListNode) {
                return nullptr;
            }
            listNode->addChild(nestedListNode);
        } else if (tokens[pos].type == TokenType::SLASH) {
            // SLASH token followed by identifier
            if (pos + 1 < tokens.size() && tokens[pos + 1].type == TokenType::IDENTIFIER) {
                // Create a node for SLASH followed by identifier
                std::string slashIdentifier = "/" + tokens[pos + 1].value;
                TreeNodePtr slashIdentifierNode = std::make_shared<TreeNode>(TokenType::SLASH, slashIdentifier);
                listNode->addChild(slashIdentifierNode);
                pos += 2; // Move past SLASH and identifier
            } else {
                std::cerr << "Error: Expected identifier after SLASH." << std::endl;
                return nullptr;
            }
        } else if (tokens[pos].type == TokenType::INTEGER || tokens[pos].type == TokenType::REAL ||
                   tokens[pos].type == TokenType::STRING || tokens[pos].type == TokenType::XSTRING ||
                   tokens[pos].type == TokenType::CSTRING || tokens[pos].type == TokenType::STAR ||
                   tokens[pos].type == TokenType::IDENTIFIER|| tokens[pos].type == TokenType::EMPTY) {
            // Value token
            TreeNodePtr valueNode = std::make_shared<TreeNode>(tokens[pos].type, tokens[pos].value);
            listNode->addChild(valueNode);
            pos++;
        } else {
            std::cerr << "Error: Invalid token in list." << std::endl;
            return nullptr;
        }

        // Check for comma or closing parenthesis
        if (pos < tokens.size() && tokens[pos].type == TokenType::COMMA) {
            pos++; // Move past the comma
        } else if (pos < tokens.size() && tokens[pos].type != TokenType::RPAREN) {
            std::cerr << "Error: Expected comma or closing parenthesis." << std::endl;
            return nullptr;
        }
    }

    // Check for closing parenthesis
    if (pos >= tokens.size() || tokens[pos].type != TokenType::RPAREN) {
        std::cerr << "Error: Expected closing parenthesis." << std::endl;
        return nullptr;
    }

    pos++; // Move past the closing parenthesis
    return listNode;
}

// Parse function to generate the parse tree
static TreeNodePtr parse(const std::vector<Token>& tokens, size_t& pos) {
    // Initialize parse tree root
    TreeNodePtr root = std::make_shared<TreeNode>(TokenType::DATASET, "DATASET");

    // Start parsing from the second token (skipping the label if present)
    if (tokens[pos].type == TokenType::IDENTIFIER) {
        TreeNodePtr labelNode = std::make_shared<TreeNode>(TokenType::IDENTIFIER, tokens[pos].value);
        root->addChild(labelNode);
        pos++;
    }

    // Ensure that the first token is DATASET
    if (tokens[pos].type != TokenType::DATASET) {
        std::cerr << "Error: Expected DATASET token." << std::endl;
        return nullptr;
    }

    // Parse dataset command
    TreeNodePtr datasetNode = std::make_shared<TreeNode>(TokenType::DATASET, "DATASET");
    root->addChild(datasetNode);
    pos++; // Move to the next token

    // Parse dataset parameters
    while (pos < tokens.size()) {
        // Ensure that we have an equal sign after a keyword
        if (tokens[pos].type != TokenType::KEYWORD || tokens[pos + 1].type != TokenType::EQUAL) {
            std::cerr << "Error: Expected keyword followed by = sign." << std::endl;
            return nullptr;
        }

        // Create a key-value pair node
        TreeNodePtr keyValueNode = std::make_shared<TreeNode>(TokenType::KEYWORD, tokens[pos].value);
        datasetNode->addChild(keyValueNode);

        // Move past the keyword and equal sign
        pos += 2;

        // Ensure that we have a value token
        if (pos >= tokens.size()) {
            std::cerr << "Error: Expected value token." << std::endl;
            return nullptr;
        }

        // Parse value token(s)
        if (tokens[pos].type == TokenType::LPAREN) {
            // List of values
            TreeNodePtr listNode = parseList(tokens, pos);
            if (!listNode) {
                return nullptr;
            }
            keyValueNode->addChild(listNode);
        } else if (tokens[pos].type == TokenType::SLASH) {
            // SLASH token followed by identifier
            if (pos + 1 < tokens.size() && tokens[pos + 1].type == TokenType::IDENTIFIER) {
                // Create a node for SLASH followed by identifier
                std::string slashIdentifier = "/" + tokens[pos + 1].value;
                TreeNodePtr slashIdentifierNode = std::make_shared<TreeNode>(TokenType::SLASH, slashIdentifier); //
                keyValueNode->addChild(slashIdentifierNode);
                pos += 2; // Move past SLASH and identifier
            } else {
                std::cerr << "Error: Expected identifier after SLASH." << std::endl;
                return nullptr;
            }
        } else if (tokens[pos].type == TokenType::INTEGER || tokens[pos].type == TokenType::REAL ||
                   tokens[pos].type == TokenType::STRING || tokens[pos].type == TokenType::XSTRING ||
                   tokens[pos].type == TokenType::CSTRING || tokens[pos].type == TokenType::STAR ||
                   tokens[pos].type == TokenType::IDENTIFIER||tokens[pos].type == TokenType::EMPTY) {
            // Value token
            TreeNodePtr valueNode = std::make_shared<TreeNode>(tokens[pos].type, tokens[pos].value);
            keyValueNode->addChild(valueNode);
            pos++;
        } else {
            std::cerr << "Error: Invalid token." << std::endl;
            return nullptr;
        }

        // Check for comma or end of line
        if (pos < tokens.size() && tokens[pos].type == TokenType::COMMA) {
            pos++; // Move past the comma
        } else if (pos < tokens.size() && tokens[pos].type == TokenType::END_OF_LINE) {
            break; // End of command
        } else {
            std::cerr << "Error: Expected comma or end of line." << std::endl;
            return nullptr;
        }
    }

    return root;
}

};

// Helper function to print the parse tree
void printTree(const TreeNodePtr& node, int depth = 0) {
    // Print indentation
    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }

    // Print node type and value
    if (node->type == TokenType::INTEGER || node->type == TokenType::REAL ||
        node->type == TokenType::STRING || node->type == TokenType::XSTRING ||
        node->type == TokenType::CSTRING || node->type == TokenType::STAR ||
        node->type == TokenType::IDENTIFIER || node->type == TokenType::SLASH || node->type == TokenType::EMPTY) {
        // For value nodes, print type and value
        std::cout << tokenTypeToString(node->type) << ": " << node->value << std::endl;
    } else {
        // For other nodes, print value only
        std::cout << node->value << std::endl;
    }

    // Recursively print children
    for (const auto& child : node->children) {
        printTree(child, depth + 1);
    }
}



int main() {
    std::string command;

    // Infinite loop for input commands
    while (true) {
        std::cout << "Enter a command (enter '0' to exit): ";
        std::getline(std::cin, command);
        command += "\n";

        // Check if the user wants to exit
        if (command == "0\n") {
            break;
        }

        // Tokenize the input command
        std::vector<Token> tokens = tokenize(command);
        //printTokens(tokens);

        // Parse the command and print the tree
        size_t pos = 0;
        TreeNodePtr parseTree = Parser::parse(tokens, pos);
        
        std::cout << "Parse Tree:" << std::endl;
        printTree(parseTree);
        
    }

    return 0;
}
