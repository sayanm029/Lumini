#include "lvm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv)
{
	/* =====================================================================
	 * Argument Validation
	 * ===================================================================== */
	if (argc < 2) {
		fprintf(stdout, "error: no files provided\n");
		return 0;
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
			"lvm  --help       			Show this help message\n"
			"lvm  --version    			Print version information\n"
			"lvm  -v           			Print detailed VM specification\n"
			"lvm <program path>  -e     Print the VM return code after execution\n"
			"lvm <program path>  -es    Print the VM return code with its description\n"
			"lvm  -e=<code>    			Explain a specific return code only. No execution.\n"
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
		fprintf(stdout, "lvm v%d.%d.0 (%s)\n"
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
	int explain_code;

	bool flag_explain = false;
	bool show_string = false;
	bool only_explain = false;


	/* =====================================================================
	 * Command-Line Flag Parsing
	 * ===================================================================== */

	/* Explain return code directly: -e=<code> */
	if (argc >= 2) {
		if (strncmp(argv[1], "-e=", 3) == 0) {
			char *endptr;

			errno = 0;

			long val = strtol(argv[2] + 3, &endptr, 10);

			/* Validate parsed value */
			if (endptr == argv[2] + 3) {
				fprintf(stderr,
					"Error: No digits found after -e=\n");

			} else if (*endptr != '\0') {
				fprintf(stderr,
					"Error: Trailing garbage characters found: '%s'\n",
					endptr);

			} else if ((val == LONG_MIN || val == LONG_MAX)
				   && errno == ERANGE) {
				fprintf(stderr,
					"Error: Value out of range for a long integer\n");

			} else if (val < INT_MIN || val > INT_MAX) {
				fprintf(stderr,
					"Error: Value out of range for a standard integer\n");

			} else {
				explain_code = (int)val;
				only_explain = true;
				show_string = true;
			}
		}
	}


	/* Program execution flags */
	if (argc >= 3) {

		/* Print return code */
		if (strcmp(argv[2], "-e") == 0) {
			flag_explain = true;
		}

		/* Explain return code with string */
		else if (strcmp(argv[2], "-es") == 0) {
			show_string = true;
		}
	}


	/* =====================================================================
	 * Standalone Return-Code Explanation
	 * ===================================================================== */
	if (only_explain) {
		explain_return_code(explain_code, show_string);
		return 0;
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