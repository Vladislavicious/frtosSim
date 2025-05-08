#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "initializable.h"

using namespace std;
//---------------------------------------------------------------
class MockInitializableRealization : public Initialazable
{
public:
  MOCK_METHOD( bool, _Init, ( ), ( override ) );
  MOCK_METHOD( bool, _DeInit, ( ), ( override ) );
};
//---------------------------------------------------------------
TEST( initializable, OnCreateFalse ) {
  MockInitializableRealization initi;
  EXPECT_FALSE(initi.IsInit());
}
//---------------------------------------------------------------
TEST( initializable, InitializeOnce ) {
  MockInitializableRealization initi;

  ON_CALL( initi, _Init() )
  .WillByDefault( testing::Return( true ) );

  EXPECT_CALL( initi, _Init() )
    .Times( 1 );
    
  initi.Init();
  initi.Init();
  initi.Init();
}
//---------------------------------------------------------------
TEST( initializable, NoDeinitIfNoInit ) {
  MockInitializableRealization initi;

  EXPECT_CALL( initi, _DeInit() )
    .Times( 0 );

  initi.DeInit();
}
//---------------------------------------------------------------
        