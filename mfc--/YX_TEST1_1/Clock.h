#pragma once


// CClock

class CClock : public CWnd
{
	DECLARE_DYNAMIC(CClock)

	int m_clockR;
	int m_hourPointR;
	int m_minutePointR;

	int m_startPointX;                                                                                                                                                                                                                                                                                               
	int m_startPointY;
	int m_centerX;
	int m_centerY;

	CPen m_pen[5];

	int m_secondLength;
	int m_minuteLength;
	int m_hourLength;
	double m_secondTime;
	double m_minuteTime;
	double m_hourTime;
	CDC *m_pdc;

	int m_dayOfWeek;
public:
	CClock();
	virtual ~CClock();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void init(int week, CDC * pdc);
	void drawHourPoint(void);
	void drawMinutePoint(void);
	void drawHourLine(void);
	void drawMinuteLine(void);
	void drawSecondLine(void);
	int getStartX(void);
	int getStartY(void);
	void drawTimeTxt(void);
	void drawDayOFWeek(void);
	void intervalTime(void);
	int getR(void);
};


