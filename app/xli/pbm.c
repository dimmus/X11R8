/* pbm.c:
 *
 * portable bit map (pbm) format images
 *
 * jim frost 09.27.89
 *
 * patched by W. David Higgins (wdh@mkt.csd.harris.com) to support
 * raw-format PBM files.
 *
 * patched by Ian MacPhedran (macphed@dvinci.usask.ca) to support
 * PGM and PPM files (03-July-1990)
 */

#include "xli.h"
#include "imagetypes.h"
#include "pbm.h"

static int          IntTable[256];
static unsigned int Initialized = 0;

#define NOTINT  -1
#define COMMENT -2
#define SPACE   -3
#define NEWLINE -4

#define BADREAD    0  /* read error */
#define NOTPBM     1  /* not a pbm file */
#define PBMNORMAL  2  /* pbm normal type file */
#define PBMCOMPACT 3  /* pbm compacty type file */
#define PBMRAWBITS 4  /* pbm raw bits type file */
#define PGMNORMAL  5  /* pgm normal type file */
#define PGMRAWBITS 6  /* pgm raw bytes type file */
#define PPMNORMAL  7  /* ppm normal type file */
#define PPMRAWBITS 8  /* ppm raw bytes type file */

static void
initializeTable(void)
{
    unsigned int a;

    for (a = 0; a < 256; a++)
        IntTable[a] = NOTINT;
    IntTable['#']  = COMMENT;
    IntTable['\n'] = NEWLINE;
    IntTable['\r'] = IntTable['\t'] = IntTable[' '] = SPACE;
    IntTable['0']                                   = 0;
    IntTable['1']                                   = 1;
    IntTable['2']                                   = 2;
    IntTable['3']                                   = 3;
    IntTable['4']                                   = 4;
    IntTable['5']                                   = 5;
    IntTable['6']                                   = 6;
    IntTable['7']                                   = 7;
    IntTable['8']                                   = 8;
    IntTable['9']                                   = 9;
    Initialized                                     = 1;
}

static int
pbmReadChar(ZFILE *zf)
{
    int c;

    if ((c = zgetc(zf)) == EOF)
    {
        zclose(zf);
        return (-1);
    }
    if (IntTable[c] == COMMENT) do
        {
            if ((c = zgetc(zf)) == EOF) return (-1);
        }
        while (IntTable[c] != NEWLINE);
    return (c);
}

static int
pbmReadInt(ZFILE *zf)
{
    int c, value;

    for (;;)
    {
        c = pbmReadChar(zf);
        if (c < 0) return (-1);
        if (IntTable[c] >= 0) break;
    };

    value = IntTable[c];
    for (;;)
    {
        c = pbmReadChar(zf);
        if (c < 0) return (-1);
        if (IntTable[c] < 0) return (value);
        value = (value * 10) + IntTable[c];
    }
}

static int
pbmReadRawInt(ZFILE *zf, int depth)
{
    int i, src, src2;

    src = 0;
    for (i = 0; i < depth; i += 8)
    {
        if ((src2 = zgetc(zf)) == EOF) return EOF;
        src = (src << 8) | src2;
    }

    return src;
}

