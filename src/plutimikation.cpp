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
#include <kstandarddirs.h>
#include <kapp.h>
#include <krun.h>

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
  connect( m_newGameView, SIGNAL( startClicked() ), SLOT( startGame() ) );

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
  m_newGameView->readSettings();
}

void Plutimikation::writeSettings()
{
  m_newGameView->writeSettings();
}

void Plutimikation::initActions()
{
  KStdAction::openNew( this, SLOT( newGame() ), actionCollection() );  

  new KAction( i18n("Start"), 0, this, SLOT( startGame() ),
    actionCollection(), "restart" );
  
  KStdAction::quit( this, SLOT( close() ), actionCollection() );


  new KAction( i18n("Import Pictures"), 0, this, SLOT( importPictures() ),
    actionCollection(), "import_pictures" );
  
  new KAction( i18n("Show Pictures"), 0, this, SLOT( showPictures() ),
    actionCollection(), "show_pictures" );
  

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
  m_viewStack->raiseWidget( m_newGameView );
}

void Plutimikation::startGame()
{
  m_viewStack->raiseWidget( m_mainView );

  m_mainView->initQuestions( m_newGameView->questionSets() );
  m_mainView->newQuestion();
}

void Plutimikation::importPictures()
{
  KURL::List urls = KFileDialog::getOpenURLs( QString::null, QString::null,
    this, i18n("Choose files to import") );

  QString destDir = locateLocal( "appdata", "progress_pictures/" );

  kdDebug() << "DEST DIR: " << destDir << endl;

  KURL::List::ConstIterator it;
  for( it = urls.begin(); it != urls.end(); ++it ) {
    KURL destUrl( "file:///" + destDir + KApplication::randomString( 10 ) );

    kdDebug() << "DEST: " << destUrl << endl;

    KIO::NetAccess::copy( *it, destUrl, this );
  }
}

void Plutimikation::showPictures()
{
  QString dir = "file:///" + locateLocal( "appdata", "progress_pictures/" );

  kapp->invokeBrowser( dir );
}

#include "plutimikation.moc"
