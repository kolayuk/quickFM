/*
========================================================================
 Name        : quickFMAppUi.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
#include <quickFM.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "quickFMAppUi.h"
#include "quickFM.hrh"
#include "AboutView.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

#include <hwrmfmtx.h>
#include <aknglobalnote.h>
#include <centralrepository.h>
#include <apgcli.h>
#include <w32std.h>
/**
 * Construct the CquickFMAppUi instance
 */ 
CquickFMAppUi::CquickFMAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The appui's destructor removes the container from the control
 * stack and destroys it.
 */
CquickFMAppUi::~CquickFMAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	if (iFm){delete iFm;}
	}

// [[[ begin generated function: do not modify
void CquickFMAppUi::InitializeContainersL()
	{
	iAboutView = CAboutView::NewL();
	AddViewL( iAboutView );
	SetDefaultViewL( *iAboutView );
	}
// ]]] end generated function

/**
 * Handle a command for this appui (override)
 * @param aCommand command id to be handled
 */
void CquickFMAppUi::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{ // code to dispatch to the AppUi's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
		if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
			{
			Exit();
			}
		}
	// ]]] end generated region [Generated Code]
	
	}

/** 
 * Override of the HandleResourceChangeL virtual function
 */
void CquickFMAppUi::HandleResourceChangeL( TInt aType )
	{
	CAknViewAppUi::HandleResourceChangeL( aType );
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}
				
/** 
 * Override of the HandleKeyEventL virtual function
 * @return EKeyWasConsumed if event was handled, EKeyWasNotConsumed if not
 * @param aKeyEvent 
 * @param aType 
 */
TKeyResponse CquickFMAppUi::HandleKeyEventL(
		const TKeyEvent& aKeyEvent,
		TEventCode aType )
	{
	// The inherited HandleKeyEventL is private and cannot be called
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	return EKeyWasNotConsumed;
	}

/** 
 * Override of the HandleViewDeactivation virtual function
 *
 * @param aViewIdToBeDeactivated 
 * @param aNewlyActivatedViewId 
 */
void CquickFMAppUi::HandleViewDeactivation( 
		const TVwsViewId& aViewIdToBeDeactivated, 
		const TVwsViewId& aNewlyActivatedViewId )
	{
	CAknViewAppUi::HandleViewDeactivation( 
			aViewIdToBeDeactivated, 
			aNewlyActivatedViewId );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here. 
 */ 
void CquickFMAppUi::ConstructL()
	{

	CEikonEnv::Static()->RootWin().SetOrdinalPosition(-4);
	HideApplicationFromFSW(ETrue);
	TRAPD(err0,iFm=CHWRMFmTx::NewL(NULL));

	if (err0==-5)
		{
		TBuf<255> t;
		CEikonEnv::Static()->ReadResource(t,R_NOT_SUPPORTED);
		CAknGlobalNote* Note=CAknGlobalNote::NewL();
		TRequestStatus status=KRequestPending;
		Note->ShowNoteL(status,EAknGlobalInformationNote,t);
		User::WaitForRequest(status);
		delete Note;
		Exit();
		}
	if (err0!=0){Exit();}
	SwitchFM();

	iTimer=CPeriodic::NewL(CActive::EPriorityHigh);
	iTimer->Start(4000000,4000000,TCallBack(Tick,this));
	// [[[ begin generated region: do not modify [Generated Contents]
	
	BaseConstructL( EAknEnableSkin  | 
					 EAknEnableMSK ); 
	InitializeContainersL();
	// ]]] end generated region [Generated Contents]
	
	}
TInt CquickFMAppUi::Tick(TAny* aObj)
	{
	((CquickFMAppUi*)aObj)->iTimer->Cancel();
	if (!((CquickFMAppUi*)aObj)->IsForeground()){((CquickFMAppUi*)aObj)->Exit();}
	return 0;
	}

void CquickFMAppUi::SwitchFM()
	{
	TInt freq;
	CRepository* cr;
	TInt err=0;
	TRAPD(errCR,cr=CRepository::NewL(TUid::Uid(0x20008EA6)));
	if (!cr){ Exit();}
	cr->Get(0x1,freq);
	delete cr;
	if (iFm)
		{
		if (!isFMEnabled()){TRAP(err,iFm->EnableL(freq));}
		else {TRAP(err,iFm->DisableL());}
		if (err!=0)
			{
			TBuf<255> t;
			CEikonEnv::Static()->ReadResource(t,R_ERROR);
			TBuf<255> txt; txt.Format(t,err);
			CAknGlobalNote* Note=CAknGlobalNote::NewL();
			TRequestStatus status=KRequestPending;
			Note->ShowNoteL(status,EAknGlobalInformationNote,txt);
			User::WaitForRequest(status);
			delete Note;
			Exit();
			}
		}
	}
TBool CquickFMAppUi::isFMEnabled()
	{
	if (iFm)
		{
		if ((iFm->Status()==EFmTxStateOff)||(iFm->Status()==EFmTxStatePowerSaveInactivity)||(iFm->Status()==EFmTxStatePowerSaveAccessory)){return EFalse;}
		else {return ETrue;}
		}
	}

void CquickFMAppUi::Launch(TUid aUid)
	{
    RApaLsSession apaLsSession;
    User::LeaveIfError(apaLsSession.Connect());
    CleanupClosePushL(apaLsSession);
    TApaAppInfo appInfo;
    TInt retVal = apaLsSession.GetAppInfo(appInfo, aUid);
 
    if(retVal == KErrNone)
        {
        CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
        cmdLine->SetExecutableNameL(appInfo.iFullName);
        cmdLine->SetCommandL(EApaCommandRun);
        User::LeaveIfError( apaLsSession.StartApp(*cmdLine) );
 
        CleanupStack::PopAndDestroy(cmdLine);
        }
    else
        {
        // The application not found!
        }
    CleanupStack::PopAndDestroy(&apaLsSession);
	}