static int
isPBM(ZFILE        *zf,
      char         *name,
      unsigned int *width,
      unsigned int *height,
      unsigned int *maxval,
      unsigned int  verbose)
{
    byte buf[4];

    if (!Initialized) initializeTable();

    if (zread(zf, buf, 2) != 2) return (NOTPBM);

    if (memToVal((byte *)buf, 2) == memToVal((byte *)"P1", 2))
    {
        if (((*width = pbmReadInt(zf)) < 0) || ((*height = pbmReadInt(zf)) < 0))
            return (NOTPBM);

        *maxval = 1;
        if (verbose)
        {
            printf("%s is a %dx%d PBM image\n", name, *width, *height);
        }
        return (PBMNORMAL);
    }

    if (memToVal((byte *)buf, 2) == memToVal((byte *)"P4", 2))
    {
        if (((*width = pbmReadInt(zf)) < 0) || ((*height = pbmReadInt(zf)) < 0))
            return (NOTPBM);

        *maxval = 1;
        if (verbose)
            printf("%s is a %dx%d RawBits PBM image\n", name, *width, *height);
        return (PBMRAWBITS);
    }

    if (memToVal(buf, 2) == 0x2a17)
    {
        if (zread(zf, buf, 4) != 4) return (NOTPBM);

        *width  = memToVal((byte *)buf, 2);
        *height = memToVal((byte *)(buf + 2), 2);
        *maxval = 1;
        if (verbose)
        {
            printf("%s is a %dx%d Compact PBM image\n", name, *width, *height);
        }
        return (PBMCOMPACT);
    }

    if (memToVal(buf, 2) == memToVal((byte *)"P2", 2))
    {
        if (((*width = pbmReadInt(zf)) < 0) || ((*height = pbmReadInt(zf)) < 0))
            return (NOTPBM);

        *maxval = pbmReadInt(zf);
        if (verbose)
        {
            printf("%s is a %dx%d PGM image with %d levels\n",
                   name,
                   *width,
                   *height,
                   (*maxval + 1));
        }
        return (PGMNORMAL);
    }

    if (memToVal(buf, 2) == memToVal((byte *)"P5", 2))
    {
        if (((*width = pbmReadInt(zf)) < 0) || ((*height = pbmReadInt(zf)) < 0))
            return (NOTPBM);

        *maxval = pbmReadInt(zf);
        if (verbose)
            printf("%s is a %dx%d Raw PGM image with %d levels\n",
                   name,
                   *width,
                   *height,
                   (*maxval + 1));
        return (PGMRAWBITS);
    }

    if (memToVal(buf, 2) == memToVal((byte *)"P3", 2))
    {
        if (((*width = pbmReadInt(zf)) < 0) || ((*height = pbmReadInt(zf)) < 0))
            return (NOTPBM);

        *maxval = pbmReadInt(zf);
        if (verbose)
        {
            printf("%s is a %dx%d PPM image with %d levels\n",
                   name,
                   *width,
                   *height,
                   (*maxval + 1));
        }
        return (PPMNORMAL);
    }

    if (memToVal(buf, 2) == memToVal((byte *)"P6", 2))
    {
        if (((*width = pbmReadInt(zf)) < 0) || ((*height = pbmReadInt(zf)) < 0))
            return (NOTPBM);

        *maxval = pbmReadInt(zf);
        if (verbose)
        {
            printf("%s is a %dx%d Raw PPM image with %d levels\n",
                   name,
                   *width,
                   *height,
                   (*maxval + 1));
        }
        return (PPMRAWBITS);
    }
    return (NOTPBM);
}

int
pbmIdent(char *fullname, char *name)
{
    ZFILE       *zf;
    unsigned int width, height, maxval, ret;

    if (!(zf = zopen(fullname))) return (0);

    ret = isPBM(zf, name, &width, &height, &maxval, (unsigned int)1);
    zclose(zf);

    return (ret != NOTPBM);
}

