#include "msg.h"
#include "retcode.h"

#include <stdio.h>
#include <stddef.h>

static msg_t message[] = {
	{RC_SUCCESS,                 nullptr},
	{RC_PROGRAM_HALTED,          "Message (0x1): Program Halted."},
	{RC_E_DIV_BY_ZERO,           "Error (0x2): Division by Zero"},
	{RC_E_INTEGER_OVERFLOW,      "Error (0x3): Integer overflow"},
	{RC_E_FPU_DOMAIN,            "Error (0x4): Invalid floating-point operation"},
	{RC_E_ILLEGAL_OPCODE,        "Error (0x5): Illegal Opcode"},
	{RC_E_JMP_MISALIGNED,        "Error (0x6): Jump Misaligned"},
	{RC_E_BRANCH_OUT_OF_BOUNDS,  "Error (0x7): Branch Out of Bounds"},
	{RC_E_INVALID_CAST,          "Error (0x8): OP_CNV failed due to incompatible types or corrupted values"},
	{RC_E_SEGFAULT,              "Error (0x10): Invalid heap access (Load/Store outside VM RAM limits)"},
	{RC_E_BUS_ALIGNMENT,         "Error (0x11): Unaligned Memory Access"},
	{RC_E_BAD_ADDRESS,           "Error (0x12): Pointer provided to a syscall points to invalid heap address"},
	{RC_E_BUFFER_OVERFLOW,       "Error (0x13): Read/Write buffer boundaries exceed valid heap space limits"},
	{RC_E_STACK_OVERFLOW,        "Error (0x14): [Stack overflow] Call stack exceeded maximum capacity"},
	{RC_E_STACK_UNDERFLOW,       "Error (0x15): [Stack Underflow] Unmatched OP_RET executed with an empty call stack"},
	{RC_E_STRING_OVERFLOW,       "Error (0x16): String Length exeeds limits"},
	{RC_E_PERMISSION_DENIED,     "Error (0x20): Operation not permitted or file is read-only"},
	{RC_E_FILE_NOT_FOUND,        "Error (0x21): The requested file path string does not exist."},
	{RC_E_BAD_DESCRIPTOR,        "Error (0x22): The register does not contain a valid open file descriptor"},
	{RC_E_INVALID_ARGUMENT,       "Error (0x23): Invalid Arguments"},
	{RC_E_INVALID_IO_TYPE,        "Error (0x24): Invalid Input/Output Request"},
	{RC_E_INVALID_SEEK,           "Error (0x25): Invalid Seek - Unrecognized seek origin or Offset Occured."},
	{RC_E_TOO_MANY_OPEN_FILES,    "Error (0x26): Exeeded Total limit of open files"},
	{RC_E_NO_SPACE_LEFT,          "Error (0x27): Storage media or virtual disk partition is full"},
	{RC_E_FILE_EXISTS,            "Error (0x28): Attempt to recreate a already existing file"},
	{RC_E_IO_FAILURE,             "Error (0x29): Host System file I/O failed."}
};

#define MESSAGE_COUNT (sizeof(message) / sizeof(message[0]))

static const msg_t *find_message(int return_code)
{
	size_t left = 0;
	size_t right = MESSAGE_COUNT;

	while (left < right) {
		size_t mid = left + (right - left) / 2;

		if (message[mid].code == return_code)
			return &message[mid];

		if (message[mid].code < return_code)
			left = mid + 1;
		else
			right = mid;
	}

	return nullptr;
}

void explain_return_code(int return_code,bool show_string) {


	if(!show_string) {
		if(return_code < 2) {
			printf("\nCode: %d\n",return_code);
		}
		printf("\nError: %d\n",return_code);

		return;
	}

	const msg_t *msg = find_message(return_code);

	if (msg == nullptr)
		return;

	if (msg->text != nullptr)
		printf("%s\n", msg->text);
}