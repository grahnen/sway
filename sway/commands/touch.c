#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "sway/commands.h"
#include "sway/config.h"
#include "sway/ipc-server.h"
#include "list.h"
#include "log.h"
#include "stringop.h"
#include <libtouch.h>

// Must be in alphabetical order for bsearch
static struct cmd_handler touch_handlers[] = {
	{ "binding", touch_cmd_binding },
	{ "gesture", touch_cmd_gesture },
};


struct cmd_results *cmd_touch(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "touch", EXPECTED_AT_LEAST, 2))) {
		return error;
	}
	
	if(!config->gesture_engine) {
		config->gesture_engine = libtouch_engine_create();
		sway_log(SWAY_DEBUG, "Created a new gesture engine");
	}
	struct cmd_handler *cmd = find_handler(argv[0], touch_handlers, sizeof(touch_handlers));
	if( cmd ) {
		return config_subcommand(argv, argc, touch_handlers, sizeof(touch_handlers));	
	}
	return cmd_results_new(CMD_FAILURE,
			       "Invalid subcommand: %s",
			       argv[0]);
		
	
};