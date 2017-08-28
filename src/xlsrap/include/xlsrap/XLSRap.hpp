#include <xlsrap/Config.hpp>
#include <xlnt\xlnt.hpp>
#include <string>


XLSRAP_BEGIN_NS

class XLSRap {
public:

	xlnt::workbook Table;
	xlnt::worksheet Sheet;

	void LoadTable(std::string PathToFile);

	void LoadSheet(int id);

	void LoadSheet();

	void LoadSheetIntoTable(xlnt::worksheet CurrentSheet);

	int GetColumnCount(xlnt::worksheet CurrentSheet);
	int GetRowCount(xlnt::worksheet CurrentSheet);
};

XLSRAP_END_NS
