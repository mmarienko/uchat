#include "../inc/client.h"

void check_username(GtkWidget *button, gpointer data)
{
    const gchar *username = gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
    printf("%s\n", username);
}

void check_password(GtkWidget *button, gpointer data)
{
    const gchar *password = gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
    printf("%s\n", password);
}

void init_authorization()
{
  // WINDOW
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "UCHAT");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  g_signal_connect(G_OBJECT(window), "destroy", gtk_main_quit, NULL);

  // LOGIN

  // login labels
  log_username_label = gtk_label_new("Login: ");
  log_password_label = gtk_label_new("Password: ");
  log_error_label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(log_error_label), "<span foreground='#ff0000'>error</span>");
  gtk_label_set_width_chars(GTK_LABEL(log_username_label), 12);
  gtk_label_set_width_chars(GTK_LABEL(log_password_label), 12);
  gtk_label_set_width_chars(GTK_LABEL(log_error_label), 12);

  // login entry
  log_username_entry = gtk_entry_new();
  log_password_entry = gtk_entry_new();
  gtk_entry_set_visibility(GTK_ENTRY(log_password_entry), FALSE);

  // login actions
  log_ok_button = gtk_button_new_with_label("OK");

  g_signal_connect(G_OBJECT(log_ok_button), "clicked", G_CALLBACK(check_username), log_username_entry);
  g_signal_connect(G_OBJECT(log_ok_button), "clicked", G_CALLBACK(check_password), log_password_entry);
  g_signal_connect(G_OBJECT(log_ok_button), "clicked", G_CALLBACK(init_chat), NULL);

  // login packing
  log_hbox_username = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  log_hbox_password = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  log_hbox_error = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  log_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  gtk_box_pack_start(GTK_BOX(log_hbox_username), log_username_label, TRUE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(log_hbox_username), log_username_entry, TRUE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(log_hbox_password), log_password_label, TRUE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(log_hbox_password), log_password_entry, TRUE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(log_hbox_error), log_error_label, TRUE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(log_vbox), log_hbox_username, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(log_vbox), log_hbox_password, FALSE, FALSE, 5);
  gtk_box_pack_end(GTK_BOX(log_vbox), log_ok_button, FALSE, FALSE, 5);
  gtk_box_pack_end(GTK_BOX(log_vbox), log_hbox_error, FALSE, FALSE, 5);

  // REGISTRATION

  // reg labels
  reg_username_label = gtk_label_new("Login: ");
  reg_password_label = gtk_label_new("Password: ");
  reg_password_label_repeat = gtk_label_new("Repeat: ");
  reg_error_label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(reg_error_label), "<span foreground='#ff0000'>error</span>");
  gtk_label_set_width_chars(GTK_LABEL(reg_username_label), 12);
  gtk_label_set_width_chars(GTK_LABEL(reg_password_label), 12);
  gtk_label_set_width_chars(GTK_LABEL(reg_password_label_repeat), 12);
  gtk_label_set_width_chars(GTK_LABEL(reg_error_label), 12);

  // reg entry
  reg_username_entry = gtk_entry_new();
  reg_password_entry = gtk_entry_new();
  reg_password_entry_repeat = gtk_entry_new();
  gtk_entry_set_visibility(GTK_ENTRY(reg_password_entry), FALSE);
  gtk_entry_set_visibility(GTK_ENTRY(reg_password_entry_repeat), FALSE);

  // reg actions
  reg_ok_button = gtk_button_new_with_label("OK");

  g_signal_connect(G_OBJECT(reg_ok_button), "clicked", G_CALLBACK(check_username), reg_username_entry);
  g_signal_connect(G_OBJECT(reg_ok_button), "clicked", G_CALLBACK(check_password), reg_password_entry);
  g_signal_connect(G_OBJECT(reg_ok_button), "clicked", G_CALLBACK(check_password), reg_password_entry_repeat);
  g_signal_connect(G_OBJECT(reg_ok_button), "clicked", G_CALLBACK(init_chat), NULL);

  // reg packing
  reg_hbox_username = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  reg_hbox_password = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  reg_hbox_password_repeat = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  reg_hbox_error = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  reg_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  gtk_box_pack_start(GTK_BOX(reg_hbox_username), reg_username_label, TRUE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(reg_hbox_username), reg_username_entry, TRUE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(reg_hbox_password), reg_password_label, TRUE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(reg_hbox_password), reg_password_entry, TRUE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(reg_hbox_password_repeat), reg_password_label_repeat, TRUE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(reg_hbox_password_repeat), reg_password_entry_repeat, TRUE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(reg_hbox_error), reg_error_label, TRUE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(reg_vbox), reg_hbox_username, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(reg_vbox), reg_hbox_password, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(reg_vbox), reg_hbox_password_repeat, FALSE, FALSE, 5);
  gtk_box_pack_end(GTK_BOX(reg_vbox), reg_ok_button, FALSE, FALSE, 5);
  gtk_box_pack_end(GTK_BOX(reg_vbox), reg_hbox_error, FALSE, FALSE, 5);

  // SWITCHER

  // switcher init
  authorization_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
  authorization_stack = gtk_stack_new();
  authorization_switcher = gtk_stack_switcher_new();

  gtk_stack_add_titled(GTK_STACK(authorization_stack), log_vbox, "Authorization", "Authorization");
  gtk_stack_add_titled(GTK_STACK(authorization_stack), reg_vbox, "Registration", "Registration");

  // switcher packing
  gtk_widget_set_halign(authorization_switcher, GTK_ALIGN_CENTER);

  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(authorization_switcher), GTK_STACK(authorization_stack));
  gtk_box_pack_start(GTK_BOX(authorization_box), authorization_switcher, FALSE, FALSE, 6);
  gtk_box_pack_start(GTK_BOX(authorization_box), authorization_stack, TRUE, TRUE, 6);

  // END
  gtk_container_add(GTK_CONTAINER(window), authorization_box);

  gtk_widget_show_all(window);
}
