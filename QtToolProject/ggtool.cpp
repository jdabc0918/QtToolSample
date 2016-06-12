#include "ggtool.h"

ggTool::ggTool(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//	点データの読み込み
	std::string data = "3d_points.csv";
	Load3DPointsData(data);

	//	点リストの表示
	ListUpCoordinate();

	//	GLViewへ点情報をセット
	ui.widget->Set3DPointsData(m_points);
}

ggTool::~ggTool()
{

}

void ggTool::Load3DPointsData(std::string pointDataStr)
{
	//	ファイルオープン
	std::ifstream ifs(pointDataStr, std::ios::in);
	if (!ifs.is_open())
	{
		std::cerr << __FUNCTION__ << " error : cannot open file." << std::endl;
		return;
	}

	//	クリア
	m_points.clear();
	//	ロード＆プッシュ
	std::string line;
	while (std::getline(ifs, line))
	{
		PointWithComment tmp;
		cv::Point3f *p = &tmp.first;
		std::string *str = &tmp.second;

		std::replace(line.begin(), line.end(), ',', ' ');
		std::stringstream ss(line);
		ss >> p->x >> p->y >> p->z >> *str;
		m_points.push_back(tmp);
		//int ret = sscanf_s(line.c_str(), "%f,%f,%f,%s", &p->x, &p->y, &p->z, str);
		//if (ret >= 3) m_points.push_back(tmp);
	}

}

void ggTool::ListUpCoordinate()
{
	int pointNum = (int)m_points.size();

	//	行数、列数
	ui.coordinateList->setColumnCount(4);
	ui.coordinateList->setRowCount(pointNum);

	//	タイトル行
	ui.coordinateList->setHorizontalHeaderLabels(
		QStringList() << tr("Comment") << tr("x") << tr("y") << tr("z"));

	//	一行選択モード
	ui.coordinateList->setSelectionMode(QAbstractItemView::ContiguousSelection);
	ui.coordinateList->setSelectionBehavior(QAbstractItemView::SelectRows);

	//	各列の設定
	ui.coordinateList->setColumnWidth(0, 170);
	ui.coordinateList->setColumnWidth(1, 60);
	ui.coordinateList->setColumnWidth(2, 60);
	ui.coordinateList->setColumnWidth(3, 60);
	
	//	各行の設定
	for (int i = 0; i < pointNum; i++)
	{
		//	高さセット
		ui.coordinateList->setRowHeight(i, 20);

		//	座標値セット＆編集不可に
		cv::Point3f p = m_points[i].first;
		ui.coordinateList->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(m_points[i].second)));
		ui.coordinateList->setItem(i, 1, new QTableWidgetItem(QString::fromStdString((boost::format("%f") % p.x).str())));
		ui.coordinateList->setItem(i, 2, new QTableWidgetItem(QString::fromStdString((boost::format("%f") % p.y).str())));
		ui.coordinateList->setItem(i, 3, new QTableWidgetItem(QString::fromStdString((boost::format("%f") % p.z).str())));
	}
}

std::vector<PointWithComment> ggTool::GetListData()
{
	std::vector<PointWithComment> ret = m_points;
	
	int pointNum = (int)m_points.size();

	for (int i = 0; i < pointNum; i++)
	{
		QTableWidgetItem *item = ui.coordinateList->item(i, 0);

		QString qstr = item->text();
		std::string com = qstr.toStdString();
		ret[i].second = com;
	}

	return ret;
}

void ggTool::s_Save()
{

	int pointNum = (int)m_points.size();
	std::string output = "3d_points.csv";
	std::string output_bu = "3d_points_backup.csv1";

	//	バックアップを保存する
	std::ofstream ofs(output_bu, std::ios::out);
	for (int i = 0; i < pointNum; i++)
	{
		cv::Point3f p = m_points[i].first;
		std::string str = m_points[i].second;
		ofs << p.x << "," << p.y << "," << p.z << "," << str << std::endl;
	}
	ofs.close();

	//	更新版を保存する
	std::vector<PointWithComment> pts = GetListData();

	ofs.open(output, std::ios::out);
	for (int i = 0; i < pointNum; i++)
	{
		cv::Point3f p = pts[i].first;
		std::string str = pts[i].second;
		ofs << p.x << "," << p.y << "," << p.z << "," << str << std::endl;
	}

	//	確認ボックス
	QMessageBox box;
	box.setText(QString::fromStdString("Saved following file.\n" + output));
	box.exec();
}