
//  WebApiTestDlg.h : ��� ����
//

#pragma once

#include "ccWin32API/ccWin32RgWebApiTransactionNotifier.h"


//  CWebApiTestDlg ��ȭ ����
class CWebApiTestDlg : public CDialogEx, public ccWin32RgWebApiTransactionNotifier

{
    //  �����Դϴ�.
public:
    CWebApiTestDlg(CWnd* pParent = NULL);    // ǥ�� �������Դϴ�.

    //  ��ȭ ���� �������Դϴ�.
    enum { IDD = IDD_CCWEBAPITEST_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    //  DDX/DDV �����Դϴ�.


    //  �����Դϴ�.
protected:
    HICON m_hIcon;

    //  ������ �޽��� �� �Լ�
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedRequestAPI();
    afx_msg void OnEnChangeRequestData();

protected:
    virtual void    OnTransactionRecveResponse(const std::string& strResponse);
    virtual void    OnTransactionRequestTimeout();

protected:
    void    DoUpdateConfiguration();
    BOOL    DoRequestAPI();

    CString     _strRequestData;
    CString     _strResponseData;

    CString     _strServerIP;
    UINT        _uServerPort;
    CString     _strWebAPI;
public:
    CString _strMethod;
};
