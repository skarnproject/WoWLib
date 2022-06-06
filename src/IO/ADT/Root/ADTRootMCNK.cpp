#include <IO/ADT/Root/ADTRootMCNK.hpp>
#include <IO/ADT/ChunkIdentifiers.hpp>

using namespace IO::ADT;
using namespace IO::ADT::ChunkIdentifiers;
using namespace IO::Common;

MCNKRoot::MCNKRoot()
{
  _heightmap.Initialize();
  _normals.Initialize();
}

void MCNKRoot::Read(Common::ByteBuffer const& buf, std::size_t size)
{
  std::size_t end_pos = buf.Tell() + size;

  buf.Read(_header);

  while (buf.Tell() != end_pos)
  {
    ChunkHeader const& chunk_header = buf.ReadView<ChunkHeader>();

    LogDebugF(LCodeZones::ADT_IO, "   Loading ADT root MCNK sub-chunk %s.", FourCCToStr(chunk_header.fourcc));

    switch (chunk_header.fourcc)
    {
      case ADTRootMCNKSubchunks::MCVT:
        _heightmap.Read(buf);
        break;
      case ADTRootMCNKSubchunks::MCLV:
        _vertex_lighting.Read(buf);
        break;
      case ADTRootMCNKSubchunks::MCCV:
        _vertex_color.Read(buf);
        break;
      case ADTRootMCNKSubchunks::MCNR:
        _normals.Read(buf);
        break;
      case ADTRootMCNKSubchunks::MCLQ:
        _tbc_water.Read(buf);
        break;
      case ADTRootMCNKSubchunks::MCSE:
        _sound_emitters.Read(buf);
        break;
      case ADTRootMCNKSubchunks::MCBB:
        _blend_batches.Read(buf);
        break;
      case ADTRootMCNKSubchunks::MCDD:
        _groundeffect_disable.Read(buf);
        break;
      default:
      {
        buf.Seek<ByteBuffer::SeekDir::Forward, ByteBuffer::SeekType::Relative>(chunk_header.size);
        LogError("    Encountered unknown ADT root MCNK sub-chunk %s.", FourCCToStr(chunk_header.fourcc));
        break;
      }

    }

  }
}

void MCNKRoot::Write(Common::ByteBuffer& buf)
{
  RequireF(CCodeZones::FILE_IO, _heightmap.IsInitialized() && _normals.IsInitialized(),
    "MCVT and MCNR must be initialized to write root MCNK.");

  std::size_t pos = buf.Tell();

  // writing chunk header to just initialize buffer bytes
  ChunkHeader chunk_header{};
  buf.Write(chunk_header);

  buf.Write(_header);
  _heightmap.Write<ADTRootMCNKSubchunks::MCVT>(buf);
  _normals.Write<ADTRootMCNKSubchunks::MCNR>(buf);

  // optional sub-chunks
  _vertex_lighting.Write<ADTRootMCNKSubchunks::MCLV>(buf);
  _vertex_color.Write<ADTRootMCNKSubchunks::MCCV>(buf);
  _tbc_water.Write<ADTRootMCNKSubchunks::MCLQ>(buf);
  _sound_emitters.Write<ADTRootMCNKSubchunks::MCSE>(buf);
  _blend_batches.Write<ADTRootMCNKSubchunks::MCBB>(buf);
  _groundeffect_disable.Write<ADTRootMCNKSubchunks::MCDD>(buf);

  // writing actual chunk header data
  std::size_t end_pos = buf.Tell();
  buf.Seek(pos);
  chunk_header.fourcc = ADTRootChunks::MCNK;
  chunk_header.size = end_pos - pos;
  buf.Write(chunk_header);
  buf.Seek(end_pos);


}