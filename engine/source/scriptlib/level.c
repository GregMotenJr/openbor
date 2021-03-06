// Level Properties
// 2017-04-26
// Caskey, Damon V.
//
// Access to level and level set properties.

#ifndef SCRIPT_LEVEL
#define SCRIPT_LEVEL 1

#include "common.c"

// Set Handle
// Caskey, Damon V.
// 2017-04-26
//
// Get the handle (pointer) of a level set.
//
// get_set_handle(int index)
HRESULT openbor_get_set_handle(ScriptVariant **varlist , ScriptVariant **pretvar, int paramCount)
{
    #define SELF_NAME       "get_set_handle(int index)"
    #define ARG_MINIMUM     1   // Minimum required arguments.
    #define ARG_INDEX       0   // Array index.

    int                 result;
    LONG                index;
    extern s_set_entry *levelsets;
    extern int          num_difficulties;

    if(paramCount != ARG_MINIMUM)
    {
        goto error_local;
    }

    if(FAILED(ScriptVariant_IntegerValue(varlist[ARG_INDEX], &index)))
    {
        goto error_local;
    }

    ScriptVariant_Clear(*pretvar);

    // Verify the index is within bounds, and
    // if so, dereference the array element pointer.
    if(index < num_difficulties && index >= 0)
    {
        ScriptVariant_ChangeType(*pretvar, VT_PTR);
        (*pretvar)->ptrVal = &levelsets[index];
    }

    result = S_OK;

    return result;

    // Error trapping.
    error_local:

    printf("You must provide a valid index: " SELF_NAME "\n");

    *pretvar    = NULL;
    result      = E_FAIL;
    return result;

    #undef SELF_NAME
    #undef ARG_MINIMUM
    #undef ARG_INDEX
}

// Level Handle
// Caskey, Damon V.
// 2017-04-26
//
// Get the handle (pointer) from a collection of levels.
//
/* get_level_handle(void collection_handle, int index)
HRESULT openbor_get_level_handle(ScriptVariant **varlist, ScriptVariant **pretvar, int paramCount)
{
    #define SELF_NAME       "openbor_get_level_handle(void levels_handle, int index)"
    #define ARG_MINIMUM     2   // Minimum required arguments.
    #define ARG_LEVEL       0   // Level handle.
    #define ARG_INDEX       1   // Array index.

    int             result;
    LONG            index;
    s_level_entry   *collection;
    extern int      num_;

    // Verify arguments and populate local
    // variables as needed.
    if(paramCount != ARG_MINIMUM)
    {
        goto error_local;
    }

    if(varlist[ARG_LEVEL]->vt != VT_PTR && varlist[ARG_LEVEL]->vt != VT_EMPTY)
    {
        goto error_local;
    }

    if(FAILED(ScriptVariant_IntegerValue(varlist[ARG_INDEX], &index)))
    {
        goto error_local;
    }

    // Clear pass by var value.
    ScriptVariant_Clear(*pretvar);

    // Get collection pointer.
    collection = varlist[ARG_LEVEL]->ptrVal;

    ScriptVariant_ChangeType(*pretvar, VT_PTR);
    (*pretvar)->ptrVal = &level->collection[index];

    result = S_OK;

    return result;

    // Error trapping.
    error_local:

    printf("You must provide a valid index: " SELF_NAME "\n");

    *pretvar    = NULL;
    result      = E_FAIL;
    return result;

    #undef SELF_NAME
    #undef ARG_MINIMUM
    #undef ARG_LEVEL
    #undef ARG_INDEX
}*/

