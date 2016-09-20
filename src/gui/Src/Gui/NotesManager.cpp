#include "NotesManager.h"
#include "Bridge.h"

NotesManager::NotesManager(QWidget* parent) : QTabWidget(parent)
{
    connect(Bridge::getBridge(), SIGNAL(dbgStateChanged(DBGSTATE)), this, SLOT(dbgStateChangedSlot(DBGSTATE)));
    mGlobal = new NotepadView(this);
    connect(Bridge::getBridge(), SIGNAL(setGlobalNotes(QString)), mGlobal, SLOT(setNotes(QString)));
    connect(Bridge::getBridge(), SIGNAL(getGlobalNotes(void*)), mGlobal, SLOT(getNotes(void*)));
    addTab(mGlobal, tr("Global"));

    mDebuggee = new NotepadView(this);
    connect(Bridge::getBridge(), SIGNAL(setDebuggeeNotes(QString)), mDebuggee, SLOT(setNotes(QString)));
    connect(Bridge::getBridge(), SIGNAL(getDebuggeeNotes(void*)), mDebuggee, SLOT(getNotes(void*)));
    mDebuggee->hide();
}

void NotesManager::dbgStateChangedSlot(DBGSTATE state)
{
    if(state == DBGSTATE::initialized)
    {
        mDebuggee->show();
        addTab(mDebuggee, tr("Debuggee"));
    }
    else if(state == DBGSTATE::stopped)
    {
        mDebuggee->hide();
        removeTab(1);
    }
}
