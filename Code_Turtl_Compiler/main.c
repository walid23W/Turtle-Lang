#include "header.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//token_types
enum TOKEN_TYPE {
    PEN_COLOR,
    PEN_WIDTH,
    PEN_STYLE,
    MOVE_FORWARD,
    MOVE_BACKWARD,
    MOVE_TO,
    TURN_LEFT,
    TURN_RIGHT,
    REPEAT,
    STYLE,
    NUMBER,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    SEMICOLON,
    ENDOFFILE,
    UNKNOWN
};

int count = 0;

//token_structure
struct token {
    enum TOKEN_TYPE type;
    char lexeme[32];
    int value;
};

struct parserOutput {
    int status;
    struct token tokens[TOKEN_CAP];
};

struct parserOutput Output = {1};
int index_token = 0;
int Index = 0;
int line_number = 1;
struct token current_token;
char input[1000];

//handle errors
void error(char *message) {
    printf("Error : %s at line %d, near %s\n", message, line_number,
           current_token.lexeme);
    exit(1);
}



//parse_input and generate tokens
void get_next_token() {
    while (isspace(input[Index])) {
        if (input[Index] == '\n') {
            line_number++;
        }
        Index++;
    }
    current_token.value = 0;
    if (isalpha(input[Index])) {
        int i = 0;
        while (isalpha(input[Index])) {
            current_token.lexeme[i++] = input[Index++];
        }
        current_token.lexeme[i] = '\0';
        if (strcmp(current_token.lexeme, "penColor") == 0) {
            current_token.type = PEN_COLOR;
        } else if (strcmp(current_token.lexeme, "penWidth") == 0) {
            current_token.type = PEN_WIDTH;
        } else if (strcmp(current_token.lexeme, "penStyle") == 0) {
            current_token.type = PEN_STYLE;
        } else if (strcmp(current_token.lexeme, "moveForward") == 0) {
            current_token.type = MOVE_FORWARD;
        } else if (strcmp(current_token.lexeme, "moveBackward") == 0) {
            current_token.type = MOVE_BACKWARD;
        } else if (strcmp(current_token.lexeme, "moveTo") == 0) {
            current_token.type = MOVE_TO;
        } else if (strcmp(current_token.lexeme, "turnLeft") == 0) {
            current_token.type = TURN_LEFT;
        } else if (strcmp(current_token.lexeme, "turnRight") == 0) {
            current_token.type = TURN_RIGHT;
        } else if (strcmp(current_token.lexeme, "repeat") == 0) {
            current_token.type = REPEAT;
        } else if (strcmp(current_token.lexeme, "solid") == 0) {
            current_token.type = STYLE;
        } else if (strcmp(current_token.lexeme, "dashed") == 0) {
            current_token.type = STYLE;
        } else if (strcmp(current_token.lexeme, "dotted") == 0) {
            current_token.type = STYLE;
        } else {
            current_token.type = UNKNOWN;
        }
    } else if (isdigit(input[Index])) {
        int i = 0;
        while (isdigit(input[Index])) {
            current_token.lexeme[i++] = input[Index++];
        }
        current_token.lexeme[i] = '\0';
        current_token.type = NUMBER;
        current_token.value = atoi(current_token.lexeme);
    } else if (input[Index] == '(') {
        current_token.type = LEFT_PAREN;
        current_token.lexeme[0] = '(';
        current_token.lexeme[1] = '\0';
        Index++;
    } else if (input[Index] == ')') {
        current_token.type = RIGHT_PAREN;
        current_token.lexeme[0] = ')';
        current_token.lexeme[1] = '\0';
        Index++;
    } else if (input[Index] == '{') {
        current_token.type = LEFT_BRACE;
        current_token.lexeme[0] = '{';
        current_token.lexeme[1] = '\0';
        Index++;
    } else if (input[Index] == '}') {

        current_token.type = RIGHT_BRACE;
        current_token.lexeme[0] = '}';
        current_token.lexeme[1] = '\0';
        Index++;
    } else if (input[Index] == ',') {
        current_token.type = COMMA;
        current_token.lexeme[0] = ',';
        current_token.lexeme[1] = '\0';
        Index++;
    } else if (input[Index] == ';') {
        current_token.type = SEMICOLON;
        current_token.lexeme[0] = ';';
        current_token.lexeme[1] = '\0';
        Index++;
    } else if (input[Index] == '\0') {
        current_token.type = ENDOFFILE;
        current_token.lexeme[0] = '\0';
    } else {
        current_token.type = UNKNOWN;
        current_token.lexeme[0] = input[Index++];
        current_token.lexeme[1] = '\0';
    }
    Output.tokens[index_token++] = current_token;
}

