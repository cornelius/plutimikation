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

#include "questionsetmultiplication.h"
#include "questionsetsquares.h"
#include "questionsetcubics.h"
#include "questionsetdivision.h"
#include "prefs.h"

#include <klocale.h>

#include <qlayout.h>
#include <qpushbutton.h>

NewGameView::NewGameView( QWidget *parent )
  : QWidget( parent )
{
  QBoxLayout *topLayout = new QVBoxLayout( this );
  topLayout->setSpacing( 8 );
  topLayout->setMargin( 8 );
  
  topLayout->addStretch( 1 );

  m_timesTableCheck = new QCheckBox( i18n("Times Table"), this );
  topLayout->addWidget( m_timesTableCheck );
  m_timesTableCheck->setChecked( true );

  topLayout->addLayout( createRowChecks( m_multiplicationRowChecks ) );
  
  m_divisionCheck = new QCheckBox( i18n("Division"), this );
  topLayout->addWidget( m_divisionCheck );

  topLayout->addLayout( createRowChecks( m_divisionRowChecks ) );
  
  m_squareNumbersCheck = new QCheckBox( i18n("Square Numbers"), this );
  topLayout->addWidget( m_squareNumbersCheck );
  
  m_cubicNumbersCheck = new QCheckBox( i18n("Cubic Numbers"), this );
  topLayout->addWidget( m_cubicNumbersCheck );

  topLayout->addStretch( 1 );
  
  QPushButton *startButton = new QPushButton( i18n("Start"), this );
  topLayout->addWidget( startButton );
  connect( startButton, SIGNAL( clicked() ), SLOT( slotStartClicked() ) );

  topLayout->addStretch( 1 );  
}

void NewGameView::readSettings()
{
  readRowSettings( Prefs::multiplicationRows(), m_multiplicationRowChecks );
  readRowSettings( Prefs::divisionRows(), m_divisionRowChecks );
}

void NewGameView::readRowSettings( const QValueList<int> &rows,
  const QValueList<QCheckBox *> &checks )
{
  QValueList<int>::ConstIterator it;
  for( it = rows.begin(); it != rows.end(); ++it ) {
    checks[ *it - 1 ]->setChecked( true );
  }
}

void NewGameView::writeSettings()
{
  Prefs::setMultiplicationRows( selectedRows( m_multiplicationRowChecks ) );
  Prefs::setDivisionRows( selectedRows( m_divisionRowChecks ) );
}

QValueList<int> NewGameView::selectedRows(
  const QValueList<QCheckBox *> &checks )
{
  QValueList<int> rows;

  for( unsigned int i = 0; i < checks.size(); ++i ) {
    if ( checks[ i ]->isChecked() ) {
      rows.append( i + 1 );
    }
  }
  
  return rows;
}

QuestionSet::List NewGameView::questionSets() const
{
  QuestionSet::List questionSets;

  if ( m_timesTableCheck->isChecked() ) {
    questionSets.append( new QuestionSetMultiplication() );
  }
  if ( m_divisionCheck->isChecked() ) {
    questionSets.append( new QuestionSetDivision() );
  }
  if ( m_squareNumbersCheck->isChecked() ) {
    questionSets.append( new QuestionSetSquares() );
  }
  if ( m_cubicNumbersCheck->isChecked() ) {
    questionSets.append( new QuestionSetCubics() );
  }

  return questionSets;
}

QBoxLayout *NewGameView::createRowChecks( QValueList<QCheckBox *> &checks )
{
  QBoxLayout *layout = new QHBoxLayout;

  layout->addSpacing( 10 );

  for( int i = 1; i <= 10; ++i ){
    QCheckBox *check = new QCheckBox( QString::number( i ), this );
    layout->addWidget( check );
    checks.append( check );
  }
  
  layout->addStretch( 1 );
  
  return layout;
}

void NewGameView::slotStartClicked()
{
  writeSettings();

  emit startClicked();
}

#include "newgameview.moc"
