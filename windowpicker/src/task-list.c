/*
 * Copyright (C) 2008 Canonical Ltd
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Neil Jagdish Patel <neil.patel@canonical.com>
 *              Sebastian Geiger <sbastig@gmx.net>
 */

#include "task-list.h"
#include "task-item.h"

#include <libwnck/libwnck.h>
#include <panel-applet.h>

struct _TaskListPrivate {
    WnckScreen *screen;
    WpApplet *windowPickerApplet;
};

G_DEFINE_TYPE_WITH_PRIVATE (TaskList, task_list, GTK_TYPE_BOX);

static GSList *task_lists;

static TaskList *
get_task_list_for_monitor (TaskList *task_list,
                           gint      monitor)
{
    GSList *list;
    gint list_monitor;

    list = task_lists;

    while (list != NULL)
      {
        task_list = list->data;
        list_monitor = task_list_get_monitor (task_list);

        if (list_monitor == monitor)
            return task_list;

        list = list->next;
      }

    return task_lists->data;
}


static void on_task_item_closed (
    TaskItem *item,
    TaskList *list)
{
    gtk_container_remove (
        GTK_CONTAINER (list),
        GTK_WIDGET (item)
    );
    gtk_widget_destroy (GTK_WIDGET (item));
}

static gint
window_get_monitor (WnckWindow *window)
{
    GdkScreen *gdk_screen;
    gint x, y, w, h;

    gdk_screen = gdk_screen_get_default ();

    wnck_window_get_geometry (window, &x, &y, &w, &h);

    return gdk_screen_get_monitor_at_point (gdk_screen,
                                            x + w / 2,
                                            y + h / 2);
}

static void
on_task_item_monitor_changed_cb (TaskItem *item,
                                 gint      old_monitor,
                                 TaskList *current_list)
{
    gint monitor;
    gint list_monitor;
    TaskList *list;

    monitor = task_item_get_monitor (item);
    list_monitor = task_list_get_monitor (current_list);

    if (monitor != list_monitor)
      {
        list = get_task_list_for_monitor (current_list, monitor);

        g_object_ref (item);
        gtk_container_remove (GTK_CONTAINER (current_list), GTK_WIDGET (item));

        gtk_widget_queue_resize (GTK_WIDGET (current_list));

        g_signal_handlers_disconnect_by_func (item,
                                              on_task_item_monitor_changed_cb,
                                              current_list);

        gtk_container_add (GTK_CONTAINER (list), GTK_WIDGET (item));

        g_signal_connect (TASK_ITEM (item), "monitor-changed",
                          G_CALLBACK (on_task_item_monitor_changed_cb), list);

        g_object_unref (item);

        gtk_widget_queue_resize (GTK_WIDGET (list));
      }
}

static void create_task_item (TaskList   *taskList,
                              WnckWindow *window)
{
    GtkWidget *item;
    gint list_monitor;
    gint window_monitor;
    guint num;

    num = g_slist_length (task_lists);

    if (num > 1)
      {
        list_monitor = task_list_get_monitor (taskList);
        window_monitor = window_get_monitor (window);

        if (list_monitor != window_monitor)
            return;
      }

    item = task_item_new (taskList->priv->windowPickerApplet,
                          window);

    if (item)
      {
        gtk_container_add (GTK_CONTAINER (taskList), item);

        g_signal_connect (TASK_ITEM (item), "task-item-closed",
                          G_CALLBACK (on_task_item_closed), taskList);

        g_signal_connect (TASK_ITEM (item), "monitor-changed",
                          G_CALLBACK (on_task_item_monitor_changed_cb),
                          taskList);
      }
}

static void type_changed (WnckWindow *window,
                          gpointer user_data)
{
    TaskList *taskList = TASK_LIST (user_data);
    WnckWindowType type = wnck_window_get_window_type (window);

    if (!(type == WNCK_WINDOW_DESKTOP
          || type == WNCK_WINDOW_DOCK
          || type == WNCK_WINDOW_SPLASHSCREEN
          || type == WNCK_WINDOW_MENU))
      {
        create_task_item (taskList, window);
      }
}