Image *
pbmLoad(char *fullname, ImageOptions *image_ops, boolean verbose)
{
    ZFILE       *zf;
    char        *name  = image_ops->name;
    Image       *image = 0;
    int          pbm_type;
    unsigned int x, y;
    unsigned int width, height, maxval, fmaxval, depth, fdepth;
    unsigned int linelen;
    byte         srcmask, destmask;
    byte        *destptr = 0, *destline;
    int          src     = -1, size;
    unsigned int numbytes, numread;

    if (!(zf = zopen(fullname))) return (NULL);

    pbm_type = isPBM(zf, name, &width, &height, &maxval, verbose);
    if (pbm_type == NOTPBM)
    {
        zclose(zf);
        return (NULL);
    }
    znocache(zf);

    switch (pbm_type)
    {
        case PBMNORMAL:
            image        = newBitImage(width, height);
            image->title = dupString(name);
            linelen      = (width / 8) + (width % 8 ? 1 : 0);
            destline     = image->data;
            for (y = 0; y < height; y++)
            {
                destptr  = destline;
                destmask = 0x80;
                for (x = 0; x < width; x++)
                {
                    do
                    {
                        if ((src = pbmReadChar(zf)) < 0)
                        {
                            fprintf(stderr,
                                    "pbmLoad: %s - Short image\n",
                                    name);
                            zclose(zf);
                            return (image);
                        }
                        if (IntTable[src] == NOTINT)
                        {
                            fprintf(stderr,
                                    "pbmLoad: %s - Bad image data\n",
                                    name);
                            zclose(zf);
                            return (image);
                        }
                    }
                    while (IntTable[src] < 0);

                    switch (IntTable[src])
                    {
                        case 1:
                            *destptr |= destmask;
                        case 0:
                            if (!(destmask >>= 1))
                            {
                                destmask = 0x80;
                                destptr++;
                            }
                            break;
                        default:
                            fprintf(stderr,
                                    "pbmLoad: %s - Bad image data\n",
                                    name);
                            zclose(zf);
                            return (image);
                    }
                }
                destline += linelen;
            }
            break;

        case PBMRAWBITS:
            image        = newBitImage(width, height);
            image->title = dupString(name);
            destline     = image->data;
            linelen      = (width + 7) / 8;
            numbytes     = linelen * height;
            srcmask      = 0; /* force initial read */
            numread      = 0;
            for (y = 0; y < height; y++)
            {
                destptr  = destline;
                destmask = 0x80;
                if (srcmask != 0x80)
                {
                    srcmask = 0x80;
                    if ((numread < numbytes) && ((src = zgetc(zf)) == EOF))
                    {
                        fprintf(stderr, "pbmLoad: %s - Short image\n", name);
                        zclose(zf);
                        return (image);
                    }
                    numread++;
                }
                for (x = 0; x < width; x++)
                {
                    if (src & srcmask) *destptr |= destmask;
                    if (!(destmask >>= 1))
                    {
                        destmask = 0x80;
                        destptr++;
                    }
                    if (!(srcmask >>= 1))
                    {
                        srcmask = 0x80;
                        if ((numread < numbytes) && ((src = zgetc(zf)) == EOF))
                        {
                            fprintf(stderr,
                                    "pbmLoad: %s - Short image\n",
                                    name);
                            zclose(zf);
                            return (image);
                        }
                        numread++;
                    }
                }
                destline += linelen;
            }
            break;

        case PBMCOMPACT:
            image        = newBitImage(width, height);
            image->title = dupString(name);
            destline     = image->data;
            linelen      = (width / 8) + (width % 8 ? 1 : 0);
            srcmask      = 0x80;
            destmask     = 0x80;
            if ((src = zgetc(zf)) == EOF)
            {
                fprintf(stderr, "pbmLoad: %s - Short image\n", name);
                zclose(zf);
                return (image);
            }
            numread  = 1;
            numbytes = width * height;
            numbytes = (numbytes / 8) + (numbytes % 8 ? 1 : 0);
            for (y = 0; y < height; y++)
            {
                destptr  = destline;
                destmask = 0x80;
                for (x = 0; x < width; x++)
                {
                    if (src & srcmask) *destptr |= destmask;
                    if (!(destmask >>= 1))
                    {
                        destmask = 0x80;
                        destptr++;
                    }
                    if (!(srcmask >>= 1))
                    {
                        srcmask = 0x80;
                        if ((numread < numbytes) && ((src = zgetc(zf)) == EOF))
                        {
                            fprintf(stderr,
                                    "pbmLoad: %s - Short image\n",
                                    name);
                            zclose(zf);
                            return (image);
                        }
                        numread++;
                    }
                }
                destline += linelen;
            }
            break;

        case PGMRAWBITS:
            fmaxval = maxval;
            if (maxval > 0xff) maxval = 0xff;
            depth = colorsToDepth(maxval + 1);
            image = newRGBImage(width, height, depth);
        /* use simple ramp for grey scale */
            for (y = 0; y <= maxval; y++)
            {
                *(image->rgb.red + y)   = PM_SCALE(y, maxval, 0xffff);
                *(image->rgb.green + y) = PM_SCALE(y, maxval, 0xffff);
                *(image->rgb.blue + y)  = PM_SCALE(y, maxval, 0xffff);
            }
            image->rgb.used = maxval + 1;
            image->gamma    = 1.0; /* overide xli IRGB guess */
            image->title    = dupString(name);
            size            = height * width;

            if (fmaxval <= 0xff)
            {
            /* read in the image in a chunk */
                if (zread(zf, image->data, size) != size)
                {
                    fprintf(stderr, "pbmLoad: %s - Short image\n", name);
                    zclose(zf);
                    return (image);
                }
            }
            else
            {
                fdepth = colorsToDepth(fmaxval + 1);
                for (y = 0; y < size; y++)
                {
                    if ((src = pbmReadRawInt(zf, fdepth)) == EOF)
                    {
                        fprintf(stderr, "pbmLoad: %s - Short image\n", name);
                        zclose(zf);
                        return (image);
                    }
                    *(destptr++) = PM_SCALE(src, fmaxval, 0xff);
                }
            }
            break;

        case PGMNORMAL:
            fmaxval = maxval;
            if (maxval > 0xff) maxval = 0xff;
            depth = colorsToDepth(maxval + 1);
            image = newRGBImage(width, height, depth);
            for (y = 0; y <= maxval; y++)
            {
                /* As in sunraster.c, use simple ramp for grey scale */
                *(image->rgb.red + y)   = PM_SCALE(y, maxval, 0xffff);
                *(image->rgb.green + y) = PM_SCALE(y, maxval, 0xffff);
                *(image->rgb.blue + y)  = PM_SCALE(y, maxval, 0xffff);
            }
            image->rgb.used = maxval + 1;
            image->gamma    = 1.0; /* overide xli IRGB guess */
            image->title    = dupString(name);
            destptr         = image->data;
            size            = height * width;
            for (y = 0; y < size; y++)
            {
                if ((src = pbmReadInt(zf)) < 0)
                {
                    fprintf(stderr, "pbmLoad: %s - Short image\n", name);
                    zclose(zf);
                    return (image);
                }
                *(destptr++) = PM_SCALE(src, fmaxval, 0xff);
            }
            break;

        case PPMRAWBITS:
            /* this is nice because the bit format is exactly what we want
		 * except for scaling.
		 */

            image        = newTrueImage(width, height);
            image->title = dupString(name);
            size         = height * width * 3;
            if (maxval <= 0xff)
            {
                if (zread(zf, image->data, size) != size)
                {
                    fprintf(stderr, "pbmLoad: %s - Short image\n", name);
                    zclose(zf);
                    return (image);
                }
                if (maxval != 0xff)
                {
                    destptr = image->data;
                    for (y = 0; y < size; y++)
                    {
                        *destptr = PM_SCALE(*destptr, maxval, 0xff);
                        destptr++;
                    }
                }
            }
            else
            {
                fdepth = colorsToDepth(maxval + 1);
                for (y = 0; y < size; y++)
                {
                    if ((src = pbmReadRawInt(zf, fdepth)) == EOF)
                    {
                        fprintf(stderr, "pbmLoad: %s - Short image\n", name);
                        zclose(zf);
                        return (image);
                    }
                    *(destptr++) = PM_SCALE(src, maxval, 0xff);
                }
            }
            break;
        case PPMNORMAL:
            image        = newTrueImage(width, height);
            image->title = dupString(name);
            size         = height * width * 3;
            destptr      = image->data;
            for (y = 0; y < size; y++)
            {
                if ((src = pbmReadInt(zf)) == EOF)
                {
                    fprintf(stderr, "pbmLoad: %s - Short image\n", name);
                    zclose(zf);
                    return (image);
                }
                *(destptr++) = PM_SCALE(src, maxval, 0xff);
            }
            break;
    }
    read_trail_opt(image_ops, zf, image, verbose);
    zclose(zf);
    return (image);
}
