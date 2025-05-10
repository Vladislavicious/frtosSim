#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <fstream>

#include "logger.h"
using namespace std;

static const std::string loggerDataPath = std::string( TEST_DATA_DIR ) + std::string( "/logger/" );
//---------------------------------------------------------------
TEST( logger, FileSingleWrite ) {

  LoggerConfig config;
  ConfigError result = config.CheckConfig( loggerDataPath + std::string( "fileLog.json" ) );
  EXPECT_TRUE( result.IsOk() );

  LoggerInterface* logger = LoggerFabric::GetLogger( config );
  EXPECT_TRUE( logger != nullptr );

  std::string outString = "123456789";
  logger->Output( outString );

  std::ifstream checkFile( config.GetLogFilepath() );
  EXPECT_TRUE( checkFile.is_open() );

  std::string fileContent{ "" };
  getline( checkFile, fileContent );
  EXPECT_STREQ( outString.c_str(), fileContent.c_str() );
}
//---------------------------------------------------------------
TEST( logger, FileMultiWrite ) {

  LoggerConfig config;
  ConfigError result = config.CheckConfig( loggerDataPath + std::string( "fileLog.json" ) );
  EXPECT_TRUE( result.IsOk() );

  LoggerInterface* logger = LoggerFabric::GetLogger( config );
  EXPECT_TRUE( logger != nullptr );

  std::string outString = "123456789";
  std::string expectedOutString{ "" };
  for( uint32_t i = 0; i < 5; i++ )
  {
    logger->Output( outString );
    expectedOutString += outString;
  }

  std::ifstream checkFile( config.GetLogFilepath() );
  EXPECT_TRUE( checkFile.is_open() );

  std::string fileContent{ "" };
  getline( checkFile, fileContent );
  EXPECT_STREQ( expectedOutString.c_str(), fileContent.c_str() );
}
//---------------------------------------------------------------
TEST( logger, FileNullWrite ) {

  LoggerConfig config;
  ConfigError result = config.CheckConfig( loggerDataPath + std::string( "fileLog.json" ) );
  EXPECT_TRUE( result.IsOk() );

  LoggerInterface* logger = LoggerFabric::GetLogger( config );
  EXPECT_TRUE( logger != nullptr );

  std::string outString = "";
  logger->Output( outString );

  std::ifstream checkFile( config.GetLogFilepath() );
  EXPECT_TRUE( checkFile.is_open() );

  std::string fileContent{ "" };
  getline( checkFile, fileContent );
  EXPECT_STREQ( outString.c_str(), fileContent.c_str() );
}
//---------------------------------------------------------------
TEST( logger, InfoLevelWrite ) {

  LoggerConfig config;
  ConfigError result = config.CheckConfig( loggerDataPath + std::string( "fileLog.json" ) );
  EXPECT_TRUE( result.IsOk() );

  LoggerInterface* logger = LoggerFabric::GetLogger( config );
  EXPECT_TRUE( logger != nullptr );

  logger->SetLogLevel( LogLevel::INFO );

  std::string expectedStr{ "Info: 123" };
  std::string outString = "123";
  logger->Output( outString );

  std::ifstream checkFile( config.GetLogFilepath() );
  EXPECT_TRUE( checkFile.is_open() );

  std::string fileContent{ "" };
  getline( checkFile, fileContent );
  EXPECT_STREQ( expectedStr.c_str(), fileContent.c_str() );
}
//---------------------------------------------------------------
