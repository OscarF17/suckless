/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
// static const char *fonts[]          = { "monospace:size=12" };
static const char *fonts[]          = { "monospace:size=12", "FontAwesome:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#82000f";
/* static const char col_cyan[]        = "#005577"; */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
/* Constants for media keys */
static const char *upvol[]           = { "amixer",    "set", "Master", "5%+",    NULL };
static const char *downvol[]         = { "amixer",    "set", "Master", "5%-",    NULL };
static const char *mutevol[]         = { "amixer",    "set", "Master", "toggle", NULL };
static const char *medplaypausecmd[] = { "playerctl", "play-pause",              NULL };
static const char *mednextcmd[]      = { "playerctl", "next",                    NULL };
static const char *medprevcmd[]      = { "playerctl", "previous",                NULL };
static const char *light_up[]        = { "light",     "-A", "5",                 NULL };
static const char *light_down[]      = { "light",     "-U", "5",                 NULL };

/* tagging */
static const char *tags[] = { "", "2", "", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask     isfloating   monitor */
	{ "firefox",        NULL,       NULL,       1 << 0,       0,           -1 },
	{ "waterfox",       NULL,       NULL,       1 << 0,       0,           -1 },
	{ "discord",        NULL,       NULL,       1 << 3,       0,           -1 },
	{ "kitty",          NULL,       NULL,       1 << 2,       0,           -1 },
	{ "libreoffice",    NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
/* Mod1Mask -> Alt
 * Mod4Mask -> Super key
 */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[] = { "kitty",     NULL   };
static const char *copycmd[] = { "copyq",     "menu" }; 
static const char *shotcmd[] = { "spectacle", "-brc" };
static const char *sshotsv[] = { "spectacle", "-br"  };

#include "shiftview.c"
#define XF_Low  XF86XK_AudioLowerVolume
#define XF_Mute XF86XK_AudioMute
#define XF_High XF86XK_AudioRaiseVolume
#define XF_Play XF86XK_AudioPlay
#define XF_Next XF86XK_AudioNext 
#define XF_Prev XF86XK_AudioPrev
#define XF_BrUp XF86XK_MonBrightnessUp
#define XF_BrDo XF86XK_MonBrightnessDown

static const Key keys[] = {
	/* modifier                     key        function        argument */
    /* media keys */
    { 0,                            XF_Low,    spawn,          {.v = downvol } },
	{ 0,                            XF_Mute,   spawn,          {.v = mutevol } },
	{ 0,                            XF_High,   spawn,          {.v = upvol   } },
    { 0,                            XF_Play,   spawn,          {.v = medplaypausecmd } },
    { 0,                            XF_Next,   spawn,          {.v = mednextcmd } },
    { 0,                            XF_Prev,   spawn,          {.v = medprevcmd } },
    { 0,		                    XF_BrUp,   spawn,	       {.v = light_up} },
	{ 0,			                XF_BrDo,   spawn,	       {.v = light_down} },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = copycmd} },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = shotcmd} },
    { MODKEY|ShiftMask,             XK_Print,  spawn,          {.v = sshotsv} },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    shiftview,      {.i = +1} },
	{ MODKEY,                       XK_x,      shiftview,      {.i = -1} },
	{ Mod1Mask,                     XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
