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
TEST( ConfigTest, InitValidity ) {
  MockConfig conf;
  EXPECT_FALSE( conf.IsValid() );
}
//---------------------------------------------------------------
TEST( ConfigTest, BadFileFormat ) {
  MockConfig conf;
  const std::string fileName( "file.bad" );

  EXPECT_CALL( conf, ReadConfig )
    .Times( 0 );

  ConfigError result = conf.CheckConfig( fileName );

  EXPECT_EQ( result, ConfigError::BAD_FILE_NAME );
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

  ConfigError result = conf.CheckConfig( fileName );

  EXPECT_EQ( result, ConfigError::FILE_NAME_TOO_LONG );
}
//---------------------------------------------------------------
TEST( ConfigTest, NonExistentFile ) {
  MockConfig conf;
  const std::string fileName( "file.json" );

  EXPECT_CALL( conf, ReadConfig )
    .Times( 0 );

  ConfigError result = conf.CheckConfig( fileName );

  EXPECT_EQ( result, ConfigError::NO_CONFIG_FILE );
}
//---------------------------------------------------------------
TEST( ConfigTest, GoodFile ) {
  MockConfig conf;
  const std::string fileName( "base.json" );

  ON_CALL( conf, ReadConfig )
    .WillByDefault( testing::Return( ConfigError::OK ) );

  EXPECT_CALL( conf, ReadConfig )
    .Times( 1 );

  ConfigError result = conf.CheckConfig( configDataPath + fileName );

  EXPECT_EQ( result, ConfigError::OK );
  EXPECT_TRUE( conf.IsValid() );
}