#pragma once

#include "../app.h"
#include "trains.h"

enum Menus {
    app5, // app5_menu
    trains_main, // trains_main_menu
    trains_view, // trains_view_menu
    //trains_add,
    trains_available, // trains_available_menu
    trains_filter, // trains_filter_menu
    //trains_filter_id,
    trains_info, // trains_info_menu
    trains_wagons, // trains_wagons_menu
    trains_wagons_info, // trains_wagons_info_menu
    wagons_main, // wagons_menu
    wagons_view, // wagons_view_menu
    //wagons_add,
    wagons_available, // wagons_available_menu
    wagons_filter, // wagons_filter_menu
    //wagons_filter_id,
    //wagons_filter_type,
    wagons_info, // wagons_info_menu
    wagons_couple, // wagons_couple_menu
};

#define ID_MAIN_MENU_TRAINS 0
#define ID_MAIN_MENU_WAGONS 1
menu app5_menu();

#define ID_TRAINS_MENU_VIEW 0
#define ID_TRAINS_MENU_ADD 1
menu trains_main_menu();

#define ID_TRAINS_VIEW_MENU_ALL 0
#define ID_TRAINS_VIEW_MENU_FILTER 1
menu trains_view_menu();

void trains_add_screen();

menu trains_available_menu(train_array available);

#define ID_TRAINS_FILTER_MENU_ID 0
#define ID_TRAINS_FILTER_MENU_APPLY 1
menu trains_filter_menu();

void trains_filter_id_screen();

#define ID_TRAINS_INFO_MENU_DELETE 0
#define ID_TRAINS_INFO_MENU_WAGONS 1
menu trains_info_menu(train t);

menu trains_wagons_menu(train t);

#define ID_TRAINS_WAGONS_INFO_MENU_DECOUPLE 0
menu trains_wagons_info_menu(coupled_wagon cw);

#define ID_WAGONS_MENU_VIEW 0
#define ID_WAGONS_MENU_ADD 1
menu wagons_main_menu();

#define ID_WAGONS_VIEW_MENU_ALL 0
#define ID_WAGONS_VIEW_MENU_FILTER 1
menu wagons_view_menu();

void wagons_add_screen();

menu wagons_available_menu(wagon_array available);

#define ID_WAGONS_FILTER_MENU_ID 0
#define ID_WAGONS_FILTER_MENU_TYPE 1
#define ID_WAGONS_FILTER_MENU_APPLY 2
menu wagons_filter_menu();

void wagons_filter_id_screen();

void wagons_filter_type_screen();

#define ID_WAGONS_INFO_MENU_DELETE 0
#define ID_WAGONS_INFO_MENU_COUPLE 1
menu wagons_info_menu(wagon w);

menu wagons_couple_menu(wagon w);
