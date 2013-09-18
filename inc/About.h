/*============================================================================
 Name        : CAboutContainer from AboutContainer.h
 Author	  	 : Fokin Alexander -=- ICQ : 285271527 -=- E-mail : alexander_fokin@symdeveloper.ru
 Version	 : 1.0
 Copyright   : 2010
 Description : Declares container control for application.
============================================================================*/
#ifndef ABOUTCONTAINER_H
#define ABOUTCONTAINER_H

//SYSTEM INCLUDES
#include <coecntrl.h>
#include <AknsDrawUtils.h>
#include <AknsBasicBackgroundControlContext.h>
#include <fbs.h>
#include <aknbutton.h>
#define VER_MAJOR 1
#define VER_MINOR 1
#define VER_BUILD 0


#ifdef __WINS__
_LIT(KImageFileName,"z:\\resource\\apps\\quickFM_aif.mif");
#else
_LIT(KImageFileName,"c:\\resource\\apps\\quickFM_aif.mif");
#endif

_LIT(KOurPageInOvi, "http://store.ovi.mobi/publisher/Alexander+Fokin");

class CAboutContainer : public CCoeControl,MCoeControlObserver
{
public:
	void ConstructL(const TRect& aRect);
	CAboutContainer();
	~CAboutContainer();

private:
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void Draw(const TRect& aRect) const;
	void DrawStringCentered(const CFont *font, const TDesC &string, TInt& top, TInt width, CWindowGc& gc) const;
	void SetIconSize(const TRect& aRect);
	void HandleResourceChange(TInt aType);
	CAknButton* btn1;
	CAknButton* btn2;
	CAknButton* btn3;
	void HandleControlEventL(CCoeControl* aControl,enum TCoeEvent aType);

private: //data
	CAknsBasicBackgroundControlContext* iBgContext;
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	CFbsBitmap *iBitmap;
	CFbsBitmap *iMask;
};
#endif


