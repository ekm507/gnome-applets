/*
 * Copyright (C) 2009 Andrej Belcijan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *     Andrej Belcijan <{andrejx} at {gmail.com}>
 */

#define PLAINTEXT_CONFIG				0

#ifndef __WT_APPLET_H__
#define __WT_APPLET_H__

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>
#include <glib-object.h>
#include <glib/gi18n.h>
#include <panel-applet.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#if PLAINTEXT_CONFIG == 1
#include <glib/gstdio.h>
#endif

#ifndef WNCK_I_KNOW_THIS_IS_UNSTABLE
#define WNCK_I_KNOW_THIS_IS_UNSTABLE
#endif
#include <libwnck/libwnck.h>

/* static paths and stuff */
#define APPLET_NAME						"Window Title"
#define APPLET_OAFIID					"WindowTitleApplet"
#define APPLET_OAFIID_FACTORY			"WindowTitleAppletFactory"
#define PATH_UI_PREFS					GTK_BUILDERDIR"/windowtitle.ui"
#define PATH_LOGO						DATA_DIR"/pixmaps/windowtitle-applet.png"
#define FILE_CONFIGFILE					".windowtitle"
#define ICON_WIDTH						16
#define ICON_HEIGHT						16
#define ICON_PADDING					5

#define WINDOWTITLE_GSCHEMA				"org.gnome.gnome-applets.window-title"
#define CFG_ALIGNMENT					"alignment"
#define CFG_SWAP_ORDER					"swap-order"
#define CFG_EXPAND_APPLET				"expand-applet"
#define CFG_HIDE_ICON					"hide-icon"
#define CFG_HIDE_TITLE					"hide-title"
#define CFG_CUSTOM_STYLE				"custom-style"
#define CFG_TITLE_SIZE					"title-size"
#define CFG_ONLY_MAXIMIZED				"only-maximized"
#define CFG_HIDE_ON_UNMAXIMIZED 		"hide-on-unmaximized"
#define CFG_SHOW_WINDOW_MENU			"show-window-menu"
#define CFG_SHOW_TOOLTIPS				"show-tooltips"
#define CFG_TITLE_ACTIVE_FONT			"title-active-font"
#define CFG_TITLE_ACTIVE_COLOR_FG		"title-active-color-fg"
#define CFG_TITLE_INACTIVE_FONT			"title-inactive-font"
#define CFG_TITLE_INACTIVE_COLOR_FG		"title-inactive-color-fg"

G_BEGIN_DECLS

#define WT_TYPE_APPLET                wt_applet_get_type()
#define WT_APPLET(obj)                (G_TYPE_CHECK_INSTANCE_CAST ((obj), WT_TYPE_APPLET, WTApplet))
#define WT_APPLET_CLASS(klass)        (G_TYPE_CHECK_CLASS_CAST ((klass), WT_TYPE_APPLET, WTAppletClass))
#define WT_IS_APPLET(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), WT_TYPE_APPLET))
#define WT_IS_APPLET_CLASS(klass)     (G_TYPE_CHECK_CLASS_TYPE ((klass), WT_TYPE_APPLET))
#define WT_APPLET_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS ((obj), WT_TYPE_APPLET, WTAppletClass))

/* Applet properties (things that get saved) */
typedef struct {
	gboolean 		only_maximized,			// [T/F] Only track maximized windows
					hide_on_unmaximized,	// [T/F] Hide when no maximized windows present
					hide_icon,				// [T/F] Hide the icon
					hide_title,				// [T/F] Hide the title
					swap_order,				// [T/F] Swap title/icon
					expand_applet,			// [T/F] Expand the applet TODO: rename to expand_title ?
					custom_style,			// [T/F] Use custom style
					show_window_menu,		// [T/F] Show window action menu on right click
					show_tooltips;			// [T/F] Show tooltips
	gint			title_size;				// Title size (minimal w/ expand and absolute w/o expand)
	gchar			*title_active_font;		// Custom active title font
	gchar			*title_active_color;	// Custom active title color
	gchar			*title_inactive_font;	// Custom inactive title font
	gchar			*title_inactive_color;	// Custom inactive title color
	gdouble			alignment;				// Title alignment [0=left, 0.5=center, 1=right]
} WTPreferences;

/* WBApplet definition (inherits from PanelApplet) */
typedef struct {
    PanelApplet		*applet;				// The actual PanelApplet
	GSettings *settings;

	/* Widgets */
	GtkBox      	*box;					// Main container widget
	GtkEventBox		*eb_icon, *eb_title;	// Eventbox widgets
	GtkImage		*icon;					// Icon image widget
	GtkLabel		*title;					// Title label widget
	GtkWidget		*window_prefs;			// Preferences window

	/* Variables */
	WTPreferences	*prefs;					// Main properties
	WnckScreen 		*activescreen;			// Active screen
	WnckWorkspace	*activeworkspace;		// Active workspace
	WnckWindow		*umaxedwindow,			// Upper-most maximized window
					*activewindow,			// Active window
					*rootwindow;			// Root window (desktop)
	gulong			active_handler_state,	// activewindow's statechange event handler ID
					active_handler_name,	// activewindow's namechange event handler ID
					active_handler_icon,	// activewindow's iconchange event handler ID
					umaxed_handler_state,	// umaxedwindow's statechange event handler ID
					umaxed_handler_name,	// umaxedwindow's manechange event handler ID
					umaxed_handler_icon;	// umaxedwindow's iconchange event handler ID
	gboolean		focused;				// [T/F] Window state (focused or unfocused)
	gchar			*panel_color_fg;		// Foreground color determined by the panel

	GdkPixbufRotation	angle;				// Applet angle
	PanelAppletOrient	orient;				// Panel orientation
	gint				size;				// Panel size
	gint				asize;				// Applet allocation size
	gint				*size_hints;		// Applet size hints
	GtkPackType			packtype;			// Packaging direction of buttons

	/* GtkBuilder */
	GtkBuilder 		*prefbuilder;			// Glade GtkBuilder for the preferences
} WTApplet;

typedef struct {
        PanelAppletClass applet_class;
} WTAppletClass;

GType wt_applet_get_type (void);
WTApplet* wt_applet_new (void);

G_END_DECLS
#endif
