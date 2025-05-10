#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "logger.h"

using namespace std;

static const std::string loggerDataPath = std::string( TEST_DATA_DIR ) + std::string( "/logger/" );
//---------------------------------------------------------------
TEST( logger, FileWrite ) {

  LoggerConfig config;
  ConfigError result = config.CheckConfig( loggerDataPath + std::string( "fileLog.json" ) );
  EXPECT_TRUE( result.IsOk() );

  LoggerInterface* logger = LoggerFabric::GetLogger( config );
  EXPECT_TRUE( logger != nullptr );

  std::string outString = "123456789";
  logger->Output( outString );
}
//---------------------------------------------------------------