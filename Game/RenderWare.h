#ifndef _RENDERWARE_H_
#define _RENDERWARE_H_

#define rwPI	(RwReal)M_PI

#define RWFORCEENUMSIZEINT		(RwInt32)((~(RwUInt32)0) >> 1)
#define RWSRCGLOBAL(variable)	((*RwEngineInstance)->variable)

#define RwRenderStateSet(state, value)	RWSRCGLOBAL(dOpenDevice).fpRenderStateSet(state, (void *)value)

typedef unsigned char RwUInt8;
typedef unsigned short RwUInt16;
typedef int RwInt32;
typedef unsigned int RwUInt32;
typedef char RwChar;
typedef RwInt32 RwBool;
typedef float RwReal;
typedef RwUInt16 RwImVertexIndex;

typedef enum RwRenderState RwRenderState;
typedef enum RwTextureFilterMode RwTextureFilterMode;
typedef enum RwBlendFunction RwBlendFunction;
typedef enum RwCullMode RwCullMode;
typedef enum RwRasterType RwRasterType;
typedef enum RwRasterFormat RwRasterFormat;
typedef enum RwRasterLockMode RwRasterLockMode;
typedef enum RwPrimitiveType RwPrimitiveType;
typedef enum RwIm3DTransformFlags RwIm3DTransformFlags;

typedef struct RwV2d RwV2d;
typedef struct RwV3d RwV3d;
typedef struct RwMatrixTag RwMatrix;
typedef struct RwRGBA RwRGBA;
typedef struct RwRGBAReal RwRGBAReal;
typedef struct RwRaster RwRaster;
typedef struct RxObjSpace3DVertex RwIm3DVertex;
typedef struct RxNodeMethods RxNodeMethods;
typedef struct RxNodeDefinition RxNodeDefinition;
typedef struct RxPipelineNode RxPipelineNode;
typedef struct RxPipelineNodeParam RxPipelineNodeParam;
typedef struct RwDevice RwDevice;
typedef struct RwGlobals RwGlobals;
typedef struct _rwIm3DPoolStash _rwIm3DPoolStash;
typedef struct RsGlobalType RsGlobalType;

typedef RwBool (*RxNodeBodyFn)(RxPipelineNode *self, const RxPipelineNodeParam *params);
typedef RwBool (*RwSystemFunc)(RwInt32 option, void *out, void *inOut, RwInt32 in);
typedef RwBool (*RwRenderStateSetFunction)(RwRenderState state, void *param);

enum RwRenderState
{
	rwRENDERSTATETEXTURERASTER		= 1,
	rwRENDERSTATEZTESTENABLE		= 6,
	rwRENDERSTATEZWRITEENABLE		= 8,
	rwRENDERSTATETEXTUREFILTER,
	rwRENDERSTATESRCBLEND,
	rwRENDERSTATEDESTBLEND,
	rwRENDERSTATEVERTEXALPHAENABLE,
	rwRENDERSTATEFOGENABLE			= 14,
	rwRENDERSTATECULLMODE			= 20,
	rwRENDERSTATEFORCEENUMSIZEINT	= RWFORCEENUMSIZEINT
};

enum RwTextureFilterMode
{
	rwFILTERNEAREST	= 1,
	rwFILTERLINEAR
};

enum RwBlendFunction
{
	rwBLENDSRCALPHA		= 5,
	rwBLENDINVSRCALPHA
};

enum RwCullMode
{
	rwCULLMODECULLNONE	= 1
};

enum RwRasterType
{
    rwRASTERTYPETEXTURE	= 0x04
};

enum RwRasterFormat
{
	rwRASTERFORMATLUM8	= 0x0400,
	rwRASTERFORMAT8888	= 0x0500
};

enum RwRasterLockMode
{
	rwRASTERLOCKWRITE	= 0x01
};

enum RwPrimitiveType
{
	rwPRIMTYPETRILIST				= 3,
	rwPRIMITIVETYPEFORCEENUMSIZEINT	= RWFORCEENUMSIZEINT
};

enum RwIm3DTransformFlags
{
	rwIM3D_VERTEXUV							= 1,
	rwIM3DTRANSFORMFLAGSFORCEENUMSIZEINT	= RWFORCEENUMSIZEINT
};

#pragma pack(push, 1)

struct RwV2d
{
	RwReal x;
	RwReal y;
};

struct RwV3d
{
	RwReal x;
	RwReal y;
	RwReal z;
};

struct RwMatrixTag
{
	RwV3d right;
	RwUInt32 flags;
	RwV3d up;
	RwUInt32 pad1;
	RwV3d at;
	RwUInt32 pad2;
	RwV3d pos;
	RwUInt32 pad3;
};

struct RwRGBA
{
	RwUInt8 red;
	RwUInt8 green;
	RwUInt8 blue;
	RwUInt8 alpha;
};

struct RwRGBAReal
{
	RwReal red;
	RwReal green;
	RwReal blue;
	RwReal alpha;
};

struct RwRaster;

struct RxObjSpace3DVertex
{
	RwV3d objVertex;
	RwV3d objNormal;
	RwUInt32 color;
	RwReal u;
	RwReal v;
};

struct RxNodeMethods
{
    RxNodeBodyFn nodeBody;
};

struct RxNodeDefinition
{
    RwChar *name;
    RxNodeMethods nodeMethods;
};

struct RwDevice
{
	char align1[4];
	RwSystemFunc fpSystem;
	char align2[8];
	RwRenderStateSetFunction fpRenderStateSet;
};