static void on_window_opened (WnckScreen *screen,
    WnckWindow *window,
    TaskList *taskList)
{
    g_return_if_fail (taskList != NULL);
    WnckWindowType type = wnck_window_get_window_type (window);

    g_signal_connect (window, "type-changed", G_CALLBACK (type_changed),
                      taskList);

    if (type == WNCK_WINDOW_DESKTOP
        || type == WNCK_WINDOW_DOCK
        || type == WNCK_WINDOW_SPLASHSCREEN
        || type == WNCK_WINDOW_MENU)
    {
        return;
    }

    create_task_item (taskList, window);
}

static void on_task_list_orient_changed(PanelApplet *applet,
                                        guint orient,
                                        GtkBox *box)
{
    g_return_if_fail(box);
    switch(orient) {
        case PANEL_APPLET_ORIENT_UP:
        case PANEL_APPLET_ORIENT_DOWN:
            gtk_orientable_set_orientation(GTK_ORIENTABLE(box), GTK_ORIENTATION_HORIZONTAL);
            break;
        case PANEL_APPLET_ORIENT_LEFT:
        case PANEL_APPLET_ORIENT_RIGHT:
            gtk_orientable_set_orientation(GTK_ORIENTABLE(box), GTK_ORIENTATION_VERTICAL);
            break;
        default:
            gtk_orientable_set_orientation(GTK_ORIENTABLE(box), GTK_ORIENTATION_HORIZONTAL);
            break;
    }
    gtk_widget_queue_resize(GTK_WIDGET(box));
}

static void
task_list_dispose (GObject *object)
{
    TaskList *task_list = TASK_LIST (object);
    g_signal_handlers_disconnect_by_func (task_list->priv->screen, on_window_opened, task_list);

    G_OBJECT_CLASS (task_list_parent_class)->dispose (object);
}

static void
task_list_finalize (GObject *object)
{
    TaskList *taskList;

    taskList = TASK_LIST (object);

    task_lists = g_slist_remove (task_lists, taskList);

    G_OBJECT_CLASS (task_list_parent_class)->finalize (object);
}

static void
task_list_class_init(TaskListClass *class) {
    GObjectClass *obj_class = G_OBJECT_CLASS (class);

    obj_class->dispose = task_list_dispose;
    obj_class->finalize = task_list_finalize;
}

static void task_list_init (TaskList *list) {
    list->priv = task_list_get_instance_private (list);
    list->priv->screen = wnck_screen_get_default ();
    gtk_container_set_border_width (GTK_CONTAINER (list), 0);
}

GtkWidget *task_list_new (WpApplet *windowPickerApplet) {
    PanelAppletOrient panel_orientation = panel_applet_get_orient(PANEL_APPLET(windowPickerApplet));
    GtkOrientation orientation;
    switch(panel_orientation) {
        case PANEL_APPLET_ORIENT_UP:
        case PANEL_APPLET_ORIENT_DOWN:
            orientation = GTK_ORIENTATION_HORIZONTAL;
            break;
        case PANEL_APPLET_ORIENT_LEFT:
        case PANEL_APPLET_ORIENT_RIGHT:
            orientation = GTK_ORIENTATION_VERTICAL;
            break;
        default:
            orientation = GTK_ORIENTATION_HORIZONTAL;
    }

    TaskList* taskList = g_object_new (TASK_TYPE_LIST,
                                       "orientation", orientation,
                                       NULL
    );

    task_lists = g_slist_append (task_lists, taskList);

    taskList->priv->windowPickerApplet = windowPickerApplet;

    g_signal_connect(PANEL_APPLET(windowPickerApplet), "change-orient",
                     G_CALLBACK(on_task_list_orient_changed), taskList);
    g_signal_connect (taskList->priv->screen, "window-opened",
            G_CALLBACK (on_window_opened), taskList);

    GList *windows = wnck_screen_get_windows (taskList->priv->screen);
    while (windows != NULL) {
        on_window_opened (taskList->priv->screen, windows->data, taskList);
        windows = windows->next;
    }
    return (GtkWidget *) taskList;
}

gint
task_list_get_monitor (TaskList *list)
{
    GdkScreen *gdk_screen;
    GdkWindow *gdk_window;

    gdk_window = gtk_widget_get_window (GTK_WIDGET (list));
    gdk_screen = gtk_widget_get_screen (GTK_WIDGET (list));

    return gdk_screen_get_monitor_at_window (gdk_screen,
                                             gdk_window);
}
