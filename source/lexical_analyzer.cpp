#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
using std::string; 

enum class TokenType {
	CONSTANT = 1,
    IDENTIFIER = 2,
    INT = 3,
    DOUBLE = 4,
    LONG = 5,
    FLOAT = 6,
    CHAR = 7,
    BOOL = 8,
    STRING = 9,
    IF = 10,
    ELSE = 11,
    WHILE = 12,
    FOR = 13,
    DO = 14,
    BREAK = 15,
    CONTINUE = 16,
    RETURN = 17,
    READ = 18,
    WRITE = 19,
    PLUS = 20,
    MINUS = 21,
    MULTIPLY = 22,
    DIVIDE = 23,
    MODULO = 24,
    EXPONENT = 25,  
    BITWISE_AND = 26,
    BITWISE_OR = 27,
    BITWISE_XOR = 28,
    BITWISE_NOT = 29,
    LOGICAL_AND = 30,
    LOGICAL_OR = 31,
    LESS = 32,
    LESS_EQUAL = 33,
    GREATER = 34,
    GREATER_EQUAL = 35,
    NOT_EQUAL = 36,
    EQUAL_EQUAL = 37,
    ASSIGN = 38,
    LEFT_PAREN = 39,
    RIGHT_PAREN = 40,
    LEFT_BRACE = 41,
    RIGHT_BRACE = 42,
    LEFT_BRACKET = 43,
    RIGHT_BRACKET = 44,
    COMMA = 45,
    SEMICOLON = 46,
    COLON = 47,
    DOT = 48,
    END_OF_FILE = 0
};

struct Token {
    TokenType type;
    string lexeme;
    
    Token(TokenType t, const string& lex = "") : type(t), lexeme(lex) {}
};

class LexicalAnalyzer {
private:
    std::ifstream input_file;
    char current_char = '\0'; 
    string current_token = "";
    std::unordered_map<string, TokenType> keywords;
    
    void get_char() {
        current_char = input_file.get();
    }

    void skip_blank() {
        while (current_char == ' ' || current_char == '\t' || current_char == '\r' || current_char == '\n') 
            get_char();
    }
    
    void concat() {
        current_token += current_char;
    }
    
    bool is_letter() const {
        return (current_char >= 'a' && current_char <= 'z') || (current_char >= 'A' && current_char <= 'Z');
    }
    
    bool is_digit() const {
        return (current_char >= '0' && current_char <= '9');
    }
    
    void retract() {
        input_file.putback(current_char); // Put character back into stream
        current_char = '\0';
    }
    
    TokenType check_keyword() const {
        auto it = keywords.find(current_token);
        if (it != keywords.end()) 
            return it->second;
        return TokenType::IDENTIFIER;
    }
    
public:
    LexicalAnalyzer() {
        keywords = {
            {"int", TokenType::INT},
            {"double", TokenType::DOUBLE},
            {"long", TokenType::LONG},
            {"float", TokenType::FLOAT},
            {"char", TokenType::CHAR},
            {"bool", TokenType::BOOL},
            {"string", TokenType::STRING},
            {"if", TokenType::IF},
            {"else", TokenType::ELSE},
            {"while", TokenType::WHILE},
            {"for", TokenType::FOR},
            {"do", TokenType::DO},
            {"break", TokenType::BREAK},
            {"continue", TokenType::CONTINUE},
            {"return", TokenType::RETURN},
            {"read", TokenType::READ},
            {"write", TokenType::WRITE}
        };
    }
    
    bool open_file(const string& filename) {
        input_file.open(filename);
        return input_file.is_open();
    }
    
