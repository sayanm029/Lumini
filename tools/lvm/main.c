#include "lvm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,char** argv) {
	if(argc < 2) {
		fprintf(stdout,"error: no files provided\n");
		return 0;
	}
	/* Help */
	if(strcmp(argv[1],"--help") == 0) {
		fprintf(stdout,"\t--- HELP ---\n\n");
		fprintf(stdout,"usage: lvm <porgram path>\n");
		fprintf(stdout,"--version\tprints version information\n");
		fprintf(stdout,"-v\tprints detailed specification\n");
		return 0;
	}
	/* Version */
	if(strcmp(argv[1],"--version") == 0) {
		fprintf(stdout,"lvm v%d.%d (%s)\n",LVM_VERSION_MAJOR,LVM_VERSION_MINOR,SYSTEM_ARCH);
		return 0;
	}
	/* Detailed Specification */
	if(strcmp(argv[1],"-v") == 0) {
		fprintf(stdout,"lvm v%d.%d.0 (%s)\ninstalled path: %s\n",LVM_VERSION_MAJOR,LVM_VERSION_MINOR,SYSTEM_ARCH,argv[0]);
		fprintf(stdout,"abi version: %d.0\n",ABI_VERSION);
		return 0;
	}

	lbf_file file;
	init_lbf_file(&file);
	lvm_instance_t instance = create_instance();

	/* Setup Instance for execution. */
	if(!load_lbf_file(&file,argv[2])) {return 1;}
	if(!setup_instance(&instance,&file)) {return 1;}

	/* Run Instance & show message on return */
	int return_code = run_instance(&instance);
	show_message_on_return(return_code);

	/* Free Allocated Memory. */
	destroy_instance(&instance);
	free_lbf_file(&file);
	return 0;
}