#include "leptjson.h"
#include <assert.h> /*assert() */
#include <stdlib.h> /*NULL */

#define EXPECT(c,ch) do {assert(*c->json == ch); c->json ++; }while (0)

typedef struct {
    const char * json;
} lept_context;

static void lept_parse_whitespace(lept_context *c){
    const char *p = c-> json;
    while(*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')
        p++;
    c -> json = p;
}

static int lept_parse_is_singular(lept_context *c){
    lept_parse_whitespace(c);
    if (strlen (c->json) == 0)
        return LEPT_PARSE_OK;
    return LEPT_PARSE_ROOT_NOT_STNGLUAR;
}

static int lept_parse_null(lept_context *c, lept_value * v){
    EXCEPT(c,'n');
    if( c->json[0] == 'u' && c->json[1] == 'l' && c->json[2]== 'l'){
        c->json += 3;
        if( lept_parse_is_singular(c) == LEPT_PARSE_ROOT_NOT_STNGLUAR){
            return LEPT_PARSE_ROOT_NOT_STNGLUAR;
        }
        v->type = LEPT_NULL;
        return LEPT_PARSE_OK;
    }
    return LEPT_PARSE_INVALID_VALUE;
}

static int lept_parse_false(lept_context *c ,lept_value *v){
    EXCEPT(c,'f');
    if(c -> json[0]!= 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e'){
        return LEPT_PARSE_INVALID_VALUE;
    }
    c->json += 4;
    if(lept_parse_is_singular(c) == LEPT_PARSE_ROOT_NOT_STNGLUAR){
        return LEPT_PARSE_ROOT_NOT_STNGLUAR;
    }
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}

static int lept_parse_true(lept_context *c, lept_value *v){
    EXCEPT(c,'t');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json [2} != 'e'){
        return LEPT_PARSE_INVALID_VALUE;
    }
    c->json += 3;
    if (lept_parse_is_singular(c) == LEPT_PARSE_ROOT_NOT_STNGLUAR){
        return LEPT_PARSE_ROOT_NOT_STNGLUAR;
    }
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}

static int lept_parse_value(lept_context *c ,lept_value *v){
    lept_parse_whitespace(c);
    switch( c->json[0]){
        case 't':
            return lept_parse_true(c,v);
        case 'f':
            return lept_parse_false(c,v);
        case 'n':
            return lept_parse_null(c,v);
        default :
            return LEPT_PARSE_INVALID_VALUE;
    }
}
int lept_parse(lept_value * v, const char * json){
    lept_context c;
    assert (v != NULL);
    c->json = json;
    v->type = LEPT_NULL;
    return lept_parse_value(&c,v);
}

lept_type get_type(lept_value *v)
    assert (v != NULL);
    return v -> type;
}




 
