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

#include "resultviewpic.h"

#include <kdebug.h>
#include <klocale.h>
#include <kstandarddirs.h>

#include <qlayout.h>
#include <qlabel.h>

ResultViewPic::ResultViewPic( QWidget *parent )
  : ResultView( parent )
{
  QBoxLayout *topLayout = new QVBoxLayout( this );
  
  mSummaryLabel = new QLabel( this  );
  topLayout->addWidget( mSummaryLabel );
  mSummaryLabel->setAlignment( AlignCenter );

  mPicLabel = new QLabel( this  );
  topLayout->addWidget( mPicLabel, 1 );
  mPicLabel->setAlignment( AlignCenter );

  QString picPath = locate( "appdata", "pics/funny_bunny.jpg" );
  kdDebug() << "PIC: " << picPath << endl;
  mFullPic = QPixmap( picPath );
  mCurrentPic.resize( mFullPic.size() );
  mCurrentPic.fill();
  
  mPicLabel->setPixmap( mCurrentPic );

  setSummary();
}

void ResultViewPic::calculatePieces()
{
  mPieces.clear();

  int row = 0;
  int col = 0;

  int size = 20;

  for ( int i = 0; i < totalCount(); ++i ) {
    QRect piece;
    piece.setLeft( row * size );
    piece.setTop( col *size );
    piece.setWidth( size );
    piece.setHeight( size );
    mPieces.append( piece );

    row++;
    if ( row * size > mFullPic.width() ) {
      col++;
      row = 0;
    }
  }
}

void ResultViewPic::doSetTotalCount( int c )
{
  calculatePieces();

  setSummary();
}

void ResultViewPic::doSetCurrentCount( int c )
{
  QRect piece = mPieces[ c ];

  copyBlt ( &mCurrentPic, piece.x(), piece.y(),
    &mFullPic, piece.x(), piece.y(), piece.width(), piece.height() );
  mPicLabel->setPixmap( mCurrentPic );
  setSummary();
}

void ResultViewPic::doSetWrongCount( int c )
{
  setSummary();
}

void ResultViewPic::setSummary()
{
  mSummaryLabel->setText( i18n("%1/%2 correct, %3 wrong").arg( currentCount() )
    .arg( totalCount() ).arg( wrongCount() ) );
}

#include "resultviewpic.moc"
