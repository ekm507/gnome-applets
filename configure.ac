dnl ***************************************************************************
dnl *** configure.in for GNOME-APPLETS                                      ***
dnl ***************************************************************************
AC_INIT(gnome-applets, 3.7.1)
AC_PREREQ(2.59)

AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE([1.11 no-dist-gzip dist-xz tar-ustar])
AC_CONFIG_MACRO_DIR(m4)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

dnl ***************************************************************************
dnl *** Minimum library versions for GNOME-APPLETS                          ***
dnl ***************************************************************************
GTK_REQUIRED=3.0
GLIB_REQUIRED=2.22.0
GIO_REQUIRED=2.15.3
GCONF_REQUIRED=2.8.0
LIBPANEL_REQUIRED=2.91.90
LIBGTOP_REQUIRED=2.11.92
LIBXKLAVIER_REQUIRED=4.0
LIBWNCK_REQUIRED=2.91.0
LIBNOTIFY_REQUIRED=0.7
HAL_REQUIRED=0.5.3
UPOWER_REQUIRED=0.9.4
DBUS_REQUIRED=1.1.2
DBUS_GLIB_REQUIRED=0.74
PYGOBJECT_REQUIRED=2.26
GNOME_ICON_THEME_REQUIRED=2.15.91
LIBXML_REQUIRED=2.5.0
GWEATHER_REQUIRED=3.5.0
GUCHARMAP3_REQUIRED=2.33.0
POLKIT_REQUIRED=0.92
NETWORKMANAGER_REQUIRED=0.7
GST10_REQUIRED=0.10.2
dnl ***************************************************************************

AM_MAINTAINER_MODE

IT_PROG_INTLTOOL([0.35.0])
PKG_PROG_PKG_CONFIG([0.19])

AC_PROG_CC
AC_ISC_POSIX
AC_STDC_HEADERS
AM_PROG_LIBTOOL
AC_PATH_XTRA
AM_PATH_PYTHON(2.4)
AM_CHECK_PYTHON_HEADERS(HAVE_PYHDRS="yes", HAVE_PYHDRS="no")

X_LIBS="$X_LIBS $X_PRE_LIBS -lX11 $X_EXTRA_LIBS"
AC_SUBST(X_LIBS)

dnl Check for libm
LT_LIB_M

GNOME_COMPILE_WARNINGS

dnl Check for non-portable headers
AC_CHECK_HEADERS([pty.h values.h])

dnl ***************************************************************************
dnl *** --enable-more-warnings turns on more compiler warnings              ***
dnl ***************************************************************************
AC_ARG_ENABLE(more-warnings,
[  --enable-more-warnings  Maximum compiler warnings],
set_more_warnings="$enableval",[
    set_more_warnings=no
])
AC_MSG_CHECKING(for more warnings, including -Werror)
if test "$GCC" = "yes" -a "$set_more_warnings" != "no"; then
    AC_MSG_RESULT(yes)
    CFLAGS="\
    -Wall \
    -Wchar-subscripts -Wmissing-declarations -Wmissing-prototypes \
    -Wnested-externs -Wpointer-arith \
    -Wcast-align -Wsign-compare \
    -std=gnu89 \
    $CFLAGS"

    for option in -Wno-strict-aliasing -Wno-sign-compare; do
        SAVE_CFLAGS="$CFLAGS"
        CFLAGS="$CFLAGS $option"
        AC_MSG_CHECKING([whether gcc understands $option])
        AC_TRY_COMPILE([], [],
            has_option=yes,
            has_option=no,)
        if test $has_option = no; then
            CFLAGS="$SAVE_CFLAGS"
        fi
        AC_MSG_RESULT($has_option)
        unset has_option
        unset SAVE_CFLAGS
    done
    unset option
else
    AC_MSG_RESULT(no)
fi
dnl ***************************************************************************

dnl ***************************************************************************
dnl *** Use pkg-config to check for dependancies                            ***
dnl ***************************************************************************

dnl -- Check for gnome-icon-theme (required) ----------------------------------
PKG_CHECK_MODULES(GIT, gnome-icon-theme >= $GNOME_ICON_THEME_REQUIRED)

dnl -- check for gio (required) ------------------------------------------
PKG_CHECK_MODULES(GIO, gio-2.0 >= $GIO_REQUIRED)
AC_SUBST(GIO_CFLAGS)
AC_SUBST(GIO_LIBS)

