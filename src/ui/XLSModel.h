#ifndef XLSMODEL_H
#define XLSMODEL_H

#include <XLSItem.h>
#include <QtCore\qdebug.h>
#include <QtCore\qstringlist.h>
#include <xlnt\xlnt.hpp>


class XLSModel : public QAbstractTableModel {
	Q_OBJECT
public:

	xlnt::worksheet ActiveWorkSheet;

	XLSModel(QObject *Parent, xlnt::worksheet CurrentWorkSheet);

	int rowCount(const QModelIndex &Parent = QModelIndex()) const;

	int columnCount(const QModelIndex &Parent = QModelIndex()) const;

	QVariant data(const QModelIndex &index, int Role = Qt::DisplayRole) const;

	QVariant headerData(int Section, Qt::Orientation Orientation, int Role) const;
};

#endif // !XLSMODEL_H
