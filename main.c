#include <ktx.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid arguments provided\n");
    printf("Usage: ./ktxprobe input.ktx\n");
    return 1;
  }

  const char *input = argv[1];

  ktxTexture *texture;
  KTX_error_code result;
  result = ktxTexture_CreateFromNamedFile(
      input, KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT, &texture);

  if (result != KTX_SUCCESS) {
    printf("Failed to read file");
    return 1;
  }

  printf("texture\n========\n");
  printf("isArray: %s\n", texture->isArray ? "true" : "false");
  printf("isCubemap: %s\n", texture->isCubemap ? "true" : "false");
  printf("isCompressed: %s\n", texture->isCompressed ? "true" : "false");
  printf("generateMipmaps: %s\n", texture->generateMipmaps ? "true" : "false");
  printf("baseWidth: %u\n", texture->baseWidth);
  printf("baseHeight: %u\n", texture->baseHeight);
  printf("baseDepth: %u\n", texture->baseDepth);
  printf("numDimensions: %u\n", texture->numDimensions);
  printf("numLevels: %u\n", texture->numLevels);
  printf("numLayers: %u\n", texture->numLayers);
  printf("numFaces: %u\n", texture->numFaces);

  if (texture->kvDataHead != NULL)
    printf("\nmetadata\n========\n");

  ktxHashList kvHead = texture->kvDataHead;
  while (kvHead != NULL) {
    unsigned int keylen;
    char *pKey;
    ktxHashListEntry_GetKey(kvHead, &keylen, &pKey);
    unsigned int valuelen;
    char *pValue;
    ktxHashListEntry_GetValue(kvHead, &valuelen, (void **)&pValue);
    kvHead = ktxHashList_Next(kvHead);

    // NOTE: we should probably add null terminators to the strings
    printf("%s: %s\n", pKey, pValue);
  }
  ktxTexture_Destroy(texture);
  return 0;
}
