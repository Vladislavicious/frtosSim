#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "simulatorConfig.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;

TEST( connectionTypes, readGoodTypes )
{
  std::string baseJsonString = R"(
    {
      "connectionType": "uart"
    }
  )";
  ConnectionTypeEnum expectedType{ ConnectionTypeEnum::CNT_UART };

  json j = json::parse( baseJsonString );
  auto parsed = j.template get<ConnectionTypeEnum>();
  EXPECT_EQ( parsed, expectedType );

  json converted = expectedType;
  EXPECT_EQ( j, converted );
}