// Set specific properties.
// Caskey, Damon V.
// 2017-04-25
//
// Access set property by handle.
//
// get_set_property(void handle, int frame, int property)
HRESULT openbor_get_set_property(ScriptVariant **varlist, ScriptVariant **pretvar, int paramCount)
{
    #define SELF_NAME       "get_set_property(void handle, int property)"
    #define ARG_MINIMUM     2   // Minimum required arguments.
    #define ARG_HANDLE      0   // Handle (pointer to property structure).
    #define ARG_PROPERTY    1   // Property to access.


    int                     result      = S_OK; // Success or error?
    s_set_entry             *handle     = NULL; // Property handle.
    e_set_properties        property    = 0;    // Property argument.

    // Clear pass by reference argument used to send
    // property data back to calling script.     .
    ScriptVariant_Clear(*pretvar);

    // Verify incoming arguments. There should at least
    // be a pointer for the property handle and an integer
    // to determine which property is accessed.
    if(paramCount < ARG_MINIMUM
       || varlist[ARG_HANDLE]->vt != VT_PTR
       || varlist[ARG_PROPERTY]->vt != VT_INTEGER)
    {
        *pretvar = NULL;
        goto error_local;
    }
    else
    {
        handle      = (s_set_entry *)varlist[ARG_HANDLE]->ptrVal;
        property    = (LONG)varlist[ARG_PROPERTY]->lVal;
    }

    // Which property to get?
    switch(property)
    {
        case SET_PROP_CREDITS:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->credits;
            break;

        case SET_PROP_GAME_OVER_SKIP:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->noshowgameover;
            break;

        case SET_PROP_HOF_DISABLE:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->noshowhof;
            break;

        case SET_PROP_COMPLETE_FLAG:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->ifcomplete;
            break;

        case SET_PROP_COMPLETE_SKIP:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->noshowcomplete;

        case SET_PROP_CONTINUE_SCORE_TYPE:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->continuescore;

        case SET_PROP_LEVELS_COUNT:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->numlevels;
            break;

        case SET_PROP_LEVELS_HANDLE:

            // Verify the handle is populated.
            if(handle->levelorder)
            {
                ScriptVariant_ChangeType(*pretvar, VT_PTR);
                (*pretvar)->ptrVal = (VOID *)handle->levelorder;
            }

            break;

        case SET_PROP_LIVES:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->lives;
            break;

        case SET_PROP_MP_RECOVER_TYPE:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->typemp;
            break;

        case SET_PROP_MUSIC_FADE_TIME:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->custfade;
            break;

        case SET_PROP_MUSIC_OVERLAP:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->musicoverlap;
            break;

        case SET_PROP_NAME:

            ScriptVariant_ChangeType(*pretvar, VT_STR);
            StrCache_Copy((*pretvar)->strVal, handle->name);
            break;

        case SET_PROP_PLAYER_MAX:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->maxplayers;
            break;

        case SET_PROP_SAVE_TYPE:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->saveflag;
            break;

        case SET_PROP_SELECT_DISABLE:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->noselect;
            break;

        case SET_PROP_SELECT_NO_SAME:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->nosame;
            break;

        default:

            printf("Unsupported property.\n");
            goto error_local;
            break;
    }

    return result;

    // Error trapping.
    error_local:

    printf("You must provide a valid handle and property: " SELF_NAME "\n");

    result = E_FAIL;
    return result;

    #undef SELF_NAME
    #undef ARG_MINIMUM
    #undef ARG_HANDLE
    #undef ARG_PROPERTY
}

// Set specific properties.
// Caskey, Damon V.
// 2016-10-20
//
// Access set property by handle (pointer).
//
// set_set_property(void handle, int property, value)
HRESULT openbor_set_set_property(ScriptVariant **varlist, ScriptVariant **pretvar, int paramCount)
{
    #define SELF_NAME           "set_set_property(void handle, int property, value)"
    #define ARG_MINIMUM         3   // Minimum required arguments.
    #define ARG_HANDLE          0   // Handle (pointer to property structure).
    #define ARG_PROPERTY        1   // Property to access.
    #define ARG_VALUE           2   // New value to apply.

    int                     result      = S_OK; // Success or error?
    s_set_entry             *handle     = NULL; // Property handle.
    e_set_properties        property    = 0;    // Property to access.

    // Value carriers to apply on properties after
    // taken from argument.
    //int     temp_int;
    //DOUBLE  temp_float;

    // Verify incoming arguments. There must be a
    // pointer for the animation handle, an integer
    // property, and a new value to apply.
    if(paramCount < ARG_MINIMUM
       || varlist[ARG_HANDLE]->vt != VT_PTR
       || varlist[ARG_PROPERTY]->vt != VT_INTEGER)
    {
        *pretvar = NULL;
        goto error_local;
    }
    else
    {
        handle      = (s_set_entry *)varlist[ARG_HANDLE]->ptrVal;
        property    = (LONG)varlist[ARG_PROPERTY]->lVal;
    }

    // Which property to modify?
    switch(property)
    {
        case SET_PROP_LEVELS_HANDLE:

            handle->levelorder = (s_level_entry *)varlist[ARG_VALUE]->ptrVal;

            break;

        default:

            printf("Unsupported or read only property.\n");
            goto error_local;

            break;
    }

    return result;

    // Error trapping.
    error_local:

    printf("You must provide a valid handle, property and value: " SELF_NAME "\n");

    result = E_FAIL;
    return result;

    #undef SELF_NAME
    #undef ARG_MINIMUM
    #undef ARG_HANDLE
    #undef ARG_PROPERTY
    #undef ARG_VALUE
}



