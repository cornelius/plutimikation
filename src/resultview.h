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
#ifndef RESULTVIEW_H
#define RESULTVIEW_H

#include "question.h"

#include <qwidget.h>
#include <qtimer.h>

/**
  View base class for showing overall results of Plutimikation.
*/
class ResultView : public QWidget
{
    Q_OBJECT
  public:
    ResultView( QWidget *parent );

    void initialize( const Question::List &questions );

    void setTotalCount( int );
    void setCurrentCount( int );
    void incrementCurrentCount();
    void setWrongCount( int );
    void incrementWrongCount();

    int totalCount() const;
    int currentCount() const;
    int wrongCount() const;

    void runAutoResult();

    QString rating() const;

  protected:
    virtual void doSetTotalCount( int );
    virtual void doSetCurrentCount( int );
    virtual void doIncrementCurrentCount();
    virtual void doSetWrongCount( int );
    virtual void doIncrementWrongCount();

  protected slots:
    void autoResultTick();

  private:
    int mTotalCount;
    int mCurrentCount;
    int mWrongCount;
    
    int m_autoResultCount;
    QTimer m_autoResultTimer;
};

#endif
