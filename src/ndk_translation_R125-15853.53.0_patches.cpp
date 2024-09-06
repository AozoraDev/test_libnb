#include <patches.h>

#include <nbtools/patchHex.h>
#include <log.h>

unsigned int sizeofNB = 2.5*1024*1024;

void Patch_Permissive_Mprotect(void* nbbase){
    int res = 0;
    #ifdef IS_32
    res |= PatchHex_8(nbbase, 0x1fdb95, 0xfa, 0xff);
    #else
    res |= PatchHex_8(nbbase, 0x212ec0, 0xfa, 0xff);
    #endif
    if (res){
        error_print("Patch_Permissive_Mprotect failed.");
    }
}

void Patch_Permissive_Mmap(void* nbbase){
    int res = 0;
    #ifdef IS_32
    res |= PatchHex_8(nbbase, 0x1fda49, 0xfa, 0xff);
    #else
    res |= PatchHex_8(nbbase, 0x212dc8, 0xfa, 0xff);
    #endif
    if (res){
        error_print("Patch_Permissive_Mmap failed.");
    }
}


void Patch_NB(void* nbbase,const android::NativeBridgeRuntimeCallbacks *art_cbs,const char *app_code_cache_dir,const char *isa){
    Patch_Permissive_Mmap(nbbase);
    Patch_Permissive_Mprotect(nbbase);


}