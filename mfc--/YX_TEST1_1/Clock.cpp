// Clock.cpp : ʵ���ļ�
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

	m_pen[0].CreatePen(PS_SOLID,1, RGB(0,0,0));//3 6 9 12����
	m_pen[1].CreatePen(PS_SOLID,1, RGB(178,34,34));//����ʱ��
	m_pen[2].CreatePen(PS_SOLID,3, RGB(0,0,0));//����
	m_pen[3].CreatePen(PS_SOLID,3, RGB( 0,0,128));//����
	m_pen[4].CreatePen(PS_SOLID,3, RGB(178,34,34));//ʱ��

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



// CClock ��Ϣ�������




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
	m_pdc->SelectObject(&m_pen[0]);//ѡ�񻭱�
	double startX,startY;//��ʼ��
	
	double rotate = 0;//�Ƕ�
	double PI = 3.14159;
	for(int i=0;i<12;i++){
		CBrush brush(RGB( 225,255,255));//��ˢ
		m_pdc->SelectObject(&brush);//ѡ��ˢ
		CRect rect(m_startPointX, m_startPointY, m_startPointX+m_hourPointR, m_startPointY+m_hourPointR);//λ��
		startX = sin(PI/180*rotate)*m_clockR;
		startY = m_clockR - cos(PI/180*rotate)*m_clockR;
		rect.OffsetRect(startX,startY);//ƫ��λ��
		m_pdc->Ellipse(&rect);//����Բ��
		rotate+=30;
		
	}
}


void CClock::drawMinutePoint(void)
{
	CBrush brush(RGB( 0,0,128));//��ˢ
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
	m_pdc->SelectObject(&m_pen[2]);//ѡ�񻭱�
	m_pdc->MoveTo(m_centerX, m_centerY);//ѡ����ʼ��

	double rotate = m_secondTime * 6;//ƫ�ƽǶ�
	double endX = m_centerX + sin(PI/180 * rotate)*m_secondLength;//�յ�X
	double endY = m_centerY - cos(PI/180 * rotate)*m_secondLength;//�յ�y
	m_pdc->LineTo(endX, endY);//ѡ���յ�
	drawMinuteLine();//������
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

//������ʱ��
void CClock::drawTimeTxt(void)
{
	int fontHeight = 25;//�ָ�
	int fontWidth = 8;//�ֿ�
	
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
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("����"));
	m_pdc->SelectObject(&font);
	if(m_dayOfWeek == 1) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("������"));
	else if(m_dayOfWeek == 2) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("����һ"));
	else if(m_dayOfWeek == 3) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("���ڶ�"));
	else if(m_dayOfWeek == 4) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("������"));
	else if(m_dayOfWeek == 5) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("������"));
	else if(m_dayOfWeek == 6) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("������"));
	else if(m_dayOfWeek == 7) m_pdc->TextOut(m_startPointX - fontWidth * 2, m_startPointY + m_clockR * 2 + fontHeight + 10, _T("������"));
}


void CClock::intervalTime(void)
{
	m_secondTime ++;//������һ
	if(m_secondTime >= 60){//��������60ʱ����ʾ����һ����
		m_minuteTime ++;
		m_secondTime = 0;
	}
	if(m_minuteTime >= 60){//��������60ʱ����ʾ����һСʱ
		m_hourTime ++;
		m_minuteTime = (int)m_minuteTime % 60;
		drawHourLine();
	}
	if(m_hourTime >= 12){//��ʱ�뵽12ʱ����ʾʱ��ת��һȦ
		m_hourTime = (int)m_hourTime % 12;
	}
}


