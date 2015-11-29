
// WebApiTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "WebApiTest.h"
#include "WebApiTestDlg.h"
#include "afxdialogex.h"

#include <afxinet.h>  
#include "HSWin32API/HSWin32RgWebApiHelper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // ��ȭ ���� �������Դϴ�.
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

    // �����Դϴ�.
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWebApiTestDlg ��ȭ ����




CWebApiTestDlg::CWebApiTestDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CWebApiTestDlg::IDD, pParent)
    , _strSendData(_T(""))
    , _strReceiveData(_T(""))
    , _strPassword(_T(""))
    , _strRgBoxIP(_T(""))
    , _uRgBoxPort(0)
    , _strRgBoxID(_T(""))
    , _strRgBoxPassword(_T(""))
    , _strRgMethod(_T(""))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebApiTestDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SEND_DATA, _strSendData);
    DDX_Text(pDX, IDC_RECEIVE_DATA, _strReceiveData);

    DDX_Text(pDX, IDC_PASSWORD, _strPassword);
    DDX_Text(pDX, IDC_RG_BOX_IP, _strRgBoxIP);
    DDX_Text(pDX, IDC_RG_BOX_PORT, _uRgBoxPort);
    DDX_Text(pDX, IDC_RG_BOX_ID, _strRgBoxID);
    DDX_Text(pDX, IDC_RG_BOX_PASSWORD, _strRgBoxPassword);
    DDX_Text(pDX, IDC_MATHOD, _strRgMethod);

}

BEGIN_MESSAGE_MAP(CWebApiTestDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_PERFORM_TEST, &CWebApiTestDlg::OnBnClickedPerformTest)
    ON_BN_CLICKED(IDC_VERIFY, &CWebApiTestDlg::OnBnClickedVerify)
    ON_EN_CHANGE(IDC_SEND_DATA, &CWebApiTestDlg::OnEnChangeSendData)
END_MESSAGE_MAP()


// CWebApiTestDlg �޽��� ó����

