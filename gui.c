#include <gtk/gtk.h>
#include <string.h>

const int OPTIONS = 5;

// Struct for headerbar
struct menu_options {
    char * options;
    char * sub_option[6];
};

// Headerbar labels
struct menu_options labels[] = {
    {"File", {"New text file", "Open...", "Save as...", "Close file", NULL}}, 
    {"Edit", {"Undo", "Redo", "Bold", "Italicize", "Underline", NULL}},
    {"Search", {"Find", "Replace", NULL}},
    {"Documents", {"Close all", "Save all", NULL}},
    {"Help", {"Report issue", NULL}}
};

struct toolbar_options {
    char * options; 
};

// Toolbar icons
struct toolbar_options tools[] = {
    {"↺"},
    {"↻"},
    {"𝐁"},
    {"𝐼"},
    {"U"}
};

// Creates toolbar that rests underneath the headerbar
void create_toolbar(GtkWidget * vbox){
    GtkWidget * toolbar; 

    toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_homogeneous(GTK_BOX(toolbar), TRUE);
    gtk_box_append(GTK_BOX(vbox), toolbar);

    for (int i = 0; i < 5; ++i){
        GtkWidget * tool_button = gtk_button_new_with_label(tools[i].options);
        gtk_button_set_has_frame(GTK_BUTTON(tool_button), FALSE);
        gtk_box_append(GTK_BOX(toolbar), tool_button);
        gtk_widget_set_halign(toolbar, GTK_ALIGN_START);
    }
}

// Creates headerbar with a drop down menubar
void create_headerbar(GtkWidget * vbox){
    GtkWidget * headerbar;
    GtkWidget * blank_title;

    // Creates headerbar and sets a blank title to remove menu button arrow from header buttons
    headerbar = gtk_header_bar_new(); 
    blank_title = gtk_label_new(" ");
    gtk_header_bar_set_title_widget(GTK_HEADER_BAR(headerbar), blank_title);

    gtk_box_append(GTK_BOX(vbox), headerbar); 

    // Creates a main menu button along with a drop-down when menu button is pressed
    for (int i = 0; i < OPTIONS; ++i){
        GtkWidget * header_button = gtk_menu_button_new();
        GtkWidget * header_label = gtk_label_new(labels[i].options);

        GtkWidget * popdown_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); 
        GtkWidget * popdown_btn = gtk_popover_new(); 

       // Makes the menu button flat and sets the title for each button
        gtk_menu_button_set_has_frame(GTK_MENU_BUTTON(header_button), FALSE);
        gtk_menu_button_set_child(GTK_MENU_BUTTON(header_button), header_label);

        // Creates drop-down menu using GTK popover 
        for (int j = 0; labels[i].sub_option[j] != NULL; ++j){
            GtkWidget * label = gtk_button_new();
            gtk_button_set_has_frame(GTK_BUTTON(label), FALSE);
            gtk_button_set_label(GTK_BUTTON(label), labels[i].sub_option[j]);
            gtk_box_append(GTK_BOX(popdown_box), label);
        }

        gtk_popover_set_child(GTK_POPOVER(popdown_btn), popdown_box); 
        gtk_menu_button_set_popover(GTK_MENU_BUTTON(header_button), popdown_btn);
        gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar), header_button); 
    }
}

void create_window(GtkApplication * app){
    GtkWidget * window;
    GtkWidget * vbox;
    GtkWidget * scrolled_window;
    GtkWidget * text_view;
    GtkTextBuffer * buffer; 
    GtkAdjustment * adjustment;

    // Creates a window
    window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "typer");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 1200); 

    // Main vertical box
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), vbox); 

    // Shows window
    create_headerbar(vbox); 
    create_toolbar(vbox);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv){
    GtkApplication * app;
    int status; 

    app = gtk_application_new("org.gtk.typer", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(create_window), NULL); 
    status = g_application_run(G_APPLICATION(app), argc, argv); 
    g_object_unref(app);

    return status; 
}