#include "../StdInc.h"

void *const _rwD3D9LastVertexShaderUsed = (decltype(_rwD3D9LastVertexShaderUsed))__rwD3D9LastVertexShaderUsed;
void *const _rwD3D9LastPixelShaderUsed = (decltype(_rwD3D9LastVertexShaderUsed))__rwD3D9LastPixelShaderUsed;
RwDevice *const RwOpenDevice = (decltype(RwOpenDevice))_RwOpenDevice;
RxNodeDefinition *const RxD3D9AtomicAllInOne = (decltype(RxD3D9AtomicAllInOne))_RxD3D9AtomicAllInOne;
RxNodeDefinition *const RxD3D9SubmitNoLight = (decltype(RxD3D9SubmitNoLight))_RxD3D9SubmitNoLight;
RsGlobalType *const RsGlobal = (decltype(RsGlobal))_RsGlobal;
RwGlobals **const RwEngineInstance = (decltype(RwEngineInstance))_RwEngineInstance;
LPDIRECT3DDEVICE9 *const _RwD3DDevice = (decltype(_RwD3DDevice))__RwD3DDevice;
RwReal (*const _rxD3D9VertexShaderConstants)[512] = (decltype(_rxD3D9VertexShaderConstants))__rxD3D9VertexShaderConstants;

RwReal _rxD3D9PixelShaderConstants[32];
RwMatrix *_rwD3D9VSCustomWorldMatrix;
void *_rwD3D9CustomVertexShader;
void *_rwD3D9CustomPixelShader;

RxNodeDefinition *(__cdecl *RxNodeDefinitionGetD3D9AtomicAllInOne)(void) = (decltype(RxNodeDefinitionGetD3D9AtomicAllInOne))(0x005D675F + *(LONG *)0x005D675B);
void (__cdecl *_rwD3D9VSSetActiveWorldMatrix)(const RwMatrix *worldMatrix) = (decltype(_rwD3D9VSSetActiveWorldMatrix))((PBYTE)RxNodeDefinitionGetD3D9AtomicAllInOne + 0x0246 + *(LONG *)((PBYTE)RxNodeDefinitionGetD3D9AtomicAllInOne + 0x0242));
void (__cdecl *_rwD3D9VSGetComposedTransformMatrix)(void *transformMatrix) = (decltype(_rwD3D9VSGetComposedTransformMatrix))((PBYTE)RxNodeDefinitionGetD3D9AtomicAllInOne + 0x0250 + *(LONG *)((PBYTE)RxNodeDefinitionGetD3D9AtomicAllInOne + 0x024C));
void *(__cdecl *RwIm3DTransform)(RwIm3DVertex *vertices, RwUInt32 numVerts, RwMatrix *ltm, RwUInt32 flags) = (decltype(RwIm3DTransform))(0x00459F3F + *(LONG *)0x00459F3B);
RwBool (__cdecl *RwIm3DEnd)(void) = (decltype(RwIm3DEnd))(0x00459F61 + *(LONG *)0x00459F5D);
RwBool (__cdecl *RwIm3DRenderIndexedPrimitive)(RwPrimitiveType primType, RwImVertexIndex *indices, RwInt32 numIndices) = (decltype(RwIm3DRenderIndexedPrimitive))(0x00459F59 + *(LONG *)0x00459F55);
RwBool (__cdecl *RwD3D9SetTransformWorld)(const RwMatrix *matrix) = (decltype(RwD3D9SetTransformWorld))((PBYTE)(*RwOpenDevice).fpSystem + 0x45B0);
RwBool (__cdecl *RwD3D9CreateVertexShader)(const RwUInt32 *function, void **shader) = (decltype(RwD3D9CreateVertexShader))((PBYTE)(*RwOpenDevice).fpSystem + 0x4CF0);
void (__cdecl *RwD3D9DeleteVertexShader)(void *shader) = (decltype(RwD3D9DeleteVertexShader))((PBYTE)(*RwOpenDevice).fpSystem + 0x4D20);
void (__cdecl *_rwD3D9SetVertexShaderConstant)(RwUInt32 registerAddress, const void *constantData, RwUInt32 constantCount) = (decltype(_rwD3D9SetVertexShaderConstant))((PBYTE)(*RwOpenDevice).fpSystem + 0x4D30);
RwBool (__cdecl *RwD3D9CreatePixelShader)(const RwUInt32 *function, void **shader) = (decltype(RwD3D9CreatePixelShader))((PBYTE)(*RwOpenDevice).fpSystem + 0x4D50);
void (__cdecl *RwD3D9DeletePixelShader)(void *shader) = (decltype(RwD3D9DeletePixelShader))((PBYTE)(*RwOpenDevice).fpSystem + 0x4D80);
void (__cdecl *_rwD3D9SetPixelShaderConstant)(RwUInt32 registerAddress, const void *constantData, RwUInt32 constantCount) = (decltype(_rwD3D9SetPixelShaderConstant))((PBYTE)(*RwOpenDevice).fpSystem + 0x4D90);
RwRaster *(__cdecl *RwRasterUnlock)(RwRaster *raster) = (decltype(RwRasterUnlock))(0x004CD7BF + *(LONG *)0x004CD7BB);
RwBool (__cdecl *RwRasterDestroy)(RwRaster *raster) = (decltype(RwRasterDestroy))(0x004CD1F0 + *(LONG *)0x004CD1EC);
RwRaster *(__cdecl *RwRasterCreate)(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags) = (decltype(RwRasterCreate))(0x004CD081 + *(LONG *)0x004CD07D);
RwUInt8 *(__cdecl *RwRasterLock)(RwRaster *raster, RwUInt8 level, RwInt32 lockMode) = (decltype(RwRasterLock))(0x004CD6D9 + *(LONG *)0x004CD6D5);
RwBool (__cdecl *RxD3D9SubmitNoLightBody)(RxPipelineNode *self, const RxPipelineNodeParam *params) = (decltype(RxD3D9SubmitNoLightBody))(*RxD3D9SubmitNoLight).nodeMethods.nodeBody;
RxNodeDefinition *(__cdecl *RxNodeDefinitionGetD3D9SubmitNoLight)(void) = (decltype(RxNodeDefinitionGetD3D9SubmitNoLight))((PBYTE)RxD3D9SubmitNoLightBody + 0x730);

LPVOID JMP_RxD3D9SubmitNoLightBody_169 = (decltype(JMP_RxD3D9SubmitNoLightBody_169))((PBYTE)RxD3D9SubmitNoLightBody + 0x0169);