// Level specific properties.
// Caskey, Damon V.
// 2017-04-25
//
// Access level property by handle.
//
// get_level_property(void handle, int frame, int property)
HRESULT openbor_get_level_property(ScriptVariant **varlist, ScriptVariant **pretvar, int paramCount)
{
    #define SELF_NAME       "get_level_property(void handle, int property)"
    #define ARG_MINIMUM     2   // Minimum required arguments.
    #define ARG_HANDLE      0   // Handle (pointer to property structure).
    #define ARG_PROPERTY    1   // Property to access.


    int                     result      = S_OK; // Success or error?
    s_level                 *handle     = NULL; // Property handle.
    e_level_properties      property    = 0;    // Property argument.

    // Clear pass by reference argument used to send
    // property data back to calling script.     .
    ScriptVariant_Clear(*pretvar);

    // Verify incoming arguments. There should at least
    // be a pointer for the property handle and an integer
    // to determine which property is accessed.
    if(paramCount < ARG_MINIMUM
       || varlist[ARG_HANDLE]->vt != VT_PTR
       || varlist[ARG_PROPERTY]->vt != VT_INTEGER)
    {
        *pretvar = NULL;
        goto error_local;
    }
    else
    {
        handle      = (s_level *)varlist[ARG_HANDLE]->ptrVal;
        property    = (LONG)varlist[ARG_PROPERTY]->lVal;
    }

    // Which property to get?
    switch(property)
    {
        case LEVEL_PROP_AUTO_SCROLL_X:

            ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
            (*pretvar)->dblVal = (DOUBLE)handle->bgspeed;
            break;

        case LEVEL_PROP_AUTO_SCROLL_Y:

            ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
            (*pretvar)->dblVal = (DOUBLE)handle->vbgspeed;
            break;

        case LEVEL_PROP_BASEMAPS_COUNT:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->numbasemaps;
            break;

        case LEVEL_PROP_BASEMAPS_HANDLE:

            // Verify the handle is populated.
            if(handle->basemaps)
            {
                ScriptVariant_ChangeType(*pretvar, VT_PTR);
                (*pretvar)->ptrVal = (VOID *)handle->basemaps;
            }

            break;

        case LEVEL_PROP_BGLAYERS_COUNT:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->numbglayers;
            break;

            break;

        case LEVEL_PROP_BGLAYERS_HANDLE:

            // Verify the handle is populated.
            if(handle->basemaps)
            {
                ScriptVariant_ChangeType(*pretvar, VT_PTR);
                (*pretvar)->ptrVal = (VOID *)handle->bglayers;
            }

            break;

        case LEVEL_PROP_CAMERA_OFFSET_X:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->cameraxoffset;
            break;

        case LEVEL_PROP_CAMERA_OFFSET_Z:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->camerazoffset;
            break;

        case LEVEL_PROP_GRAVITY:

           ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
            (*pretvar)->dblVal = (DOUBLE)handle->gravity;
            break;

        case LEVEL_PROP_HOLES_COUNT:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->numholes;
            break;

        case LEVEL_PROP_HOLES_HANDLE:

            // Verify the handle is populated.
            if(handle->holes)
            {
                ScriptVariant_ChangeType(*pretvar, VT_PTR);
                (*pretvar)->ptrVal = (VOID *)handle->holes;
            }

            break;

        case LEVEL_PROP_LAYERS_COUNT:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->numlayers;
            break;

        case LEVEL_PROP_LAYERS_HANDLE:

            // Verify animation has item.
            if(handle->layers)
            {
                ScriptVariant_ChangeType(*pretvar, VT_PTR);
                (*pretvar)->ptrVal = (VOID *)handle->layers;
            }

            break;

        case LEVEL_PROP_MAX_FALL_VELOCITY:

            ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
            (*pretvar)->dblVal = (DOUBLE)handle->maxfallspeed;
            break;

        case LEVEL_PROP_MAX_TOSS_VELOCITY:

            ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
            (*pretvar)->dblVal = (DOUBLE)handle->maxtossspeed;
            break;

        case LEVEL_PROP_PALETTES_COUNT:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->numpalettes;
            break;

        case LEVEL_PROP_PALETTES_HANDLE:

            // Verify animation has item.
            if(handle->palettes)
            {
                ScriptVariant_ChangeType(*pretvar, VT_PTR);
                (*pretvar)->ptrVal = (VOID *)handle->palettes;
            }

            break;

        case LEVEL_PROP_QUAKE:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->quake;
            break;

        case LEVEL_PROP_ROCKING:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->rocking;
            break;

        case LEVEL_PROP_SCROLL_VELOCITY:

            ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
            (*pretvar)->lVal = (DOUBLE)handle->scrollspeed;
            break;

        case LEVEL_PROP_TYPE:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->type;
            break;

        case LEVEL_PROP_WALLS_COUNT:

            ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
            (*pretvar)->lVal = (LONG)handle->numwalls;
            break;

        case LEVEL_PROP_WALLS_HANDLE:

            // Verify animation has item.
            if(handle->walls)
            {
                ScriptVariant_ChangeType(*pretvar, VT_PTR);
                (*pretvar)->ptrVal = (VOID *)handle->walls;
            }

            break;

        default:

            printf("Unsupported property.\n");
            goto error_local;
            break;
    }

    return result;

    // Error trapping.
    error_local:

    printf("You must provide a valid handle and property: " SELF_NAME "\n");

    result = E_FAIL;
    return result;

    #undef SELF_NAME
    #undef ARG_MINIMUM
    #undef ARG_HANDLE
    #undef ARG_PROPERTY
}

