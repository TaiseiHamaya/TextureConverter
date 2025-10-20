#pragma once

#include <filesystem>

#include "third_party/DirectXTex/DirectXTex.h"

/// <summary>
/// テクスチャ変換クラス
/// </summary>
class TextureConverter final {
public:
	/// <summary>
	/// WICからDDSへの変換
	/// </summary>
	/// <param name="path"></param>
	void convert_wic_to_dds(std::filesystem::path path);

private:
	/// <summary>
	/// WIC形式のテクスチャをファイルから読み込む
	/// </summary>
	/// <param name="path"></param>
	void load_wic_from_file(const std::filesystem::path& path);

	/// <summary>
	/// DDS形式でテクスチャを保存
	/// </summary>
	/// <param name="path">保存先ファイルパス</param>
	void save_dds_to_file(const std::filesystem::path& path);

private:
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage scratchImage;
};
