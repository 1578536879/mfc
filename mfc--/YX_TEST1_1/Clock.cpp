// Clock.cpp : 实现文件
//

#include "stdafx.h"
#include "YX_TEST1_1.h"
#include "Clock.h"
#include <math.h>
#include<string>
#include<sstream>
using namespace std;
// CClock

IMPLEMENT_DYNAMIC(CClock, CWnd)

CClock::CClock()
{
	CTime time = CTime::GetCurrentTime();
	m_clockR = 100;
	m_hourPointR=8;
	m_minutePointR=3;

	m_startPointX= GetSystemMetrics(SM_CXFULLSCREEN) / 4 - 100;                                                                                                                                                                                                                                                                                             
	m_startPointY= GetSystemMetrics(SM_CYFULLSCREEN) / 8 + 50; 
	m_centerX = m_startPointX;
	m_centerY = m_startPointY + m_clockR;

	m_pen[0].CreatePen(PS_SOLID,1, RGB(0,0,0));//3 6 9 12整点
	m_pen[1].CreatePen(PS_SOLID,1, RGB(178,34,34));//其余时间
	m_pen[2].CreatePen(PS_SOLID,3, RGB(0,0,0));//秒钟
	m_pen[3].CreatePen(PS_SOLID,3, RGB( 0,0,128));//分钟
	m_pen[4].CreatePen(PS_SOLID,3, RGB(178,34,34));//时钟

	m_secondLength = 80;
	m_minuteLength = 60;
	m_hourLength = 50;
	m_hourTime = time.GetHour();
	m_secondTime = time.GetSecond();
	m_minuteTime = time.GetMinute();
}

CClock::~CClock()
{
}


BEGIN_MESSAGE_MAP(CClock, CWnd)
END_MESSAGE_MAP()



// CClock 消息处理程序




void CClock::init(int week, CDC * pdc)
{
	m_dayOfWeek = week;
	m_pdc = pdc;
	drawHourPoint();
	drawMinutePoint();
	drawMinuteLine();
	drawSecondLine(); 
	drawDayOFWeek();
	drawTimeTxt();
}


void CClock::drawHourPoint(void)
{
	m_pdc->SelectObject(&m_pen[0]);//选择画笔
	double startX,startY;//起始点
	
	double rotate = 0;//角度
	double PI = 3.14159;
	for(int i=0;i<12;i++){
		CBrush brush(RGB( 225,255,255));//画刷
		m_pdc->SelectObject(&brush);//选择画刷
		CRect rect(m_startPointX, m_startPointY, m_startPointX+m_hourPointR, m_startPointY+m_hourPointR);//位置
		startX = sin(PI/180*rotate)*m_clockR;
		startY = m_clockR - cos(PI/180*rotate)*m_clockR;
		rect.OffsetRect(startX,startY);//偏移位置
		m_pdc->Ellipse(&rect);//画出圆形
		rotate+=30;
		
	}
}


void CClock::drawMinutePoint(void)
{
	CBrush brush(RGB( 0,0,128));//画刷
	m_pdc->SelectObject(&brush);
	m_pdc->SelectObject(&m_pen[1]);
	double startX,startY;
	
	double rotate = 0;
	double PI = 3.14159;
	for(int i=1;i<60;i++){
		rotate+=6;
		if(i%5==0) continue;
		CRect rect(m_startPointX,m_startPointY,m_startPointX+m_minutePointR,m_startPointY+m_minutePointR);
		startX = sin(PI/180*rotate)*(m_clockR-m_minutePointR);
		startY = m_clockR - cos(PI/180*rotate)*(m_clockR-m_minutePointR);
		rect.OffsetRect(startX,startY);
		m_pdc->Ellipse(&rect);
	}
	
}


void CClock::drawSecondLine(void)
{
	double PI = 3.14159;
	//m_pdc->SelectObject(&brush);
	m_pdc->SelectObject(&m_pen[2]);//选择画笔
	m_pdc->MoveTo(m_centerX, m_centerY);//选择起始点

	double rotate = m_secondTime * 6;//偏移角度
	double endX = m_centerX + sin(PI/180 * rotate)*m_secondLength;//终点X
	double endY = m_centerY - cos(PI/180 * rotate)*m_secondLength;//终点y
	m_pdc->LineTo(endX, endY);//选择终点
	drawMinuteLine();//画分针
}


void CClock::drawMinuteLine(void)
{
	double PI = 3.14159;
	double rotate = m_minuteTime * 6;
	double endX = m_centerX + sin(PI/180 * rotate)*m_minuteLength;
	double endY = m_centerY - cos(PI/180 * rotate)*m_minuteLength;
	m_pdc->SelectObject(&m_pen[3]);
	m_pdc->MoveTo(m_centerX, m_centerY);
	m_pdc->LineTo(endX, endY);
	drawHourLine();
}


void CClock::drawHourLine(void)
{
	double PI = 3.14159;
	double rotate = m_hourTime * 30;
	double endX = sin(PI/180 * rotate)*m_hourLength + m_centerX;
	double endY = m_centerY - cos(PI/180 * rotate)*m_hourLength;
	m_pdc->SelectObject(&m_pen[4]);
	m_pdc->MoveTo(m_centerX, m_centerY);
	m_pdc->LineTo(endX, endY);
}


int CClock::getStartX(void)
{
	return m_startPointX;
}


int CClock::getStartY(void)
{
	return m_startPointY;
}


int CClock::getR(void)
{
	return m_clockR;
}

//画数字时钟
void CClock::drawTimeTxt(void)
{
	int fontHeight = 25;//字高
	int fontWidth = 8;//字宽
	
	stringstream s1;
	s1<<m_hourTime;
	string h = s1.str();

	stringstream s2;
	s2<<m_minuteTime;
	string min=s2.str();

	stringstream s3;
	s3<<m_secondTime;
	string sec=s3.str();
	
	CString hour;
	hour=CA2T(h.c_str());
	CString minute ;
	minute=CA2T(min.c_str());
	//minute.Format(_T("%d"), m_minuteTime);
	CString second ;
	second=CA2T(sec.c_str());
	//second.Format(_T("%d"), m_secondTime);
	CString colon(":");

	CString time = hour + colon + minute + colon + second;
	m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + 10, time);
}


void CClock::drawDayOFWeek(void)
{
	int fontHeight = 25;
	int fontWidth = 8;
	CFont font;
	font.CreateFont(
		fontHeight,fontWidth,0,0,100,
		FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("宋体"));
	m_pdc->SelectObject(&font);
	if(m_dayOfWeek == 1) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("星期天"));
	else if(m_dayOfWeek == 2) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("星期一"));
	else if(m_dayOfWeek == 3) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("星期二"));
	else if(m_dayOfWeek == 4) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("星期三"));
	else if(m_dayOfWeek == 5) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("星期四"));
	else if(m_dayOfWeek == 6) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("星期五"));
	else if(m_dayOfWeek == 7) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("星期六"));
}


void CClock::intervalTime(void)
{
	m_secondTime ++;//秒数加一
	if(m_secondTime >= 60){//当秒数到60时，表示过了一分钟
		m_minuteTime ++;
		m_secondTime = 0;
	}
	if(m_minuteTime >= 60){//当分数到60时，表示过了一小时
		m_hourTime ++;
		m_minuteTime = (int)m_minuteTime % 60;
		drawHourLine();
	}
	if(m_hourTime >= 12){//当时针到12时，表示时针转了一圈
		m_hourTime = (int)m_hourTime % 12;
	}
}


