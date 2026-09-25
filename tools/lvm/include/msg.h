#ifndef MSG_
#define MSG_

typedef struct {
	int code;
	const char* text;
} msg_t;

/**
 * @brief Shows message on return code after execution.
 * @param return_code returned form any execution function from `runtime.c`
 */
void explain_return_code(int return_code,bool show_string);


#endif /* MSG_H */