#pragma once

#include "../app.h"
#include "rooms.h"

enum Menus {
    main, // main_menu
    rooms, // rooms_menu
    bookings, // bookings_menu
    view_rooms, // view_rooms_menu
    add_room, // add_room_menu
    all_rooms, // all_rooms_menu
    filter, // filter_menu
    filter_name, // filter_name_menu
    filter_capacity, // filter_capacity_menu
    filter_availability // filter_availability_menu
};

#define ID_MAIN_MENU_ROOMS 0
#define ID_MAIN_MENU_BOOKINGS 1
menu main_menu();

#define ID_ROOMS_MENU_VIEW 0
#define ID_ROOMS_MENU_ADD 1
menu rooms_menu();

menu bookings_menu();

#define ID_VIEW_ROOMS_MENU_ALL_ROOMS 0
#define ID_VIEW_ROOMS_MENU_FILTER 1
menu view_rooms_menu();

menu add_room_menu();

menu all_rooms_menu();

#define ID_FILTER_MENU_FILTER_NAME 0
#define ID_FILTER_MENU_FILTER_CAPACITY 1
#define ID_FILTER_MENU_FILTER_AVAILABILITY 2
#define ID_FILTER_MENU_APPLY 3
menu filter_menu();

menu filter_name_menu();

menu filter_capacity_menu();

menu filter_availability_menu();
