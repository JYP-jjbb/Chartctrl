
// CCurveDlg.h : 头文件
//

#pragma once
#include "ChartCtrl\ChartAxisLabel.h"              
#include "ChartCtrl\ChartLineSerie.h"
#include "resource.h"   // 解决未声明标识符报错

// 注意：原文档缺少空格！！DATA_SHOW_LENGHT_PICE  =20000
#define DATA_SHOW_LENGHT_PICE 20000


// CCCurveDlg 对话框
class CCCurveDlg : public CDialogEx
{
// 构造
public:
	// 原始数据指针，存储读取文件4路通道
    short * m_nU_C1;
    short* m_nU_C2;
    short* m_nU_C3;
    short* m_nU_C4;

    //绘图缓冲区
    double y1Buff[DATA_SHOW_LENGHT_PICE];
    double x1Buff[DATA_SHOW_LENGHT_PICE];

    // 原始文档语法错误：不能 =; 删掉 =;
    double yy1Buff[2];
    double xx1Buff[2];

    CChartXYSerie* m_pSeries1_1;
    CChartXYSerie* m_pSeries1_2;

    // 文件指针，用于读取txt
    FILE* m_pf;

    CChartCtrl m_Chartctrl1; // 控件变量，向导生成也可以

	CCCurveDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CCURVE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
