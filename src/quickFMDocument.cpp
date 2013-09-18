/*
========================================================================
 Name        : quickFMDocument.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated User Includes]
#include "quickFMDocument.h"
#include "quickFMAppUi.h"
// ]]] end generated region [Generated User Includes]

/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CquickFMDocument::CquickFMDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CquickFMDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CquickFMDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CquickFMDocument
 */
CquickFMDocument* CquickFMDocument::NewL( CEikApplication& aApp )
	{
	CquickFMDocument* self = new ( ELeave ) CquickFMDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CquickFMDocument::CreateAppUiL()
	{
	return new ( ELeave ) CquickFMAppUi;
	}
				
