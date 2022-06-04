#pragma once
#include <IO/Common.hpp>
#include <IO/ADT/DataStructures.hpp>
#include <IO/ADT/Root/ADTRootMCNK.hpp>

#include <array>
#include <cstdint>

namespace IO::ADT
{
  class ADTRoot 
  {
  public:
 
    ADTRoot(std::uint32_t file_data_id);
    ADTRoot(std::uint32_t file_data_id, Common::ByteBuffer const& buf);

    [[nodiscard]]
    std::uint32_t FileDataID() const { return _file_data_id; };
    
    void Read(Common::ByteBuffer const& buf);
    void Write(Common::ByteBuffer& buf);

  
    Common::DataChunk<std::uint32_t> version;
    Common::DataChunk<DataStructures::MHDR> header;
    std::array<MCNKRoot, 256> chunks;
    // todo: mh20
    Common::DataChunk<DataStructures::MFBO> flight_bounds;
    Common::DataArrayChunk<DataStructures::MBMH> blend_mesh_headers;
    Common::DataArrayChunk<DataStructures::MBBB> blend_mesh_bounding_boxes;
    Common::DataArrayChunk<DataStructures::MBNV> blend_mesh_vertices;
    Common::DataArrayChunk<std::uint16_t> blend_mesh_indices;
  
  private:
    std::uint32_t _file_data_id;
  };


}