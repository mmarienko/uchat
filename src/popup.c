#include "../inc/client.h"

void popup_add_chat()
{
    // create components
    add_chat_dialog = gtk_dialog_new_with_buttons("Crete new chat",
                                         GTK_WINDOW(window),
                                         GTK_DIALOG_MODAL,
                                         ("Create"),
                                         GTK_RESPONSE_OK,
                                         ("Cancel"),
                                         GTK_RESPONSE_REJECT,
                                         NULL);

    add_chat_label = gtk_label_new("Enter chat name");
    add_chat_entry = gtk_entry_new();
    add_chat_content_area = gtk_dialog_get_content_area(GTK_DIALOG(add_chat_dialog));

    // packing
    gtk_container_set_border_width(GTK_CONTAINER(add_chat_content_area), 10);
    gtk_box_pack_start(GTK_BOX(add_chat_content_area), add_chat_entry, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(add_chat_content_area), add_chat_label, TRUE, FALSE, 10);

apply_css (window, provider);
    // show all
    gtk_widget_show_all(add_chat_content_area);

    // listener
    gint result = gtk_dialog_run(GTK_DIALOG(add_chat_dialog));

    switch (result)
    {
    case GTK_RESPONSE_OK:
        add_chat(gtk_entry_get_text(GTK_ENTRY(add_chat_entry)));
        puts("ok");
        break;
    case GTK_RESPONSE_REJECT:
        puts("cancel");
        break;
    default:
        printf("%d",result);
        gtk_widget_destroy(add_chat_dialog);
        break;
    }

    // end
    
}

void popup_add_user()
{
    // create components
    add_user_dialog = gtk_dialog_new_with_buttons("Add new user",
                                         GTK_WINDOW(window),
                                         GTK_DIALOG_MODAL,
                                         ("Ok"),
                                         GTK_RESPONSE_OK,
                                         ("Cancel"),
                                         GTK_RESPONSE_REJECT,
                                         NULL);

    add_user_label = gtk_label_new("Enter nickname");
    add_user_entry = gtk_entry_new();
    add_user_content_area = gtk_dialog_get_content_area(GTK_DIALOG(add_user_dialog));

    // packing
    gtk_container_set_border_width(GTK_CONTAINER(add_user_content_area), 10);
    gtk_box_pack_start(GTK_BOX(add_user_content_area), add_user_entry, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(add_user_content_area), add_user_label, TRUE, FALSE, 10);

apply_css (window, provider);
    // show all
    gtk_widget_show_all(add_user_content_area);

    // listener
    gint result = gtk_dialog_run(GTK_DIALOG(add_user_dialog));

    switch (result)
    {
    case GTK_RESPONSE_OK:
        puts("ok");
        break;
    case GTK_RESPONSE_REJECT:
        puts("cancel");
        break;
    default:
        printf("%d",result);
        gtk_widget_destroy(add_user_dialog);
        break;
    }

}