// Level specific properties.
// Caskey, Damon V.
// 2017-04-25
//
// Access level property by handle (pointer).
//
// set_level_property(void handle, int property, value)
HRESULT openbor_set_level_property(ScriptVariant **varlist, ScriptVariant **pretvar, int paramCount)
{
    #define SELF_NAME           "set_level_property(void handle, int property, value)"
    #define ARG_MINIMUM         3   // Minimum required arguments.
    #define ARG_HANDLE          0   // Handle (pointer to property structure).
    #define ARG_PROPERTY        1   // Property to access.
    #define ARG_VALUE           2   // New value to apply.

    int                     result      = S_OK; // Success or error?
    s_level                 *handle     = NULL; // Property handle.
    e_level_properties      property    = 0;    // Property to access.

    // Value carriers to apply on properties after
    // taken from argument.
    //int     temp_int;
    //DOUBLE  temp_float;

    // Verify incoming arguments. There must be a
    // pointer for the animation handle, an integer
    // property, and a new value to apply.
    if(paramCount < ARG_MINIMUM
       || varlist[ARG_HANDLE]->vt != VT_PTR
       || varlist[ARG_PROPERTY]->vt != VT_INTEGER)
    {
        *pretvar = NULL;
        goto error_local;
    }
    else
    {
        handle      = (s_level *)varlist[ARG_HANDLE]->ptrVal;
        property    = (LONG)varlist[ARG_PROPERTY]->lVal;
    }

    // Which property to modify?
    switch(property)
    {

        case SET_PROP_LEVELS_HANDLE:

            handle->bglayers = (s_layer **)varlist[ARG_VALUE]->ptrVal;

            break;

        default:

            printf("Unsupported property.\n");
            goto error_local;

            break;
    }

    return result;

    // Error trapping.
    error_local:

    printf("You must provide a valid handle and property: " SELF_NAME "\n");

    result = E_FAIL;
    return result;

    #undef SELF_NAME
    #undef ARG_MINIMUM
    #undef ARG_HANDLE
    #undef ARG_PROPERTY
    #undef ARG_VALUE
}

// ===== Depreciated =====
//
// The following items are depreciated as
// of 2017-04-26 and are included only for
// backward compatibility. Do not add to or
// update.
//
// DC

// ===== level properties ======
enum levelproperty_enum
{
    _lp_basemap,
    _lp_bgspeed,
    _lp_cameraxoffset,
    _lp_camerazoffset,
    _lp_gravity,
    _lp_hole,
    _lp_maxfallspeed,
    _lp_maxtossspeed,
    _lp_quake,
    _lp_rocking,
    _lp_scrollspeed,
    _lp_type,
    _lp_vbgspeed,
    _lp_wall,
    _lp_the_end,
};

enum basemap_enum
{
    _lp_bm_map,
    _lp_bm_x,
    _lp_bm_xsize,
    _lp_bm_z,
    _lp_bm_zsize,
    _lp_bm_the_end,
};

enum terrain_enum
{
    _lp_terrain_depth,
    _lp_terrain_height,
    _lp_terrain_lowerleft,
    _lp_terrain_lowerright,
    _lp_terrain_type,
    _lp_terrain_upperleft,
    _lp_terrain_upperright,
    _lp_terrain_x,
    _lp_terrain_z,
    _lp_terrain_the_end,
};