PKG_CHECK_MODULES(GIO_UNIX, gio-unix-2.0 >= $GIO_REQUIRED)
AC_SUBST(GIO_UNIX_CFLAGS)
AC_SUBST(GIO_UNIX_LIBS)

dnl -- Check for GTK+ 3.0 (required) ------------------------------------------
PKG_CHECK_MODULES(GTK, gtk+-3.0 >= $GTK_REQUIRED)
AC_SUBST(GTK_FLAGS)
AC_SUBST(GTK_LIBS)

dnl -- check for libpanelapplet (required) ------------------------------------
PKG_CHECK_MODULES(GNOME_APPLETS, libpanelapplet-4.0 >= $LIBPANEL_REQUIRED)
LIBPANEL_APPLET_DIR=`$PKG_CONFIG --variable=libpanel_applet_dir libpanelapplet-4.0`
AC_SUBST(LIBPANEL_APPLET_DIR)
AC_SUBST(GNOME_APPLETS_CFLAGS)
AC_SUBST(GNOME_APPLETS_LIBS)

dnl -- check for libgtop (optional) -------------------------------------------
build_gtop_applets=false
PKG_CHECK_MODULES(GTOP_APPLETS,
                 [libgtop-2.0 >= $LIBGTOP_REQUIRED],
                 build_gtop_applets=true,
		 AC_MSG_WARN([libgtop not found. Not building gtop applets.]))
AC_SUBST(GTOP_APPLETS_CFLAGS)
AC_SUBST(GTOP_APPLETS_LIBS)
AM_CONDITIONAL(BUILD_GTOP_APPLETS, $build_gtop_applets)

dnl -- check for gnome-settings-daemon (optional) -----------------------------
PKG_CHECK_MODULES(GNOME_SETTINGS_DAEMON, gnome-settings-daemon,
	HAVE_GNOME_SETTINGS_DAEMON=yes, HAVE_GNOME_SETTINGS_DAEMON=no)

if test "x$HAVE_GNOME_SETTINGS_DAEMON" = "xno"; then
	AC_MSG_WARN([gnome-settings-daemon DBUS API is required to build modem-applet.])
fi

AC_SUBST(GNOME_SETTINGS_DAEMON_CFLAGS)
AC_SUBST(GNOME_SETTINGS_DAEMON_LIBS)

dnl -- check for libwnck (required) -------------------------------------------
PKG_CHECK_MODULES(LIBWNCK, libwnck-3.0 >= $LIBWNCK_REQUIRED,,
	AC_MSG_ERROR([libwnck is required to build gnome-applets.], 1))

AC_SUBST(LIBWNCK_CFLAGS)
AC_SUBST(LIBWNCK_LIBS)

dnl -- check for libnotify (optional) -----------------------------------------
LIBNOTIFY_CFLAGS=
LIBNOTIFY_LIBS=
PKG_CHECK_MODULES(LIBNOTIFY, libnotify >= $LIBNOTIFY_REQUIRED,
		  HAVE_LIBNOTIFY="yes", HAVE_LIBNOTIFY="no")

if test "x$HAVE_LIBNOTIFY" = "xyes"; then
	AC_DEFINE(HAVE_LIBNOTIFY, 1, [libnotify available])
fi

AC_SUBST(LIBNOTIFY_CFLAGS)
AC_SUBST(LIBNOTIFY_LIBS)

dnl -- check for glib/gobject (required) --------------------------------------
PKG_CHECK_MODULES(CPUFREQ_SELECTOR, glib-2.0 >= $GLIB_REQUIRED gobject-2.0 >= $GLIB_REQUIRED)
AC_SUBST(CPUFREQ_SELECTOR_CFLAGS)
AC_SUBST(CPUFREQ_SELECTOR_LIBS)

dnl -- check for dbus (required for cpufreq-selector)
PKG_CHECK_MODULES(DBUS, dbus-1 >= $DBUS_REQUIRED dbus-glib-1 >= $DBUS_GLIB_REQUIRED, HAVE_DBUS=yes, HAVE_DBUS=no)

AC_SUBST(DBUS_CFLAGS)
AC_SUBST(DBUS_LIBS)

dnl -- check for PolicyKit and PolicyKit-gnome (optional) -----------------------------------------
POLKIT_CFLAGS=
POLKIT_LIBS=
AC_ARG_ENABLE([polkit],
    AC_HELP_STRING([--enable-polkit], [Enable PolicyKit support @<:@default auto@:>@]),
    enable_polkit=$enableval,
    enable_polkit=auto)
