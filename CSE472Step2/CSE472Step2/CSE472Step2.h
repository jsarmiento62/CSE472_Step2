
// CSE472Step2.h : main header file for the CSE472Step2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCSE472Step2App:
// See CSE472Step2.cpp for the implementation of this class
//

class CCSE472Step2App : public CWinAppEx
{
public:
	CCSE472Step2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCSE472Step2App theApp;
