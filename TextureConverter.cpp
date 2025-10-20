#include "TextureConverter.h"

#include <Windows.h>

void TextureConverter::convert_wic_to_dds(std::filesystem::path path) {
	load_wic_from_file(path);
	save_dds_to_file(path.replace_extension(".dds"));
}

void TextureConverter::load_wic_from_file(const std::filesystem::path& path) {
	HRESULT hr;
	hr = DirectX::LoadFromWICFile(path.native().c_str(), DirectX::WIC_FLAGS_NONE, &metadata, scratchImage);
	assert(SUCCEEDED(hr));
}

void TextureConverter::save_dds_to_file(const std::filesystem::path& path) {
	metadata.format = DirectX::MakeSRGB(metadata.format);
	HRESULT hr;
	hr = DirectX::SaveToDDSFile(scratchImage.GetImages(), scratchImage.GetImageCount(), metadata, DirectX::DDS_FLAGS_NONE, path.native().c_str());
	assert(SUCCEEDED(hr));
}
