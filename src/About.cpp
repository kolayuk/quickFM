/*============================================================================
 Name        : CAboutContainer from AboutContainer.h
 Author	  	 : Fokin Alexander -=- ICQ : 285271527 -=- E-mail : alexander_fokin@symdeveloper.ru
 Version	 : 1.0
 Copyright   : 2010
 Description : Container control implementation
 ============================================================================*/
//SYSTEM INCLUDES
#include <akndef.hrh>
#include <aknutils.h>
#include <APGCLI.H>

//USER INCLUDES
#include "About.h"
#include <quickFM.rsg>
#include <utils.h>
#include <aknquerydialog.h>
#include <eikenv.h>
#include <aknappui.h>
#include <quickFMAppUi.h>

void CAboutContainer::HandleControlEventL(CCoeControl* aControl,enum TCoeEvent aType)
	{
	if (aType==EEventStateChanged)
		{
		if (aControl==btn1)
			{
			((CquickFMAppUi*)CEikonEnv::Static()->AppUi())->SwitchFM();
			TBuf<255> txt;
			if (((CquickFMAppUi*)CEikonEnv::Static()->AppUi())->isFMEnabled()){CEikonEnv::Static()->ReadResource(txt,R_DISABLE);}
			else {CEikonEnv::Static()->ReadResource(txt,R_ENABLE);}
			btn1->State()->SetTextL(txt);
			}
		else if (aControl==btn3)
			{
				TFileName message;
				CEikonEnv::Static()->ReadResource(message, R_BUF_GOTOBUY_DLGMSG);
				CAknQueryDialog* dialog = new (ELeave) CAknQueryDialog();
				dialog->SetPromptL(message);
				TInt ret = dialog->ExecuteLD(R_CONTINUE_CANCEL_QUERY);
				if (ret == EEikBidOk)
				{
					Utils::OpenBrowser(KOurPageInOvi);
				}
			}
		else if (aControl==btn2)
			{
			((CquickFMAppUi*)CEikonEnv::Static()->AppUi())->Launch(TUid::Uid(0x10282bef));
			}
		}
	}
CAboutContainer::CAboutContainer():MCoeControlObserver()
{
}

void CAboutContainer::ConstructL(const TRect& aRect)
{
	CreateWindowL();
	iBgContext = CAknsBasicBackgroundControlContext::NewL(KAknsIIDQsnBgAreaMain, aRect, EFalse);
	TFileName fileName = KImageFileName();
	InitComponentArrayL();
#ifndef __WINS__
	Utils::CompleteWithAppPathM(fileName);
#endif

	AknIconUtils::CreateIconL(iBitmap, iMask, fileName, 16386, 16387);
	SetIconSize(aRect);
	SetRect(aRect);
	TInt max;
	TRect cba;
	AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EControlPane,cba);
	max=cba.iTl.iY;
	TBuf<255> txt;
	if (((CquickFMAppUi*)CEikonEnv::Static()->AppUi())->isFMEnabled()){CEikonEnv::Static()->ReadResource(txt,R_DISABLE);}
	else {CEikonEnv::Static()->ReadResource(txt,R_ENABLE);}
	TInt h=CEikonEnv::Static()->TitleFont()->HeightInPixels();
	h=h+10;
	btn1=CAknButton::NewL();
	btn1->CreateWindowL();
	//btn1->SetContainerWindowL(*this);
	btn1->ConstructFromResourceL(R_BUTTON_SWITCH);
	btn1->SetObserver(this);
	btn1->State()->SetTextL(txt);
	btn1->MakeVisible(ETrue);
	btn1->SetSize(TSize(Size().iWidth,h));
	btn1->SetPosition(TPoint(0,max-3*h));
	btn1->ActivateL();
	
	btn2=CAknButton::NewL();
	btn2->CreateWindowL();
	//btn2->SetContainerWindowL(*this);
	btn2->ConstructFromResourceL(R_BUTTON_TO_FM);
	btn2->SetObserver(this);
	btn2->MakeVisible(ETrue);
	btn2->SetSize(TSize(Size().iWidth,h));
	btn2->SetPosition(TPoint(0,max-2*h));
	btn2->ActivateL();
	
	btn3=CAknButton::NewL();
	btn3->CreateWindowL();
	//btn3->SetContainerWindowL(*this);
	btn3->ConstructFromResourceL(R_BUTTON_TO_OVI);
	btn3->SetObserver(this);
	btn3->SetSize(TSize(Size().iWidth,h));
	btn3->SetPosition(TPoint(0,max-h));
	btn3->MakeVisible(ETrue);
	btn3->ActivateL();
	SizeChanged();
	ActivateL();
}

CAboutContainer::~CAboutContainer()
{
	delete iBgContext;
	delete iBitmap;
	delete iMask;
	delete btn1;
	delete btn2;
	delete btn3;
}

TTypeUid::Ptr CAboutContainer::MopSupplyObject(TTypeUid aId)
{
	if (iBgContext != NULL)
	{
		return MAknsControlContext::SupplyMopObject(aId, iBgContext);
	}
	return CCoeControl::MopSupplyObject(aId);
}

void CAboutContainer::DrawStringCentered(const CFont *font, const TDesC &string, TInt& top, TInt width, CWindowGc& gc) const
{
	CArrayFixFlat<TPtrC> *arrStr = new CArrayFixFlat<TPtrC> (5);
	CleanupStack::PushL(arrStr);
	TRAPD(err, AknTextUtils::WrapToArrayL(string, width - 10, *font, *arrStr));
	if (err == KErrNone)
	{
		for (int i = 0; i < arrStr->Count(); i++)
		{
			TInt txtWidth = font->TextWidthInPixels((*arrStr)[i]);
			TPoint pt(width / 2 - txtWidth / 2, top);
			gc.DrawText((*arrStr)[i], pt);
			top += font->HeightInPixels() + 5;
		}
	}
	CleanupStack::PopAndDestroy(arrStr);
}