void match(enum TOKEN_TYPE expected_type) {
    if (current_token.type == expected_type) {
        get_next_token();
    } else {
        error("Unexpected token, expected something else");
    }
}

void pen_command() {
    get_next_token(); // consume the command token
    match(LEFT_PAREN);
    if (current_token.type == NUMBER) {
        get_next_token();
        if (current_token.type == COMMA) {
            get_next_token();
            if (current_token.type == NUMBER) {
                get_next_token();
                if (current_token.type == COMMA) {
                    get_next_token();
                    if (current_token.type == NUMBER) {
                        get_next_token();
                    } else {
                        error("Invalid third argument. Expected number");
                    }
                } else {
                    error("Syntax error. Expected ','.");
                }
            } else {
                error("Invalid second argument. Expected number");
            }
        }
    } else if (current_token.type == STYLE) {
        get_next_token();
    } else {
        error("Invalid argument for pen command");
    }
    match(RIGHT_PAREN);
    match(SEMICOLON);
}

void movement_command() {
    get_next_token(); // consume the command token
    match(LEFT_PAREN);
    if (current_token.type == NUMBER) {
        get_next_token();
        match(RIGHT_PAREN);
        match(SEMICOLON);
    } else {
        error("Invalid argument for movement command");
    }
}

void movement_to_command() {
    get_next_token(); // consume the command token
    match(LEFT_PAREN);
    if (current_token.type == NUMBER) {
        get_next_token();
        match(COMMA);
        if (current_token.type == NUMBER) {
            get_next_token();
            match(RIGHT_PAREN);
            match(SEMICOLON);
        } else {
            error("Invalid second argument for movement_to_command");
        }
    } else {
        error("Invalid first argument for movement_to command");
    }
}

void rotation_command() {
    get_next_token(); // consume the command token
    match(LEFT_PAREN);
    if (current_token.type == NUMBER) {
        get_next_token();
        match(RIGHT_PAREN);
        match(SEMICOLON);
    } else {
        error("Invalid argument for rotation command");
    }
}

void program_list() {
    while (current_token.type != ENDOFFILE && current_token.type != RIGHT_BRACE) {
        command();
    }
}

void loop_command() {
    get_next_token(); // consume the command token
    match(LEFT_PAREN);
    if (current_token.type == NUMBER) {
        get_next_token();
        match(RIGHT_PAREN);
        match(LEFT_BRACE);
        program_list();
        // get_next_token();
        match(RIGHT_BRACE);
    } else {
        error("Invalid argument for loop command");
    }
}

void command() {
    if (current_token.type == PEN_COLOR) {
        pen_command();
    } else if (current_token.type == PEN_WIDTH) {
        pen_command();
    } else if (current_token.type == PEN_STYLE) {
        pen_command();
    } else if (current_token.type == MOVE_FORWARD) {
        movement_command();
    } else if (current_token.type == MOVE_BACKWARD) {
        movement_command();
    } else if (current_token.type == MOVE_TO) {
        movement_to_command();
    } else if (current_token.type == TURN_LEFT) {
        rotation_command();
    } else if (current_token.type == TURN_RIGHT) {
        rotation_command();
    } else if (current_token.type == REPEAT) {
        loop_command();
    } else {
        error("Invalid command");
    }
}

void program() {
    get_next_token();
    program_list();
    match(ENDOFFILE);
}