int mapstrings_levelproperty(ScriptVariant **varlist, int paramCount)
{
    char *propname = NULL;
    int prop;

    static const char *proplist[] =
    {
        "basemap",
        "bgspeed",
        "cameraxoffset",
        "camerazoffset",
        "gravity",
        "hole",
        "maxfallspeed",
        "maxtossspeed",
        "quake",
        "rocking",
        "scrollspeed",
        "type",
        "vbgspeed",
        "wall",
    };

    static const char *basemaplist[] =
    {
        "map",
        "x",
        "xsize",
        "z",
        "zsize",
    };

    static const char *terrainlist[] =
    {
        /*
        Walls and holes.
        */

        "depth",
        "height",
        "lowerleft",
        "lowerright",
        "type",
        "upperleft",
        "upperright",
        "x",
        "z",
    };

    if(paramCount < 1)
    {
        return 1;
    }
    MAPSTRINGS(varlist[0], proplist, _lp_the_end,
               "Level property '%s' is not supported.\n");

    if(paramCount >= 3 && varlist[0]->vt == VT_INTEGER && varlist[0]->lVal == _lp_basemap)
    {
        MAPSTRINGS(varlist[2], basemaplist, _lp_bm_the_end,
                   _is_not_supported_by_, "basemap");
    }

    if(paramCount >= 3 && varlist[0]->vt == VT_INTEGER && (varlist[0]->lVal == _lp_hole || varlist[0]->lVal == _lp_wall))
    {
        MAPSTRINGS(varlist[2], terrainlist, _lp_terrain_the_end,
                   _is_not_supported_by_, "wall/hole");
    }

    return 1;
}

