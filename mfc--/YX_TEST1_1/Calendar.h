#pragma once


// CCalendar

class CCalendar : public CWnd
{
	DECLARE_DYNAMIC(CCalendar)

	int m_dayOfWeek;
	int m_year;
	int m_mouth;
	int m_day;
	int m_intervalSpace;
	int m_clockR;
	int m_startWeek;
	CFont font ;
	int m_startPointX;
	int m_startPointY;
	CDC *m_pdc;
public:
	CCalendar();
	virtual ~CCalendar();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void init(int x, int y, CDC * pdc, int r);
	void drawTitle(void);
	void drawDay(void);
	int getDayOfWeek(void);
};


