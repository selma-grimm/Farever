#ifndef UTILS_H
#define UTILS_H

#include "Precompile.h"

namespace Utils
{
	QString getAfterLastSlash(const QString& sFilePath);
	void	cutAfterLastSlash(QString& sFilePath);

}


//using namespace Utils;

#endif // UTILS_H