HRESULT openbor_getlevelproperty(ScriptVariant **varlist , ScriptVariant **pretvar, int paramCount)
{
    LONG ltemp;
    DOUBLE dbltemp2, dbltemp3;
    mapstrings_levelproperty(varlist, paramCount);

    switch(varlist[0]->lVal)
    {
    case _lp_bgspeed:
    {
        ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
        (*pretvar)->lVal = (DOUBLE)level->bgspeed;
        break;
    }
    case _lp_vbgspeed:
    {
        ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
        (*pretvar)->lVal = (DOUBLE)level->vbgspeed;
        break;
    }
    case _lp_cameraxoffset:
    {
        ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
        (*pretvar)->lVal = (LONG)level->cameraxoffset;
        break;
    }
    case _lp_camerazoffset:
    {
        ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
        (*pretvar)->lVal = (LONG)level->camerazoffset;
        break;
    }
    case _lp_gravity:
    {
        ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
        (*pretvar)->dblVal = (DOUBLE)level->gravity;
        break;
    }
    case _lp_maxfallspeed:
    {
        ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
        (*pretvar)->dblVal = (DOUBLE)level->maxfallspeed;
        break;
    }
    case _lp_maxtossspeed:
    {
        ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
        (*pretvar)->dblVal = (DOUBLE)level->maxtossspeed;
        break;
    }
    case _lp_quake:
    {
        ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
        (*pretvar)->lVal = (LONG)level->quake;
        break;
    }
    case _lp_scrollspeed:
    {
        ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);
        (*pretvar)->dblVal = (DOUBLE)level->scrollspeed;
        break;
    }
    case _lp_type:
    {
        ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
        (*pretvar)->lVal = (LONG)level->type;
        break;
    }
    case _lp_hole:
    {

        if(paramCount > 2 && SUCCEEDED(ScriptVariant_IntegerValue(varlist[1], &ltemp))
                && ltemp >= 0 && ltemp < level->numholes)
        {

            if(varlist[2]->vt != VT_STR)
                printf("You must provide a string value for hole subproperty.\n");
                goto getlevelproperty_error;

            ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);

            switch(varlist[2]->lVal)
            {
                case _lp_terrain_height:
                {
                    (*pretvar)->dblVal = level->holes[ltemp].height;
                    break;
                }
                case _lp_terrain_depth:
                {
                    (*pretvar)->dblVal = level->holes[ltemp].depth;
                    break;
                }
                case _lp_terrain_lowerleft:
                {
                    (*pretvar)->dblVal = level->holes[ltemp].lowerleft;
                    break;
                }
                case _lp_terrain_lowerright:
                {
                    (*pretvar)->dblVal = level->holes[ltemp].lowerright;
                    break;
                }
                case _lp_terrain_upperleft:
                {
                    (*pretvar)->dblVal = level->holes[ltemp].upperleft;
                    break;
                }
                case _lp_terrain_upperright:
                {
                    (*pretvar)->dblVal = level->holes[ltemp].upperright;
                    break;
                }
                case _lp_terrain_x:
                {
                    (*pretvar)->dblVal = level->holes[ltemp].x;
                    break;
                }
                case _lp_terrain_z:
                {
                    (*pretvar)->dblVal = level->holes[ltemp].z;
                    break;
                }
                case _lp_terrain_type:
                {
                    ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
                    (*pretvar)->lVal = level->holes[ltemp].type;
                    break;
                }
                default:
                {
                    printf("Invalid subproperty for hole.\n");
                    goto getlevelproperty_error;
                }
            }
        }
        else
        {
            printf("Error in wall property.\n");
            goto getlevelproperty_error;
        }
        break;

    }
    case _lp_wall:
    {
        if(paramCount > 2 && SUCCEEDED(ScriptVariant_IntegerValue(varlist[1], &ltemp))
                && ltemp >= 0 && ltemp < level->numwalls)
        {

            if(varlist[2]->vt != VT_STR)
                printf("You must provide a string value for wall subproperty.\n");
                goto getlevelproperty_error;

            ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);

            switch(varlist[2]->lVal)
            {
                case _lp_terrain_depth:
                {
                    (*pretvar)->dblVal = level->walls[ltemp].depth;
                    break;
                }
                case _lp_terrain_height:
                {
                    (*pretvar)->dblVal = level->walls[ltemp].height;
                    break;
                }
                case _lp_terrain_lowerleft:
                {
                    (*pretvar)->dblVal = level->walls[ltemp].lowerleft;
                    break;
                }
                case _lp_terrain_lowerright:
                {
                    (*pretvar)->dblVal = level->walls[ltemp].lowerright;
                    break;
                }
                case _lp_terrain_upperleft:
                {
                    (*pretvar)->dblVal = level->walls[ltemp].upperleft;
                    break;
                }
                case _lp_terrain_upperright:
                {
                    (*pretvar)->dblVal = level->walls[ltemp].upperright;
                    break;
                }
                case _lp_terrain_x:
                {
                    (*pretvar)->dblVal = level->walls[ltemp].x;
                    break;
                }
                case _lp_terrain_z:
                {
                    (*pretvar)->dblVal = level->walls[ltemp].z;
                    break;
                }
                case _lp_terrain_type:
                {
                    ScriptVariant_ChangeType(*pretvar, VT_INTEGER);
                    (*pretvar)->lVal = level->walls[ltemp].type;
                    break;
                }
                default:
                {
                    printf("Invalid subproperty for wall.\n");
                    goto getlevelproperty_error;
                }
            }
        }
        else
        {
            printf("Error in wall property.\n");
            goto getlevelproperty_error;
        }
        break;
    }
    case _lp_basemap:
        if(SUCCEEDED(ScriptVariant_IntegerValue(varlist[1], &ltemp)) && ltemp >= 0 && ltemp < level->numbasemaps)
        {
            if(paramCount >= 3)
            {

                if(varlist[2]->vt != VT_STR)
                    printf("You must provide a string value for basemap subproperty.\n");
                    goto getlevelproperty_error;

                ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);

                switch(varlist[2]->lVal)
                {
                case _lp_bm_x:
                    (*pretvar)->dblVal = level->basemaps[ltemp].position.x;
                    break;
                case _lp_bm_xsize:
                    (*pretvar)->dblVal = level->basemaps[ltemp].size.x;
                    break;
                case _lp_bm_z:
                    (*pretvar)->dblVal = level->basemaps[ltemp].position.z;
                    break;
                case _lp_bm_zsize:
                    (*pretvar)->dblVal = level->basemaps[ltemp].size.z;
                    break;
                case _lp_bm_map:
                    if(paramCount >= 5 && SUCCEEDED(ScriptVariant_DecimalValue(varlist[3], &dbltemp2)) &&
                            SUCCEEDED(ScriptVariant_DecimalValue(varlist[4], &dbltemp3)) &&
                            dbltemp2 >= 0 && dbltemp2 < level->basemaps[ltemp].size.x && dbltemp3 >= 0 && dbltemp3 < level->basemaps[ltemp].size.z
                      )
                    {
                        if(!level->basemaps[ltemp].map)
                        {
                            (*pretvar)->dblVal = (DOUBLE)0;
                        }
                        else (*pretvar)->dblVal = (DOUBLE)level->basemaps[ltemp].map[(LONG)(dbltemp2 + dbltemp3 * level->basemaps[ltemp].size.x)];
                    }
                    else
                    {
                        goto getlevelproperty_error;
                    }
                    break;
                default:
                    goto getlevelproperty_error;
                }
            }
            else
            {
                goto getlevelproperty_error;
            }
        }
        else
        {
            goto getlevelproperty_error;
        }
        break;
    default:
        printf("Property is not supported by function getlevelproperty yet. %d\n", varlist[0]->lVal);
        goto getlevelproperty_error;
        break;
    }

    return S_OK;

getlevelproperty_error:
    *pretvar = NULL;
    return E_FAIL;
}

