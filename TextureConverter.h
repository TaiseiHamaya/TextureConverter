#pragma once

#include <filesystem>

#include "third_party/DirectXTex/DirectXTex.h"

/// <summary>
/// �e�N�X�`���ϊ��N���X
/// </summary>
class TextureConverter final {
public:
	/// <summary>
	/// WIC����DDS�ւ̕ϊ�
	/// </summary>
	/// <param name="path"></param>
	void convert_wic_to_dds(std::filesystem::path path);

private:
	/// <summary>
	/// WIC�`���̃e�N�X�`�����t�@�C������ǂݍ���
	/// </summary>
	/// <param name="path"></param>
	void load_wic_from_file(const std::filesystem::path& path);

	/// <summary>
	/// DDS�`���Ńe�N�X�`����ۑ�
	/// </summary>
	/// <param name="path">�ۑ���t�@�C���p�X</param>
	void save_dds_to_file(const std::filesystem::path& path);

private:
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage scratchImage;
};
