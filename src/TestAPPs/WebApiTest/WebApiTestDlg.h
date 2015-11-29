
//  WebApiTestDlg.h : ��� ����
//

#pragma once

#include "HSWin32API/IHSWin32RgWebApiTransactionNotifier.h"


//  CWebApiTestDlg ��ȭ ����
class CWebApiTestDlg : public CDialogEx, public IHSWin32RgWebApiTransactionNotifier

{
    //  �����Դϴ�.
public:
    CWebApiTestDlg(CWnd* pParent = NULL);    // ǥ�� �������Դϴ�.

    //  ��ȭ ���� �������Դϴ�.
    enum { IDD = IDD_HSPWEBAPITEST_DIALOG };

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
    afx_msg void OnBnClickedPerformTest();
    afx_msg void OnBnClickedVerify();
    afx_msg void OnEnChangeSendData();


protected:
    virtual void    OnTransactionRecveResponse(const CString& strResponse);
    virtual void    OnTransactionRequestTimeout();


protected:
    void    DoUpdateConfiguration();
    BOOL    DoRequestLogin();
    BOOL    DoRequestAPI();

    CString     _strSendData;
    CString     _strReceiveData;

    CString     _strPassword;
    CString     _strRgBoxIP;
    UINT        _uRgBoxPort;
    CString     _strRgBoxID;
    CString     _strRgBoxPassword;
    CString     _strRgOpenAPIToken;
    CString     _strRgMethod;
};
