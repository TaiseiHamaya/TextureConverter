#include <cstdlib>
#include <cassert>

#include <windows.h>

enum Argument {
	ApplicationPath,
	FilePath,
	NumArguments,
};

#include "TextureConverter.h"

int main(int argc, char* argv[]) {
	assert(argc >= NumArguments);

	HRESULT hr;
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;
	converter.convert_wic_to_dds(argv[Argument::FilePath]);

	CoUninitialize();

	system("pause");
	return 0;
}
