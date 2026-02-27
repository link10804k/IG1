#ifndef _H_TextureManager_H_
#define _H_TextureManager_H_

#include <string>
#include <unordered_map>
#include <memory>

#include "Texture.h"

#define TEXTURE_MANAGER TextureManager::Instance()  

class TextureManager
{
	TextureManager(std::string root = "../assets/images/");
	~TextureManager() = default;

	TextureManager(const Texture& tex) = delete;            // no copy constructor
	TextureManager& operator=(const Texture& tex) = delete; // no copy assignment

	static TextureManager* _instance;
public:
	static TextureManager* Instance();
	static void Release();

	Texture* getTexture(const std::string& name, GLubyte alpha = 255);

protected:
	std::string textureRoot;
	std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
};

#endif //_H_TextureManager_H_
