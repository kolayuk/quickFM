/*
========================================================================
 Name        : quickFMAppUi.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
#ifndef QUICKFMAPPUI_H
#define QUICKFMAPPUI_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknviewappui.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CAboutView;
// ]]] end generated region [Generated Forward Declarations]
#include <hwrmfmtx.h>
/**
 * @class	CquickFMAppUi quickFMAppUi.h
 * @brief The AppUi class handles application-wide aspects of the user interface, including
 *        view management and the default menu, control pane, and status pane.
 */
class CquickFMAppUi : public CAknViewAppUi
	{
public: 
	// constructor and destructor
	CquickFMAppUi();
	virtual ~CquickFMAppUi();
	void ConstructL();

public:
	TBool isFMEnabled();
	void SwitchFM();
	void Launch(TUid aUid);
	CHWRMFmTx* iFm;
	CPeriodic* iTimer;
	static TInt Tick(TAny* aObj);
	// from CCoeAppUi
	TKeyResponse HandleKeyEventL(
				const TKeyEvent& aKeyEvent,
				TEventCode aType );

	// from CEikAppUi
	void HandleCommandL( TInt aCommand );
	void HandleResourceChangeL( TInt aType );

	// from CAknAppUi
	void HandleViewDeactivation( 
			const TVwsViewId& aViewIdToBeDeactivated, 
			const TVwsViewId& aNewlyActivatedViewId );

private:
	void InitializeContainersL();
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CAboutView* iAboutView;
	// ]]] end generated region [Generated Instance Variables]
	
	
	// [[[ begin [User Handlers]
protected: 
	// ]]] end [User Handlers]
	
	};

#endif // QUICKFMAPPUI_H			
