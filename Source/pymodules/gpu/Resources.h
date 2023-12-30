#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "TypeIds.h"
#include <coalpy.render/Resources.h>

namespace coalpy
{
namespace gpu
{

struct CoalpyTypeObject;

struct Texture
{
    //Data
    PyObject_HEAD
    render::Texture texture;
    bool owned = true;
    bool isFile = false;
    bool hasImguiRef = false;

    //Functions
    static const TypeId s_typeId = TypeId::Texture;
    static void constructType(CoalpyTypeObject& t);
    static int  init(PyObject* self, PyObject * vargs, PyObject* kwds);
    static void destroy(PyObject* self);
};

struct Buffer
{
    //Data
    PyObject_HEAD
    bool isAppendConsume = false;
    bool owned = true;
    render::Buffer buffer;
    PyObject* mappedMemory = nullptr;

    //Functions
    static const TypeId s_typeId = TypeId::Buffer;
    static void constructType(CoalpyTypeObject& t);
    static int  init(PyObject* self, PyObject * vargs, PyObject* kwds);
    static void destroy(PyObject* self);
};

struct Sampler
{
    //Data
    PyObject_HEAD
    render::Sampler sampler;

    //Functions
    static const TypeId s_typeId = TypeId::Sampler;
    static void constructType(CoalpyTypeObject& t);
    static int  init(PyObject* self, PyObject * vargs, PyObject* kwds);
    static void destroy(PyObject* self);
};

struct InResourceTable
{
    //Data
    PyObject_HEAD
    render::InResourceTable table;

    //Functions
    static const TypeId s_typeId = TypeId::InResourceTable;
    static void constructType(CoalpyTypeObject& t);
    static int  init(PyObject* self, PyObject * vargs, PyObject* kwds);
    static void destroy(PyObject* self);
};

struct OutResourceTable
{
    //Data
    PyObject_HEAD
    render::OutResourceTable table;

    //Functions
    static const TypeId s_typeId = TypeId::OutResourceTable;
    static void constructType(CoalpyTypeObject& t);
    static int  init(PyObject* self, PyObject * vargs, PyObject* kwds);
    static void destroy(PyObject* self);
};

struct SamplerTable
{
    //Data
    PyObject_HEAD
    render::SamplerTable table;

    //Functions
    static const TypeId s_typeId = TypeId::SamplerTable;
    static void constructType(CoalpyTypeObject& t);
    static int  init(PyObject* self, PyObject * vargs, PyObject* kwds);
    static void destroy(PyObject* self);
};

struct MarkerResults
{
    //Data
    PyObject_HEAD
    PyObject* markers = nullptr;
    Buffer* timestampBuffer = nullptr;
    uint64_t timestampFrequency = 0ull;

    //Functions
    static const TypeId s_typeId = TypeId::MarkerResults;
    static void constructType(CoalpyTypeObject& t);
    static int  init(PyObject* self, PyObject * vargs, PyObject* kwds);
    static void destroy(PyObject* self);
};

}
}