if test "x$enable_polkit" != "xno"; then
    PKG_CHECK_MODULES(POLKIT, polkit-gobject-1 >= $POLKIT_REQUIRED dbus-glib-1 >= $DBUS_GLIB_REQUIRED, HAVE_POLKIT=yes, HAVE_POLKIT=no)
    if test "x$enable_polkit" = "xyes" -a "x$HAVE_POLKIT" = "xno"; then
        AC_MSG_ERROR([PolicyKit support explicitly requested but dependencies not found])
    fi
fi
dnl - This is only so the printout at the end of configure is correct -
if test "x$enable_polkit" = "xno"; then
   HAVE_POLKIT=no
fi
if test "x$HAVE_POLKIT" = "xyes"; then
    AC_DEFINE(HAVE_POLKIT, [1], [PolicyKit available])
fi
AM_CONDITIONAL(HAVE_POLKIT, test "x$HAVE_POLKIT" = "xyes")
AC_SUBST(POLKIT_CFLAGS)
AC_SUBST(POLKIT_LIBS)


dnl -- check for libhal (optional) --------------------------------------------
HAL_CFLAGS=
HAL_LIBS=
AC_ARG_WITH(hal,[  --without-hal           build without hal support])

if test "x$with_hal" != xno; then
	PKG_CHECK_MODULES(HAL, hal >= $HAL_REQUIRED dbus-glib-1 >= $DBUS_GLIB_REQUIRED,
		  HAVE_HAL="yes",
		  HAVE_HAL="no")

	if test "x$HAVE_HAL" = "xyes"; then
		AC_DEFINE(HAVE_HAL, 1, [HAL available])
	fi
else
	AC_MSG_WARN(["Hal support disabled"])
fi

AC_SUBST(HAL_CFLAGS)
AC_SUBST(HAL_LIBS)

dnl -- check for libupower-glib (optional) --------------------------------------------
UPOWER_CFLAGS=
UPOWER_LIBS=
AC_ARG_WITH(upower,[  --without-upower           build without upower support])

if test "x$with_upower" != xno; then
	PKG_CHECK_MODULES(UPOWER, upower-glib >= $UPOWER_REQUIRED,
		  HAVE_UPOWER="yes",
		  HAVE_UPOWER="no")

	LT_LIB_M
	if test "x$HAVE_UPOWER" = "xyes"; then
		AC_DEFINE(HAVE_UPOWER, 1, [UPOWER available])
	fi
else
	AC_MSG_WARN(["upower support disabled"])
fi

AC_SUBST(UPOWER_CFLAGS)
AC_SUBST(UPOWER_LIBS)
AC_SUBST(LIBM)



dnl -- check for gucharmap (optional) -----------------------------------------

PKG_CHECK_MODULES([GUCHARMAP],[gucharmap-2.90 >= $GUCHARMAP3_REQUIRED],
                  [have_gucharmap=yes],[have_gucharmap=no])
if test "$have_gucharmap" = "yes"; then
	AC_DEFINE([HAVE_GUCHARMAP],[1],[Gucharmap Available])
else
  AC_MSG_WARN([*** 'charpick' applet will not be built with gucharmap support ***])
fi
AC_SUBST(GUCHARMAP_CFLAGS)
AC_SUBST(GUCHARMAP_LIBS)

dnl -- check for Python/GNOME modules (optional) ------------------------------
PYGTK_CFLAGS=
PYGTK_LIBS=
PKG_CHECK_MODULES(PYGTK,
	pygobject-2.0	>= $PYGOBJECT_REQUIRED,
	HAVE_PYGTK="yes", HAVE_PYGTK="no")
AC_SUBST(PYGTK_LIBS)
AC_SUBST(PYGTK_CFLAGS)

dnl -- check for libxml2 (required) ------------------------------------------
PKG_CHECK_MODULES(XML2, libxml-2.0 >= $LIBXML_REQUIRED)
AC_SUBST(XML2_CFLAGS)
AC_SUBST(XML2_LIBS)

 dnl -- check for libgweather (required for gweather applet) ------------------
build_libgweather_applets=false
PKG_CHECK_MODULES(LIBGWEATHER, gweather-3.0 >= $GWEATHER_REQUIRED gweather-3.0 <= 3.7,
	          build_libgweather_applets=true,
		  AC_MSG_WARN([libgweather not found. Not building the weather applet.]))
