#include <gtest/gtest.h>
#include "hoaDataBase.h"
#include "hoaPlane.h"
#include "hoaLine.h"
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

	hoaPoint c1(1.1,7.8,9);
	hoaPoint c2(133.1, 72.8, 91);

	hoaPlane plane1;
	plane1.setCenter(c1);

	hoaPlane plane2;
	plane2.setCenter(c2);

	int id1 = db.addObject(&plane1);
	int id2 = db.addObject(&plane2);

	auto retrieved2 = db.getObject(id2);
	auto retrieved1 = db.getObject(id1);

	EXPECT_NE(retrieved1, nullptr);
	EXPECT_NE(retrieved2, nullptr);
	EXPECT_EQ(retrieved1->type(), 1);
	EXPECT_EQ(retrieved2->type(), 1);
	EXPECT_EQ(static_cast<hoaPlane*>(retrieved1.get())->getCenter().x, c1.x);
}

TEST_F(HoaDataBaseTest, AddAndRetrieveAndSaveObject) {
	hoaDataBase db;
	db.create(testFilePath, hoaIRWType::SimpleText);

	hoaPoint c1(1.1, 7.8, 9);
	hoaPoint c2(133.1, 72.8, 91);

	hoaPlane plane1;
	plane1.setCenter(c1);

	hoaLine line;
	line.setStart(c2);

	int id1 = db.addObject(&plane1);
	int id2 = db.addObject(&line);
	db.save();

	hoaDataBase db2;
	db2.open(testFilePath);
	auto retrieved2 = db2.getObject(id2);
	auto retrieved1 = db2.getObject(id1);

	EXPECT_NE(retrieved1, nullptr);
	EXPECT_NE(retrieved2, nullptr);
	EXPECT_EQ(retrieved1->type(), 1);
	EXPECT_EQ(retrieved2->type(), 2);
	EXPECT_EQ(static_cast<hoaPlane*>(retrieved1.get())->getCenter().x, c1.x);
}