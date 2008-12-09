/*
    This file is part of Plutimikation.

    Copyright (c) 2004 Cornelius Schumacher <schumacher@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

    As a special exception, permission is given to link this program
    with any edition of Qt, and distribute the resulting executable,
    without including the source code for Qt in the source distribution.
*/
#ifndef PLUTIMIKATION_H
#define PLUTIMIKATION_H

#include <kmainwindow.h>

#include "mainview.h"
#include "newgameview.h"

class KAction;
class KToggleAction;

/**
  Main window for Plutimikation.
*/
class Plutimikation : public KMainWindow
{
    Q_OBJECT
  public:
    Plutimikation();
    ~Plutimikation();

    void readSettings();
    void writeSettings();

  protected:
    void initActions();

    void showStatus( const QString & );

  protected slots:
    void configureKeyBindings();
    void showOptions();

    void newGame();
    void startGame();
    
  private:
    QWidgetStack *m_viewStack;

    NewGameView *m_newGameView;
    MainView *m_mainView;
};

#endif
