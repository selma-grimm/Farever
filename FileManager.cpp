#include "Precompile.h"
#include "FileManager.h"

#include "Utils.h"

#ifndef Q_OS_WIN32
#define MAX_PATH 255
#endif

FileManager::FileManager(BrowsePanel *pLeft, BrowsePanel *pRight):
	QObject()
  , m_pLeft(pLeft)
  , m_pRight(pRight)
{

}

void FileManager::copy()
{	
	copy(dynamic_cast<BrowsePanel*>(sender()));
}

void FileManager::remove()
{
	remove(dynamic_cast<BrowsePanel*>(sender()));
}

void FileManager::move()
{
	BrowsePanel* senderPanel = dynamic_cast<BrowsePanel*>(sender());
	copy(senderPanel);
	remove(senderPanel);
}

void FileManager::copyDir(const QString& sSource, const QString& sDest)
{
    QDir sourceDir(sSource);
    QDir destDir(sDest);

    QString sName = Utils::getAfterLastSlash(sSource);
    if (QString(sDest + QDir::separator() + sName).length() >= MAX_PATH)
        return;
    destDir.mkdir(sName);

    foreach (const QString& sDir, sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        copyDir(sSource + QDir::separator() + sDir, sDest + QDir::separator() + sName);

    foreach (const QString& sFile, sourceDir.entryList(QDir::Files))
    {
        QString sSourcePath = sSource + QDir::separator() + sFile;
        QString sDestPath = sDest + QDir::separator() + sName + QDir::separator() + sFile;
        QFile::copy(sSourcePath, sDestPath);
    }
}



void FileManager::removeDir(const QString& sPath)
{
    QDir dir(sPath);

    foreach (const QFileInfo& fiDir, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
        removeDir(fiDir.absoluteFilePath());
    foreach (const QFileInfo& fiFile, dir.entryInfoList(QDir::Files))
        QFile::remove(fiFile.absoluteFilePath());

	dir.rmdir(sPath);    
}

void FileManager::copy(BrowsePanel* senderPanel)
{
	QString sDestPath;

	if (senderPanel == m_pLeft)
		sDestPath = m_pRight->getSelectedPath();
	else
		sDestPath = m_pLeft->getSelectedPath();

	QModelIndexList filesList = senderPanel->getSelectedIndexes();
	foreach (const QModelIndex& index, filesList)
	{
		QPair<bool, QString> path = senderPanel->getAbsPath(index);

		if (path.first)
		{
			QString sSourcePath = path.second;
			copyDir(sSourcePath, sDestPath);
		}
		else
		{
			QString sSourceFile = path.second;
			QString sDestFile = sDestPath + QDir::separator() + Utils::getAfterLastSlash(sSourceFile);
			QFile::copy(sSourceFile, sDestFile);
		}
	}
}

void FileManager::remove(BrowsePanel* senderPanel)
{
	QModelIndexList filesList = senderPanel->getSelectedIndexes();
	foreach (const QModelIndex& index, filesList)
	{
		QPair<bool, QString> path = senderPanel->getAbsPath(index);
		QString sPath = path.second;		

		if (path.first)
			removeDir(sPath);
		else
			QFile::remove(sPath);
	}
}

//void FileManager::createFolder(const QString& current_path, const QString& name)
//{
//	if (!m_pNameEdit->text().isEmpty())
//	{
//		QDir dir(current_path);
//		if (dir.exists(name))
//			m_pLabel->setText("Folder with this name already exists within current location.");
//		else if (dir.mkdir(name))
//			emit Close();
//		else
//			m_pLabel->setText("Name is not valid. Creation failed.");
//	}
//}