AC_SUBST(LIBGWEATHER_CFLAGS)
AC_SUBST(LIBGWEATHER_LIBS)
AM_CONDITIONAL(BUILD_LIBGWEATHER_APPLETS, $build_libgweather_applets)

dnl -- check for GSettings (required for gweather applet)
GLIB_GSETTINGS

dnl -- check for NetworkManager -----------------------------------------------
AC_ARG_ENABLE([networkmanager],
	AC_HELP_STRING([--enable-networkmanager],
	[Enable NetworkManager support @<:@default=yes@:>@]),
	ENABLE_NETWORKMANAGER=$enableval, ENABLE_NETWORKMANAGER=yes)

HAVE_NETWORKMANAGER=no
NETWORKMANAGER_VERSION=unkown
AC_SUBST(NETWORKMANAGER_VERSION)
if test "x$ENABLE_NETWORKMANAGER" = "xyes"; then
   PKG_CHECK_MODULES(NETWORKMANAGER, NetworkManager >= $NETWORKMANAGER_REQUIRED,
   		HAVE_NETWORKMANAGER=yes, HAVE_NETWORKMANAGER=no)

   if test "x$HAVE_NETWORKMANAGER" = "xyes"; then
      AC_DEFINE(HAVE_NETWORKMANAGER, 1, [NetworkManager available])
      NETWORKMANAGER_VERSION=`$PKG_CONFIG --modversion NetworkManager`
      AC_SUBST(NETWORKMANAGER_CFLAGS)
      AC_SUBST(NETWORKMANAGER_LIBS)
   fi
fi

dnl -- check for the Mixer ----------------------------------------------------
AC_ARG_ENABLE([mixer-applet],
    AC_HELP_STRING([--enable-mixer-applet], [Enable the gstreamer-based mixer applet.]),
    enable_mixer=$enableval,
    enable_mixer=no)
MIXER_CFLAGS=
MIXER_LIBS=
if test "x$enable_mixer" != "xno"; then
    GST10_PKGS="gstreamer-0.10 >= $GST10_REQUIRED gstreamer-interfaces-0.10 >= $GST10_REQUIRED gstreamer-audio-0.10 >= $GST10_REQUIRED"
    PKG_CHECK_MODULES(MIXER, $GST10_PKGS, HAVE_GST=yes, HAVE_GST=no)
    if test "x$HAVE_GST" = "xno"; then
        enable_mixer=no
        AC_MSG_ERROR([Mixer applet explicitly requested but a compatible gstreamer version was not found])
    fi
fi
MIXER_LIBS="$MIXER_LIBS -lm"
AM_CONDITIONAL(BUILD_MIXER_APPLET, test "x$enable_mixer" = "xyes")
AC_SUBST(MIXER_CFLAGS)
AC_SUBST(MIXER_LIBS)

dnl ***************************************************************************
dnl *** find paths to installed binaries                                    ***
dnl ***************************************************************************

dnl -- gdk-pixbuf-csource -----------------------------------------------------
AC_PATH_PROG(GDK_PIXBUF_CSOURCE, gdk-pixbuf-csource, no)

if test x"$GDK_PIXBUF_CSOURCE" = xno; then
  AC_MSG_ERROR([gdk-pixbuf-csource executable not found in your path - should be installed with GTK])
fi
AC_SUBST(GDK_PIXBUF_CSOURCE)

dnl -- glib-genmarshal --------------------------------------------------------
AC_PATH_PROG(GLIB_GENMARSHAL, glib-genmarshal)

dnl -- gconftool-2 ------------------------------------------------------------
AC_PATH_PROG(GCONFTOOL, gconftool-2, no)
if test x"$GCONFTOOL" = xno; then
  AC_MSG_ERROR([gconftool-2 executable not found in your path - should be installed with GConf])
fi

dnl -- xsltproc ---------------------------------------------------------------
AC_PATH_PROG(XSLTPROC, xsltproc, no)
if test x"$XSLTPROC" = xno; then
  AC_MSG_ERROR([xsltproc executable not found in your path - should be installed with libxslt])
fi

