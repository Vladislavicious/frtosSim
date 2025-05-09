#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "loggerConfig.h"

using namespace std;

static const std::string loggerConfigDataPath = std::string( TEST_DATA_DIR ) + std::string( "/loggerConfig/" );
//---------------------------------------------------------------
TEST( loggerConfig, creation ) {
  LoggerConfig conf;

  EXPECT_STREQ( conf.GetLogFilepath().c_str(), "" );
  EXPECT_EQ( conf.GetLogType(), LogInterfaceEnum::NONE );
}
//---------------------------------------------------------------
TEST( loggerConfig, consoleConfigRead ) {
  LoggerConfig conf;
  ConfigError result = conf.CheckConfig( loggerConfigDataPath + std::string( "consoleLog.json" ) );

  EXPECT_TRUE( result.IsOk() );
  EXPECT_EQ( conf.GetLogType(), LogInterfaceEnum::CONSOLE );
  EXPECT_STREQ( conf.GetLogFilepath().c_str(), "" );
}
//---------------------------------------------------------------
TEST( loggerConfig, fileConfigRead ) {
  LoggerConfig conf;
  ConfigError result = conf.CheckConfig( loggerConfigDataPath + std::string( "fileLog.json" ) );

  EXPECT_TRUE( result.IsOk() );
  EXPECT_EQ( conf.GetLogType(), LogInterfaceEnum::FILE );
  EXPECT_STREQ( conf.GetLogFilepath().c_str(), "./smh.log" );
}
//---------------------------------------------------------------
TEST( loggerConfig, fileTypeNoFilePassed ) {
  LoggerConfig conf;
  ConfigError result = conf.CheckConfig( loggerConfigDataPath + std::string( "badFileLog.json" ) );

  EXPECT_EQ( result.GetValue(), ConfigErrorEnum::NO_LOG_FILEPATH );
  EXPECT_EQ( conf.GetLogType(), LogInterfaceEnum::NONE );
  EXPECT_STREQ( conf.GetLogFilepath().c_str(), "" );
}
//---------------------------------------------------------------
TEST( loggerConfig, badFileFormat ) {
  LoggerConfig conf;
  ConfigError result = conf.CheckConfig( loggerConfigDataPath + std::string( "badLogFile.json" ) );

  EXPECT_EQ( result.GetValue(), ConfigErrorEnum::NO_LOG_TYPE );
  EXPECT_EQ( conf.GetLogType(), LogInterfaceEnum::NONE );
  EXPECT_STREQ( conf.GetLogFilepath().c_str(), "" );
}
//---------------------------------------------------------------
