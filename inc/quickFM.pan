
#ifndef QUICKFM_PAN_H
#define QUICKFM_PAN_H

/** quickFM application panic codes */
enum TquickFMPanics
	{
	EquickFMUi = 1
	// add further panics here
	};

inline void Panic(TquickFMPanics aReason)
	{
	_LIT(applicationName,"quickFM");
	User::Panic(applicationName, aReason);
	}

#endif // QUICKFM_PAN_H
