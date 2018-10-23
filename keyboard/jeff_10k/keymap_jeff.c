#include "keymap_common.h"
#include "action.h"
#include "action_layer.h"
#include "action_util.h"

/*
 * Hasu
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer
     * ,---------------.
     * |Num|  /|  *|  -|
     * |---------------|
     * |  7|  8|  9|  +|
     * |-----------|   |
     * |  4|  5|  6|   |
     * |---------------|
     * |  1|  2|  3|Ent|
     * |-----------|   |
     * |      0|  .|   | 
     * `---------------`
     */
    KEYMAP_ANSI(
        NLCK, PSLS, PAST, PMNS, \
        P7,   P8,   P9,   PPLS, \
        P4,   P5,   P6,         \ 
        P1,   P2,   P3,   PENT, \
        P0, PDOT                ),
	/* Keymap 0: Default Layer
     * ,---------------.
     * |Num|  /|  *|  -|
     * |---------------|
     * |  Q|  W|  E|  R|
     * |-----------|   |
     * |  A|  S|  D|   |
     * |---------------|
     * |  1|  2|  3|SPC|
     * |-----------|   |
     * |      0|  .|   | 
     * `---------------`
     */
    KEYMAP_ANSI(
        NLCK, PSLS, PAST, PMNS, \
        Q,    W,    E,    R,    \
        A,    S,    D,          \ 
        LSFT,   P2,   P3,   SPC , \
        ,  TAB                ),
    /* Overlay 6: Mouse mode (Semicolon/App)
     * ,-----------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |   |   |   |   |   |MwL|MwD|MwU|MwR|   |   |   |     |
     * |-----------------------------------------------------------|
     * |Contro|   |Ac0|Ac1|Ac1|   |McL|McD|McU|McR|   |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl|Gui |Alt |      Space             |    |    |    |    |
     * `-----------------------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel
     */
    KEYMAP_ANSI(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, BSPC, INS, HOME, PGUP, \
        TAB, TRNS,TRNS,TRNS,TRNS,TRNS,WH_L,WH_D,WH_U,WH_R,TRNS,TRNS,TRNS,TRNS, DEL, END, PGDN, \
        LCTL,TRNS,ACL0,ACL1,ACL2,TRNS,MS_L,MS_D,MS_U,MS_R,TRNS,TRNS,     ENT,  \
        LSFT,TRNS,TRNS,TRNS,TRNS,BTN3,BTN2,BTN1,BTN4,BTN5,TRNS,          RSFT, UP, \
        LCTL,LGUI,LALT,          BTN1,                    TRNS,TRNS,TRNS,RCTL,LEFT, DOWN, RGHT),
    /* Overlay 7: Layout selector
     * ,-----------------------------------------------------------.
     * | Lq| Lc| Ld| Lw|   |   |   |   |   |   |   |   |   |       |
     * |-----------------------------------------------------------|
     * |     |Lq |Lw |   |   |   |   |   |   |   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |   |   |Ld |   |   |   |   |   |   |   |   |        |
     * |-----------------------------------------------------------|
     * |        |   |   |Lc |   |   |   |   |   |   |   |          |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |    |    |    |    |
     * `-----------------------------------------------------------'
     * Lq: set Qwerty layout
     * Lc: set Colemak layout
     * Ld: set Dvorak layout
     * Lw: set Workman layout
     */
    KEYMAP_ANSI(
        FN4, FN5, FN6, FN7, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS, TRNS, \
        TRNS,FN4, FN7, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, TRNS, TRNS, TRNS, \
        TRNS,TRNS,TRNS,FN6, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
        TRNS,TRNS,TRNS,FN5, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,       TRNS      , \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,TRNS,TRNS,TRNS, TRNS, TRNS, TRNS),
};


enum function_id {
	ESCAPE
};



/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_KEY(4, KC_RGUI),
    [1] = ACTION_LAYER_TAP_KEY(5, KC_SLASH),
    [2] = ACTION_LAYER_TAP_KEY(6, KC_SCLN),
    [3] = ACTION_LAYER_MOMENTARY(7),   // to Layout selector
    [4] = ACTION_DEFAULT_LAYER_SET(0),  // set qwerty layout
    [5] = ACTION_DEFAULT_LAYER_SET(1),  // set colemak layout
    [6] = ACTION_DEFAULT_LAYER_SET(2),  // set dvorak layout
    [7] = ACTION_DEFAULT_LAYER_SET(3),  // set workman layout
    [8] = ACTION_FUNCTION(ESCAPE),
};





void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	if(id == ESCAPE){
		void (*method)(uint8_t) = (record->event.pressed) ? &add_key : &del_key;
		uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));

		if(layer_state == 0)
			method(shifted ? KC_GRAVE : KC_ESCAPE);
		else
			method(shifted ? KC_ESCAPE : KC_GRAVE);

		send_keyboard_report();
	}
}

