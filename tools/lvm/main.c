#include "lvm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>


int main(int argc, char** argv)
{
	/* =====================================================================
	 * Argument Validation
	 * ===================================================================== */
	if (argc < 2) {
		fprintf(stderr, "error: no files provided\n");
		return 1;
	}


	/* =====================================================================
	 * Built-in Commands
	 * ===================================================================== */

	/* Help */
	if (strcmp(argv[1], "--help") == 0) {
		fprintf(stdout,
			"\t--- HELP ---\n\n"
			"Usage: lvm <program path> [option]\n\n"

			"Options:\n"
			"lvm  --help                 Show this help message\n"
			"lvm  --version              Print version information\n"
			"lvm  -v                     Print detailed VM specification\n"
			"lvm <program path> -e      Print the VM return code after execution\n"
			"lvm <program path> -es     Print the VM return code with its description\n"
			"lvm  -e=<code>              Explain a specific return code only. No execution.\n"
		);

		return 0;
	}


	/* Version */
	if (strcmp(argv[1], "--version") == 0) {
		fprintf(stdout, "lvm v%d.%d (%s)\n",
			LVM_VERSION_MAJOR,
			LVM_VERSION_MINOR,
			SYSTEM_ARCH);

		return 0;
	}


	/* Detailed Specification */
	if (strcmp(argv[1], "-v") == 0) {
		fprintf(stdout,
			"lvm v%d.%d.0 (%s)\n"
			"installed path: %s\n",
			LVM_VERSION_MAJOR,
			LVM_VERSION_MINOR,
			SYSTEM_ARCH,
			argv[0]);

		fprintf(stdout, "abi version: %d.0\n", ABI_VERSION);

		return 0;
	}


	/* =====================================================================
	 * Variables & Flags
	 * ===================================================================== */
	int explain_code = 0;

	bool flag_explain = false;
	bool show_string = false;
	bool only_explain = false;


	/* =====================================================================
	 * Standalone Return-Code Explanation
	 * ===================================================================== */

	/*
	 * Syntax:
	 *
	 *     lvm -e=<code>
	 *
	 * No VM execution occurs in this mode.
	 */
	if (strncmp(argv[1], "-e=", 3) == 0) {
		char *endptr;
		const char *value = argv[1] + 3;

		errno = 0;

		long val = strtol(value, &endptr, 10);

		if (value == endptr) {
			fprintf(stderr,
				"error: no digits found after -e=\n");
			return 1;
		}

		if (*endptr != '\0') {
			fprintf(stderr,
				"error: invalid characters after return code: '%s'\n",
				endptr);
			return 1;
		}

		if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
			fprintf(stderr,
				"error: return code is out of range\n");
			return 1;
		}

		explain_code = (int)val;
		only_explain = true;
		show_string = true;
	}


	/* =====================================================================
	 * Standalone Explanation
	 * ===================================================================== */
	if (only_explain) {
		explain_return_code(explain_code, show_string);
		return 0;
	}


	/* =====================================================================
	 * Program Execution Flags
	 * ===================================================================== */

	if (argc >= 3) {
		if (strcmp(argv[2], "-e") == 0) {
			flag_explain = true;
		}
		else if (strcmp(argv[2], "-es") == 0) {
			flag_explain = true;
			show_string = true;
		}
		else {
			fprintf(stderr,
				"error: unknown option '%s'\n",
				argv[2]);
			return 1;
		}
	}

	/* Reject extra arguments */
	if (argc > 3) {
		fprintf(stderr,
			"error: too many arguments\n"
			"usage: lvm <program path> [option]\n");
		return 1;
	}


	/* =====================================================================
	 * Core VM Execution
	 * ===================================================================== */

	lbf_file file;
	init_lbf_file(&file);

	lvm_instance_t instance = create_instance();


	/* Load program */
	if (!load_lbf_file(&file, argv[1])) {
		goto cleanup;
	}


	/* Setup VM instance */
	if (!setup_instance(&instance, &file)) {
		goto cleanup;
	}


	/* =====================================================================
	 * Run VM
	 * ===================================================================== */

	explain_code = run_instance(&instance);


	/* Show return-code information */
	if (flag_explain) {
		explain_return_code(explain_code, show_string);
	}


	/* =====================================================================
	 * Cleanup
	 * ===================================================================== */

cleanup:
	destroy_instance(&instance);
	free_lbf_file(&file);

	return 0;
}

