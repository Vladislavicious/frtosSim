#ifndef SIMULATOR_CONFIG_H_
#define SIMULATOR_CONFIG_H_

#include <vector>

#include "config.h"
#include "fileWork.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;
//---------------------------------------------------------------
enum class ConnectionTypeEnum {
  CNT_UART,
  CNT_I2C,
  CNT_SPI,
  CNT_NOT_SET,
  CNT_UNKNOWN
};
ConnectionTypeEnum FromString( const std::string& str );
std::string ToString( ConnectionTypeEnum type );

void to_json( json& j, const ConnectionTypeEnum& t );
void from_json( const json& j, ConnectionTypeEnum& t );
//---------------------------------------------------------------
//       ConnectionIdentificator class definition:
//---------------------------------------------------------------
struct ConnectionIdentificator
{
  std::string connectionName{ "" };
  std::string hostSimulatorName{ "" };
  ConnectionTypeEnum connectionType{ ConnectionTypeEnum::CNT_NOT_SET };
};
//---------------------------------------------------------------
//       ConnectionDescriptor class definition:
//---------------------------------------------------------------
struct ConnectionDescriptor
{
  using cnt_size_t = uint32_t;

  ConnectionIdentificator id;
  cnt_size_t rxCapacity{ 1 };
  cnt_size_t rxMinPacketSize{ 1 };
  cnt_size_t txCapacity{ 1 };
  cnt_size_t txMinPacketSize{ 1 };
  ConnectionIdentificator connectsTo;
};
//---------------------------------------------------------------
//       SimulatorConfig class definition:
//---------------------------------------------------------------
class SimulatorConfig : public BaseConfig
{
public:
  SimulatorConfig();
private:
  ConfigError ReadConfig( const json& Config ) override;

  double simulationSpeed{ 1.0f };
  std::string simulatorName{ "" };
  std::vector<ConnectionDescriptor> availableInterfaces;
  std::string loggerConfigFilepath{ "" };
};
//---------------------------------------------------------------
#endif // SIMULATOR_CONFIG_H_
