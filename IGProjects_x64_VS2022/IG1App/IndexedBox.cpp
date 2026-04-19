#include "IndexedBox.h"

#include "IndexMesh.h"

IndexedBox::IndexedBox(GLdouble l){
    mMesh = IndexMesh::generateIndexedBox(l);
}