dnl -- scrollkeeper -----------------------------------------------------------
AC_PATH_PROG(SCROLLKEEPER_CONFIG, scrollkeeper-config, no)
if test x$SCROLLKEEPER_CONFIG = xno; then
  AC_MSG_ERROR(Couldn't find scrollkeeper-config, please install the Scrollkeeper 0.1.4 package)
fi
AC_SUBST(SCROLLKEEPER_REQUIRED)

dnl -- jw ---------------------------------------------------------------------
AC_PATH_PROG(JW, jw, no)
if test x$JW = xno; then
  HAVE_JW="no"
else
  HAVE_JW="yes"
fi
AM_CONDITIONAL(HAVE_JW, test "x$HAVE_JW" = "xyes")
AC_SUBST(HAVE_JW)

dnl ***************************************************************************
dnl *** GConf                                                               ***
dnl ***************************************************************************
AM_GCONF_SOURCE_2

dnl ***************************************************************************
dnl *** Set up gettext                                                      ***
dnl ***************************************************************************

GETTEXT_PACKAGE=gnome-applets-3.0
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Gettext Package])
AC_DEFINE_DIR(GNOMELOCALEDIR, "${datadir}/locale", [locale directory])
AM_GLIB_GNU_GETTEXT

# this is the directory where the *.{mo,gmo} files are installed
gnomelocaledir='${prefix}/${DATADIRNAME}/locale'
AC_SUBST(gnomelocaledir)

YELP_HELP_INIT

case "$host" in
	sparc-*-solaris*)	gkb_type_sun=true;;
	*)			gkb_type_sun=false;;
esac
AM_CONDITIONAL(GKB_SUN, $gkb_type_sun)

dnl ***************************************************************************
dnl *** battstat specific checks                                            ***
dnl ***************************************************************************

dnl --disable-battstat=(yes|no)
AC_ARG_ENABLE(battstat,
	      [  --disable-battstat=[@<:@no/yes@:>@]
                          don't build battery monitor applet [@<:@default: no@:>@]],,
	      disable_battstat=no)

HAVE_LIBAPM=no
NEED_LIBAPM=no
ACPIINC=
build_battstat_applet=no

if test x$disable_battstat = xno; then
   build_battstat_applet=yes
   AC_CHECK_HEADERS([err.h sys/sysctl.h])
   case "${host}" in
       powerpc-*-linux*)
           NEED_LIBAPM=yes
           AC_CHECK_LIB(apm,apm_read,[HAVE_LIBAPM=yes],[HAVE_LIBAPM=no])
	   ;;
       # list of supported OS cores that use libapm
       *-*-linux*)
	   NEED_LIBAPM=yes
	   AC_CHECK_LIB(apm,apm_read,[HAVE_LIBAPM=yes],[HAVE_LIBAPM=no])
	   ;;
       # list of supported OS cores that do not use libapm
       i386-*-freebsd*|*-*-netbsd*|*-*-openbsd*|*-*kfreebsd*-gnu)
          if [ -n "${OS_SYS}" ]; then
	       ACPIINC="-I${OS_SYS}"
	   else
	       ACPIINC="-I/usr/src/sys"
	   fi

	   savecppflags=$CPPFLAGS
	   CPPFLAGS="$CPPFLAGS $ACPIINC"
	   AC_CHECK_HEADER(dev/acpica/acpiio.h, have_acpiio=true, have_acpiio=false)
	   if test $have_acpiio = true; then
	     AC_DEFINE(HAVE_ACPIIO, 1, [Define if acpiio.h exists on the system])
	   fi

	   ;;
       *)
	   echo "warning: ${host} is not supported by battstat_applet, not building" >&2
	   build_battstat_applet=no
	   ;;
    esac
fi

AC_SUBST(HAVE_LIBAPM)
AC_SUBST(NEED_LIBAPM)
AC_SUBST(ACPIINC)
AM_CONDITIONAL(HAVE_LIBAPM, test "x$HAVE_LIBAPM" = "xyes")
AM_CONDITIONAL(NEED_LIBAPM, test "x$NEED_LIBAPM" = "xyes")
AM_CONDITIONAL(BUILD_BATTSTAT_APPLET, test x$build_battstat_applet = xyes)

dnl ***************************************************************************
dnl *** Mini-Commander specific checks                                      ***
dnl ***************************************************************************
AC_ARG_ENABLE(mini-commander, [  --enable-mini-commander build mini-commander
                          [@<:@default: no, transparent upgrade to deskbar-applet@:>@]], enable_mini_commander="yes", enable_mini_commander="no")
