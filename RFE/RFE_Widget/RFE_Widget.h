#ifndef __RFE_WIDGET_H__
#define __RFE_WIDGET_H__

#include <QtGui>

namespace RFE
{

class Widget : public QWidget
{
Q_OBJECT

private:
	QStandardItemModel *modelView;
	QTreeView *treeView;

	QLineEdit *path, *projectLocation;
	QPushButton *selectResource;
	QPushButton *moveUp, *moveDown;
	QPushButton *addItem, *addGroup, *remove;

	void setupLayout();
	QString supportedImageFormats();
	void addNewItem(QString&, QString&);
	void addNewGroup(QString&);

private slots:
	void onSelectResource();
	void onSelectProjectLocation();
	void treeViewClicked(const QModelIndex &);
	void treeViewItemActivated(const QModelIndex &);
	void treeViewDoubleClicked(const QModelIndex &);
	void onMoveUp();
	void onMoveDown();

public slots:
	void addNewGroup();
	void addNewItem();
	void onRemove();
	void saveResourceFile();
	void loadResourceFile();

public:
	Widget(QWidget *parent = 0);
};

} // namespace RFE

#endif // __RESOURCEFILEEDITOR_WIDGET_H__
