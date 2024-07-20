#include "s21_smartCalc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gtk/gtk.h>
#include <cairo.h>

GtkWidget *entry;
GtkWidget *entry_x;
GtkWidget *entry_y;
void button_clicked(GtkWidget *button, gpointer data);

int main (int argc, char *argv[]) {
	GtkWidget *window;
	gtk_init(&argc, &argv);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_window_set_title(GTK_WINDOW (window), "Calculator");

	GtkWidget *grid;
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER (window), grid);

	entry = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 6, 1);
	gtk_entry_set_text(GTK_ENTRY((GtkWidget*) entry), "");

	GtkWidget *button_clear = gtk_button_new_with_label("clear");
	gtk_grid_attach(GTK_GRID(grid), button_clear, 6, 0, 1, 1);
	g_signal_connect(GTK_BUTTON(button_clear), "clicked", G_CALLBACK(button_clicked), "clear");

	GtkWidget *button_foo = gtk_button_new_with_label("f(x)");
	gtk_grid_attach(GTK_GRID(grid), button_foo, 7, 3, 1, 1);
	g_signal_connect(GTK_BUTTON(button_foo), "clicked", G_CALLBACK(button_clicked), "f(x)=");

	entry_x = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), entry_x, 0, 6, 3, 1);
	gtk_entry_set_text(GTK_ENTRY((GtkWidget*) entry_x), "100");

	entry_y = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), entry_y, 0, 7, 3, 1);
	gtk_entry_set_text(GTK_ENTRY((GtkWidget*) entry_y), "100");

	GtkWidget *label_x = gtk_label_new("(_ < x < _)");
	gtk_grid_attach(GTK_GRID(grid), label_x, 3, 6, 2, 1);

	GtkWidget *label_y = gtk_label_new("(_ < y < _)");
	gtk_grid_attach(GTK_GRID(grid), label_y, 3, 7, 2, 1);

	GtkWidget *button_x = gtk_button_new_with_label("x");
	gtk_grid_attach(GTK_GRID(grid), button_x, 7, 2, 1, 1);
	g_signal_connect(GTK_BUTTON(button_x), "clicked", G_CALLBACK(button_clicked), "x");

	GtkWidget *button_7 = gtk_button_new_with_label("7");
	gtk_grid_attach(GTK_GRID(grid), button_7, 0, 1, 1, 1);
	g_signal_connect(GTK_BUTTON(button_7), "clicked", G_CALLBACK(button_clicked), "7");

	GtkWidget *button_8 = gtk_button_new_with_label("8");
	gtk_grid_attach(GTK_GRID(grid), button_8, 1, 1, 1, 1);
	g_signal_connect(GTK_BUTTON(button_8), "clicked", G_CALLBACK(button_clicked), "8");

	GtkWidget *button_9 = gtk_button_new_with_label("9");
	gtk_grid_attach(GTK_GRID(grid), button_9, 2, 1, 1, 1);
	g_signal_connect(GTK_BUTTON(button_9), "clicked", G_CALLBACK(button_clicked), "9");

	GtkWidget *button_4 = gtk_button_new_with_label("4");
	gtk_grid_attach(GTK_GRID(grid), button_4, 0, 2, 1, 1);
	g_signal_connect(GTK_BUTTON(button_4), "clicked", G_CALLBACK(button_clicked), "4");
	
	GtkWidget *button_5 = gtk_button_new_with_label("5");
	gtk_grid_attach(GTK_GRID(grid), button_5, 1, 2, 1, 1);
	g_signal_connect(GTK_BUTTON(button_5), "clicked", G_CALLBACK(button_clicked), "5");

	GtkWidget *button_6 = gtk_button_new_with_label("6");
	gtk_grid_attach(GTK_GRID(grid), button_6, 2, 2, 1, 1);
	g_signal_connect(GTK_BUTTON(button_6), "clicked", G_CALLBACK(button_clicked), "6");

	GtkWidget *button_1 = gtk_button_new_with_label("1");
	gtk_grid_attach(GTK_GRID(grid), button_1, 0, 3, 1, 1);
	g_signal_connect(GTK_BUTTON(button_1), "clicked", G_CALLBACK(button_clicked), "1");
	
	GtkWidget *button_2 = gtk_button_new_with_label("2");
	gtk_grid_attach(GTK_GRID(grid), button_2, 1, 3, 1, 1);
	g_signal_connect(GTK_BUTTON(button_2), "clicked", G_CALLBACK(button_clicked), "2");

	GtkWidget *button_3 = gtk_button_new_with_label("3");
	gtk_grid_attach(GTK_GRID(grid), button_3, 2, 3, 1, 1);
	g_signal_connect(GTK_BUTTON(button_3), "clicked", G_CALLBACK(button_clicked), "3");

	GtkWidget *button_0 = gtk_button_new_with_label("0");
	gtk_grid_attach(GTK_GRID(grid), button_0, 0, 4, 1, 1);
	g_signal_connect(GTK_BUTTON(button_0), "clicked", G_CALLBACK(button_clicked), "0");
	
	GtkWidget *button_point = gtk_button_new_with_label(".");
	gtk_grid_attach(GTK_GRID(grid), button_point, 1, 4, 1, 1);
	g_signal_connect(GTK_BUTTON(button_point), "clicked", G_CALLBACK(button_clicked), ".");

	GtkWidget *button_equals = gtk_button_new_with_label("=");
	gtk_grid_attach(GTK_GRID(grid), button_equals, 2, 4, 1, 1);
	g_signal_connect(GTK_BUTTON(button_equals), "clicked", G_CALLBACK(button_clicked), "=");

	GtkWidget *button_plus = gtk_button_new_with_label("+");
	gtk_grid_attach(GTK_GRID(grid), button_plus, 3, 4, 1, 1);
	g_signal_connect(GTK_BUTTON(button_plus), "clicked", G_CALLBACK(button_clicked), " + ");

	GtkWidget *button_minus = gtk_button_new_with_label("-");
	gtk_grid_attach(GTK_GRID(grid), button_minus, 3, 3, 1, 1);
	g_signal_connect(GTK_BUTTON(button_minus), "clicked", G_CALLBACK(button_clicked), " - ");

	GtkWidget *button_div = gtk_button_new_with_label("/");
	gtk_grid_attach(GTK_GRID(grid), button_div, 3, 1, 1, 1);
	g_signal_connect(GTK_BUTTON(button_div), "clicked", G_CALLBACK(button_clicked), " / ");

	GtkWidget *button_mul = gtk_button_new_with_label("*");
	gtk_grid_attach(GTK_GRID(grid), button_mul, 3, 2, 1, 1);
	g_signal_connect(GTK_BUTTON(button_mul), "clicked", G_CALLBACK(button_clicked), " * ");

	GtkWidget *button_start = gtk_button_new_with_label("(");
	gtk_grid_attach(GTK_GRID(grid), button_start, 4, 1, 1, 1);
	g_signal_connect(GTK_BUTTON(button_start), "clicked", G_CALLBACK(button_clicked), " ( ");

	GtkWidget *button_end = gtk_button_new_with_label(")");
	gtk_grid_attach(GTK_GRID(grid), button_end, 4, 2, 1, 1);
	g_signal_connect(GTK_BUTTON(button_end), "clicked", G_CALLBACK(button_clicked), " ) ");

	GtkWidget *button_pow = gtk_button_new_with_label("^");
	gtk_grid_attach(GTK_GRID(grid), button_pow, 4, 3, 1, 1);
	g_signal_connect(GTK_BUTTON(button_pow), "clicked", G_CALLBACK(button_clicked), " ^ ");

	GtkWidget *button_mod = gtk_button_new_with_label("mod");
	gtk_grid_attach(GTK_GRID(grid), button_mod, 4, 4, 1, 1);
	g_signal_connect(GTK_BUTTON(button_mod), "clicked", G_CALLBACK(button_clicked), " mod ");

	GtkWidget *button_sin = gtk_button_new_with_label("sin");
	gtk_grid_attach(GTK_GRID(grid), button_sin, 5, 1, 1, 1);
	g_signal_connect(GTK_BUTTON(button_sin), "clicked", G_CALLBACK(button_clicked), "sin(");

	GtkWidget *button_cos = gtk_button_new_with_label("cos");
	gtk_grid_attach(GTK_GRID(grid), button_cos, 5, 2, 1, 1);
	g_signal_connect(GTK_BUTTON(button_cos), "clicked", G_CALLBACK(button_clicked), "cos(");

	GtkWidget *button_tan = gtk_button_new_with_label("tan");
	gtk_grid_attach(GTK_GRID(grid), button_tan, 5, 3, 1, 1);
	g_signal_connect(GTK_BUTTON(button_tan), "clicked", G_CALLBACK(button_clicked), "tan(");

	GtkWidget *button_atan = gtk_button_new_with_label("atan");
	gtk_grid_attach(GTK_GRID(grid), button_atan, 6, 3, 1, 1);
	g_signal_connect(GTK_BUTTON(button_atan), "clicked", G_CALLBACK(button_clicked), "atan(");

	GtkWidget *button_asin = gtk_button_new_with_label("asin");
	gtk_grid_attach(GTK_GRID(grid), button_asin, 6, 1, 1, 1);
	g_signal_connect(GTK_BUTTON(button_asin), "clicked", G_CALLBACK(button_clicked), "asin(");

	GtkWidget *button_acos = gtk_button_new_with_label("acos");
	gtk_grid_attach(GTK_GRID(grid), button_acos, 6, 2, 1, 1);
	g_signal_connect(GTK_BUTTON(button_acos), "clicked", G_CALLBACK(button_clicked), "acos(");

	GtkWidget *button_sqrt = gtk_button_new_with_label("sqrt");
	gtk_grid_attach(GTK_GRID(grid), button_sqrt, 5, 4, 1, 1);
	g_signal_connect(GTK_BUTTON(button_sqrt), "clicked", G_CALLBACK(button_clicked), "sqrt(");

	GtkWidget *button_log = gtk_button_new_with_label("log");
	gtk_grid_attach(GTK_GRID(grid), button_log, 6, 4, 1, 1);
	g_signal_connect(GTK_BUTTON(button_log), "clicked", G_CALLBACK(button_clicked), "log(");

	GtkWidget *button_ln = gtk_button_new_with_label("ln");
	gtk_grid_attach(GTK_GRID(grid), button_ln, 7, 4, 1, 1);
	g_signal_connect(GTK_BUTTON(button_ln), "clicked", G_CALLBACK(button_clicked), "ln(");

	gtk_widget_show_all(window);

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_main ();
	return 0;
}

gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data) {
	guint width, height;
	GdkRGBA color;
	GtkStyleContext *context;
	context = gtk_widget_get_style_context (widget);
	width = gtk_widget_get_allocated_width (widget);
	height = gtk_widget_get_allocated_height (widget);
	gtk_render_background (context, cr, 0, 0, width, height);
	
	// нарисовать оси
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width (cr, 2);
	cairo_move_to(cr, 0, height / 2);
	cairo_line_to(cr, width, height / 2);
	cairo_move_to(cr, width / 2, 0);
	cairo_line_to(cr, width / 2, height);
	cairo_stroke(cr);

	// нарисовать полупрозрачную разметку
	cairo_set_source_rgb(cr, 0.5f, 0.5f, 0.5f);
	cairo_set_line_width (cr, 1);
	for (int i = 0; i < 20; i++) {
		cairo_move_to(cr, 0, height * i / 20);
		cairo_line_to(cr, width, height * i / 20);
		cairo_move_to(cr, width * i / 20, 0);
		cairo_line_to(cr, width * i / 20, height);
	}
	cairo_stroke(cr);

	// берём область определения
	char *temp = g_strdup(gtk_entry_get_text(GTK_ENTRY(entry_x)));
	char *text = g_locale_from_utf8(temp, strlen(temp), NULL, NULL, NULL);
	for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '.')
            text[i] = ',';
    }
    double o_x = atof(text);
	if (text != NULL)
		g_free(text);
	if (temp != NULL)
		g_free(temp);

	// берём область значения
	temp = g_strdup(gtk_entry_get_text(GTK_ENTRY(entry_y)));
	text = g_locale_from_utf8(temp, strlen(temp), NULL, NULL, NULL);
	for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '.')
            text[i] = ',';
    }
    double o_y = atof(text);
	if (text != NULL)
		g_free(text);
	if (temp != NULL)
		g_free(temp);

	// берём функцию
	temp = g_strdup(gtk_entry_get_text(GTK_ENTRY(entry)));
	text = g_locale_from_utf8(temp, strlen(temp), NULL, NULL, NULL);

	for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '.')
            text[i] = ',';
    }
	int k = 0;
	for (; text[k] != '=' && k < 256; k++) {
		text[k] = ' ';
	}
	text[k] = ' ';
	// рисуем график
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width (cr, 2);
	double unit_x = (double)(width / 2) / o_x;
	double unit_y = (double)(height / 2) / o_y;
	for (double i = -o_x; i < o_x; i += 0.01) {
		double result = smartCalc(text, 1, i);
		if (!isnan(result)) {
			if (i == -o_x)
				cairo_move_to(cr, width / 2 + i * unit_x, height / 2 - result * unit_y);
			cairo_line_to(cr, width / 2 + i * unit_x, height / 2 - result * unit_y);
			if (i != -o_x)
				cairo_move_to(cr, width / 2 + i * unit_x, height / 2 - result * unit_y);
		}
	}
	cairo_stroke(cr);

	if (text != NULL)
		g_free(text);
	if (temp != NULL)
		g_free(temp);

	gtk_style_context_get_color (context, gtk_style_context_get_state (context), &color);
	gdk_cairo_set_source_rgba (cr, &color);

	cairo_fill (cr);
	return FALSE;
}

