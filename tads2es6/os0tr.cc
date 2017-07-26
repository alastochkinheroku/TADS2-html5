#include "os.h"
#include "lib.h"
#include <emscripten.h>

extern "C" {

int os_init(int *argc, char *argv[], const char *prompt,
        char *buf, int bufsiz)
{
    return (0);
}
void os_uninit() { }
void os_term(int rc) { }

int os_get_abs_filename(char *result_buf, size_t result_buf_size,
                        const char *filename)
{
	strncpy(result_buf, filename, result_buf_size);
	return 1;
}

char *os_strlwr(char *s) { return strlwr(s); }
void os_plain(void) {}
int os_paramfile(char *buf) { return 0; }
int os_break(void) { return 0; }
void os_set_title(const char *title) {}

// Also needed os_gets, osfoprb

// Stub implementations

osfildef *osfoprwb(char *fname, os_filetype_t typ)
{
	fprintf(stderr, "osfoprwb\n");
	return 0;
}

extern int js_getc(void);

int os_getc_raw(void)
{
	printf("os_getc_raw\n");
	return 0;
}

int os_getc(void)
{
//	printf("os_getc\n");
	int a = js_getc();
	return a;
}

void os_get_tmp_path(char *buf)
{
	printf("os_get_tmp_path\n");
	strcpy(buf, "");
}

// from osglk.c
void os_xlat_html4(unsigned int html4_char, char *result, size_t result_len)
{
    /* Return all standard Latin-1 characters as-is */
    if (html4_char <= 128 || (html4_char >= 160 && html4_char <= 255))
	{
		result[0] = (unsigned char)html4_char;
	}
    else {
        switch (html4_char) {	
        case 130:                                      /* single back quote */
            result[0] = '`'; break;
        case 132:                                      /* double back quote */
            result[0] = '\"'; break;
        case 153:                                             /* trade mark */
            strcpy(result, "(tm)"); return;
        case 140:                                            /* OE ligature */
        case 338:                                            /* OE ligature */
            strcpy(result, "OE"); return;
        case 339:                                            /* oe ligature */
            strcpy(result, "oe"); return;
        case 159:                                                   /* Yuml */
            result[0] = 255;
        case 376:                                        /* Y with diaresis */
            result[0] = 'Y'; break;
        case 352:                                           /* S with caron */
            result[0] = 'S'; break;
        case 353:                                           /* s with caron */
            result[0] = 's'; break;
        case 150:                                                /* en dash */
        case 8211:                                               /* en dash */
            result[0] = '-'; break;
        case 151:                                                /* em dash */
        case 8212:                                               /* em dash */
            strcpy(result, "--"); return;
        case 145:                                      /* left single quote */
        case 8216:                                     /* left single quote */
            result[0] = '`'; break;
        case 146:                                     /* right single quote */
        case 8217:                                    /* right single quote */
        case 8218:                                    /* single low-9 quote */
            result[0] = '\''; break;
        case 147:                                      /* left double quote */
        case 148:                                     /* right double quote */
        case 8220:                                     /* left double quote */
        case 8221:                                    /* right double quote */
        case 8222:                                    /* double low-9 quote */
            result[0] = '\"'; break;
        case 8224:                                                /* dagger */
        case 8225:                                         /* double dagger */
        case 8240:                                        /* per mille sign */
            result[0] = ' '; break;
        case 139:                       /* single left-pointing angle quote */
        case 8249:                      /* single left-pointing angle quote */
            result[0] = '<'; break;
        case 155:                      /* single right-pointing angle quote */
        case 8250:                     /* single right-pointing angle quote */
            result[0] = '>'; break;
        case 8482:                                           /* small tilde */
            result[0] = '~'; break;
            
        default:
            /* unmappable character - return space */
            result[0] = (unsigned char)' ';
        }
    }
    result[1] = 0;
}

void os_advise_load_charmap(char *id, char *ldesc, char *sysinfo) 
{
	printf("os_advise_load_charmap\n");
}

void os_gen_charmap_filename(char *filename, char *internal_id,
                             char *argv0)
{
	printf("os_gen_charmap_filename\n");
	strcpy(filename, "");
}

void os_waitc(void)
{
	printf("os_waitc\n");
}

void os_sleep_ms(long delay_in_milliseconds)
{
	// Not valid if I'm not using the Emterpreter
	emscripten_sleep(delay_in_milliseconds);
}

long os_get_sys_clock_ms(void)
{
	printf("os_get_sys_clock_ms\n");
	return 0;
}

int os_is_file_in_dir(const char *filename, const char *path,
                      int include_subdirs, int match_self)
{
	printf("os_is_file_in_dir\n");
	return 0;
}

// Tries to find a game file at the end of the executable. Not used in js version.
osfildef *os_exeseek(const char *argv0, const char *typ)
{
	printf("os_exeseek\n");
	return 0;
}

int os_askfile(const char *prompt, char *fname_buf, int fname_buf_len,
               int prompt_type, os_filetype_t file_type)
{
	printf("os_askfile\n");
	return OS_AFE_FAILURE;
}

int trdmain(int argc, char *argv[], appctxdef *appctx, char *save_ext);


int tads_worker_main()
//int main()
{
    int   argc = 2;
    char *argv[] = {"tr_es6", "game.gam"};
    int err;

    os_init(&argc, argv, (char *)0, (char *)0, 0);
    err = os0main2(argc, argv, trdmain, "", "config.tr", 0);
    os_uninit();
    os_term(err);
	return 0;
}












//**********************************************************************
// The code below is taken from osgen3.c

extern void js_printz(const char *s);

//из iconvlite
static void cp2utf1(char *out, const char *in) {
    static const int table[128] = {
        0x82D0,0x83D0,0x9A80E2,0x93D1,0x9E80E2,0xA680E2,0xA080E2,0xA180E2,
        0xAC82E2,0xB080E2,0x89D0,0xB980E2,0x8AD0,0x8CD0,0x8BD0,0x8FD0,
        0x92D1,0x9880E2,0x9980E2,0x9C80E2,0x9D80E2,0xA280E2,0x9380E2,0x9480E2,
        0,0xA284E2,0x99D1,0xBA80E2,0x9AD1,0x9CD1,0x9BD1,0x9FD1,
        0xA0C2,0x8ED0,0x9ED1,0x88D0,0xA4C2,0x90D2,0xA6C2,0xA7C2,
        0x81D0,0xA9C2,0x84D0,0xABC2,0xACC2,0xADC2,0xAEC2,0x87D0,
        0xB0C2,0xB1C2,0x86D0,0x96D1,0x91D2,0xB5C2,0xB6C2,0xB7C2,
        0x91D1,0x9684E2,0x94D1,0xBBC2,0x98D1,0x85D0,0x95D1,0x97D1,
        0x90D0,0x91D0,0x92D0,0x93D0,0x94D0,0x95D0,0x96D0,0x97D0,
        0x98D0,0x99D0,0x9AD0,0x9BD0,0x9CD0,0x9DD0,0x9ED0,0x9FD0,
        0xA0D0,0xA1D0,0xA2D0,0xA3D0,0xA4D0,0xA5D0,0xA6D0,0xA7D0,
        0xA8D0,0xA9D0,0xAAD0,0xABD0,0xACD0,0xADD0,0xAED0,0xAFD0,
        0xB0D0,0xB1D0,0xB2D0,0xB3D0,0xB4D0,0xB5D0,0xB6D0,0xB7D0,
        0xB8D0,0xB9D0,0xBAD0,0xBBD0,0xBCD0,0xBDD0,0xBED0,0xBFD0,
        0x80D1,0x81D1,0x82D1,0x83D1,0x84D1,0x85D1,0x86D1,0x87D1,
        0x88D1,0x89D1,0x8AD1,0x8BD1,0x8CD1,0x8DD1,0x8ED1,0x8FD1
    };
    while (*in)
        if (*in & 0x80) {
            int v = table[(int)(0x7f & *in++)];
            if (!v)
                continue;
            *out++ = (char)v;
            *out++ = (char)(v >> 8);
            if (v >>= 16)
                *out++ = (char)v;
        }
        else
            *out++ = *in++;
    *out = 0;
}

typedef struct ConvLetter {
        char    win1251;
        int             unicode;
} Letter;

static Letter g_letters[] = {
        {0x82, 0x201A}, // SINGLE LOW-9 QUOTATION MARK
        {0x83, 0x0453}, // CYRILLIC SMALL LETTER GJE
        {0x84, 0x201E}, // DOUBLE LOW-9 QUOTATION MARK
        {0x85, 0x2026}, // HORIZONTAL ELLIPSIS
        {0x86, 0x2020}, // DAGGER
        {0x87, 0x2021}, // DOUBLE DAGGER
        {0x88, 0x20AC}, // EURO SIGN
        {0x89, 0x2030}, // PER MILLE SIGN
        {0x8A, 0x0409}, // CYRILLIC CAPITAL LETTER LJE
        {0x8B, 0x2039}, // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
        {0x8C, 0x040A}, // CYRILLIC CAPITAL LETTER NJE
        {0x8D, 0x040C}, // CYRILLIC CAPITAL LETTER KJE
        {0x8E, 0x040B}, // CYRILLIC CAPITAL LETTER TSHE
        {0x8F, 0x040F}, // CYRILLIC CAPITAL LETTER DZHE
        {0x90, 0x0452}, // CYRILLIC SMALL LETTER DJE
        {0x91, 0x2018}, // LEFT SINGLE QUOTATION MARK
        {0x92, 0x2019}, // RIGHT SINGLE QUOTATION MARK
        {0x93, 0x201C}, // LEFT DOUBLE QUOTATION MARK
        {0x94, 0x201D}, // RIGHT DOUBLE QUOTATION MARK
        {0x95, 0x2022}, // BULLET
        {0x96, 0x2013}, // EN DASH
        {0x97, 0x2014}, // EM DASH
        {0x99, 0x2122}, // TRADE MARK SIGN
        {0x9A, 0x0459}, // CYRILLIC SMALL LETTER LJE
        {0x9B, 0x203A}, // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
        {0x9C, 0x045A}, // CYRILLIC SMALL LETTER NJE
        {0x9D, 0x045C}, // CYRILLIC SMALL LETTER KJE
        {0x9E, 0x045B}, // CYRILLIC SMALL LETTER TSHE
        {0x9F, 0x045F}, // CYRILLIC SMALL LETTER DZHE
        {0xA0, 0x00A0}, // NO-BREAK SPACE
        {0xA1, 0x040E}, // CYRILLIC CAPITAL LETTER SHORT U
        {0xA2, 0x045E}, // CYRILLIC SMALL LETTER SHORT U
        {0xA3, 0x0408}, // CYRILLIC CAPITAL LETTER JE
        {0xA4, 0x00A4}, // CURRENCY SIGN
        {0xA5, 0x0490}, // CYRILLIC CAPITAL LETTER GHE WITH UPTURN
        {0xA6, 0x00A6}, // BROKEN BAR
        {0xA7, 0x00A7}, // SECTION SIGN
        {0xA8, 0x0401}, // CYRILLIC CAPITAL LETTER IO
        {0xA9, 0x00A9}, // COPYRIGHT SIGN
        {0xAA, 0x0404}, // CYRILLIC CAPITAL LETTER UKRAINIAN IE
        {0xAB, 0x00AB}, // LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
        {0xAC, 0x00AC}, // NOT SIGN
        {0xAD, 0x00AD}, // SOFT HYPHEN
        {0xAE, 0x00AE}, // REGISTERED SIGN
        {0xAF, 0x0407}, // CYRILLIC CAPITAL LETTER YI
        {0xB0, 0x00B0}, // DEGREE SIGN
        {0xB1, 0x00B1}, // PLUS-MINUS SIGN
        {0xB2, 0x0406}, // CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I
        {0xB3, 0x0456}, // CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I
        {0xB4, 0x0491}, // CYRILLIC SMALL LETTER GHE WITH UPTURN
        {0xB5, 0x00B5}, // MICRO SIGN
        {0xB6, 0x00B6}, // PILCROW SIGN
        {0xB7, 0x00B7}, // MIDDLE DOT
        {0xB8, 0x0451}, // CYRILLIC SMALL LETTER IO
        {0xB9, 0x2116}, // NUMERO SIGN
        {0xBA, 0x0454}, // CYRILLIC SMALL LETTER UKRAINIAN IE
        {0xBB, 0x00BB}, // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
        {0xBC, 0x0458}, // CYRILLIC SMALL LETTER JE
        {0xBD, 0x0405}, // CYRILLIC CAPITAL LETTER DZE
        {0xBE, 0x0455}, // CYRILLIC SMALL LETTER DZE
        {0xBF, 0x0457} // CYRILLIC SMALL LETTER YI
};

static int convert_utf8_to_windows1251(const char* utf8, char* windows1251, int n)
{
        int i = 0;
        int j = 0;
        for(; i < (int)n && utf8[i] != 0; ++i) {
                char prefix = utf8[i];
                char suffix = utf8[i+1];
                if ((prefix & 0x80) == 0) {
                        windows1251[j] = (char)prefix;
                        ++j;
                } else if ((~prefix) & 0x20) {
                        int first5bit = prefix & 0x1F;
                        first5bit <<= 6;
                        int sec6bit = suffix & 0x3F;
                        int unicode_char = first5bit + sec6bit;

                        if ( unicode_char >= 0x410 && unicode_char <= 0x44F ) {
                                windows1251[j] = (char)(unicode_char - 0x350);
                        } else if (unicode_char >= 0x80 && unicode_char <= 0xFF) {
                                windows1251[j] = (char)(unicode_char);
                        } else if (unicode_char >= 0x402 && unicode_char <= 0x403) {
                                windows1251[j] = (char)(unicode_char - 0x382);
                        } else {
                                int count = sizeof(g_letters) / sizeof(Letter);
                                for (int k = 0; k < count; ++k) {
                                        if (unicode_char == g_letters[k].unicode) {
                                                windows1251[j] = g_letters[k].win1251;
                                                goto NEXT_LETTER;
                                        }
                                }
                                // can't convert this char
                                return 0;
                        }
NEXT_LETTER:
                        ++i;
                        ++j;
                } else {
                        // can't convert this chars
                        return 0;
                }
        }
        windows1251[j] = 0;
        return 1;
}


//fixme: может небольшая величина буфера???
static char out_str[4086];

/* 
 *   os_printz works just like fputs() to stdout: we write a null-terminated
 *   string to the standard output.  
 */
void os_printz(const char *str)
{
	//cp1251toUtf8(str,out_str);
	cp2utf1(out_str,str);
	js_printz(out_str);
//    fputs(str, stdout);
}


/*
 *   os_puts works like fputs() to stdout, except that we are given a
 *   separate length, and the string might not be null-terminated 
 */
void os_print(const char *str, size_t len)
{
	char* strz = (char *)malloc(len + 100);
    sprintf(strz, "%.*s", (int)len, str);
	cp2utf1(out_str,strz);
	js_printz(strz);
	free(strz);
}

/*
 *   os_flush forces output of anything buffered for standard output.  It
 *   is generally used prior to waiting for a key (so the normal flushing
 *   may not occur, as it does when asking for a line of input).  
 */
void os_flush(void)
{
    fflush(stdout);
}

/* 
 *   update the display - since we're using text mode, there's nothing we
 *   need to do 
 */
void os_update_display(void)
{
}

extern void js_gets(char *s, size_t bufl);

static char in_utf8[2048];
/*
 *   os_gets performs the same function as gets().  It should get a
 *   string from the keyboard, echoing it and allowing any editing
 *   appropriate to the system, and return the null-terminated string as
 *   the function's value.  The closing newline should NOT be included in
 *   the string.  
 */
uchar *os_gets(uchar *s, size_t bufl)
{
    /* make sure everything we've displayed so far is actually displayed */
    fflush(stdout);

    /* get a line of input from the standard input */
	js_gets(in_utf8, bufl);
	//Преобразование кодировки
	convert_utf8_to_windows1251(in_utf8,(char *)s,bufl);
	
	return s;
}

/*
 *   The default stdio implementation does not support reading a line of
 *   text with timeout.  
 */
int os_gets_timeout(unsigned char *buf, size_t bufl,
                    unsigned long timeout, int resume_editing)
{
    /* tell the caller this operation is not supported */
    return OS_EVT_NOTIMEOUT;
}

/* 
 *   since we don't support os_gets_timeout(), we don't need to do anything
 *   in the cancel routine
 */
void os_gets_cancel(int reset)
{
    /* os_gets_timeout doesn't do anything, so neither do we */
}

/*
 *   Get an event - stdio version.  This version does not accept a timeout
 *   value, and can only get a keystroke.  
 */
int os_get_event(unsigned long timeout, int use_timeout,
                 os_event_info_t *info)
{
    /* if there's a timeout, return an error indicating we don't allow it */
    if (use_timeout)
        return OS_EVT_NOTIMEOUT;

    /* get a key the normal way */
    info->key[0] = os_getc();

    /* if it's an extended key, get the other key */
    if (info->key[0] == 0)
    {
        /* get the extended key code */
        info->key[1] = os_getc();

        /* if it's EOF, return an EOF event rather than a key event */
        if (info->key[1] == CMD_EOF)
            return OS_EVT_EOF;
    }

    /* return the keyboard event */
    return OS_EVT_KEY;
}






//************************
// File stuff (some stuff taken from osunixt.h)

extern int js_openfile(const char *fname);
extern long js_ftell(int id);
extern int js_fread(void * ptr, int elSize, int numEl, int id);
extern void js_fclose(int id);
extern int js_fseek(int id, long offset, int mode);


struct EsFileProxy
{
	bool isPosixFile;  // POSIX file or ES6 in-memory file
	int inMemoryId;    // If using in-memory file, this is the file id to access it
	FILE *fptr;
};

static osfildef* wrapFile(FILE *fptr)
{
	if (fptr == NULL) return NULL;
	struct EsFileProxy *fileProxy = new EsFileProxy();
	fileProxy->isPosixFile = true;
	fileProxy->fptr = fptr;
	return fileProxy;
}

/* open text file for reading; returns NULL on error */
osfildef *osfoprt(char *fname, int typ)
{
	// Used for reading script files
	fprintf(stderr, "osfoptr: %s\n", fname);
	return wrapFile(fopen(fname, "r"));
}

/* open text file for writing; returns NULL on error */
osfildef *osfopwt(char *fname, int typ)
{
	fprintf(stderr, "osfopwt: %s\n", fname);
	return wrapFile(fopen(fname, "w"));
}

/* open text file for reading/writing; don't truncate */
osfildef *osfoprwt(const char *fname, os_filetype_t typ);

/* open text file for reading/writing; truncate; returns NULL on error */
osfildef *osfoprwtt(char *fname, int typ)
{
	fprintf(stderr, "osfoprwtt: %s\n", fname);
	return wrapFile(fopen(fname, "w+"));
}

/* open binary file for writing; returns NULL on error */
osfildef *osfopwb(char *fname, int typ)
{
	fprintf(stderr, "osfopwb: %s\n", fname);
	return wrapFile(fopen(fname, "wb"));
}

/* open source file for reading */
osfildef *osfoprs(char *fname, int typ)
{
	fprintf(stderr, "osfoprs: %s\n", fname);
	return osfoprt(fname, typ);
}

/* open binary file for reading; returns NULL on error */
osfildef *osfoprb(char *fname, int typ)
{
//	fprintf(stderr, "osfoprb: %s\n", fname);
	int id = js_openfile(fname);
	if (id < 0)
		return NULL;
	EsFileProxy *fileProxy = new EsFileProxy();
	fileProxy->isPosixFile = false;
	fileProxy->fptr = 0;
	fileProxy->inMemoryId = id;
	return fileProxy;
}

/* get a line of text from a text file (fgets semantics) */
char *osfgets(char *buf, size_t len, osfildef *fp)
{
	fprintf(stderr, "osfgets\n");
	return fgets(buf, len, fp->fptr);
}

/* open binary file for reading/writing; don't truncate */
osfildef *osfoprwb(char *fname, os_filetype_t typ);

/* open binary file for reading/writing; truncate; returns NULL on error */
osfildef *osfoprwtb(const char *fname, int typ)
{
	fprintf(stderr, "osfoprwtb: %s\n", fname);
	return wrapFile(fopen(fname, "w+b"));
}

/* write bytes to file; TRUE ==> error */
int osfwb(osfildef *fp, uchar *buf, int bufl)
{
	fprintf(stderr, "osfwb\n");
	return (fwrite(buf, bufl, 1, fp->fptr) != 1);
}

/* read bytes from file; TRUE ==> error */
int osfrb(osfildef *fp, uchar *buf, int bufl)
{
//	fprintf(stderr, "osfrb\n");
	if (fp->isPosixFile)
		return (fread(buf, bufl, 1, fp->fptr) != 1);
	else
		return (js_fread(buf, bufl, 1, fp->inMemoryId) != 1);
}

/* read bytes from file and return count; returns # bytes read, 0=error */
size_t osfrbc(osfildef *fp, uchar *buf, size_t bufl)
{
	fprintf(stderr, "osfrbc\n");
	return (fread(buf, 1, bufl, fp->fptr));
}

/* get position in file */
long osfpos(osfildef *fp)
{
//	fprintf(stderr, "osfpos\n");
	if (fp->isPosixFile)
		return ftell(fp->fptr);
	else
		return js_ftell(fp->inMemoryId);
}

/* seek position in file; TRUE ==> error */
int osfseek(osfildef *fp, long pos, int mode)
{
//	fprintf(stderr, "osfseek\n");
	if (fp->isPosixFile)
		return fseek(fp->fptr, pos, mode);
	int jsFMode = 0;
	if (mode == OSFSK_SET) 
		jsFMode = -1;
	else if (mode == OSFSK_END)
		jsFMode = 1;
	return js_fseek(fp->inMemoryId, pos, jsFMode);
}

/* close a file */
void osfcls(osfildef *fp)
{
	if (fp->isPosixFile)
		fclose(fp->fptr);
	else
		js_fclose(fp->inMemoryId);
	delete fp;
}

/* delete a file - TRUE if error */
int osfdel(char *fname)
{
	return remove(fname);
}

/* access a file - 0 if file exists */
int osfacc(char *fname)
{
	return access(fname, 0);
}

/* get a character from a file */
int osfgetc(osfildef *fp)
{
	fprintf(stderr, "osfgetc\n");
	return fgetc(fp->fptr);
}

/* write a string to a file */
int osfputs(char *buf, osfildef *fp)
{
	fprintf(stderr, "osfputs\n");
	fputs(buf, fp->fptr);
}

} // extern "C"