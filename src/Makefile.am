
INCLUDES = $(all_includes)
METASOURCES = AUTO
KDE_ICON = plutimikation

bin_PROGRAMS = plutimikation

plutimikation_LDFLAGS = $(all_libraries) $(KDE_RPATH)
plutimikation_LDADD = $(LIB_KDEGAMES) $(LIB_KFILE)
plutimikation_SOURCES = main.cpp plutimikation.cpp prefs.kcfgc \
                        configdialog.cpp resultview.cpp krandom.cpp \
                        question.cpp \
                        questionset.cpp questionsetmultiplication.cpp \
                        questionsetsquares.cpp questionsetcubics.cpp \
                        questionsetdivision.cpp \
                        mainview.cpp newgameview.cpp resultviewtext.cpp

xdg_apps_DATA = plutimikation.desktop
kde_kcfg_DATA = plutimikation.kcfg

rcdir = $(kde_datadir)/plutimikation
rc_DATA = plutimikationui.rc

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/plutimikation.pot

