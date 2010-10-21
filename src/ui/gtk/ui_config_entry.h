#ifndef __UI_CONFIG_ENTRY_H
#define __UI_CONFIG_ENTRY_H

#include <iostream>
#include <vector>

#include <gtk/gtkbuilder.h>
#include <gtk/gtk.h>

#include "ui_widget_entry.h"

class ui_config_entry
{
	public:

		// these should be const's but it make std::vector fail
		// see: http://groups.google.com/group/comp.lang.c++/msg/2cc5480095ca9b73?pli=1
		const std::string id;
		const std::string program_name;
		const std::string node_name;

		enum ui_config_entry_type {
			ROOT,
			MP_PARENT,
			MP,
			SENSORS_PARENT,
			SENSOR,
			VSP,
			EFFECTORS_PARENT,
			EFFECTOR,
			ECP,
			EDP
		} type;

		ui_config_entry();
		ui_config_entry(ui_config_entry_type _type, const char *program = NULL, const char *node = NULL, const char *ui_def = NULL);
		~ui_config_entry();

		GtkTreeIter & getTree_iter() const;
		void setTree_iter(GtkTreeIter & _tree_iter);

		void add_child(ui_config_entry & child);

		void remove_childs(void);

		int childrens(void);

		//! children nodes
		typedef std::vector <ui_config_entry *> childrens_t;
		childrens_t children;

		void show_page(bool visible);

		GtkBuilder & getBuilder(void) {
			if (this->builder) {
				return *(GTK_BUILDER(this->builder));
			} else {
				std::string message = "no GtkBuilder in module ";
				message += program_name;
				throw (message);
			}
		}

		childrens_t getChildByType(ui_config_entry_type _type);
		void addWidget(ui_widget_entry *entry);
		ui_widget_entry * getWidget(gint whichOne);

		//! create process
		void process_spawn(void);

		//! kill process
		void process_kill(int signum);

		//! user data, intended for widget main object
		void *user_data;

	private:

		GtkBuilder *builder;
		GtkWidget *window;
		GModule *module;

		bool page_visible;

		GtkTreeIter tree_iter;

		//! pagetab widgets
		GtkHBox *hbox;
		GtkImage *tabicon;
		GtkLabel *tablabel;
		GtkButton *tabbutton;
		GtkImage *tabcloseicon;
		GtkWidget *content;

		GtkNotebook *getNotebook(void);

		//! manual motion windows
		std::vector<ui_widget_entry *> widgetVector;

		//! process running flag
		bool is_running;

		//! process ID
		pid_t pid;
};

#endif /* __UI_CONFIG_ENTRY_H */
