#include "../inc/client.h"

void auto_scroll()
{
    GtkAdjustment *vadjustment;
    vadjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(chat_text_scrolled_window));

    gtk_adjustment_set_value(vadjustment, (gtk_adjustment_get_upper(vadjustment) - gtk_adjustment_get_page_size(vadjustment)));
}

int send_message_key(GtkWidget *widget, GdkEventKey *event, GtkTextBuffer *buffer)
{
    if (event->keyval == GDK_KEY_KP_Enter || event->keyval == GDK_KEY_Return)
    {
        GtkTextIter iter;
        GtkTextMark *cursor;

        const gchar *text = gtk_entry_get_text(GTK_ENTRY(widget));

        cursor = gtk_text_buffer_get_mark(buffer, "insert");
        gtk_text_buffer_get_iter_at_mark(buffer, &iter, cursor);
        gtk_text_iter_forward_to_end(&iter);
        gtk_text_buffer_place_cursor(buffer, &iter);
        gtk_text_buffer_insert(buffer, &iter, text, -1);
        gtk_text_buffer_insert(buffer, &iter, "\n\n", -1);
        gtk_entry_set_text(GTK_ENTRY(widget), "");

        auto_scroll();
    }

    return FALSE;
}

void send_message_btn(GtkWidget *widget, GtkTextBuffer *buffer)
{
    GtkTextIter iter;
    GtkTextMark *cursor;

    const gchar *text = gtk_entry_get_text(GTK_ENTRY(chat_text_entry));

    if (strcmp(text, "") == 0) {
        return;
    }

    cursor = gtk_text_buffer_get_mark(buffer, "insert");
    gtk_text_buffer_get_iter_at_mark(buffer, &iter, cursor);
    gtk_text_iter_forward_to_end(&iter);
    gtk_text_buffer_place_cursor(buffer, &iter);
    gtk_text_buffer_insert(buffer, &iter, text, -1);
    gtk_text_buffer_insert(buffer, &iter, "\n\n", -1);
    gtk_entry_set_text(GTK_ENTRY(chat_text_entry), "");

    auto_scroll();
}

void add_chat(const gchar *title)
{
    // create components
    chat_text_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    chat_text_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    chat_text_top_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    context = gtk_widget_get_style_context(chat_text_hbox);
    gtk_style_context_add_class(context,"chat_text_hbox");

    chat_text_label_top = gtk_label_new(title);
    context = gtk_widget_get_style_context(chat_text_label_top);
    gtk_style_context_add_class(context,"chat_text_label_top");
    chat_text_area = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(chat_text_area), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(chat_text_area), FALSE);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(chat_text_area), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(chat_text_area), 10);
    gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(chat_text_area), 10);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(chat_text_area), 10);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(chat_text_area), GTK_WRAP_WORD);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat_text_area));
    chat_text_scrolled_window = gtk_scrolled_window_new(NULL, NULL);

    chat_text_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text (GTK_ENTRY(chat_text_entry), "Write a message");
    chat_text_add_button = gtk_button_new_with_label(" ");
    context = gtk_widget_get_style_context(chat_text_add_button);
    gtk_style_context_add_class(context,"chat_text_add_button");

    chat_text_send_button = gtk_button_new_with_label("Send");

    g_signal_connect(G_OBJECT(chat_text_add_button), "clicked", G_CALLBACK(popup_add_user), NULL);
    g_signal_connect(G_OBJECT(chat_text_send_button), "clicked", G_CALLBACK(send_message_btn), buffer);
    g_signal_connect(G_OBJECT(chat_text_entry), "key-press-event", G_CALLBACK(send_message_key), buffer);

    // packing
    gtk_container_add(GTK_CONTAINER(chat_text_scrolled_window), chat_text_area);

    gtk_box_pack_start(GTK_BOX(chat_text_top_hbox), chat_text_label_top, FALSE, FALSE, 10);
    gtk_box_pack_end(GTK_BOX(chat_text_top_hbox), chat_text_add_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chat_text_vbox), chat_text_top_hbox, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chat_text_vbox), chat_text_scrolled_window, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat_text_hbox), chat_text_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(chat_text_hbox), chat_text_send_button, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(chat_text_vbox), chat_text_hbox, FALSE, FALSE, 0);

    gtk_stack_add_named(GTK_STACK(chat_stack), chat_text_vbox, title);
    gtk_container_child_set(GTK_CONTAINER(chat_stack), chat_text_vbox, "title", title, NULL);

    // style 
    apply_css (window, provider);

    // show all
    gtk_widget_show_all(chat_stack);
}

void init_chat()
{
    // change window
    gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(window)));
    gtk_window_resize(GTK_WINDOW(window), 980, 620);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    // sidebar init
    chat_label_top = gtk_label_new(" YOUR CHATS ");
    context = gtk_widget_get_style_context(chat_label_top);
    gtk_style_context_add_class(context,"chat_label_top");
    chat_sidebar = gtk_stack_sidebar_new();
    chat_stack = gtk_stack_new();
    //chat_separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    chat_top_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    chat_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    chat_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // gtk_stack_set_transition_type(GTK_STACK(chat_stack), GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
    // gtk_stack_set_transition_duration(GTK_STACK(chat_stack), 1000);
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(chat_sidebar), GTK_STACK(chat_stack));

    chat_add_button = gtk_button_new_with_label("Add chat");

    g_signal_connect(G_OBJECT(chat_add_button), "clicked", G_CALLBACK(popup_add_chat), NULL);

    

    // packing
    gtk_box_pack_start(GTK_BOX(chat_vbox), chat_label_top, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(chat_vbox), chat_sidebar, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(chat_vbox), chat_add_button, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(chat_hbox), chat_vbox, FALSE, FALSE, 0);
    //gtk_box_pack_start(GTK_BOX(chat_hbox), chat_separator, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chat_hbox), chat_stack, TRUE, TRUE, 0);

    // code
    add_chat("Ucode connect");

    // END
    gtk_container_add(GTK_CONTAINER(window), chat_hbox);

    apply_css (window, provider);
    
    gtk_widget_show_all(window);
}
