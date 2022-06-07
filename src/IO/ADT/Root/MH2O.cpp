#include <IO/ADT/Root/MH2O.hpp>

#include <cstdint>

using namespace IO::ADT;

void MH2O::Read(Common::ByteBuffer const& buf, std::size_t size)
{
  LogDebugF(LCodeZones::ADT_IO, "Loading ADT root chunk MH2O.");

  std::size_t pos = buf.Tell();
  buf.Read(_header);
  



}

void MH2O::Write(Common::ByteBuffer& buf)
{
   
}