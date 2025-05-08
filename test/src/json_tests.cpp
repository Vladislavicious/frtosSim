#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;

static const std::string baseJsonString = R"(
  {
    "pi": 3.141,
    "happy": true
  }
)";
//---------------------------------------------------------------
TEST( JSONtest, Creation ) {
  json ex1;
  EXPECT_TRUE( ex1.empty() );
  ex1 = json::parse( baseJsonString );
  EXPECT_FALSE( ex1.empty() );
}
//---------------------------------------------------------------
TEST( JSONtest, AccessingExistingMembers ) {
  json ex1 = json::parse( baseJsonString );
  double val = ex1["pi"];
  EXPECT_EQ( val, 3.141 );

  bool bul = ex1["happy"];
  EXPECT_EQ( bul, true );
}
//---------------------------------------------------------------
TEST( JSONtest, AccessingNonExistingMembers ) {
  json ex1 = json::parse( baseJsonString );
  json val = ex1["unknown"];
  EXPECT_TRUE( val.is_null() );
}
//---------------------------------------------------------------
TEST( JSONtest, AccessingAtNonExistingMembers ) {
  json ex1 = json::parse( baseJsonString );
  EXPECT_THROW( ex1.at( "unknown" ), nlohmann::json::out_of_range );
}
//---------------------------------------------------------------