AM_CONDITIONAL(BUILD_MINICOMMANDER_APPLET, test "x$enable_mini_commander" = "xyes")

dnl ***************************************************************************
dnl *** Stickynotes specific checks                                         ***
dnl ***************************************************************************
# AC_ARG_ENABLE(stickynotes, [  --enable-stickynotes build stickynotes
#                           [@<:@default: no, transparent upgrade to Tomboy@:>@]], enable_stickynotes="yes", enable_stickynotes="no")
enable_stickynotes="yes"
AM_CONDITIONAL(BUILD_STICKYNOTES_APPLET, test "x$enable_stickynotes" = "xyes")

dnl ***************************************************************************
dnl *** keyboard accessibility status applet check                          ***
dnl ***************************************************************************

savecppflags=$CPPFLAGS
CPPFLAGS="$CPPFLAGS $X_CFLAGS"
AC_CHECK_HEADER(X11/extensions/XKB.h, HAVE_XKB=true, HAVE_XKB=false)
AC_SUBST(HAVE_XKB)

AM_CONDITIONAL(APPLET_ACCESSX, $HAVE_XKB)
if test "x$APPLET_ACCESSX" = "xtrue"; then
  AC_MSG_WARN([*** keyboard accessibility status applet will not be built ***])
fi
CPPFLAGS=$savecppflags

dnl ***************************************************************************
dnl *** modemlights applet check                                            ***
dnl ***************************************************************************

SU_TOOL=
HAVE_LIBUTIL=

AC_PATH_PROG(SU_TOOL, su)
AC_CHECK_LIB(util, forkpty, HAVE_LIBUTIL=true, HAVE_LIBUTIL=false)

dnl ***
dnl *** Modem lights does not currently compile. It needs to be ported to a
dnl *** modern gnome-system-tools backend.
dnl ***
dnl if test "x$HAVE_LIBUTIL" = "xtrue" -a "x$HAVE_GNOME_SETTINGS_DAEMON" = "xyes"; then
dnl   MODEMLIGHTS_LIBS=" -lutil"
dnl   AC_SUBST(MODEMLIGHTS_LIBS)
dnl   AC_DEFINE_UNQUOTED(STB_SCRIPTS_DIR, "$STB_SCRIPTS_DIR", [System tools backends])
dnl   AC_DEFINE_UNQUOTED(SU_PATH, "${SU_TOOL}", [su executable path])
dnl   BUILD_MODEM_LIGHTS=yes
dnl else
  AC_MSG_WARN([*** modemlights applet will not be built ***])
  BUILD_MODEM_LIGHTS=no
dnl fi

AM_CONDITIONAL(APPLET_MODEMLIGHTS, test "x$BUILD_MODEM_LIGHTS" = "xyes")

dnl ***************************************************************************
dnl *** cpufreq applet check                                                ***
dnl ***************************************************************************

dnl --disable-cpufreq=(yes|no)
AC_ARG_ENABLE(cpufreq,
	      [  --disable-cpufreq[@<:@=no/yes@:>@]
                          don't build cpu frequency scaling monitor applet
			  [@<:@default: no@:>@]],,
	      disable_cpufreq=no)

dnl --enable-frequency-selector=(yes/no)
AC_ARG_ENABLE(frequency-selector,
	      [  --enable-frequency-selector[@<:@=yes/no@:>@]
	                  build frequency selector [@<:@default: yes@:>@]], ,
	      enable_selector=yes)

dnl --enable-suid=(yes/no)
AC_ARG_ENABLE(suid,
       [  --enable-suid[@:<@=yes/no@:>@]  suid root the frequency selector executable
                   [@<:@default: yes@:>@]], ,
       suid=yes)

if test "x$HAVE_POLKIT" = "xyes"; then
   suid=no
fi

AC_CHECK_HEADER(cpufreq.h, have_libcpufreq=yes, have_libcpufreq=no)
LIBCPUFREQ_LIBS=
if test "x$have_libcpufreq" = "xyes"; then
   AC_DEFINE([HAVE_LIBCPUFREQ], [1], [Have libcpufreq.])
   LIBCPUFREQ_LIBS=-lcpufreq
fi
AM_CONDITIONAL(HAVE_LIBCPUFREQ, test x$have_libcpufreq = xyes)
AC_SUBST(LIBCPUFREQ_LIBS)

build_cpufreq_applet=no

