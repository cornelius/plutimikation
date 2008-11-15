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

#include "mainview.h"

#include "resultviewtext.h"
#include "resultviewpic.h"
#include "krandom.h"

#include <klocale.h>
#include <kdebug.h>
#include <kmessagebox.h>

#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>

MainView::MainView( QWidget *parent )
  : QWidget( parent )
{
  QGridLayout *topLayout = new QGridLayout( this );
  topLayout->setSpacing( 8 );
  topLayout->setMargin( 8 );

  QLabel *label = new QLabel( i18n("Question:"), this );
  topLayout->addWidget( label, 0, 0 );

  mQuestionLabel = new QLabel( this );
  QFont f = mQuestionLabel->font();
  f.setPointSize( 30 );
  mQuestionLabel->setFont( f );
  mQuestionLabel->setAlignment( AlignCenter );
  topLayout->addWidget( mQuestionLabel, 1, 0 );
  
  label = new QLabel( i18n("Answer:"), this );
  topLayout->addWidget( label, 2, 0 );
  
  mAnswerEdit = new QLineEdit( this );
  topLayout->addWidget( mAnswerEdit, 3, 0 );
  connect( mAnswerEdit, SIGNAL( returnPressed() ), SLOT( checkAnswer() ) );
  mAnswerEdit->setAlignment( AlignCenter );

  mOkButton = new QPushButton( i18n("Ok"), this );
  topLayout->addWidget( mOkButton, 4, 0 );
  connect( mOkButton, SIGNAL( clicked() ), SLOT( checkAnswer() ) );

  mFeedbackText = new QLabel( this );
  topLayout->addWidget( mFeedbackText, 5, 0 );
  mFeedbackText->setFrameStyle( QFrame::Panel | QFrame::Plain );
  mFeedbackText->setLineWidth( 2 );
  mFeedbackText->setAlignment( AlignCenter );

  QFontMetrics fm( mFeedbackText->font() );
  mFeedbackText->setFixedHeight( fm.height() * 3 + 6 );

//  mResultView = new ResultViewText( this );
  mResultView = new ResultViewPic( this );
  topLayout->addMultiCellWidget( mResultView, 0, 5, 1, 1 );

  connect( &mReadyTimer, SIGNAL( timeout() ), SLOT( setReady() ) );
}

MainView::~MainView()
{
  clear();
}

void MainView::clear()
{
}

void MainView::initQuestions( const QuestionSet::List &questionSets )
{
  mQuestions.clear();

  QuestionSet::List::ConstIterator it;
  for( it = questionSets.begin(); it != questionSets.end(); ++it ) {
    QuestionSet *set = *it;
    set->initQuestions( mQuestions );
  }

  mResultView->setTotalCount( mQuestions.count() );
  mResultView->setCurrentCount( 0 );
  mResultView->setWrongCount( 0 );

  setReady();

  mOkButton->setEnabled( true );
  mAnswerEdit->setEnabled( true );
}

void MainView::setReady()
{
  mFeedbackText->setText( i18n("Ready") );
}

void MainView::newQuestion()
{
  int i = KRandom::number( mQuestions.count() );
  kdDebug() << "Question number " << i << endl;
  
  mCurrentQuestion = mQuestions.at( i );
  
  mQuestionLabel->setText( (*mCurrentQuestion).question() );

  mAnswerEdit->setText( "" );

  mReadyTimer.start( 1000, true ); // 1 second

//  mResultView->runAutoResult();
}

void MainView::checkAnswer()
{
  if ( mQuestions.count() == 0 ) {
    kdError() << "checkAnswer(): no questions." << endl;
    return;
  }

  mReadyTimer.stop();

  Question q = *mCurrentQuestion;

  QString text = "<qt>";
  if ( mAnswerEdit->text() == q.answer() ) {
    text += i18n("Correct answer:");
    mResultView->incrementCurrentCount();
    mQuestions.remove( mCurrentQuestion );
  } else {
    text += "<font color=\"red\">" + i18n("Wrong answer.") + "</font><br>";
    text += i18n("Correct Answer:");
    mResultView->incrementWrongCount();
  }
  text += "<br>";
  text += q.question() + " = " + q.answer();
  text += "</qt>";

  mFeedbackText->setText( text );
  
  if ( mQuestions.count() == 0 ) {
    KMessageBox::information( this, i18n("<qt><b>Congratulation!</b><br>"
                                         "You answered all questions.</qt>") );
    mQuestionLabel->setText( "" );
    mAnswerEdit->setText( "" );
    mAnswerEdit->setEnabled( false );
    mOkButton->setEnabled( false );
    mFeedbackText->setText( i18n("You won.") );
  } else {
    newQuestion();
  }
}

#include "mainview.moc"
