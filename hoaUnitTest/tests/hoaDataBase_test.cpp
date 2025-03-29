#include <gtest/gtest.h>
#include "hoaDataBase.h"
#include "hoaPlane.h"
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
	EXPECT_NO_THROW(db.create(testFilePath, hoaIRWType::SimpleText));
	EXPECT_NO_THROW(db.open(testFilePath));
}

TEST_F(HoaDataBaseTest, AddAndRetrieveObject) {
	hoaDataBase db;
	db.create(testFilePath, hoaIRWType::SimpleText);

	hoaPlane plane;
	EXPECT_NO_THROW(db.addObject(&plane));

	auto retrieved = db.getObject(1);
	EXPECT_NE(retrieved, nullptr);
	EXPECT_EQ(retrieved->type(), 1);
}