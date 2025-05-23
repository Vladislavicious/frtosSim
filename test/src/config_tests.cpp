#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "config.h"

using namespace std;

static const std::string configDataPath = std::string( TEST_DATA_DIR ) + std::string( "/config/" );
//---------------------------------------------------------------
class MockConfig : public BaseConfig
{
public:
  MOCK_METHOD( ConfigError, ReadConfig, ( const json& Config ), ( override ) );
};
//---------------------------------------------------------------
TEST( ConfigTest, NonExistentFile ) {
  MockConfig conf;
  const std::string fileName( "file.json" );

  EXPECT_CALL( conf, ReadConfig )
    .Times( 0 );

  ConfigError result = conf.ParseConfig( fileName );

  EXPECT_EQ( result.GetValue(), ConfigErrorEnum::NO_CONFIG_FILE );
}
//---------------------------------------------------------------
TEST( ConfigTest, GoodFile ) {
  MockConfig conf;
  const std::string fileName( "base.json" );

  ON_CALL( conf, ReadConfig )
    .WillByDefault( testing::Return( ConfigError( ConfigErrorEnum::OK ) ) );

  EXPECT_CALL( conf, ReadConfig )
    .Times( 1 );

  ConfigError result = conf.ParseConfig( configDataPath + fileName );

  EXPECT_EQ( result.GetValue(), ConfigErrorEnum::OK );
  EXPECT_TRUE( conf.IsValidated() );
}
//---------------------------------------------------------------
TEST( ConfigTest, InitValidity ) {
  MockConfig conf;
  EXPECT_FALSE( conf.IsValidated() );
}
//---------------------------------------------------------------
TEST( ConfigTest, BadFileFormat ) {
  MockConfig conf;
  const std::string fileName( "file.bad" );

  EXPECT_CALL( conf, ReadConfig )
    .Times( 0 );

  ConfigError result = conf.ParseConfig( fileName );

  EXPECT_EQ( result.GetValue(), ConfigErrorEnum::BAD_FILE_NAME );
}
//---------------------------------------------------------------
TEST( ConfigTest, GiantFilename ) {
  MockConfig conf;

  char fakeName[1024];
  for( uint32_t i = 0; i < 1024; i++ )
    fakeName[i] = 'a';
  fakeName[1023] = '\0';

  const std::string fileName( fakeName );

  EXPECT_CALL( conf, ReadConfig )
    .Times( 0 );

  ConfigError result = conf.ParseConfig( fileName );

  EXPECT_EQ( result.GetValue(), ConfigErrorEnum::FILE_NAME_TOO_LONG );
}
//---------------------------------------------------------------