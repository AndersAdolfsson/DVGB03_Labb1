#ifndef UI_H
#define UI_H

#define MENU_WIDTH 40
#define RESULT_ROWS 6
#define INPUT_BUFFER_SMALL 3

// algorithm_t defines different algorithms
typedef enum
{
	main_menu,
	testcase_menu
} menu_state_t;

// ui_run starts a terminal-based user interface
void ui_run();

#endif
