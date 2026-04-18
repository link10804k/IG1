#ifndef INDEXED_BOX_H
#define INDEXED_BOX_H

#include "ColorMaterialEntity.h"

class IndexedBox : public ColorMaterialEntity {
public:
	IndexedBox(GLdouble l);
	virtual ~IndexedBox() = default;
};

#endif
