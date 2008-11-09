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

#include "plutimikation.h"

#include "configdialog.h"
#include "prefs.h"
#include "resultview.h"
#include "krandom.h"
#include "questionsetmultiplication.h"
#include "questionsetquadrats.h"
#include "questionsetcube.h"

#include <klocale.h>
#include <kkeydialog.h>
#include <kfiledialog.h>
#include <kmessagebox.h>
#include <ktempfile.h>
#include <kstdgameaction.h>
#include <kaction.h>
#include <kio/netaccess.h>
#include <kstatusbar.h>
#include <kdebug.h>

#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

Plutimikation::Plutimikation()
{
  QWidget *topWidget = new QWidget( this );
  setCentralWidget( topWidget );

  QGridLayout *topLayout = new QGridLayout( topWidget );
  topLayout->setSpacing( 8 );
  topLayout->setMargin( 8 );

  QLabel *label = new QLabel( i18n("Question:"), topWidget );
  topLayout->addWidget( label, 0, 0 );

  mQuestionLabel = new QLabel( topWidget );
  QFont f = mQuestionLabel->font();
  f.setPointSize( 30 );
  mQuestionLabel->setFont( f );
  mQuestionLabel->setAlignment( AlignCenter );
  topLayout->addWidget( mQuestionLabel, 1, 0 );
  
  label = new QLabel( i18n("Answer:"), topWidget );
  topLayout->addWidget( label, 2, 0 );
  
  mAnswerEdit = new QLineEdit( topWidget );
  topLayout->addWidget( mAnswerEdit, 3, 0 );
  connect( mAnswerEdit, SIGNAL( returnPressed() ), SLOT( checkAnswer() ) );
  mAnswerEdit->setAlignment( AlignCenter );

  mOkButton = new QPushButton( i18n("Ok"), topWidget );
  topLayout->addWidget( mOkButton, 4, 0 );
  connect( mOkButton, SIGNAL( clicked() ), SLOT( checkAnswer() ) );

  mFeedbackText = new QLabel( topWidget );
  topLayout->addWidget( mFeedbackText, 5, 0 );
  mFeedbackText->setFrameStyle( QFrame::Panel | QFrame::Plain );
  mFeedbackText->setLineWidth( 2 );
  mFeedbackText->setAlignment( AlignCenter );

  QFontMetrics fm( mFeedbackText->font() );
  mFeedbackText->setFixedHeight( fm.height() * 3 + 6 );

  mResultView = new ResultView( topWidget );
  topLayout->addMultiCellWidget( mResultView, 0, 5, 1, 1 );

  connect( &mReadyTimer, SIGNAL( timeout() ), SLOT( setReady() ) );

  initActions();

  setAutoSaveSettings();

  readSettings();

  initQuestionSets();

  initQuestions();

  newQuestion();
}

Plutimikation::~Plutimikation()
{
  writeSettings();
  Prefs::writeConfig();

  QuestionSet::List::ConstIterator it;
  for( it = mQuestionSets.begin(); it != mQuestionSets.end(); ++it ) {
    delete *it;
  }
  mQuestionSets.clear();
}

void Plutimikation::readSettings()
{
#if 0
  KConfig *cfg = KGlobal::config();
  cfg->setGroup( "GameHandling" );
  bool autoRoll = cfg->readBoolEntry( "AutoRoll", false );
  mAutoRollAction->setChecked( autoRoll );
  toggleAutoRoll();
#endif
}

void Plutimikation::writeSettings()
{
#if 0
  KConfig *cfg = KGlobal::config();
  cfg->setGroup( "GameHandling" );
  cfg->writeEntry( "AutoRoll", mAutoRollAction->isChecked() );
#endif
}

void Plutimikation::initQuestionSets()
{
  mQuestionSets.append( new QuestionSetMultiplication() );
  mQuestionSets.append( new QuestionSetQuadrats() );
  mQuestionSets.append( new QuestionSetCube() );
}

void Plutimikation::initQuestions()
{
  mQuestions.clear();

  QuestionSet::List::ConstIterator it;
  for( it = mQuestionSets.begin(); it != mQuestionSets.end(); ++it ) {
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

void Plutimikation::setReady()
{
  mFeedbackText->setText( i18n("Ready") );
}

void Plutimikation::initActions()
{
  KStdAction::openNew( this, SLOT( newGame() ), actionCollection() );

  KStdAction::quit( this, SLOT( close() ), actionCollection() );


  createStandardStatusBarAction();
  setStandardToolBarMenuEnabled(true);

  KStdAction::keyBindings( this, SLOT( configureKeyBindings() ),
                           actionCollection() );

  KStdAction::preferences(this, SLOT(showOptions()), actionCollection());

  // finally create toolbar and menubar
  createGUI();
}

void Plutimikation::newGame()
{
  kdDebug() << "NEW GAME" << endl;
  initQuestions();
  newQuestion();
}

void Plutimikation::newQuestion()
{
  int i = KRandom::number( mQuestions.count() );
  kdDebug() << "Question number " << i << endl;
  
  mCurrentQuestion = mQuestions.at( i );
  
  mQuestionLabel->setText( (*mCurrentQuestion).question() );

  mAnswerEdit->setText( "" );

  mReadyTimer.start( 1000, true ); // 1 second
}

void Plutimikation::checkAnswer()
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

void Plutimikation::configureKeyBindings()
{
#if 0
  KKeyDialog::configure(actionCollection(), this);
#endif
}

void Plutimikation::showOptions()
{
  ConfigDialog dlg( this );
  int result = dlg.exec();
  if ( result == QDialog::Accepted ) {
    kdDebug() << "Apply settings" << endl;
  }

  newGame();
}

void Plutimikation::showStatus( const QString &msg )
{
  statusBar()->message( msg );
}

void Plutimikation::guteNacht()
{
  mQuestionLabel->setText( "Gute Nacht, Antonia!" );
}

#include "plutimikation.moc"
