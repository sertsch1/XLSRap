#include <xlsrap/XLSRap.hpp>
#include <iterator>

XLSRAP_BEGIN_NS

void XLSRap::LoadTable(std::string PathToFile) {
	//Construct path
	auto PathToTable = xlnt::path(PathToFile);
	Table.load(PathToTable);
}

void XLSRap::LoadSheet(int id) {
	Sheet = Table.sheet_by_index(id);
}

void XLSRap::LoadSheet()
{
	Sheet = Table.sheet_by_index(0);
}

void XLSRap::LoadSheetIntoTable(xlnt::worksheet CurrentSheet)
{
	auto ColumnRange = CurrentSheet.cend();
	auto RowRange = CurrentSheet.cend();

}

int XLSRap::GetColumnCount(xlnt::worksheet CurrentSheet) {
	//xlnt::range Range = CurrentSheet.columns();
	auto LastColumn = CurrentSheet.highest_column();
	return LastColumn.index;
	//auto Iterator = Range.cend();
	//int count = 0;
	
}

int XLSRap::GetRowCount(xlnt::worksheet CurrentSheet)
{
	auto LastRow = CurrentSheet.highest_row();
	return LastRow;
}

XLSRAP_END_NS
