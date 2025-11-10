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
	HRESULT hr;
	DirectX::ScratchImage mipChain;
	hr = DirectX::GenerateMipMaps(scratchImage.GetImages(), scratchImage.GetImageCount(), scratchImage.GetMetadata(), DirectX::TEX_FILTER_DEFAULT, 0, mipChain);
	assert(SUCCEEDED(hr));
	scratchImage = std::move(mipChain);

	// à≥èk
	DirectX::ScratchImage compressed;
	hr = DirectX::Compress(scratchImage.GetImages(), scratchImage.GetImageCount(), scratchImage.GetMetadata(),
		DXGI_FORMAT_BC7_UNORM_SRGB, DirectX::TEX_COMPRESS_BC7_QUICK | DirectX::TEX_COMPRESS_SRGB_OUT | DirectX::TEX_COMPRESS_PARALLEL, 1.0f, compressed);
	assert(SUCCEEDED(hr));
	// ì]ëó
	scratchImage = std::move(compressed);
	metadata = scratchImage.GetMetadata();

	metadata.format = DirectX::MakeSRGB(metadata.format);
	hr = DirectX::SaveToDDSFile(scratchImage.GetImages(), scratchImage.GetImageCount(), metadata, DirectX::DDS_FLAGS_NONE, path.native().c_str());
	assert(SUCCEEDED(hr));
}
