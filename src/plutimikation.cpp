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

#include "plutimikation.h"

#include "configdialog.h"
#include "prefs.h"

#include <klocale.h>
#include <kkeydialog.h>
#include <kfiledialog.h>
#include <kmessagebox.h>
#include <ktempfile.h>
#include <kstdgameaction.h>
#include <kaction.h>
#include <kio/netaccess.h>
#include <kstatusbar.h>
#include <kdebug.h>

#include <qwidgetstack.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

Plutimikation::Plutimikation()
{
  m_viewStack = new QWidgetStack( this );
  setCentralWidget( m_viewStack );

  m_newGameView = new NewGameView( this );
  m_viewStack->addWidget( m_newGameView );
  connect( m_newGameView, SIGNAL( startClicked() ), SLOT( newGame() ) );

  m_mainView = new MainView( this );
  m_viewStack->addWidget( m_mainView );

  m_viewStack->raiseWidget( m_newGameView );

  initActions();

  setAutoSaveSettings();

  readSettings();
}

Plutimikation::~Plutimikation()
{
  writeSettings();
  Prefs::writeConfig();
}

void Plutimikation::readSettings()
{
#if 0
  KConfig *cfg = KGlobal::config();
  cfg->setGroup( "GameHandling" );
  bool autoRoll = cfg->readBoolEntry( "AutoRoll", false );
  mAutoRollAction->setChecked( autoRoll );
  toggleAutoRoll();
#endif
}

void Plutimikation::writeSettings()
{
#if 0
  KConfig *cfg = KGlobal::config();
  cfg->setGroup( "GameHandling" );
  cfg->writeEntry( "AutoRoll", mAutoRollAction->isChecked() );
#endif
}

void Plutimikation::initActions()
{
  KStdAction::openNew( this, SLOT( newGame() ), actionCollection() );

  KStdAction::quit( this, SLOT( close() ), actionCollection() );


  createStandardStatusBarAction();
  setStandardToolBarMenuEnabled(true);

  KStdAction::keyBindings( this, SLOT( configureKeyBindings() ),
                           actionCollection() );

  KStdAction::preferences(this, SLOT(showOptions()), actionCollection());

  // finally create toolbar and menubar
  createGUI();
}

void Plutimikation::configureKeyBindings()
{
#if 0
  KKeyDialog::configure(actionCollection(), this);
#endif
}

void Plutimikation::showOptions()
{
  ConfigDialog dlg( this );
  int result = dlg.exec();
  if ( result == QDialog::Accepted ) {
    kdDebug() << "Apply settings" << endl;
  }

  newGame();
}

void Plutimikation::showStatus( const QString &msg )
{
  statusBar()->message( msg );
}

void Plutimikation::newGame()
{
  kdDebug() << "NEW GAME" << endl;

  m_viewStack->raiseWidget( m_mainView );

  m_mainView->initQuestions();
  m_mainView->newQuestion();
}

#include "plutimikation.moc"
