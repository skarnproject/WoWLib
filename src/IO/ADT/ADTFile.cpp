#include <IO/ADT/ADTFile.hpp>

using namespace IO::ADT;

ADTFile::ADTFile(std::uint32_t file_data_id)
{
  // register readers
  // common
 
  /*
  
  // tex
  _tex_chunks[ChunkIdentifiers::ADTTexChunks::MDID] = &_diffuse_texture_ids;
  _tex_chunks[ChunkIdentifiers::ADTTexChunks::MHID] = &_height_texture_ids;
  _tex_chunks[ChunkIdentifiers::ADTTexChunks::MTXF] = &_texture_flags;
  _tex_chunks[ChunkIdentifiers::ADTTexChunks::MTXP] = &_texture_params;
  _tex_chunks[ChunkIdentifiers::ADTTexChunks::MTCG] = &_texture_color_grading;
  _tex_chunks[ChunkIdentifiers::ADTTexChunks::MAMP] = &_texture_amplifier;

  // obj0
  _obj0_chunks[ChunkIdentifiers::ADTObj0Chunks::MODF] = &_wmo_instances;
  _obj0_chunks[ChunkIdentifiers::ADTObj0Chunks::MDDF] = &_model_instances;
  _obj0_chunks[ChunkIdentifiers::ADTObj0Chunks::MLMB] = &_mlmb;
  _obj0_chunks[ChunkIdentifiers::ADTObj0Chunks::MWDR] = &_wmo_doodadset_ranges;
  _obj0_chunks[ChunkIdentifiers::ADTObj0Chunks::MWDS] = &_wmo_dooodad_set_indices;

  // obj1
  _obj1_chunks[ChunkIdentifiers::ADTObj1Chunks::MLMD] = &_wmo_instanced_lod;
  _obj1_chunks[ChunkIdentifiers::ADTObj1Chunks::MLMX] = &_wmo_instances_lod_extents;
  _obj1_chunks[ChunkIdentifiers::ADTObj1Chunks::MLDD] = &_model_instances_lod;
  _obj1_chunks[ChunkIdentifiers::ADTObj1Chunks::MLDX] = &_model_instances_lod_extents;
  _obj1_chunks[ChunkIdentifiers::ADTObj1Chunks::MLDL] = &_mldl;
  _obj1_chunks[ChunkIdentifiers::ADTObj1Chunks::MLFD] = &_object_lod_levels;
  _obj1_chunks[ChunkIdentifiers::ADTObj1Chunks::MLMB] = &_mlmb_obj1;
  _obj1_chunks[ChunkIdentifiers::ADTObj1Chunks::MLDB] = &_mldb;
  _obj1_chunks[ChunkIdentifiers::ADTObj1Chunks::MWDR] = &_wmo_doodadset_ranges_lod;
  _obj1_chunks[ChunkIdentifiers::ADTObj1Chunks::MWDS] = &_wmo_doodad_set_indices_lod;

  */

}

