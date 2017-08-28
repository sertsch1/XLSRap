#include <XLSModel.h>

XLSModel::XLSModel(QObject *Parent, xlnt::worksheet CurrentWorkSheet) : QAbstractTableModel(Parent)
{
	ActiveWorkSheet = CurrentWorkSheet;
}


int XLSModel::rowCount(const QModelIndex & /*Parent*/) const
{
	auto i = ActiveWorkSheet.highest_row();
	return i - 1;
}

int XLSModel::columnCount(const QModelIndex & /*Parent*/) const
{
	auto i = ActiveWorkSheet.highest_column();
	return i.index;
}

QVariant XLSModel::data(const QModelIndex &Index, int Role) const
{
	if (Role == Qt::DisplayRole) {
		xlnt::cell_reference CellRef = xlnt::cell_reference(Index.column() + 1, Index.row() + 2);
		auto Cell = ActiveWorkSheet.cell(CellRef);
		auto CellString = Cell.to_string();
		QString CellContent = QString::fromStdString(CellString);
		return CellContent;
	}
	return QVariant();
}

QVariant XLSModel::headerData(int Section, Qt::Orientation Orientation, int Role) const
{
	if (Role == Qt::DisplayRole && Orientation == Qt::Horizontal)
		return QString::fromStdString(ActiveWorkSheet.cell(xlnt::cell_reference(Section + 1, 1)).to_string());
	return QVariant();
}
