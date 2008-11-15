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

#include "krandom.h"

#include <kdebug.h>
#include <klocale.h>
#include <kstandarddirs.h>

#include <qlayout.h>
#include <qlabel.h>

#include <math.h>

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
  mFullPic = QPixmap( picPath );
  mCurrentPic.resize( mFullPic.size() );
  mCurrentPic.fill();
  
  mPicLabel->setPixmap( mCurrentPic );

  setSummary();
}

void ResultViewPic::calculatePieces()
{
  mPieces.clear();

  float aspectRatio = float( mFullPic.width() ) / float( mFullPic.height() );

  kdDebug() << "AR: " << aspectRatio << endl;

  int y = sqrt( float( totalCount() ) / aspectRatio );
  int x = y * aspectRatio;

  kdDebug() << "TOTAL: " << x << " " << y << endl;

  while( x * y < totalCount() ) {
    y += 1;
    x = y * aspectRatio;
  }

  kdDebug() << "TOTAL2: " << x << " " << y << endl;

  int row = 0;
  int col = 0;

  float x_size = float( mFullPic.width() ) / float( x );
  float y_size = float( mFullPic.height() ) / float( y );

  kdDebug() << "X_SIZE: " << x_size << " Y_SIZE: " << y_size << endl;

  for ( int i = 0; i < x * y; ++i ) {
    QRect piece;
    piece.setLeft( row * x_size );
    piece.setTop( col * y_size );
    piece.setWidth( ceil( x_size ) );
    piece.setHeight( ceil( y_size ) );
    mPieces.append( piece );

    row++;
    if ( row >= x ) {
      col++;
      row = 0;
    }
  }

//  showPiece( mPieces.last() );
  
  kdDebug() << "PIECES: " << mPieces.count() << endl;
}

void ResultViewPic::doSetTotalCount( int c )
{
  Q_UNUSED( c );

  calculatePieces();

  setSummary();
}

void ResultViewPic::doSetCurrentCount( int c )
{
  Q_UNUSED( c );

  if ( c > 0 ) {
    int select = KRandom::number( mPieces.count() );
    Q_ASSERT( select < int( mPieces.count() ) );

    QRect piece = mPieces[ select ];
    QValueList<QRect>::Iterator it = mPieces.at( select );
    mPieces.erase( it );

    showPiece( piece );
  }

  if ( c == totalCount() ) {
    for( unsigned int i = 0; i < mPieces.count(); ++i ) {
      showPiece( mPieces[ i ] );
    }
  }

  setSummary();
}

void ResultViewPic::showPiece( const QRect &piece )
{
  copyBlt ( &mCurrentPic, piece.x(), piece.y(),
    &mFullPic, piece.x(), piece.y(), piece.width(), piece.height() );
  mPicLabel->setPixmap( mCurrentPic );
}

void ResultViewPic::doSetWrongCount( int c )
{
  Q_UNUSED( c );

  setSummary();
}

void ResultViewPic::setSummary()
{
  mSummaryLabel->setText( i18n("%1/%2 correct, %3 wrong").arg( currentCount() )
    .arg( totalCount() ).arg( wrongCount() ) );
}

#include "resultviewpic.moc"
