#include "ClassThatUsesDB.h"
#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class MockDBConnection : public DBConnectionInterface
{
public:
    MOCK_METHOD(bool, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(MYSQL_RES*, execQuery, (const std::string& query), (override));
};

TEST(Test_ClassThatUsesDB, testcase)
{
    MockDBConnection connection;

    EXPECT_CALL(connection, open).Times(::testing::AtLeast(1));
    EXPECT_CALL(connection, execQuery).Times(::testing::AtLeast(1));
    EXPECT_CALL(connection, close).Times(::testing::AtLeast(1));

    ClassThatUsesDB db_user(&connection);
    db_user.openConnection();
    db_user.useConnection();
    db_user.closeConnection();
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


