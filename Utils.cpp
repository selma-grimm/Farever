#include "Utils.h"


QString Utils::getAfterLastSlash(const QString& sFilePath)
{
	QRegExp rxFileName(".*[\\\\|/](.*)$");
	rxFileName.setMinimal(true);
	int i = sFilePath.lastIndexOf(rxFileName);
	if (i<0)
		return sFilePath;

	return rxFileName.cap(1);
}

void Utils::cutAfterLastSlash(QString& sFilePath)
{
	QRegExp rxFileName("(\\\\|/)[^\\\\/]*$");
	rxFileName.setMinimal(true);
	int i = sFilePath.lastIndexOf(rxFileName);
	if (i != -1)
		sFilePath.remove(rxFileName);

}