struct RwGlobals
{
	char align1[0x10];
	RwDevice dOpenDevice;
};

struct _rwIm3DPoolStash
{
	char align1[4];
	RwMatrix *ltm;
};

struct RsGlobalType
{
    char align_0[4];
    RwInt32 maximumWidth;
    RwInt32 maximumHeight;
};

#pragma pack(pop)

//#define _RxNodeDefinitionGetD3D9AtomicAllInOne	0x007582E0
extern RxNodeDefinition *(__cdecl *RxNodeDefinitionGetD3D9AtomicAllInOne)(void);
//#define __rwD3D9VSSetActiveWorldMatrix			0x00764650
extern void (__cdecl *_rwD3D9VSSetActiveWorldMatrix)(const RwMatrix *worldMatrix);
//#define __rwD3D9VSGetComposedTransformMatrix	0x007646E0
extern void (__cdecl *_rwD3D9VSGetComposedTransformMatrix)(void *transformMatrix);
//#define _RwIm3DTransform						0x007EF450
extern void *(__cdecl *RwIm3DTransform)(RwIm3DVertex *vertices, RwUInt32 numVerts, RwMatrix *ltm, RwUInt32 flags);
//#define _RwIm3DEnd								0x007EF520
extern RwBool (__cdecl *RwIm3DEnd)(void);
//#define _RwIm3DRenderIndexedPrimitive			0x007EF550
extern RwBool (__cdecl *RwIm3DRenderIndexedPrimitive)(RwPrimitiveType primType, RwImVertexIndex *indices, RwInt32 numIndices);
//#define _RwD3D9SetTransformWorld				0x007FA520
extern RwBool (__cdecl *RwD3D9SetTransformWorld)(const RwMatrix *matrix);
//#define _RwD3D9CreateVertexShader				0x007FAC60
extern RwBool (__cdecl *RwD3D9CreateVertexShader)(const RwUInt32 *function, void **shader);
//#define _RwD3D9DeleteVertexShader				0x007FAC90
extern void (__cdecl *RwD3D9DeleteVertexShader)(void *shader);
//#define __rwD3D9SetVertexShaderConstant			0x007FACA0
extern void (__cdecl *_rwD3D9SetVertexShaderConstant)(RwUInt32 registerAddress, const void *constantData, RwUInt32 constantCount);
//#define _RwD3D9CreatePixelShader				0x007FACC0
extern RwBool (__cdecl *RwD3D9CreatePixelShader)(const RwUInt32 *function, void **shader);
//#define _RwD3D9DeletePixelShader				0x007FACF0
extern void (__cdecl *RwD3D9DeletePixelShader)(void *shader);
//#define __rwD3D9SetPixelShaderConstant			0x007FAD00
extern void (__cdecl *_rwD3D9SetPixelShaderConstant)(RwUInt32 registerAddress, const void *constantData, RwUInt32 constantCount);
//#define _RwRasterUnlock							0x007FAEC0
extern RwRaster *(__cdecl *RwRasterUnlock)(RwRaster *raster);
//#define _RwRasterDestroy						0x007FB020
extern RwBool (__cdecl *RwRasterDestroy)(RwRaster *raster);
//#define _RwRasterCreate							0x007FB230
extern RwRaster *(__cdecl *RwRasterCreate)(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags);
//#define _RwRasterLock							0x007FB2D0
extern RwUInt8 *(__cdecl *RwRasterLock)(RwRaster *raster, RwUInt8 level, RwInt32 lockMode);
//#define _RxD3D9SubmitNoLightBody				0x0080E270
extern RwBool (__cdecl *RxD3D9SubmitNoLightBody)(RxPipelineNode *self, const RxPipelineNodeParam *params);
//#define _RxNodeDefinitionGetD3D9SubmitNoLight	0x0080E9A0
extern RxNodeDefinition *(__cdecl *RxNodeDefinitionGetD3D9SubmitNoLight)(void);

//#define _RxD3D9SubmitNoLightBody_169	0x0080E3D9
extern LPVOID JMP_RxD3D9SubmitNoLightBody_169;
#define __rwD3D9LastVertexShaderUsed	0x008E2448
extern void *const _rwD3D9LastVertexShaderUsed;
#define __rwD3D9LastPixelShaderUsed		0x008E244C
extern void *const _rwD3D9LastPixelShaderUsed;
#define _RwOpenDevice					0x008E2498
extern RwDevice *const RwOpenDevice;
#define _RxD3D9AtomicAllInOne			0x008D6338
extern RxNodeDefinition *const RxD3D9AtomicAllInOne;
#define _RxD3D9SubmitNoLight			0x008E2978
extern RxNodeDefinition *const RxD3D9SubmitNoLight;
#define _RsGlobal						0x00C17040
extern RsGlobalType *const RsGlobal;
#define _RwEngineInstance				0x00C97B24
extern RwGlobals **const RwEngineInstance;
#define __RwD3DDevice					0x00C97C28
extern LPDIRECT3DDEVICE9 *const _RwD3DDevice;
#define __rxD3D9VertexShaderConstants	0x00C9B0C0
extern RwReal (*const _rxD3D9VertexShaderConstants)[512];

extern WINEXP RwReal _rxD3D9PixelShaderConstants[32];
extern WINEXP RwMatrix *_rwD3D9VSCustomWorldMatrix;
extern WINEXP void *_rwD3D9CustomVertexShader;
extern WINEXP void *_rwD3D9CustomPixelShader;

#endif //_RENDERWARE_H_