if test x$disable_cpufreq = xno; then
   case "${host}" in
      *linux*)
         build_cpufreq_applet=yes
	 ;;
      *)
         AC_MSG_WARN([${host} is not supported by cpufreq applet, not building])
	 build_cpufreq_applet=no
	 ;;
   esac
fi

AM_CONDITIONAL(BUILD_CPUFREQ_APPLET, test x$build_cpufreq_applet = xyes)
AM_CONDITIONAL(BUILD_CPUFREQ_SELECTOR, test x$enable_selector = xyes)
AM_CONDITIONAL(CPUFREQ_SELECTOR_SUID, test x$suid = xyes)

dnl ***************************************************************************
dnl *** invest-applet specific checks                                       ***
dnl ***************************************************************************

AM_CONDITIONAL(BUILD_INVEST_APPLET, test "x$HAVE_PYGTK" = "xyes")

dnl ***************************************************************************
dnl *** Check if IPv6 is available                                          ***
dnl ***************************************************************************
AC_MSG_CHECKING([whether to enable ipv6])
AC_ARG_ENABLE(ipv6, [  --enable-ipv6 enable IPv6 extensions], ,enable_ipv6=yes)
if test $enable_ipv6 = yes; then

  dnl Code for checking presence of AF_INET6 on the system.
  AC_TRY_COMPILE([
    #include <sys/types.h>
    #include <sys/socket.h>], [
    socket(AF_INET6, SOCK_STREAM, 0)
    ],
    have_ipv6=yes,
    have_ipv6=no
  )
  AC_MSG_RESULT($have_ipv6)
  if test $have_ipv6 = yes; then
      AC_DEFINE(ENABLE_IPV6, 1, [Define if system is IPv6 enabled])
  fi
fi

dnl ***************************************************************************
dnl *** Check for getaddrinfo                                               ***
dnl ***************************************************************************
have_getaddrinfo=no
AC_CHECK_FUNC(getaddrinfo, have_getaddrinfo=yes)
if test $have_getaddrinfo != yes; then
  # getaddrinfo is not in the default libraries.  See if it's in some other.
  for lib in bsd socket inet; do
    AC_CHECK_LIB($lib, getaddrinfo, [LIBS="$LIBS -l$lib";have_getaddrinfo=yes; break])
  done
fi
if test $have_getaddrinfo = yes; then
  AC_DEFINE(HAVE_GETADDRINFO, 1, [Define if getaddrinfo() exists on the system])
fi

dnl ***************************************************************************
dnl *** Check for presence of tm.tm_gmtoff on the system                    ***
dnl ***************************************************************************
AC_CHECK_MEMBER([struct tm.tm_gmtoff],[struct_tm_tm_gmtoff=true],[struct_tm_tm_gmtoff=false],[#include <time.h>])
case $struct_tm_tm_gmtoff in
        true)
                AC_DEFINE_UNQUOTED(HAVE_TM_TM_GMOFF, 1, Have the tm.tm_gmtoff member.)
                ;;
        *)
                AC_CHECK_DECL(timezone,AC_DEFINE(HAVE_TIMEZONE,1,Have timezone),,
[
#include <time.h>
])
                ;;
esac

dnl ***************************************************************************
dnl *** _NL_MEASUREMENT_MEASUREMENT is an enum and not a define             ***
dnl ***************************************************************************
AC_MSG_CHECKING([for _NL_MEASUREMENT_MEASUREMENT])
AC_TRY_LINK([#include <langinfo.h>], [
char c;
c = *((unsigned char *)  nl_langinfo(_NL_MEASUREMENT_MEASUREMENT));
], gtk_ok=yes, gtk_ok=no)
AC_MSG_RESULT($gtk_ok)
if test "$gtk_ok" = "yes"; then
  AC_DEFINE([HAVE__NL_MEASUREMENT_MEASUREMENT], [1],
            [Define if _NL_MEASUREMENT_MEASUREMENT is available])
fi

dnl ***************************************************************************
dnl *** Honour aclocal flags                                                ***
dnl ***************************************************************************
ACLOCAL_AMFLAGS="\${ACLOCAL_FLAGS}"
AC_SUBST(ACLOCAL_AMFLAGS)

dnl ***************************************************************************
dnl *** Set install directories                                             ***
dnl ***************************************************************************
iconsdir="${datadir}/icons"
AC_SUBST(iconsdir)
pixmapsdir="${datadir}/pixmaps"
AC_SUBST(pixmapsdir)
pkgdatadir="${datadir}/gnome-applets"
AC_SUBST(pkgdatadir)
builderdir="${pkgdatadir}/builder"
AC_SUBST(builderdir)