BOOL CWebApiTestDlg::OnInitDialog()
{

    CDialogEx::OnInitDialog();

    // �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

    // IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
    //  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
    SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
    SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

    // TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

    return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CWebApiTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CWebApiTestDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // �������� �׸��ϴ�.
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CWebApiTestDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CWebApiTestDlg::DoUpdateConfiguration()
{
    UpdateData();

    AfxGetApp()->WriteProfileString(_T("Config"), _T("RgBoxIP"), _strRgBoxIP);
    AfxGetApp()->WriteProfileInt(_T("Config"), _T("RgBoxPort"), _uRgBoxPort);

    AfxGetApp()->WriteProfileString(_T("Config"), _T("RgBoxID"), _strRgBoxID);
    AfxGetApp()->WriteProfileString(_T("Config"), _T("RgBoxPassword"), _strRgBoxPassword);

    AfxGetApp()->WriteProfileString(_T("Config"), _T("SendData"),   _strSendData);
    AfxGetApp()->WriteProfileString(_T("Config"), _T("RgMethod"),   _strRgMethod);

    HSWin32RgWebApiHelper::getInstance()->SetConnectionInfo(_strRgBoxIP, _uRgBoxPort);
}

BOOL CWebApiTestDlg::DoRequestLogin()
{
    CString     strResponse;
    Json::Value oParams;

    oParams["id"]           = (LPCTSTR)_strRgBoxID;
    oParams["password"]     = (LPCTSTR)_strRgBoxPassword;

    _strRgOpenAPIToken = "";

    if (HSWin32RgWebApiHelper::getInstance()->RequestAPI("login", oParams, strResponse))
    {
        Json::Value     oValue;
        Json::Reader    oReader;

        std::string strData = strResponse;

        if (oReader.parse(strData, oValue) == true)
        {
            HSWin32RgWebApiHelper::getValueString(oValue, "token", _strRgOpenAPIToken, _T(""));
            HSWin32RgWebApiHelper::getInstance()->SetToken(_strRgOpenAPIToken);

            return TRUE;
        }

        MessageBox("It's invalid ID or Password!. Please check the login info.", "Warring", MB_ICONWARNING);
    }
    else
    {
        MessageBox("Could not connect to HUMAX RG Box!", "Warring", MB_ICONWARNING);
    }

    return FALSE;
}

void CWebApiTestDlg::OnTransactionRecveResponse(const CString& strResponse)
{
    if (!IsWindow(m_hWnd))
        return;

    Json::Value     oValue;
    Json::Reader    oReader;

    std::string strData = strResponse;

    if (oReader.parse(strData, oValue) == false)
        OnTransactionRequestTimeout();
}

void CWebApiTestDlg::OnTransactionRequestTimeout()
{
    if (!IsWindow(m_hWnd))
        return;
}

BOOL CWebApiTestDlg::DoRequestAPI()
{
    UpdateData();
    CString     strResponse;
    Json::Value     oParams;
    Json::Reader    oRequestReader;
    _strReceiveData = "";

    if (oRequestReader.parse((const char *)_strSendData, oParams) == false)
    {
        MessageBox("JCON Parser Error!", "Warring", MB_ICONWARNING);
        UpdateData(FALSE);
        return FALSE;
    }

    if (HSWin32RgWebApiHelper::getInstance()->RequestAPI(_strRgMethod, oParams, strResponse))
    {
        _strReceiveData = strResponse;
        _strReceiveData.Replace("\n", "\r\n");
    }
    else
        MessageBox("Could not connect to HUMAX RG Box!", "Warring", MB_ICONWARNING);

    UpdateData(FALSE);

    return TRUE;
}

void CWebApiTestDlg::OnBnClickedPerformTest()
{
    DoUpdateConfiguration();

    if (_strRgOpenAPIToken == "")
    {
        if (DoRequestLogin() == FALSE)
            return;
    }

    DoRequestAPI();
}


void CWebApiTestDlg::OnBnClickedVerify()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

    const char pAuthorizedPassword[] = {
        '@', '!', 'R', 'G', 'D', 'e', 'v', 'c', 'h', 'l', 'r', 'h', '!', '!', NULL};

    UpdateData();

    if (_strPassword == pAuthorizedPassword)
    {
        GetDlgItem(IDC_PASSWORD)->EnableWindow(FALSE);
        GetDlgItem(IDC_VERIFY)->EnableWindow(FALSE);

        GetDlgItem(IDC_RG_BOX_IP)->EnableWindow(TRUE);
        GetDlgItem(IDC_RG_BOX_PORT)->EnableWindow(TRUE);

        GetDlgItem(IDC_RG_BOX_ID)->EnableWindow(TRUE);
        GetDlgItem(IDC_RG_BOX_PASSWORD)->EnableWindow(TRUE);

        GetDlgItem(IDC_MATHOD)->EnableWindow(TRUE);

        GetDlgItem(IDC_PERFORM_TEST)->EnableWindow(TRUE);
        GetDlgItem(IDC_SEND_DATA)->EnableWindow(TRUE);
        GetDlgItem(IDC_RECEIVE_DATA)->EnableWindow(TRUE);

        _strRgBoxIP = AfxGetApp()->GetProfileString("Config", "RgBoxIP", "192.168.0.1");
        _uRgBoxPort = AfxGetApp()->GetProfileInt("Config", "RgBoxPort", 80);

        _strRgBoxID         = AfxGetApp()->GetProfileString("Config", "RgBoxID", "root");
        _strRgBoxPassword   = AfxGetApp()->GetProfileString("Config", "RgBoxPassword", "humax");

        _strSendData    = AfxGetApp()->GetProfileString(_T("Config"), _T("SendData"),   _T(""));
        _strRgMethod    = AfxGetApp()->GetProfileString(_T("Config"), _T("RgMethod"),   _T("Device.setDBInfo"));
    }
    else
        GetDlgItem(IDC_PASSWORD)->SetFocus();


    _strPassword = _T("");

    UpdateData(FALSE);
}


void CWebApiTestDlg::OnEnChangeSendData()
{
    // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
    // __super::OnInitDialog() �Լ��� ������ 
    //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
    // �� �˸� �޽����� ������ �ʽ��ϴ�.

    // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
