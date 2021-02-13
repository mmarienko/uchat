#include "../inc/client.h"

void apply_css(GtkWidget *widget, GtkStyleProvider *provider) {
  gtk_style_context_add_provider (gtk_widget_get_style_context (widget), provider, G_MAXUINT);
  if (GTK_IS_CONTAINER (widget))
    gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, provider);
}

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
  gtk_window_set_default_size(GTK_WINDOW(window), 200,300);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  g_signal_connect(G_OBJECT(window), "destroy", gtk_main_quit, NULL);

  // LOGIN

  // login labels
  log_error_label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(log_error_label), "<span foreground='#E61B58'></span>");
  gtk_label_set_width_chars(GTK_LABEL(log_error_label), 12);

  // login entry
  log_username_entry = gtk_entry_new();
  gtk_entry_set_placeholder_text (GTK_ENTRY(log_username_entry), "Login");
  log_password_entry = gtk_entry_new();
  gtk_entry_set_placeholder_text (GTK_ENTRY(log_password_entry), "Password");
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

  log_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  gtk_box_pack_start(GTK_BOX(log_hbox_username), log_username_entry, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(log_hbox_password), log_password_entry, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(log_hbox_error), log_error_label, TRUE, TRUE, 5);

  gtk_box_pack_start(GTK_BOX(log_vbox), log_hbox_username, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(log_vbox), log_hbox_password, FALSE, TRUE, 5);
  gtk_box_pack_end(GTK_BOX(log_vbox), log_ok_button, FALSE, TRUE, 0);
  gtk_box_pack_end(GTK_BOX(log_vbox), log_hbox_error, FALSE, TRUE, 5);

  // REGISTRATION

  // reg labels
  reg_error_label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(reg_error_label), "<span foreground='#ff0000'></span>");
  gtk_label_set_width_chars(GTK_LABEL(reg_error_label), 12);

  // reg entry
  reg_username_entry = gtk_entry_new();
  gtk_entry_set_placeholder_text (GTK_ENTRY(reg_username_entry), "Login");
  reg_password_entry = gtk_entry_new();
  gtk_entry_set_placeholder_text (GTK_ENTRY(reg_password_entry), "Password");
  reg_password_entry_repeat = gtk_entry_new();
  gtk_entry_set_placeholder_text (GTK_ENTRY(reg_password_entry_repeat), "Repeat Password");
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

  reg_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  gtk_box_pack_start(GTK_BOX(reg_hbox_username), reg_username_entry, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(reg_hbox_password), reg_password_entry, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(reg_hbox_password_repeat), reg_password_entry_repeat, TRUE, TRUE, 5);

  gtk_box_pack_start(GTK_BOX(reg_hbox_error), reg_error_label, TRUE, TRUE, 5);

  gtk_box_pack_start(GTK_BOX(reg_vbox), reg_hbox_username, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(reg_vbox), reg_hbox_password, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(reg_vbox), reg_hbox_password_repeat, FALSE, TRUE, 5);
  gtk_box_pack_end(GTK_BOX(reg_vbox), reg_ok_button, FALSE, TRUE, 0);
  gtk_box_pack_end(GTK_BOX(reg_vbox), reg_hbox_error, FALSE, TRUE, 5);

  // SWITCHER

  // switcher init
  authorization_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  authorization_stack = gtk_stack_new();
  authorization_switcher = gtk_stack_switcher_new();

  gtk_stack_add_titled(GTK_STACK(authorization_stack), log_vbox, "SIGN IN", "SIGN IN");
  gtk_stack_add_titled(GTK_STACK(authorization_stack), reg_vbox, "SIGN UP", "SIGN UP");

  // switcher packing
  gtk_widget_set_halign(authorization_switcher, GTK_ALIGN_CENTER);

  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(authorization_switcher), GTK_STACK(authorization_stack));
  gtk_box_pack_start(GTK_BOX(authorization_box), authorization_switcher, TRUE, FALSE, 6);
  gtk_box_pack_start(GTK_BOX(authorization_box), authorization_stack, TRUE, TRUE, 6);

  gtk_container_add(GTK_CONTAINER(window), authorization_box);

  // style.css
  context = gtk_widget_get_style_context(window);
  provider = GTK_STYLE_PROVIDER(gtk_css_provider_new ());

  gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider), "./src/style.css", NULL);
  apply_css (window, provider);

  // END
  gtk_widget_show_all(window);
}
