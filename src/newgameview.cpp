/*
    This file is part of KDE.

    Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>

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
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
    USA.
*/

#include "newgameview.h"

#include <klocale.h>

#include <qlayout.h>
#include <qpushbutton.h>

NewGameView::NewGameView( QWidget *parent )
  : QWidget( parent )
{
  QBoxLayout *topLayout = new QVBoxLayout( this );
  
  topLayout->addStretch( 1 );
  
  QPushButton *startButton = new QPushButton( i18n("Start"), this );
  topLayout->addWidget( startButton );
  connect( startButton, SIGNAL( clicked() ), SIGNAL( startClicked() ) );

  topLayout->addStretch( 1 );  
}

#include "newgameview.moc"
