/*
#2. System for keeping track of books in a library

The system allows to store the data of the books in a library.
App user can add books by specifying title, author, type, location,
search and display books by title, author and availability, borrow
books for a number of days (10 days) and return borrowed books.
Use the file manipulation mechanism to retrieve/save data from/to
the file. Also use data structures for information read from the file.
*/

#include "main.h"

int p2_main() {
    clear_screen();
    
    option options[] = {
        new_option_builder()
                .name("           ")
                .separator()
                .build(),
        new_option_builder()
                .name("yes")
                .build(),
        new_option_builder()
                .name("           ")
                .separator()
                .build(),
        new_option_builder()
                .name("no")
                .build(),
        new_option_builder()
                .name("           ")
                .separator()
                .build(),
    };
    option opt = hmenu(sizeof(options) / sizeof(option), options);

    pause_console();

    return 0;
}