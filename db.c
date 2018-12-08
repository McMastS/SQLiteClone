#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>

enum StatementType_t {
	STATEMENT_INSERT,
	STATEMENT_SELECT
};
typedef enum StatementType_t StatementType;

struct InputBuffer_t 
{
	char* buffer;         
	size_t buffer_length;
	ssize_t input_length; // may return an error value, therefore a signed int must be used
};
typedef struct InputBuffer_t InputBuffer;

struct Statement_t {
	StatementType type;
};
typedef struct Statement_t Statement;

InputBuffer* new_input_buffer() {
	InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
	input_buffer->buffer = NULL;
	input_buffer->buffer_length = 0;
	input_buffer->input_length = 0;

	return input_buffer;
}

void print_prompt() 
{
	printf("sqlite> ");
}

void read_input(InputBuffer* input_buffer)
{
	ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

	if (bytes_read <= 0) {
		printf("Error reading input.\n");
		exit(EXIT_FAILURE);
	}

	// Ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void handle_meta_command(InputBuffer* input_buffer)
{
	if (strcmp(input_buffer->buffer, ".exit") == 0) {
		printf("Exiting. Have a nice day!\n");
		exit(EXIT_SUCCESS);
	} else if (strcmp(input_buffer->buffer, ".help") == 0) {
		printf("Enter .exit to leave.\n");
		printf("Enter insert or select to not actually do anything useful.\n");
    } else {
		printf("Unrecognized meta command.\n");
	}
}

void prepare_SQL(InputBuffer* input_buffer, Statement* statement) 
{
	if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
		statement->type = STATEMENT_INSERT;
		printf("I'm pretending to insert!\n");
		printf("Insertion successful!\n");
	} else if (strncmp(input_buffer->buffer, "select", 6) == 0) {
		statement->type = STATEMENT_SELECT;
		printf("I'm pretending to select!\n");
		printf("Select successful!\n");
	} else {
		printf("Unrecognized command %s\n", input_buffer->buffer);
	}
}

void execute_SQL() {

}

int main() 
{
	printf("Spencer's Custom Database Version 0.2\n");
	printf("Enter .help for instructions\n");

	InputBuffer* input_buffer = new_input_buffer();
	while (1) {
		print_prompt();
		read_input(input_buffer);

		Statement statement;
		if (input_buffer->buffer[0] == '.') {
			handle_meta_command(input_buffer);
		} else {
			prepare_SQL(input_buffer, &statement);
		}
	}
}