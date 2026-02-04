#include "hoaDataBase.h"

#include "hoaDataBaseGuard.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


class hoaDataBase::Impl
{
public:
	std::string mPath;
	bool mIsOpen = false;
	std::map<int, std::string> mChanck;
	int mMaxId = 0;
};

hoaDataBase::hoaDataBase() : pImpl(new Impl), mDataBaseGuard(std::make_shared<hoaDataBaseGuard>(this))
{
}

hoaDataBase::~hoaDataBase()
{
	mDataBaseGuard->invalid();
	delete pImpl;
}

void hoaDataBase::create(std::string path)
{
	if (pImpl->mIsOpen)
		return;

	std::ofstream dbFile(path, std::ios::out | std::ios::binary);
	if (!dbFile)
	{
		return;
	}

	pImpl->mPath = path;
	pImpl->mIsOpen = true;
}

void hoaDataBase::open(std::string path)
{
	if (pImpl->mIsOpen)
		return;

	std::ifstream dbFile(path);
	if (!dbFile)
		return;

	if (!dbFile.is_open())
		return;

	std::string line;
	while (std::getline(dbFile, line)) {
		std::istringstream iss(line);
		int index;
		std::string text;
		if (!(iss >> index))
			continue;

		if (iss.peek() == ' ')
			iss.ignore();

		std::getline(iss, text);

		if (index > pImpl->mMaxId)
			pImpl->mMaxId = index;

		pImpl->mChanck[index] = std::move(text);
	}

	pImpl->mPath = path;
	pImpl->mIsOpen = true;
	dbFile.close();
}

void hoaDataBase::save()
{
	if (!pImpl->mIsOpen || pImpl->mPath.empty())
		return;

	std::string tempPath = pImpl->mPath + ".tmp";
	std::ofstream dbFile(tempPath, std::ios::out | std::ios::trunc);

	if (!dbFile.is_open())
		return;

	for (const auto& [index, text] : pImpl->mChanck) {
		dbFile << index << " " << text << "\n";
	}

	dbFile.close();

	std::remove(pImpl->mPath.c_str());
	std::rename(tempPath.c_str(), pImpl->mPath.c_str());

}

void hoaDataBase::saveAs(std::string newPath)
{
	if (!pImpl->mIsOpen)
		return;

	pImpl->mPath = std::move(newPath);

	save();
}

void hoaDataBase::close() {
	if (!pImpl->mIsOpen)
		return;

	save();
	pImpl->mChanck.clear();
	pImpl->mMaxId = 0;
	pImpl->mPath.clear();
	pImpl->mIsOpen = false;
}

std::unique_ptr<hoaObject> hoaDataBase::getObject(unsigned int index)
{
	if (pImpl->mChanck.find(index) == pImpl->mChanck.end())
		return {};

	std::istringstream iss(pImpl->mChanck[index]);
	int type;
	if (!(iss >> type))
		return {};

	if (iss.peek() == ' ')
		iss.ignore();

	std::string text;
	std::getline(iss, text);
	std::unique_ptr<hoaObject> obj = create(type);
	obj->store(std::move(text));
	obj->setDataBaseGuard(mDataBaseGuard);
	return obj;
}

int hoaDataBase::addObject(hoaObject* obj)
{
	if (!obj)
		return 0;

	int type = obj->type();

	std::ostringstream oss;
	oss << type << " " << obj->store();

	pImpl->mChanck[++pImpl->mMaxId] = oss.str();
	obj->setDataBaseGuard(mDataBaseGuard);
	return pImpl->mMaxId;
}

void hoaDataBase::modifyObject(hoaObject* obj) {
	if (!obj)
		return;

	int index = obj->getId();
	int type = obj->type();

	std::ostringstream oss;
	oss << type << " " << obj->store();

	pImpl->mChanck[index] = oss.str();
}
