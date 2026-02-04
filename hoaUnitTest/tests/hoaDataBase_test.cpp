#include <gtest/gtest.h>
#include "hoaDataBase.h"
#include <filesystem>

class HoaDataBaseTest : public ::testing::Test {
protected:
	void SetUp() override {
		testFilePath = "test_db.tho";
		if (std::filesystem::exists(testFilePath)) {
			std::filesystem::remove(testFilePath);
		}
	}

	void TearDown() override {
		if (std::filesystem::exists(testFilePath)) {
			std::filesystem::remove(testFilePath);
		}
	}

	std::string testFilePath;
};

TEST_F(HoaDataBaseTest, CreateAndOpenDatabase) {
	hoaDataBase db;
	EXPECT_NO_THROW(db.create(testFilePath));
	EXPECT_NO_THROW(db.open(testFilePath));
}

class testInt : public hoaObject {
public:
	void printMessage() {};
	void store(std::string text) { 
		std::istringstream iss(text);
		iss >> value;
	};
	std::string store() {
		return  std::to_string(value);
	}
	int type() { return 11; }
	int value;
};

TEST_F(HoaDataBaseTest, AddAndRetrieveObject) {
	hoaDataBase db;
	db.create(testFilePath);
	db.registerClass<testInt>(11);

	testInt t;
	t.value = 77;

	testInt t2;
	t2.value = 88;

	int id1 = db.addObject(&t);
	int id2 = db.addObject(&t2);

	auto retrieved1 = db.getObject(id1);
	auto retrieved2 = db.getObject(id2);

	EXPECT_NE(retrieved1, nullptr);
	EXPECT_NE(retrieved2, nullptr);
}

TEST_F(HoaDataBaseTest, DeleteDataBase) {
	{
		testInt t;
		t.value = 77;

		{
			hoaDataBase db;
			db.create(testFilePath);
			db.registerClass<testInt>(11);
			int id1 = db.addObject(&t);
		}
		t.modify();
	}

	EXPECT_EQ(1, 1);
}