// Calendar.cpp : 实现文件
//

#include "stdafx.h"
#include "YX_TEST1_1.h"
#include "Calendar.h"


// CCalendar

IMPLEMENT_DYNAMIC(CCalendar, CWnd)

CCalendar::CCalendar()
{
	m_intervalSpace = 30;
	font.CreateFont(
		20, 10,0,0,100,
		FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("宋体"));
	
}

CCalendar::~CCalendar()
{
}


BEGIN_MESSAGE_MAP(CCalendar, CWnd)
END_MESSAGE_MAP()



// CCalendar 消息处理程序




void CCalendar::init(int x, int y, CDC * pdc, int r)
{
	m_pdc = pdc;
	CTime time;
	time = CTime::GetCurrentTime();
	m_year = time.GetYear();//年份
	m_mouth = time.GetMonth();//月份
	m_dayOfWeek = time.GetDayOfWeek();//周几
	m_startWeek = (1 + 2 * m_mouth + 3 * (m_mouth + 1) / 5 + m_year + m_year / 4 - m_year / 100 + m_year / 400) % 7;  
	m_day = time.GetDay();//日
	m_startPointX = x;
	m_startPointY = y;
	m_clockR = r;
	//run(pdc);
	
	drawTitle();
	drawDay();
}


void CCalendar::drawTitle(void)
{
	
	m_pdc->SelectObject(&font);
	CString year;
	year.Format(_T("%d"), m_year);
	CString mouth;
	mouth.Format(_T("%d"), m_mouth);
	CString day;
	day.Format(_T("%d"), m_day);
	CString l1("年");
	CString l2("月");
	CString l3("日");
	CString time;
	time = year + l1 + mouth + l2 + day + l3;

	m_pdc->TextOut(m_startPointX + m_clockR * 2 + 25, m_startPointY - 30, time);
	m_pdc->TextOut(m_startPointX + m_clockR * 2 , m_startPointY, _T("日"));
	m_pdc->TextOut(m_startPointX + m_clockR * 2 + m_intervalSpace, m_startPointY, _T("一"));
	m_pdc->TextOut(m_startPointX + m_clockR * 2 + m_intervalSpace * 2, m_startPointY, _T("二"));
	m_pdc->TextOut(m_startPointX + m_clockR * 2 + m_intervalSpace * 3, m_startPointY, _T("三"));
	m_pdc->TextOut(m_startPointX + m_clockR * 2 + m_intervalSpace * 4, m_startPointY, _T("四"));
	m_pdc->TextOut(m_startPointX + m_clockR * 2 + m_intervalSpace * 5, m_startPointY, _T("五"));
	m_pdc->TextOut(m_startPointX + m_clockR * 2 + m_intervalSpace * 6, m_startPointY, _T("六"));
}


void CCalendar::drawDay(void)
{
	int allDay = 30;
	if(m_mouth == 1 || m_mouth == 3 || m_mouth == 5 || m_mouth == 7 || m_mouth == 8 || m_mouth == 10 || m_mouth == 12) allDay = 31; //判断是否为大月，大月一个月为31天
	else if (m_mouth == 2){
		//判断是否为闰年，闰年2月是29天
		if(m_year%400==0 || m_year%4==0&&m_year%100!=0){
			allDay = 29;
		}else{
			allDay = 28;//平年2月18天
		}
	
	}else allDay = 30;//小月天数30天
	
	int afterWeeks = 1;//是否过了7天，用于计算y轴
	for(int i = 1;i <= allDay; i++){
		m_startWeek ++;
		if(m_startWeek >= 7){
			m_startWeek = 0;//星期几，用于计算x轴
			afterWeeks ++;
		}
		if(i == m_day){//如果是当天，那么就画出一个黑框
			CPen pen;
			CRect rect(m_startPointX + m_clockR * 2 + m_intervalSpace * m_startWeek - m_intervalSpace / 4, 
						m_startPointY + afterWeeks * 40 - m_intervalSpace / 10,
						m_startPointX + m_clockR * 2 + m_intervalSpace * m_startWeek + m_intervalSpace - 5, 
						m_startPointY + afterWeeks * 45);
			m_pdc->SelectObject(&pen);
			m_pdc->Rectangle(&rect);
		}
		CString buf ;
		buf.Format(_T("%d"), i);//将整数转为CString
		m_pdc->TextOut(m_startPointX + m_clockR * 2 + m_intervalSpace * m_startWeek, m_startPointY + afterWeeks * 40, buf);//写出日期
		
	}
}


int CCalendar::getDayOfWeek(void)
{
	return m_dayOfWeek;
}
