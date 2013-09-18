/*
========================================================================
 Name        : quickFMDocument.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
#ifndef QUICKFMDOCUMENT_H
#define QUICKFMDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CquickFMDocument quickFMDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CquickFMDocument : public CAknDocument
	{
public: 
	// constructor
	static CquickFMDocument* NewL( CEikApplication& aApp );

private: 
	// constructors
	CquickFMDocument( CEikApplication& aApp );
	void ConstructL();
	
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // QUICKFMDOCUMENT_H
