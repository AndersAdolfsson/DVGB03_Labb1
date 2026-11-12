#include "ui.h"
#include "debug.h"

#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	for(int i = 1; i<argc; i++)
	{
		if(strcmp(argv[i], "-debug") == 0)
		{
			debug_set_enabled(true);
		}
	}

	ui_run();
	return 0;
}