AC_DEFINE_DIR(GNOME_ICONDIR, "${iconsdir}", [Gnome Icon Directory])
AC_DEFINE_DIR(GNOME_PIXMAPSDIR, "${pixmapsdir}", [Gnome Pixmaps Directory])
AC_DEFINE_DIR(GTK_BUILDERDIR, "${builderdir}", [GtkBuilder Resources Directory])
AC_DEFINE_DIR(DATADIR, "${datadir}", [datadir])
AC_DEFINE_DIR(SYSCONFDIR, "${sysconfdir}", [sysconfdir])
AC_DEFINE_DIR(LIBDIR, "${libdir}", [libdir])
AC_DEFINE_DIR(PREFIX, "$prefix", [install prefix])

AS_AC_EXPAND(DATADIR, "${datadir}")
AS_AC_EXPAND(PKGDATADIR, "${pkgdatadir}")
AS_AC_EXPAND(PYTHONDIR, $pythondir)
AS_AC_EXPAND(BUILDERDIR, $builderdir)

AC_SUBST(VERSION)
AC_SUBST(PACKAGE)
AC_SUBST(PKGDATADIR)
AC_SUBST(DATADIR)
AC_SUBST(LIBDIR)
AC_SUBST(PYTHONDIR)
AC_SUBST(BUILDERDIR)

dnl ***************************************************************************
dnl *** Output Makefiles et al                                              ***
dnl ***************************************************************************
AC_OUTPUT([
gnome-applets.spec
Makefile
po/Makefile.in
accessx-status/help/Makefile
accessx-status/Makefile
accessx-status/pixmaps/Makefile
battstat/apmlib/Makefile
battstat/help/Makefile
battstat/Makefile
battstat/sounds/Makefile
charpick/help/Makefile
charpick/Makefile
cpufreq/help/Makefile
cpufreq/Makefile
cpufreq/pixmaps/Makefile
cpufreq/src/cpufreq-selector/Makefile
cpufreq/src/Makefile
drivemount/help/Makefile
drivemount/Makefile
geyes/help/Makefile
geyes/Makefile
geyes/themes/Makefile
gweather/help/Makefile
gweather/Makefile
invest-applet/data/art/Makefile
invest-applet/data/Makefile
invest-applet/help/Makefile
invest-applet/invest/defs.py
invest-applet/invest/Makefile
invest-applet/Makefile
man/Makefile
mini-commander/help/Makefile
mini-commander/Makefile
mini-commander/src/Makefile
mixer/help/Makefile
mixer/Makefile
modemlights/Makefile
multiload/help/Makefile
multiload/Makefile
null_applet/Makefile
stickynotes/data/Makefile
stickynotes/help/Makefile
stickynotes/Makefile
stickynotes/pixmaps/Makefile
trashapplet/help/Makefile
trashapplet/Makefile
trashapplet/src/Makefile
])

dnl ***************************************************************************
dnl *** Display Summary                                                     ***
dnl ***************************************************************************
echo "
gnome-applets-$VERSION configure summary:

	Prefix:				${prefix}
	Source code location:		${srcdir}
	Compiler:			${CC}

	Building:
	 - accessx-status		$HAVE_XKB
	 - battstat			$build_battstat_applet
	 - charpick			always
	 	- gucharmap support	$have_gucharmap
	 - cpufreq			$build_cpufreq_applet
	 	- building selector	$enable_selector
		- using PolicyKit       $HAVE_POLKIT
		- enabling suid bit	$suid
	 - drivemount			always
	 - geyes			always
	 - gweather			$build_libgweather_applets
	 - invest-applet		$BUILD_INVEST_APPLET
	 - mini-commander		$enable_mini_commander
	 - modemlights			$BUILD_MODEM_LIGHTS
	 - mixer			$enable_mixer
	 - multiload			$build_gtop_applets
	 - stickynotes			$enable_stickynotes
	 - trashapplet			always

	Using DBUS:			$HAVE_DBUS
	Using NetworkManager:		$HAVE_NETWORKMANAGER
	Using HAL:			$HAVE_HAL
	Using UPOWER:			$HAVE_UPOWER
	Enabling IPv6:			$have_ipv6
" >&2