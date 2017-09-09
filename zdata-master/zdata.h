//
//  zdata.h
//  Created by Luwei on 14/12/6.
//

#ifndef __luwei__zdata__
#define __luwei__zdata__

#include <zlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
extern int zcompress(Bytef *data, uLong ndata, Bytef *zdata, uLong *nzdata);
extern int gzcompress(Bytef *data, uLong ndata, Bytef *zdata, uLong *nzdata);

extern int zdecompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
extern int gzdecompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);

extern int httpgzdecompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
    
#ifdef __cplusplus
}
#endif

#endif

//================================ TEST ================================
//#define BUF_SIZE 65535
//int main()
//{
//    char *data = "kjdalkfjdflkjdlkfjdklfjdlkfjlkdjflkdjflddajfkdjfkdfaskf;ldsfk;ldakf;ldskfl;dskf;ld";
//    uLong ndata = strlen(data);
//    Bytef zdata[BUF_SIZE];
//    uLong nzdata = BUF_SIZE;
//    Bytef odata[BUF_SIZE];
//    uLong nodata = BUF_SIZE;
//    memset(zdata, 0, BUF_SIZE);
//    //if(zcompress((Bytef *)data, ndata, zdata, &nzdata) == 0)
//    if(gzcompress((Bytef *)data, ndata, zdata, &nzdata) == 0)
//    {
//        fprintf(stdout, "nzdata:%d %s\n", nzdata, zdata);
//        memset(odata, 0, BUF_SIZE);
//        //if(zdecompress(zdata, ndata, odata, &nodata) == 0)
//        if(gzdecompress(zdata, ndata, odata, &nodata) == 0)
//        {
//            fprintf(stdout, "%d %s\n", nodata, odata);
//        }
//    }
//}
