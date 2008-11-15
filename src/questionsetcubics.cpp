/*
    This file is part of Plutimikation.

    Copyright (c) 2007 Cornelius Schumacher <schumacher@kde.org>

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

#include "questionsetcubics.h"

#include "prefs.h"

QuestionSetCubics::QuestionSetCubics()
{
}

void QuestionSetCubics::initQuestions( Question::List &questions )
{
  for( int b = 1; b <= 10; ++b ) {
    Question q;
    q.setQuestion( QString::number( b ) + " cube" );
    q.setAnswer( QString::number( b * b * b ) );
    questions.append( q );
  }
}
