#include <coalpy.core/Formats.h>
#include <coalpy.core/Assert.h>
#include <stdlib.h>

namespace coalpy
{

static const char* g_formatNames[] = {
/*    RGBA_32_FLOAT,    */    "RGBA_32_FLOAT",
/*    RGBA_32_UINT,     */    "RGBA_32_UINT",
/*    RGBA_32_SINT,     */    "RGBA_32_SINT",
/*    RGBA_32_TYPELESS, */    "RGBA_32_TYPELESS",
/*    RGB_32_FLOAT,     */    "RGB_32_FLOAT",
/*    RGB_32_UINT,      */    "RGB_32_UINT",
/*    RGB_32_SINT,      */    "RGB_32_SINT",
/*    RGB_32_TYPELESS,  */    "RGB_32_TYPELESS",
/*    RG_32_FLOAT,      */    "RG_32_FLOAT",
/*    RG_32_UINT,       */    "RG_32_UINT",
/*    RG_32_SINT,       */    "RG_32_SINT",
/*    RG_32_TYPELESS,   */    "RG_32_TYPELESS",
/*    RGBA_16_FLOAT,    */    "RGBA_16_FLOAT",
/*    RGBA_16_UINT,     */    "RGBA_16_UINT",
/*    RGBA_16_SINT,     */    "RGBA_16_SINT",
/*    RGBA_16_UNORM,    */    "RGBA_16_UNORM",
/*    RGBA_16_SNORM,    */    "RGBA_16_SNORM",
/*    RGBA_16_TYPELESS, */    "RGBA_16_TYPELESS",
/*    RGBA_8_UINT,      */    "RGBA_8_UINT",
/*    RGBA_8_SINT,      */    "RGBA_8_SINT",
/*    RGBA_8_UNORM,     */    "RGBA_8_UNORM",
/*    BGRA_8_UNORM,     */    "BGRA_8_UNORM",
/*    RGBA_8_UNORM_SRGB,*/    "RGBA_8_UNORM_SRGB",
/*    BGRA_8_UNORM_SRGB,*/    "BGRA_8_UNORM_SRGB",
/*    RGBA_8_SNORM,     */    "RGBA_8_SNORM",
/*    RGBA_8_TYPELESS,  */    "RGBA_8_TYPELESS",
/*    D32_FLOAT,        */    "D32_FLOAT",
/*    R32_FLOAT,        */    "R32_FLOAT",
/*    R32_UINT,         */    "R32_UINT",
/*    R32_SINT,         */    "R32_SINT",
/*    R32_TYPELESS,     */    "R32_TYPELESS",
/*    D16_UNORM,        */    "D16_UNORM",
/*    R16_FLOAT,        */    "R16_FLOAT",
/*    R16_UINT,         */    "R16_UINT",
/*    R16_SINT,         */    "R16_SINT",
/*    R16_UNORM,        */    "R16_UNORM",
/*    R16_SNORM,        */    "R16_SNORM",
/*    R16_TYPELESS,     */    "R16_TYPELESS",
/*    RG16_FLOAT,       */    "RG16_FLOAT",
/*    RG16_UINT,        */    "RG16_UINT",
/*    RG16_SINT,        */    "RG16_SINT",
/*    RG16_UNORM,       */    "RG16_UNORM",
/*    RG16_SNORM,       */    "RG16_SNORM",
/*    RG16_TYPELESS,    */    "RG16_TYPELESS",
/*    R8_UNORM,         */    "R8_UNORM",
/*    R8_SINT,          */    "R8_SINT",
/*    R8_UINT,          */    "R8_UINT",
/*    R8_SNORM,         */    "R8_SNORM",
/*    R8_TYPELESS,      */    "R8_TYPELESS"
};

static_assert(sizeof(g_formatNames)/sizeof(g_formatNames[0]) == (size_t)Format::MAX_COUNT);

const char* getFormatName(Format f)
{
    CPY_ASSERT((int)f < (int)Format::MAX_COUNT);
    return g_formatNames[(int)f];
}

}
