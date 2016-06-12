#ifndef TTTOOL_H
#define TTTOOL_H

#include <QWidget>
#include "ui_tttool.h"
#include <QComboBox>

class ttTool : public QWidget
{
	Q_OBJECT
private:
	typedef std::pair<int, int> PairIndex;

	std::vector<cv::Point> m_2Dpoints;
	
	std::vector<PointWithComment> m_3Dpoints;

	std::vector<PairIndex> m_2D3Dpairs;

public:
	ttTool(QWidget *parent = 0);
	~ttTool();

private:
	Ui::ttTool ui;
	void Load2DPointsData(std::string pointDataStr2D);
	void Load3DPointsData(std::string pointDataStr3D);
	void InitPairIndex();

	void ListUp2DPoint();

	std::vector<PairIndex> GetPairs();

	double AutoSelection(cv::Mat RT);
	private slots:
	void s_Save();
};

#endif // TTTOOL_H
