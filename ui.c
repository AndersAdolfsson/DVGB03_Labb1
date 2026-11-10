#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>

//
// Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[INPUT_BUFFER_SMALL];

	printf("input> ");
	return read_line(buf, INPUT_BUFFER_SMALL) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0)
	{
		putchar(c);
	}
	putchar('\n');
}

static void ui_print_results(const result_t *results, size_t count)
{
    printf("%12s %16s\n", "Antal", "Tid (sekunder)");
    ui_line('=', MENU_WIDTH);

    for (size_t i = 0; i < count; i++)
    {
        printf("%12d %16.9f\n", results[i].size, results[i].time);
    }

    ui_line('-', MENU_WIDTH);
	enter_continue();
}

static void ui_printMenu(const char *options[], size_t count)
{
    ui_line('=', MENU_WIDTH);

    for (size_t i = 0; i < count; i++)
    {
        printf("    %c) %s\n", 'a' + (int)i, options[i]);
    }

    ui_line('-', MENU_WIDTH);
}

//
// Public
//
void ui_run()
{
	bool running = true;
	menu_state_t menuState = main_menu;
	
	algorithm_t algorithmChoice = algo_none_t;
	case_t testcaseChoice = testcase_none_t;

	result_t result[RESULT_ROWS];

	while (running) 
	{
		switch (menuState) 
		{
			case main_menu:
			{
				algorithmChoice = algo_none_t;
				testcaseChoice = testcase_none_t;

				const char *mainMenuOptions[] = 
				{
					"Bubble sort",
					"Insertion sort",
					"Quick sort",
					"Linear search",
					"Binary search",
					"Exit\n"
				};
				ui_printMenu(mainMenuOptions, sizeof(mainMenuOptions) / sizeof(mainMenuOptions[0]));
				
				switch (ui_get_choice()) 
				{
					case 'a':
						algorithmChoice = bubble_sort_t;
						break;
					
					case 'b':
						algorithmChoice = insertion_sort_t;
						break;

					case 'c':
						algorithmChoice = quick_sort_t;
						break;

					case 'd':
						algorithmChoice = linear_search_t;
						break;

					case 'e':
						algorithmChoice = binary_search_t;
						break;

					// Exit
					case 'f':
						running = false;
						break;

					// Invalid input
					default:
						ui_invalid_input();
						break;
				}

				if(algorithmChoice != algo_none_t)
				{
					menuState = testcase_menu;
				}
					
				break;
			}

			case testcase_menu:
			{
				testcaseChoice = testcase_none_t;
				const char *testcaseMenuOptions[] = 
				{
					"Best",
					"Average",
					"Worst",
					"Back\n"
				};
				ui_printMenu(testcaseMenuOptions, sizeof(testcaseMenuOptions) / sizeof(testcaseMenuOptions[0]));

				switch (ui_get_choice())
				{
					case 'a':
						testcaseChoice = best_t;
						break;

					case 'b':
						testcaseChoice = average_t;
						break;

					case 'c':
						testcaseChoice = worst_t;
						break;

					case 'd':
						menuState = main_menu;
						break;

					default:
						ui_invalid_input();
						break;
				}

				if (testcaseChoice != testcase_none_t)
				{
					menuState = main_menu;
				}

				break;
			}

			default:
				break;
		}
		
		if(algorithmChoice != algo_none_t && testcaseChoice != testcase_none_t)
		{
			benchmark(algorithmChoice, testcaseChoice, result, RESULT_ROWS);
			ui_print_results(result, RESULT_ROWS);
		}
	}
	ui_exit();
}
