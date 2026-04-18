#include "IndexedBox.h"

#include "IndexMesh.h"

IndexedBox::IndexedBox(GLdouble l){
    mMesh = IndexMesh::generateIndexBox8(l);
}