void create_a_graph(char *str) {
	GtkWidget *window;
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
	gtk_window_set_title(GTK_WINDOW (window), "Graph");

	GtkWidget *drawing_area = gtk_drawing_area_new ();
	gtk_container_add(GTK_CONTAINER(window), drawing_area);
  	g_signal_connect (G_OBJECT (drawing_area), "draw", G_CALLBACK (draw_callback), NULL);

	gtk_widget_show_all(window);

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_main ();
}

void button_clicked(GtkWidget *button, gpointer data) {
	char *temp = g_strdup(gtk_entry_get_text(GTK_ENTRY(entry)));
	char *text = g_locale_from_utf8(temp, strlen(temp), NULL, NULL, NULL);
	text = (char*)realloc(text, 256 * sizeof(char));

	int append_to_string = 1;
	int append_to_entry = 1;
	int length = 0;
	Stack *stack = NULL;
	stack = trimString(text, &length, 0, 0);
	if (stack != NULL) {
		if (data == "clear") {
			free(text);
			text = NULL;
			append_to_string = 0;
		} else if (data == "=") {
			int start_count = 0;
			int end_count = 0;
			for (int i = 0; i < length; i++) {
				if (stack[i].type == estart)
					start_count++;
				else if (stack[i].type == eend)
					end_count++;
			}
			for (int i = 0; i < start_count - end_count; i++) {
				strcat(text, ")");
			}
			int define_x = 0;
			for (int i = 0; text[i] != '\0' && text[i] != '\n'; i++) {
				if (text[i] == 'x')
					define_x = 1;
			}
			if (define_x) {
				create_a_graph(text);
				append_to_entry = 0;
				append_to_string = 0;
			} else {
				double result = smartCalc(text, 0, 0);
				free(text);
				text = (char*)malloc(256 * sizeof(char));
				if (isnan(result) == 0)
					sprintf(text, "%.7lf", result);
				else
					sprintf(text, "nan");
				append_to_entry = 1;
				append_to_string = 0;
			}
		} else if (stack[length - 1].type == eplus && data == " + ") {
			append_to_entry = 0;
		} else if (stack[length - 1].type == eminus && data == " - ") {
			append_to_entry = 0;
		} else if (stack[length - 1].type == eplus && data == " - ") {
			int i = 0;
			for (; text[i] != '\0'; i++);
			for (; i >= 0 && text[i - 1] != '+'; i--);
			text[i - 1] = '-';
			append_to_string = 0;
		} else if (stack[length - 1].type == eminus && data == " + ") {
			int i = 0;
			for (; text[i] != '\0'; i++);
			for (; i >= 0 && text[i - 1] != '-'; i--);
			text[i - 1] = '+';
			append_to_string = 0;
		}

		free(stack);
	}
	if (append_to_string) {
		strcat(text, data);
	}
	if (append_to_entry) {
		if (text != NULL)
			gtk_entry_set_text(GTK_ENTRY((GtkWidget*) entry), text);
		else
			gtk_entry_set_text(GTK_ENTRY((GtkWidget*) entry), "");
	}
	if (text != NULL)
		g_free(text);
	if (temp != NULL)
		g_free(temp);
}
