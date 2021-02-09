#include "../inc/client.h"

void add_chat(const gchar *title, gpointer data)
{
    // create components
    GtkWidget *stack = (GtkWidget *)data;
    GtkWidget *label = gtk_label_new(title);
    gtk_stack_add_named(GTK_STACK(stack), label, title);
    gtk_container_child_set(GTK_CONTAINER(stack), label, "title", title, NULL);

    // show all
    gtk_widget_show_all(stack);
}

void add_chat_window(GtkWidget *button, gpointer data)
{
    // create components
    popup_dialog = gtk_dialog_new_with_buttons("Crete new chat",
                                         GTK_WINDOW(window),
                                         GTK_DIALOG_MODAL,
                                         ("Create"),
                                         GTK_RESPONSE_OK,
                                         ("Cancel"),
                                         GTK_RESPONSE_REJECT,
                                         NULL);

    popup_label = gtk_label_new("Enter chat name");
    popup_entry = gtk_entry_new();
    popup_content_area = gtk_dialog_get_content_area(GTK_DIALOG(popup_dialog));

    // packing
    gtk_container_set_border_width(GTK_CONTAINER(popup_content_area), 10);
    gtk_box_pack_start(GTK_BOX(popup_content_area), popup_entry, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(popup_content_area), popup_label, TRUE, FALSE, 10);

    //show all
    gtk_widget_show_all(popup_content_area);

    //listener
    gint result = gtk_dialog_run(GTK_DIALOG(popup_dialog));

    switch (result)
    {
    case GTK_RESPONSE_OK:
        add_chat(gtk_entry_get_text(GTK_ENTRY(popup_entry)), (GtkWidget *)data);
        puts("ok");
        break;
    case GTK_RESPONSE_REJECT:
        puts("cancel");
        break;
    default:
        printf("%d",result);
        break;
    }

    //end
    gtk_widget_destroy(popup_dialog);
}

void init_chat(GtkWidget *button, gpointer data)
{
  // change window
  window = (GtkWidget *)data;
  gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(window)));
  gtk_window_resize(GTK_WINDOW(window), 600, 400);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
  gtk_container_set_border_width(GTK_CONTAINER(window), 0);

  // sidebar init
  chat_sidebar = gtk_stack_sidebar_new();
  chat_stack = gtk_stack_new();
  chat_separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
  chat_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  chat_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  chat_message_entry = gtk_entry_new();

  gtk_stack_set_transition_type(GTK_STACK(chat_stack), GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
  gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(chat_sidebar), GTK_STACK(chat_stack));

  chat_add_button = gtk_button_new_with_label("Add chat");
  chat_message_button = gtk_button_new_with_label("Send"); // not implemented

  g_signal_connect(G_OBJECT(chat_add_button), "clicked", G_CALLBACK(add_chat_window), chat_stack);

  // packing
  gtk_box_pack_start(GTK_BOX(chat_vbox), chat_sidebar, TRUE, TRUE, 0);
  gtk_box_pack_end(GTK_BOX(chat_vbox), chat_add_button, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(chat_hbox), chat_vbox, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(chat_hbox), chat_separator, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(chat_hbox), chat_stack, TRUE, TRUE, 0);

  // code
  add_chat("roma lox", chat_stack);

  // END
  gtk_container_add(GTK_CONTAINER(window), chat_hbox);
  gtk_widget_show_all(window);
}