//changelevelproperty(name, value)
HRESULT openbor_changelevelproperty(ScriptVariant **varlist , ScriptVariant **pretvar, int paramCount)
{
    LONG ltemp, ltemp1;
    DOUBLE dbltemp, dbltemp2, dbltemp3;
    static char buf[64];
    int i;
    ScriptVariant *arg = NULL;

    *pretvar = NULL;

    if(paramCount < 2)
    {
        printf("Function changelevelproperty(prop, value) need at least 2 parameters.\n");
        return E_FAIL;
    }

    mapstrings_levelproperty(varlist, paramCount);

    arg = varlist[1];

    switch(varlist[0]->lVal)
    {
    case _lp_rocking:
        if(SUCCEEDED(ScriptVariant_IntegerValue(arg, &ltemp)))
        {
            level->rocking = (int)ltemp;
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_bgspeed:
        if(SUCCEEDED(ScriptVariant_DecimalValue(arg, &dbltemp)))
        {
            level->bgspeed = (float)dbltemp;
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_vbgspeed:
        if(SUCCEEDED(ScriptVariant_DecimalValue(arg, &dbltemp)))
        {
            level->vbgspeed = (float)dbltemp;
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_scrollspeed:
        if(SUCCEEDED(ScriptVariant_DecimalValue(arg, &dbltemp)))
        {
            level->scrollspeed = (float)dbltemp;
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_type:
        if(SUCCEEDED(ScriptVariant_IntegerValue(arg, &ltemp)))
        {
            level->type = (int)ltemp;
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_cameraxoffset:
        if(SUCCEEDED(ScriptVariant_IntegerValue(arg, &ltemp)))
        {
            level->cameraxoffset = (int)ltemp;
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_camerazoffset:
        if(SUCCEEDED(ScriptVariant_IntegerValue(arg, &ltemp)))
        {
            level->camerazoffset = (int)ltemp;
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_gravity:
        if(SUCCEEDED(ScriptVariant_DecimalValue(arg, &dbltemp)))
        {
            level->gravity = (float)dbltemp;
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_maxfallspeed:
        if(SUCCEEDED(ScriptVariant_DecimalValue(arg, &dbltemp)))
        {
            level->maxfallspeed = (float)dbltemp;
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_maxtossspeed:
        if(SUCCEEDED(ScriptVariant_DecimalValue(arg, &dbltemp)))
        {
            level->maxtossspeed = (float)dbltemp;
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_quake:
        if(SUCCEEDED(ScriptVariant_IntegerValue(arg, &ltemp)))
        {
            level->quake = (int)ltemp;
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_basemap:
        if(SUCCEEDED(ScriptVariant_IntegerValue(varlist[1], &ltemp)) && ltemp >= 0)
        {
            if(ltemp >= level->numbasemaps)
            {
                __reallocto(level->basemaps, level->numbasemaps, ltemp + 1);
                level->numbasemaps = ltemp + 1;
            }
            if(paramCount >= 4)
            {
                switch(varlist[2]->lVal)
                {
                case _lp_bm_x:
                    if(SUCCEEDED(ScriptVariant_DecimalValue(varlist[3], &dbltemp2)) )
                    {
                        level->basemaps[ltemp].position.x = dbltemp2;
                    }
                    else
                    {
                        goto clperror;
                    }
                    break;
                case _lp_bm_xsize:
                    if(SUCCEEDED(ScriptVariant_DecimalValue(varlist[3], &dbltemp2)) )
                    {
                        level->basemaps[ltemp].size.x = dbltemp2;
                    }
                    else
                    {
                        goto clperror;
                    }
                    break;
                case _lp_bm_z:
                    if(SUCCEEDED(ScriptVariant_DecimalValue(varlist[3], &dbltemp2)) )
                    {
                        level->basemaps[ltemp].position.z = dbltemp2;
                    }
                    else
                    {
                        goto clperror;
                    }
                    break;
                case _lp_bm_zsize:
                    if(SUCCEEDED(ScriptVariant_DecimalValue(varlist[3], &dbltemp2)) )
                    {
                        level->basemaps[ltemp].size.z = dbltemp2;
                    }
                    else
                    {
                        goto clperror;
                    }
                    break;
                case _lp_bm_map:
                    if(paramCount >= 6 && SUCCEEDED(ScriptVariant_DecimalValue(varlist[3], &dbltemp2)) &&
                            SUCCEEDED(ScriptVariant_DecimalValue(varlist[4], &dbltemp3)) &&
                            SUCCEEDED(ScriptVariant_DecimalValue(varlist[5], &dbltemp)) &&
                            dbltemp2 >= 0 && dbltemp2 < level->basemaps[ltemp].size.x && dbltemp3 >= 0 && dbltemp3 < level->basemaps[ltemp].size.z
                      )
                    {
                        if(!level->basemaps[ltemp].map)
                        {
                            level->basemaps[ltemp].map = calloc( 1, (LONG)(sizeof(*(level->basemaps[ltemp].map)) * (level->basemaps[ltemp].size.x+1)*(level->basemaps[ltemp].size.z+1)) );
                        }
                        level->basemaps[ltemp].map[(LONG)(dbltemp2 + dbltemp3 * level->basemaps[ltemp].size.x)] = (float)dbltemp;
                    }
                    else
                    {
                        goto clperror;
                    }
                    break;
                default:
                    goto clperror;
                }
            }
            else
            {
                goto clperror;
            }
        }
        else
        {
            goto clperror;
        }
        break;
    case _lp_hole:
    {
        if( SUCCEEDED(ScriptVariant_IntegerValue(varlist[1], &ltemp)) && ltemp >= 0
           && ( SUCCEEDED(ScriptVariant_DecimalValue(varlist[3], &dbltemp)) || SUCCEEDED(ScriptVariant_IntegerValue(varlist[3], &ltemp1)) ) )
        {
            if(varlist[2]->vt != VT_STR)
                printf("You must provide a string value for hole subproperty.\n");
                goto clperror;

            if(ltemp >= level->numholes)
            {
                __reallocto(level->holes, level->numholes, ltemp + 1);
                level->numholes = ltemp + 1;
            }

            switch(varlist[2]->lVal)
            {
                case _lp_terrain_height:
                {
                    level->holes[ltemp].height = dbltemp;
                    break;
                }
                case _lp_terrain_depth:
                {
                    level->holes[ltemp].depth = dbltemp;
                    break;
                }
                case _lp_terrain_lowerleft:
                {
                    level->holes[ltemp].lowerleft = dbltemp;
                    break;
                }
                case _lp_terrain_lowerright:
                {
                    level->holes[ltemp].lowerright = dbltemp;
                    break;
                }
                case _lp_terrain_upperleft:
                {
                    level->holes[ltemp].upperleft = dbltemp;
                    break;
                }
                case _lp_terrain_upperright:
                {
                    level->holes[ltemp].upperright = dbltemp;
                    break;
                }
                case _lp_terrain_x:
                {
                    level->holes[ltemp].x = dbltemp;
                    break;
                }
                case _lp_terrain_z:
                {
                    level->holes[ltemp].z = dbltemp;
                    break;
                }
                case _lp_terrain_type:
                {
                    level->holes[ltemp].type = ltemp1;
                    break;
                }
                default:
                {
                    printf("Invalid subproperty for hole.\n");
                    goto clperror;
                }
            }
        }
        else
        {
            goto clperror;
        }
        break;

    }
    case _lp_wall:
    {
        if( SUCCEEDED(ScriptVariant_IntegerValue(varlist[1], &ltemp)) && ltemp >= 0
           && ( SUCCEEDED(ScriptVariant_DecimalValue(varlist[3], &dbltemp)) || SUCCEEDED(ScriptVariant_IntegerValue(varlist[3], &ltemp1)) ) )
        {
            if(varlist[2]->vt != VT_STR)
                printf("You must provide a string value for wall subproperty.\n");
                goto clperror;

            if(ltemp >= level->numwalls)
            {
                __reallocto(level->walls, level->numwalls, ltemp + 1);
                level->numwalls = ltemp + 1;
            }

            switch(varlist[2]->lVal)
            {
                case _lp_terrain_depth:
                {
                    level->walls[ltemp].depth = dbltemp;
                    break;
                }
                case _lp_terrain_height:
                {
                    level->walls[ltemp].height = dbltemp;
                    break;
                }
                case _lp_terrain_lowerleft:
                {
                    level->walls[ltemp].lowerleft = dbltemp;
                    break;
                }
                case _lp_terrain_lowerright:
                {
                    level->walls[ltemp].lowerright = dbltemp;
                    break;
                }
                case _lp_terrain_upperleft:
                {
                    level->walls[ltemp].upperleft = dbltemp;
                    break;
                }
                case _lp_terrain_upperright:
                {
                    level->walls[ltemp].upperright = dbltemp;
                    break;
                }
                case _lp_terrain_x:
                {
                    level->walls[ltemp].x = dbltemp;
                    break;
                }
                case _lp_terrain_z:
                {
                    level->walls[ltemp].z = dbltemp;
                    break;
                }
                case _lp_terrain_type:
                {
                    level->walls[ltemp].type = ltemp1;
                    break;
                }
                default:
                {
                    printf("Invalid subproperty for wall.\n");
                    goto clperror;
                }
            }
        }
        else
        {
            goto clperror;
        }
        break;
    }
    default:
        printf("Invalid or read-only level property.\n");
        return E_FAIL;
        break;
    }

    return S_OK;
clperror:
    printf("Function changelevelproperty(prop, value) received invalid value(s). \n");
    printf("Dumping values: ");
    for(i = 1; i < paramCount; i++)
    {
        ScriptVariant_ToString(varlist[i], buf);
        printf("%s, ", buf);
    }
    printf("\n");
    return E_FAIL;
}


#endif // OPENBOR_SCRIPT_MAIN