//Generate JScode
char *generateJS(struct parserOutput syntaxAnalyzerOutput) {
    char *jsCode ;
    jsCode = (char *)malloc(1000 * (sizeof(char)));
    memset(jsCode,0,sizeof(jsCode));
    strcat(jsCode,"import {ctx} from \"./translate.js\";\nexport function turtlePath(drawTurtle){\nctx.beginPath()\n");
    int i = 0;

    while (i < index_token - 2) {
        struct token t = syntaxAnalyzerOutput.tokens[i];
        char *jsStatement;
        jsStatement = (char *)malloc(1000 * sizeof(char));
        int value;
        int x, y;
        int r, g, b;
        char *style;
        switch (t.type) {
            case MOVE_TO:
                x = syntaxAnalyzerOutput.tokens[i + 2].value;
                y = syntaxAnalyzerOutput.tokens[i + 4].value;
                sprintf(jsStatement,
                        "ctx.resetTransform()\nctx.translate(%d,%d)\n",
                        x, y);
                strcat(jsCode, jsStatement);
                i += 7;
                break;
            case MOVE_FORWARD:
                value = syntaxAnalyzerOutput.tokens[i + 2].value;
                sprintf(jsStatement,
                        "ctx.beginPath()\nctx.moveTo(0, 0)\nctx.lineTo(0, "
                        "%d)\nctx.stroke()\nctx.translate(0, %d)\nctx.closePath()\n",
                        value, value);
                strcat(jsCode, jsStatement);
                i += 5;
                break;
            case MOVE_BACKWARD:
                value = syntaxAnalyzerOutput.tokens[i + 2].value;
                sprintf(jsStatement,
                        "ctx.beginPath()\nctx.rotate(Math.PI)\nctx.beginPath()\nctx.moveTo(0, "
                        "0)\nctx.lineTo(0, %d)\nctx.stroke()\nctx.translate(0, %d)\nctx.closePath()\n",
                        value, value);
                strcat(jsCode, jsStatement);
                i += 5;
                break;
            case TURN_LEFT:
                value = -syntaxAnalyzerOutput.tokens[i + 2].value;
                sprintf(jsStatement, "ctx.rotate((%d * Math.PI)/180)\n", value);
                strcat(jsCode, jsStatement);
                i += 5;
                break;
            case TURN_RIGHT:
                value = syntaxAnalyzerOutput.tokens[i + 2].value;
                sprintf(jsStatement, "ctx.rotate((%d * Math.PI)/180)\n", value);
                strcat(jsCode, jsStatement);
                i += 5;
                break;
            case REPEAT:
                value = syntaxAnalyzerOutput.tokens[i + 2].value;
                sprintf(jsStatement, "for(let i = 0; i < %d; i++){\n", value);
                strcat(jsCode, jsStatement);
                i += 5;
                break;
            case RIGHT_BRACE:
                jsStatement = "\n}\n";
                strcat(jsCode, jsStatement);
                i++;
                break;
            case PEN_COLOR:
                r = syntaxAnalyzerOutput.tokens[i + 2].value;
                g = syntaxAnalyzerOutput.tokens[i + 4].value;
                b = syntaxAnalyzerOutput.tokens[i + 6].value;
                sprintf(jsStatement, "ctx.strokeStyle = \"rgb(%d,%d,%d)\"\n", r, g, b);
                strcat(jsCode, jsStatement);
                i += 9;
                break;
            case PEN_WIDTH:
                value = syntaxAnalyzerOutput.tokens[i + 2].value;
                sprintf(jsStatement, "ctx.lineWidth = %d\n", value);
                strcat(jsCode, jsStatement);
                i += 5;
                break;
            case PEN_STYLE:
                style = syntaxAnalyzerOutput.tokens[i + 2].lexeme;
                if (strcmp(style, "dashed") == 0) {
                    sprintf(jsStatement, "ctx.setLineDash([10,10])\n");
                } else if (strcmp(style, "dotted") == 0) {
                    printf("%s",style);
                    sprintf(jsStatement, "ctx.setLineDash([2,6])\n");
                } else {
                    sprintf(jsStatement, "ctx.setLineDash([])\n");
                }
                strcat(jsCode, jsStatement);
                i += 5;
                break;
            default:
                break;
        }
    }
    strcat(jsCode,"\nctx.rotate(Math.PI)\ndrawTurtle()\n}");
    return jsCode;
}

int main(int argc,char *argv []) {

    FILE *file;
    file = fopen("./input.txt","r");

    // Check if the file was successfully opened
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    // Determine the size of the file
    fseek(file, 0, SEEK_END);
    long long file_size = ftell(file);
    rewind(file);

    fread(input, 1, file_size, file);

    fclose(file);

    program();
    Output.status = 0;
    printf("Program parsed successfully\n");
    for (int i = 0; i < index_token - 1; i++) {
        struct token t = Output.tokens[i];
        printf("type : %d | lexeme : %s | value : %d\n", t.type, t.lexeme, t.value);
    }
    char *generatedJS = generateJS(Output);
    printf("%s",generatedJS);
    file = fopen("./output.txt","w");

    fwrite(generatedJS, strlen(generatedJS), 1, file);

    fclose(file);
    return 0;
}
