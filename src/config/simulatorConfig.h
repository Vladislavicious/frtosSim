#ifndef SIMULATOR_CONFIG_H_
#define SIMULATOR_CONFIG_H_

#include <vector>

#include "config.h"
#include "fileWork.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;
//---------------------------------------------------------------
enum ConnectionTypeEnum {
  CNT_UART,
  CNT_I2C,
  CNT_SPI,
  CNT_NOT_SET,
  CNT_UNKNOWN
};

NLOHMANN_JSON_SERIALIZE_ENUM( ConnectionTypeEnum, {
  { ConnectionTypeEnum::CNT_UNKNOWN, nullptr },
  { ConnectionTypeEnum::CNT_UART, "uart" },
  { ConnectionTypeEnum::CNT_I2C, "i2c" },
  { ConnectionTypeEnum::CNT_SPI, "spi" },
  { ConnectionTypeEnum::CNT_NOT_SET, "none" },
  } );
//---------------------------------------------------------------
//       ConnectionIdentificator class definition:
//---------------------------------------------------------------
struct ConnectionIdentificator
{
  std::string connectionName{ "" };
  std::string hostSimulatorName{ "" };
  ConnectionTypeEnum connectionType{ ConnectionTypeEnum::CNT_NOT_SET };
};

bool operator==( const ConnectionIdentificator&, const ConnectionIdentificator& );
void to_json( json& j, const ConnectionIdentificator& t );
void from_json( const json& j, ConnectionIdentificator& t );
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

bool operator==( const ConnectionDescriptor&, const ConnectionDescriptor& );
void to_json( json& j, const ConnectionDescriptor& t );
void from_json( const json& j, ConnectionDescriptor& t );
//---------------------------------------------------------------
//       SimulatorConfig class definition:
//---------------------------------------------------------------
class SimulatorConfig : public BaseConfig
{
public:
  SimulatorConfig();
  std::string GetRunFilepath();
  double GetSimulationSpeed();
  std::string GetSimulatorName();
  std::string GetLoggerConfigPath();
  const std::vector<ConnectionDescriptor>& GetAvailableInterfaces();
private:
  ConfigError ReadConfig( const json& Config ) override;

  double simulationSpeed{ 1.0 };
  std::string simRunnerFilepath{ "" };
  std::string simulatorName{ "" };
  std::vector<ConnectionDescriptor> availableInterfaces;
  std::string loggerConfigFilepath{ "" };
};
//---------------------------------------------------------------
#endif // SIMULATOR_CONFIG_H_
