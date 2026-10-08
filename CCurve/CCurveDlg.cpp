
// CCurveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CCurve.h"
#include "CCurveDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCCurveDlg 对话框




CCCurveDlg::CCCurveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCCurveDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nU_C1 = new short[20000];           
	m_nU_C2 = new short[20000];
	m_nU_C3 = new short[20000];
	m_nU_C4 = new short[20000];
}

void CCCurveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCCurveDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CCCurveDlg 消息处理程序

BOOL CCCurveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标

	CRect rect;
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	int cxIcon = GetSystemMetrics(SM_CXICON);
	int cyIcon = GetSystemMetrics(SM_CYICON);
	GetClientRect(&rect);
	int x = (rect.Width() - cxIcon + 1) / 2;
	int y = (rect.Height() - cyIcon + 1) / 2;

	FILE* m_pf;
	fopen_s(&m_pf, "2021228152930lubo_r.txt", "r");
	if (!m_pf)
		return false;
	for (int i = 0; i < 20000; i++)
	{
		fscanf_s(m_pf, "%d", m_nU_C1 + i);
	}
	for (int i = 0; i < 20000; i++)
	{
		fscanf_s(m_pf, "%d", m_nU_C2 + i);
	}
	for (int i = 0; i < 20000; i++)
	{
		fscanf_s(m_pf, "%d", m_nU_C3 + i);
	}
	for (int i = 0; i < 20000; i++)
	{
		fscanf_s(m_pf, "%d", m_nU_C4 + i);
	}
	fclose(m_pf);

	CChartStandardAxis* pBottomAxis0 =
		m_Chartctrl1.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis0->SetMinMax(0, DATA_SHOW_LENGHT_PICE); //1000);
	CChartStandardAxis* pTopAxis0 =
		m_Chartctrl1.CreateStandardAxis(CChartCtrl::TopAxis);
	pTopAxis0->SetMinMax(0, DATA_SHOW_LENGHT_PICE); //1000);
	
	m_Chartctrl1.m_nchartnum = 0; 
	m_Chartctrl1.m_pBottomAxis = pBottomAxis0;//设置坐标轴用于缩放
											  
	m_Chartctrl1.m_pTopAxis = pTopAxis0; //设置坐标轴用于缩放

	m_Chartctrl1.SetEdgeType(3);
	m_Chartctrl1.SetPanEnabled(true);
	m_Chartctrl1.SetZoomEnabled(TRUE);

	CChartStandardAxis* pLeftAxis0 =
		m_Chartctrl1.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis0->SetMinMax(-10, 200);

	CChartAxisLabel* label;
	label = pBottomAxis0->GetLabel();
	label->SetText(_T("时间"));
	TChartString strText = label->GetText();
	pLeftAxis0->SetAutomatic(FALSE); //zoom to fit	
	label = pLeftAxis0->GetLabel();
	label->SetText(_T("平台电流"));

	CChartLineSerie* pLineSerie;
	pLineSerie = m_Chartctrl1.CreateLineSerie();
	m_pSeries1_1 = pLineSerie;
	int i;
	for (i = 0; i < DATA_SHOW_LENGHT_PICE; i++)
	{		
			y1Buff[i] = m_nU_C3[i];
			x1Buff[i] = i;			
	}


	TChartString Name;
	pLineSerie->AddPoints(x1Buff, y1Buff, DATA_SHOW_LENGHT_PICE);
	Name = _T("电流1");//设置标识
	pLineSerie->SetName(Name); //设置标识

	pLineSerie->SetColor(RGB(255, 0, 0));
	pLineSerie->SetSeriesOrdering(poNoOrdering);//设置为无序


	CChartLineSerie* pLineSerie1;
	pLineSerie1 = m_Chartctrl1.CreateLineSerie();
	m_pSeries1_2 = pLineSerie1;
	for (i = 0; i < DATA_SHOW_LENGHT_PICE; i++)
	{		
		y1Buff[i] = m_nU_C4[i];				
	}


	pLineSerie1->AddPoints(x1Buff, y1Buff, DATA_SHOW_LENGHT_PICE);
	Name = _T("电流2");//设置标识
	pLineSerie1->SetName(Name); //设置标识
							  
	pLineSerie1->SetColor(RGB(0, 255, 0));
	pLineSerie1->SetSeriesOrdering(poNoOrdering); //设置为无序

	m_Chartctrl1.GetLegend()->SetVisible(true);/**/
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCCurveDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCCurveDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCCurveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

