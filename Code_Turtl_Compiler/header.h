//
// Created by WALID on 09/02/2023.
//

#ifndef COMPILATION_HEADER_H

enum TOKEN_TYPE;

//parse command
void command();

//parse_next_token
void get_next_token();

//generate_error
void error(char* message);

//matches_current_token
void match(enum TOKEN_TYPE expected_type);

//parsers_of_grammar
void program();
void program_list();
void movement_to_command();
void movement_command();
void loop_command();
void rotation_command();


#define  TOKEN_CAP 200

#define COMPILATION_HEADER_H

#endif //COMPILATION_HEADER_H
