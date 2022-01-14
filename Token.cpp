#include "Token.h"


Token::Token(TokenType tokenType, std::string description, int line) {

    theDescription = description;
    theLine = line;
    switch (tokenType) {
        case COMMA:
            type = "COMMA";
            break;
        case PERIOD:
            type = "PERIOD";
            break;
        case Q_MARK:
            type = "Q_MARK";
            break;
        case LEFT_PAREN:
            type = "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            type = "RIGHT_PAREN";
            break;
        case COLON:
            type = "COLON";
            break;
        case COLON_DASH:
            type = "COLON_DASH";
            break;
        case MULTIPLY:
            type = "MULTIPLY";
            break;
        case ADD:
            type = "ADD";
            break;
        case SCHEMES:
            type = "SCHEMES";
            break;
        case FACTS:
            type = "FACTS";
            break;
        case RULES:
            type = "RULES";
            break;
        case QUERIES:
            type = "QUERIES";
            break;
        case ID:
            type = "ID";
            break;
        case STRING:
            type = "STRING";
            break;
        case COMMENT:
            type = "COMMENT";
            break;
        case UNDEFINED:
            type = "UNDEFINED";
            break;
        case EOFa:
            type = "EOF";
            break;
        case ERROR:
            type = "ERROR";
    }
    theTokenType = tokenType;
}

//============================================================================================

Token::~Token() {

}

//============================================================================================

string Token::toString() {

    theToken = "  (" + type + ",\"" + theDescription + "\"," + to_string(theLine) +")";
    return theToken;
}

//============================================================================================


string Token::GetType() {
    return type;

}

string Token::GetDescription() {
    return theDescription;
}

