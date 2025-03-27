#include "hoaDataBase.h"
#include <fstream>
#include "hoaPlane.h"

static std::string tho_suffix = ".tho";

struct hoaHeaderItem
{
	int addres;
	int type;
};

class hoaDataBase::Impl
{
public:
	std::string mPath;
	bool mIsOpen = false;
	std::vector<char> mFileBuffer;
	std::unordered_map<unsigned int, hoaHeaderItem> mHeader;
	hoaIRWType mType;
	int mMaxId;
};

hoaDataBase::hoaDataBase() : pImpl(new Impl)
{
}

hoaDataBase::~hoaDataBase()
{
	delete pImpl;
}

void hoaDataBase::create(std::string path, hoaIRWType type)
{
	pImpl->mType = type;
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

	if (path.ends_with(tho_suffix))
	{
		pImpl->mType = hoaIRWType::SimpleText;
	}

	std::ifstream dbFile(path, std::ios::in | std::ios::binary);
	if (!dbFile)
		return;

	std::streamsize size = dbFile.tellg();
	dbFile.seekg(0, std::ios::beg);

	pImpl->mFileBuffer.resize(size+1);
	dbFile.read(&pImpl->mFileBuffer[0], size);

	std::unique_ptr<hoaIR> r = hoaIRWFabrica::getR(pImpl->mType, pImpl->mFileBuffer.data(), size);
	int count = 0;
	pImpl->mMaxId = 0;
	r->store(count);
	for (int i = 0; i < count; i++)
	{
		int id = 0;
		int addres = 0;
		int type = 0;
		r->store(id);
		r->store(addres);
		r->store(type);
		pImpl->mHeader[id] = hoaHeaderItem(addres, type);
		pImpl->mMaxId = std::max(pImpl->mMaxId, id);
	}

	pImpl->mPath = path;
	pImpl->mIsOpen = true;
}

void hoaDataBase::save() {
	if (pImpl->mIsOpen)
		return;

	std::ofstream dbFile(pImpl->mPath, std::ios::out | std::ios::binary);
	if (!dbFile)
		return;
}

void hoaDataBase::close() {
	if (pImpl->mIsOpen)
		return;

	pImpl->mIsOpen = false;
}

std::unique_ptr<hoaObject> hoaDataBase::getObject(unsigned int index)
{
	std::unique_ptr<hoaObject> re;
	if (pImpl->mHeader.find(index) != pImpl->mHeader.end())
	{
		const hoaHeaderItem& item = pImpl->mHeader[index];
		std::unique_ptr<hoaIR> r = hoaIRWFabrica::getR(pImpl->mType, pImpl->mFileBuffer.data()+ item.addres, 10);

		if (item.type == 1)
		{
			re = std::make_unique<hoaPlane>();
		}
		re->store(r.get());
	}
	return re;
}

void hoaDataBase::addObject(hoaObject* obj)
{
	std::unique_ptr<hoaIW> w = hoaIRWFabrica::getW(pImpl->mType);
	obj->store(w.get());
	std::vector<char> vec = w->get();
	pImpl->mHeader[++pImpl->mMaxId] = hoaHeaderItem((int)pImpl->mFileBuffer.size(), obj->type());
	pImpl->mFileBuffer.reserve(pImpl->mFileBuffer.size() + vec.size());
	pImpl->mFileBuffer.insert(pImpl->mFileBuffer.end(), vec.begin(), vec.end());
}