void CAboutContainer::SizeChanged()
{
	if (iBgContext != NULL)
	{
		iBgContext->SetRect(Rect());
	}
	TInt scrX=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
	TInt scrY=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;
	if (scrY>scrX)
		{
		TInt h=CEikonEnv::Static()->TitleFont()->HeightInPixels();
		h=h+10;
		TInt max;
		TRect cba;
		AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EControlPane,cba);
		max=cba.iTl.iY;
		if (btn1) {btn1->SetPosition(TPoint(0,max-3*h));btn1->SetSize(TSize(Size().iWidth,h));}
		if (btn2) {btn2->SetPosition(TPoint(0,max-2*h));btn2->SetSize(TSize(Size().iWidth,h));}
		if (btn3) {btn3->SetPosition(TPoint(0,max-1*h));btn3->SetSize(TSize(Size().iWidth,h));}
		}
	else
		{
		TInt h=CEikonEnv::Static()->TitleFont()->HeightInPixels();
		h=h+10;
		if (btn1) {btn1->SetPosition(TPoint(scrX/2,1*h));btn1->SetSize(TSize(Size().iWidth/2,h));}
		if (btn2) {btn2->SetPosition(TPoint(scrX/2,2*h));btn2->SetSize(TSize(Size().iWidth/2,h));}
		if (btn3) {btn3->SetPosition(TPoint(scrX/2,3*h));btn3->SetSize(TSize(Size().iWidth/2,h));}
		}
	DrawNow();
}

void CAboutContainer::HandleResourceChange(TInt aType)
{
	if (aType == KEikDynamicLayoutVariantSwitch)
	{
		TRect rect;
		AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
		SetRect(rect);
		SetIconSize(rect);
	}
}

void CAboutContainer::SetIconSize(const TRect& aRect)
{
	TInt icon_width = (TInt)(aRect.Width() / 2);
	TInt icon_height = (TInt)(icon_width / 5.35);
	AknIconUtils::SetSize(iBitmap, TSize(icon_width, icon_height), EAspectRatioPreserved);
	AknIconUtils::SetSize(iMask, TSize(icon_width, icon_height), EAspectRatioPreserved);
}

TInt CAboutContainer::CountComponentControls() const
{
	return NULL; // return nbr of controls inside this container
}

CCoeControl* CAboutContainer::ComponentControl(TInt aIndex) const
{
	switch (aIndex)
	{
		default:
			return NULL;
	}
}

void CAboutContainer::Draw(const TRect& aRect) const
{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();

	// Redraw the background using the default skin
	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	MAknsControlContext* cc = AknsDrawUtils::ControlContext(this);
	AknsDrawUtils::Background(skin, cc, this, gc, aRect);

	TRgb textColor;
	AknsUtils::GetCachedColor(skin, textColor, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG6); // text #6	main area	main area texts	#215

	TRect rect(iBitmap->SizeInPixels());
	TInt client_width;
	if (Rect().Width()>Rect().Height()) {client_width=Rect().Width()/2;}
	else{client_width=Rect().Width();}
	
	TInt bitmap_width = rect.Width();
	TInt bitmap_height = rect.Height();
	TInt x_coord = (client_width - bitmap_width) / 2;
	TInt y_coord = 10;

	TRect canvas = TRect(x_coord - 5, y_coord - 5, x_coord + bitmap_width + 5, y_coord + bitmap_height + 5);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(KRgbWhite);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(KRgbBlack);
	gc.DrawRect(canvas);

	gc.BitBltMasked(TPoint(x_coord, y_coord), iBitmap, rect, iMask, 0);

	gc.SetPenColor(textColor);

	const CFont *font;
	TFileName buff;
	
	TInt width;
	if (Rect().Width()>Rect().Height())
		{width=Rect().Width()/2;}
	else{width=Rect().Width();}
	font = CEikonEnv::Static()->TitleFont();
	gc.UseFont(font);
	TFileName buff_format;
	CEikonEnv::Static()->ReadResource(buff_format, R_PROGRAM_NAME);

	buff.Format(buff_format, VER_MAJOR, VER_MINOR);

	TInt top = font->HeightInPixels() + bitmap_height + 25;
	DrawStringCentered(font, buff, top, width, gc);
	gc.DiscardFont();

	font = CEikonEnv::Static()->DenseFont();
	gc.UseFont(font);

	CEikonEnv::Static()->ReadResource(buff, R_PUBLISHER_INFORMATION);
	DrawStringCentered(font, buff, top, width, gc);

	CEikonEnv::Static()->ReadResource(buff, R_AUTOR_INFORMATION);
	DrawStringCentered(font, buff, top, width, gc);

	CEikonEnv::Static()->ReadResource(buff, R_COPYRIGHT_INFORMATION);
	DrawStringCentered(font, buff, top, width, gc);

	CEikonEnv::Static()->ReadResource(buff, R_SUPPORT_INFORMATION);
	DrawStringCentered(font, buff, top, width, gc);

	CEikonEnv::Static()->ReadResource(buff, R_EMAIL_INFORMATION);
	DrawStringCentered(font, buff, top, width, gc);
	gc.DiscardFont();
}


