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

#include "configdialog.h"
#include "krandom.h"

#include <klocale.h>

#include <qlayout.h>
#include <qpushbutton.h>

ConfigDialog::ConfigDialog( QWidget *parent, const char *name )
  : KDialogBase( parent, name, true, i18n("Preferences"), Ok | Cancel )
{
  QWidget *topWidget = new QWidget( this );
  setMainWidget( topWidget );
  
  QBoxLayout *topLayout = new QHBoxLayout( topWidget );

  QBoxLayout *rowLayout = new QVBoxLayout( topLayout );
  
  for( uint i = 1; i <= 10; ++i ) {
    QCheckBox *checkBox = new QCheckBox( QString::number( i ), topWidget );
    rowLayout->addWidget( checkBox );
    mRowChecks.append( checkBox );
  }

  QValueList<int> rows = Prefs::rows();
  QValueList<int>::ConstIterator it;
  for( it = rows.begin(); it != rows.end(); ++it ) {
    int i = *it;
    if ( i < 1 || i > 10 ) continue;
    mRowChecks.at( i - 1 )->setChecked( true );
  }

  QBoxLayout *buttonLayout = new QVBoxLayout( topLayout );

  QPushButton *button = new QPushButton( i18n("Check all"), topWidget );
  buttonLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( checkAll() ) );
  
  button = new QPushButton( i18n("Uncheck all"), topWidget );
  buttonLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( uncheckAll() ) );

  button = new QPushButton( i18n("Check random row"), topWidget );
  buttonLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( checkRandom() ) );

  buttonLayout->addStretch();
}

ConfigDialog::~ConfigDialog()
{
}

void ConfigDialog::checkAll()
{
  QCheckBox *r;
  for( r = mRowChecks.first(); r; r = mRowChecks.next() ) {
    r->setChecked( true );
  }
}

void ConfigDialog::uncheckAll()
{
  QCheckBox *r;
  for( r = mRowChecks.first(); r; r = mRowChecks.next() ) {
    r->setChecked( false );
  }
}

void ConfigDialog::checkRandom()
{
  uncheckAll();
  QCheckBox *r = mRowChecks.at( KRandom::number( mRowChecks.count() - 1 ) );
  r->setChecked( true );
}

void ConfigDialog::slotOk()
{
  QValueList<int> rows;

  for( uint i = 0; i < mRowChecks.count(); ++i ) {
    if ( mRowChecks.at( i )->isChecked() ) rows.append( i + 1 );
  }

  Prefs::setRows( rows );

  accept();
}

#include "configdialog.moc"

