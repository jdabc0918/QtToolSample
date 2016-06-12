#ifndef GGTOOL_H
#define GGTOOL_H

#include <QtWidgets/QMainWindow>
#include "ui_ggtool.h"
#include <glview.h>
#include "common.h"

class ggTool : public QMainWindow
{
	Q_OBJECT
private:
	std::vector<PointWithComment> m_points;
public:
	ggTool(QWidget *parent = 0);
	~ggTool();

private:
	Ui::ggToolClass ui;
	void Load3DPointsData(std::string pointDataStr);
	void ListUpCoordinate();
	std::vector<PointWithComment> GetListData();
private slots:
	void s_Save();
};

#endif // GGTOOL_H
