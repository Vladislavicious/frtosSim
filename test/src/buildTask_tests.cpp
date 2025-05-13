#include "gtest/gtest.h"

#include <thread>
#include <vector>
#include <future>

#include "buildTask.h"

using namespace std;

static const std::string BuildConfigPath = std::string( TEST_DATA_DIR ) + std::string( "/buildTask/" );
//---------------------------------------------------------------
TEST( buildTaskTest, makefileExistCheck ) {
  static const std::string ExpectedMakefilePath = BuildConfigPath + std::string( "test.mk" );

  BuildConfig config;
  config.CheckConfig( BuildConfigPath + std::string( "build.json" ) );
  EXPECT_TRUE( config.IsValid() );


  BuildTask buildTask( config );
}
//---------------------------------------------------------------