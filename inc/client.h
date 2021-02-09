#pragma once

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

// functions
void init_authorization(void);
void init_chat(GtkWidget *button, gpointer data);

// Global window
GtkWidget *window;

// Authorization
GtkWidget *authorization_box;
GtkWidget *authorization_stack;
GtkWidget *authorization_switcher;

GtkWidget *log_username_label, *log_password_label, *log_error_label;
GtkWidget *log_username_entry, *log_password_entry;
GtkWidget *log_ok_button;
GtkWidget *log_hbox_username, *log_hbox_password, *log_hbox_error;
GtkWidget *log_vbox;

GtkWidget *reg_username_label, *reg_password_label, *reg_password_label_repeat, *reg_error_label;
GtkWidget *reg_username_entry, *reg_password_entry, *reg_password_entry_repeat;
GtkWidget *reg_ok_button;
GtkWidget *reg_hbox_username, *reg_hbox_password, *reg_hbox_password_repeat, *reg_hbox_error;
GtkWidget *reg_vbox;

// chat
GtkWidget *chat_sidebar;
GtkWidget *chat_stack;
GtkWidget *chat_hbox, *chat_vbox;
GtkWidget *chat_separator;
GtkWidget *chat_message_entry;
GtkWidget *chat_add_button, *chat_message_button;

// popup add_chat
GtkWidget *popup_dialog;
GtkWidget *popup_label;
GtkWidget *popup_entry;
GtkWidget *popup_content_area;