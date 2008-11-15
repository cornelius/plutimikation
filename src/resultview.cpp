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

#include "resultview.h"

#include <kdebug.h>
#include <klocale.h>

ResultView::ResultView( QWidget *parent )
  : QWidget( parent ), mTotalCount( 0 ), mCurrentCount( 0 ), mWrongCount( 0 )
{
}

void ResultView::setTotalCount( int c )
{
  mTotalCount = c;
  doSetTotalCount( c );
}

void ResultView::setCurrentCount( int c )
{
  mCurrentCount = c;
  doSetCurrentCount( c );
}

void ResultView::setWrongCount( int c )
{
  mWrongCount = c;
  doSetWrongCount( c );
}

void ResultView::incrementCurrentCount()
{
  setCurrentCount( mCurrentCount + 1 );
  doIncrementCurrentCount();
}

void ResultView::incrementWrongCount()
{
  setWrongCount( mWrongCount + 1 );
  doIncrementWrongCount();
}


void ResultView::doSetTotalCount( int )
{
}

void ResultView::doSetCurrentCount( int )
{
}

void ResultView::doSetWrongCount( int )
{
}

void ResultView::doIncrementCurrentCount()
{
}

void ResultView::doIncrementWrongCount()
{
}

int ResultView::totalCount()
{
  return mTotalCount;
}

int ResultView::currentCount()
{
  return mCurrentCount;
  
}

int ResultView::wrongCount()
{
  return mWrongCount;
}

#include "resultview.moc"
