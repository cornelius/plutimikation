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

#include <kapplication.h>
#include <kcmdlineargs.h>
#include <kaboutdata.h>

static const char description[] = I18N_NOOP("Multiplication Table Game");

int main( int argc, char *argv[] )
{
  KAboutData aboutData( "plutimikation", I18N_NOOP("Plutimikation"),
                        "0.1", description, KAboutData::License_GPL,
                        "(c) 2004, Cornelius Schumacher",
                        I18N_NOOP("For Antonia") );
  aboutData.addAuthor("Cornelius Schumacher", 0, "schumacher@kde.org");

  KCmdLineArgs::init( argc, argv, &aboutData );

  KApplication app;

  // All session management is handled in the RESTORE macro
  if ( app.isRestored() )
    RESTORE( Plutimikation )
  else {
    QWidget *mainWindow = new Plutimikation;
    app.setMainWidget( mainWindow );
    mainWindow->show();
  }

  return app.exec();
}