    Token get_next_token() {
        current_token = "";
        get_char();
        skip_blank();
        
        if (input_file.eof()) 
            return Token(TokenType::END_OF_FILE);

        if (current_char == '/') {
            get_char();
            // Single line comment
            if (current_char == '/') {
                while (current_char != '\n' && !input_file.eof()) 
                    get_char();
                return get_next_token();
            } 
            else if (current_char == '*') {
                get_char();
                while (!input_file.eof()) {
                    if (current_char == '*') {
                        get_char();
                        if (current_char == '/') {
                            return get_next_token();
                        }
                    } else {
                        get_char();
                    }
                }
                throw std::runtime_error("Error: unclosed block comment");
            }
            // not a comment, '/' as division
            else {
                retract(); 
                return Token(TokenType::DIVIDE);
            }
        }
        if (current_char == '\'') {
            concat(); 
            get_char(); 
            if (current_char == '\\') {
                concat(); 
                get_char();
                if (input_file.eof()) {
                    throw std::runtime_error("Error: unexpected end of file in char");
                }
                concat(); 
                get_char();
            } else {
                concat();
                get_char();
            }
            if (current_char == '\'') {
                concat();
                return Token(TokenType::CONSTANT, current_token);
            } else {
                throw std::runtime_error("Error: unclosed char");
            }
        }
        
        if (current_char == '"') {
            concat(); 
            get_char();
            
            while (current_char != '"' && !input_file.eof()) {
                if (current_char == '\\') {
                    concat(); 
                    get_char();
                    if (input_file.eof()) {
                        throw std::runtime_error("Error: unexpected end of file in string");
                    }
                    concat(); 
                    get_char();
                } else {
                    concat();
                    get_char();
                }
            }
            
            if (current_char == '"') {
                concat(); 
                return Token(TokenType::CONSTANT, current_token);
            } else {
                throw std::runtime_error("Error: unclosed string");
            }
        }
        if (is_letter()) {
            while (is_letter() || is_digit()) {
                concat();
                get_char();
            }
            retract();
            
            TokenType type = check_keyword();
            if (type != TokenType::IDENTIFIER) 
                return Token(type);
            return Token(TokenType::IDENTIFIER, current_token);
        }
        
        if (is_digit()) {
            while (is_digit()) {
                concat();
                get_char();
            }
            retract();
            return Token(TokenType::CONSTANT, current_token);
		}
        switch (current_char) {
			case '+': return Token(TokenType::PLUS);
			case '-': return Token(TokenType::MINUS);
			case '*': return Token(TokenType::MULTIPLY);
			case '/': return Token(TokenType::DIVIDE);
			case '%': return Token(TokenType::MODULO);
			case '^': return Token(TokenType::EXPONENT);
			case '&':
                concat();
                get_char();
                if (current_char == '&') {
                    return Token(TokenType::LOGICAL_AND);
                } else {
                    retract();
                    return Token(TokenType::BITWISE_AND);
                }
                
            case '|':
                concat();
                get_char();
                if (current_char == '|') {
                    return Token(TokenType::LOGICAL_OR);
                } else {
                    retract();
                    return Token(TokenType::BITWISE_OR);
                }
			case '~': return Token(TokenType::BITWISE_NOT);
			case '.': return Token(TokenType::DOT);
			case ':': return Token(TokenType::COLON);
			case '{': return Token(TokenType::LEFT_BRACE);
			case '}': return Token(TokenType::RIGHT_BRACE);
			case '[': return Token(TokenType::LEFT_BRACKET);
			case ']': return Token(TokenType::RIGHT_BRACKET);
            case '<':
                concat();
                get_char();
                if (current_char == '=') {
                    return Token(TokenType::LESS_EQUAL);
                } else {
                    retract();
                    return Token(TokenType::LESS);
                }
            
            case '>':
                concat();
                get_char();
                if (current_char == '=') {
                    return Token(TokenType::GREATER_EQUAL);
                } else {
                    retract();
                    return Token(TokenType::GREATER);
                }
            
            case '!':
                concat();
                get_char();
                if (current_char == '=') {
                    return Token(TokenType::NOT_EQUAL);
                } else {
                    retract();
                    throw std::runtime_error("Error: unexpected '!' character");
                }
            
            case '=':
                concat();
                get_char();
                if (current_char == '=') {
                    return Token(TokenType::EQUAL_EQUAL);
                } else {
                    retract();
                    return Token(TokenType::ASSIGN);
                }
            
            case '(': return Token(TokenType::LEFT_PAREN);
            case ')': return Token(TokenType::RIGHT_PAREN);
            case ',': return Token(TokenType::COMMA);
            case ';': return Token(TokenType::SEMICOLON);
            
            default:
                string error = "Error: unexpected character '";
                error += current_char;
                error += "'";
                throw std::runtime_error(error);
        }
    }
    
    static void print_token(const Token& token) {
        int type_num = static_cast<int>(token.type);
        
        if (token.type == TokenType::IDENTIFIER || token.type == TokenType::CONSTANT) {
            std::cout << "( " << type_num << " , " << token.lexeme << " )" << std::endl;
        } else {
            std::cout << "( " << type_num << " , - )" << std::endl;
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
        return 1;
    }
    
    LexicalAnalyzer analyzer;
    if (!analyzer.open_file(argv[1])) {
        std::cerr << "Error: cannot open file \"" << argv[1] << "\"" << std::endl;
        return 1;
    }
    
    try {
        while (true) {
            Token token = analyzer.get_next_token();
            if (token.type == TokenType::END_OF_FILE) {
                break;
            }
            LexicalAnalyzer::print_token(token);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
