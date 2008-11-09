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
#ifndef QUESTION_H
#define QUESTION_H

#include <qstring.h>
#include <qvaluelist.h>

class Question
{
  public:
    typedef QValueList<Question> List;

    Question();

    void setQuestion( const QString & );
    QString question() const;
    
    void setAnswer( const QString & );
    QString answer() const;
    
  private:
    QString mQuestion;
    QString mAnswer;
};

#endif
