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

#include "resultviewtext.h"

#include <kdebug.h>
#include <klocale.h>

#include <qlayout.h>
#include <qlabel.h>

ResultViewText::ResultViewText( QWidget *parent )
  : ResultView( parent )
{
  QBoxLayout *topLayout = new QVBoxLayout( this );
  
  QLabel *label = new QLabel( i18n("Total questions:" ), this );
  topLayout->addWidget( label );
  
  mTotalCountLabel = new QLabel( this  );
  topLayout->addWidget( mTotalCountLabel );
  mTotalCountLabel->setAlignment( AlignCenter );

  label = new QLabel( i18n("Correct Answers:" ), this );
  topLayout->addWidget( label );

  mCurrentCountLabel = new QLabel( this  );
  topLayout->addWidget( mCurrentCountLabel );
  mCurrentCountLabel->setAlignment( AlignCenter );

  label = new QLabel( i18n("Wrong Answers:" ), this );
  topLayout->addWidget( label );

  mWrongCountLabel = new QLabel( this  );
  topLayout->addWidget( mWrongCountLabel );
  mWrongCountLabel->setAlignment( AlignCenter );
}

void ResultViewText::doSetTotalCount( int c )
{
  mTotalCountLabel->setText( QString::number( c ) );
}

void ResultViewText::doSetCurrentCount( int c )
{
  mCurrentCountLabel->setText( QString::number( c ) );
}

void ResultViewText::doSetWrongCount( int c )
{
  mWrongCountLabel->setText( QString::number( c ) );
}

#include "resultviewtext.moc"
