#include "TextureManager.h"

TextureManager* TextureManager::_instance = nullptr;

TextureManager::TextureManager(std::string root)
 : textureRoot(std::move(root))
{
}

Texture*
TextureManager::getTexture(const std::string& name, GLubyte alpha)
{
	// Check whether the texture is already loaded
	auto it = textures.find(name);

	if (it == textures.end()) {
		auto texture = std::make_unique<Texture>();
		// Load the texture from file (under the texture root)
		texture->load(textureRoot + name, alpha);
		it = textures.insert({name, std::move(texture)}).first;
	}

	return it->second.get();
}

TextureManager* TextureManager::Instance() {
	if (_instance == nullptr) _instance = new TextureManager();
	return _instance;
}

void TextureManager::Release() {
	if (_instance != nullptr) delete _instance;
}

