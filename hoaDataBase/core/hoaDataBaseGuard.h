#pragma once
class hoaDataBase;

class hoaDataBaseGuard {
public:
	hoaDataBaseGuard(hoaDataBase* dataBase);
	virtual ~hoaDataBaseGuard() = default;
	hoaDataBase* getDataBase();
	void invalid();
	bool isValid() const;
private:
	hoaDataBase* mDataBase = nullptr;
};
