
//  WebApiTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.



//  CWebApiTestApp:
//  �� Ŭ������ ������ ���ؼ��� WebApiTest.cpp�� �����Ͻʽÿ�.
//

class CWebApiTestApp : public CWinApp
{
public:
    CWebApiTestApp();

    // �������Դϴ�.
public:
    virtual BOOL InitInstance();

    // �����Դϴ�.

    DECLARE_MESSAGE_MAP()
};

extern CWebApiTestApp theApp;
