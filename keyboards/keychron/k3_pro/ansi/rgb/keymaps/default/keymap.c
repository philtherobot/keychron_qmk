/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// Launch QMK MSYS.
// CDir to project directory.
// To build: `make keychron/k3_pro/ansi/rgb:default`
// To enter flash mode:
// - turn off
// - hold Esc, turn on


enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN,
  EXTEND,
  SYMBOLS1
};

enum extend_colors {
    ARR = 1, // arrows
    MOV,     // moving/jumping
    RUB,     // rubbing
    MOS,     // mouse
    CLP,     // clipboard
    MDE,     // modes
    OTH,     // other
    BAS,     // base
    HIG,     // highlight
    CAP      // capslock
};

// clang-format off
uint8_t win_base_rgb_matrix[MATRIX_ROWS * MATRIX_COLS] = {
   BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,
   BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,            BAS,
   BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,            BAS,
   BAS,    HIG,    HIG,    HIG,    HIG,    BAS,    BAS,    BAS,    HIG,    HIG,    HIG,    HIG,            BAS,            BAS,
   BAS,            BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,            BAS,    BAS,    BAS,
   BAS,    BAS,    BAS,                            BAS,                            BAS,    BAS,    BAS,    BAS,    BAS,    BAS,
};

uint8_t caps_on_rgb_matrix[MATRIX_ROWS * MATRIX_COLS] = {
   BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,
   BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,    BAS,            BAS,
   BAS,    CAP,    CAP,    CAP,    CAP,    CAP,    BAS,    CAP,    CAP,    CAP,    CAP,    BAS,    BAS,    BAS,            BAS,
   BAS,    CAP,    CAP,    CAP,    CAP,    CAP,    BAS,    CAP,    CAP,    CAP,    CAP,    CAP,            BAS,            BAS,
   BAS,            CAP,    CAP,    CAP,    CAP,    CAP,    BAS,    CAP,    CAP,    BAS,    BAS,            BAS,    BAS,    BAS,
   BAS,    BAS,    BAS,                            BAS,                            BAS,    BAS,    BAS,    BAS,    BAS,    BAS,
};

uint8_t extend_rgb_matrix[MATRIX_ROWS * MATRIX_COLS] = {
   OTH,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,
   OTH,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,              0,
   0,      OTH,    0,      0,      0,      MOS,    0,      MOV,    MOV,    ARR,    MOV,    RUB,    0,      0,              0,
   0,      MDE,    MDE,    MDE,    MDE,    MOS,    0,      MOV,    ARR,    ARR,    ARR,    RUB,            0,              0,
   0,              RUB,    CLP,    CLP,    CLP,    CLP,    MOS,    MOS,    MOS,    MOS,    MOS,            0,      0,      0,
   0,      0,      0,                              0,                              0,      0,      0,      0,      0,      0
};
// clang-format on

void set_rgb_matrix(uint8_t led_min, uint8_t led_max, uint8_t * rgb_matrix) {
    for (uint8_t i = led_min; i < led_max; i++) {
        uint8_t color_index = rgb_matrix[i];

        switch(color_index) {
            case CLP:
                rgb_matrix_set_color(i, RGB_GOLD);
                break;
            case MDE:
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            case MOS:
                rgb_matrix_set_color(i, RGB_AZURE);
                break;
            case RUB:
                rgb_matrix_set_color(i, RGB_RED);
                break;
            case OTH:
            case MOV:
            case HIG:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case ARR:
                rgb_matrix_set_color(i, RGB_YELLOW);
                break;
            case BAS:
                rgb_matrix_set_color(i, RGB_PINK);
                break;
            case CAP:
                rgb_matrix_set_color(i, RGB_RED);
                break;
            default:
            case 0:
                rgb_matrix_set_color(i, RGB_BLACK);
                break;
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case WIN_BASE:
        case SYMBOLS1:
            if(host_keyboard_led_state().caps_lock) {
                set_rgb_matrix(led_min, led_max, caps_on_rgb_matrix);
            }
            else {
                set_rgb_matrix(led_min, led_max, win_base_rgb_matrix);
            }
            break;
        case WIN_FN:
            rgb_matrix_set_color_all(RGB_PINK);
            break;
        case EXTEND:
            set_rgb_matrix(led_min, led_max, extend_rgb_matrix);
            break;
        default:
            break;
    }
    return false;
}

// clang-format off

enum unicode_names {
    agrav,    Agrav,
    acirc,    Acirc,
    adiae,    Adiae,

    egrav,    Egrav,
    eacut,    Eacut,
    ecirc,    Ecirc,
    ediae,    Ediae,

    icirc,    Icirc,
    idiae,    Idiae,

    ocirc,    Ocirc,

    ugrav,    Ugrav,
    ucirc,    Ucirc,
    udiae,    Udiae,

    ccedi,    Ccedi,

    LAngQuot,
    RAngQuot
};

const uint32_t unicode_map[] PROGMEM = {
    [agrav]     = 0x00E0, // à
    [Agrav]     = 0x00C0, // À

    [acirc]     = 0x00E2, // â
    [Acirc]     = 0x00C2, // Â

    [adiae]     = 0x00E4, // ä
    [Adiae]     = 0x00C4, // Ä

    [egrav]     = 0x00E8, // è
    [Egrav]     = 0x00C8, // È

    [eacut]     = 0x00E9, // é
    [Eacut]     = 0x00C9, // É

    [ecirc]     = 0x00EA, // ê
    [Ecirc]     = 0x00CA, // Ê

    [ediae]     = 0x00EB, // ë
    [Ediae]     = 0x00CB, // Ë

    [icirc]     = 0x00EE, // î
    [Icirc]     = 0x00CE, // Î

    [idiae]     = 0x00EF, // ï
    [Idiae]     = 0x00CF, // Ï

    [ocirc]     = 0x00F4, // ô
    [Ocirc]     = 0x00D4, // Ô

    [ugrav]     = 0x00F9, // ù
    [Ugrav]     = 0x00D9, // Ù

    [ucirc]     = 0x00FB, // û
    [Ucirc]     = 0x00DB, // Û

    [udiae]     = 0x00FC, // ü
    [Udiae]     = 0x00DC, // Ü

    [ccedi]     = 0x00E7, // ç
    [Ccedi]     = 0x00C7, // Ç

    [LAngQuot]  = 0x00AB, // «
    [RAngQuot]  = 0x00BB, // »
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// I replaced the original MAC layers with the original WIN layers.
// This means I can get a regular WIN layout by setting the keyboard
// to "MAC/IOS".
[MAC_BASE] = LAYOUT_ansi_84(
     KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   RGB_MOD,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[MAC_FN] = LAYOUT_ansi_84(
     KC_TRNS,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  KC_TRNS,  RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),


[WIN_BASE] = LAYOUT_ansi_84(
     KC_ESC,      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,        KC_F11,     KC_F12,   KC_PSCR,  KC_DEL,   KC_PAUSE,
     KC_GRV,      KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_EQL,   KC_7,     KC_8,     KC_9,          KC_0,       KC_MINS,  KC_BSPC,            KC_PGUP,
     KC_TAB,      KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_LBRC,  KC_J,     KC_L,     KC_U,     KC_Y,          KC_SCLN,    KC_QUOT,  KC_BSLS,            KC_PGDN,
     TT(EXTEND),  KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_RBRC,  KC_M,     KC_N,     KC_E,     KC_I,          KC_O,                 KC_ENT,             KC_HOME,
     KC_LSFT,               KC_X,     KC_C,     KC_D,     KC_V,     KC_Z,     KC_SLSH,  KC_K,     KC_H,     KC_COMM,       KC_DOT,               KC_RSFT,  KC_UP,    KC_END,
     KC_LCTL,     KC_LGUI,  KC_LALT,                                KC_SPC,                                 OSL(SYMBOLS1), MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN_FN] = LAYOUT_ansi_84(
     KC_TRNS,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  KC_TRNS,  RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[EXTEND] = LAYOUT_ansi_84(
     KC_TRNS,  KC_BRID,  KC_BRIU,    KC_TASK,    KC_FILE,    RGB_VAD,    RGB_VAI,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MUTE,    KC_VOLD,     KC_VOLU,  KC_TRNS,  KC_TRNS,  UC_NEXT,
     KC_TRNS,  BT_HST1,  BT_HST2,    BT_HST3,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_ESC,   KC_INS,     KC_CAPS,    RGB_SAI,    KC_MS_UP,   RGB_SPI,    KC_PGUP,    KC_HOME,    KC_UP,      KC_END,     KC_DEL,      KC_ESC,   KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_LALT,  KC_LSFT,    KC_LCTL,    KC_TRNS,    KC_MS_DOWN, KC_TRNS,    KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_BSPC,               KC_TRNS,            KC_TRNS,
     KC_TRNS,            LCTL(KC_X), LCTL(KC_C), LCTL(KC_D), LCTL(KC_V), LCTL(KC_Z), KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2, KC_MS_LEFT, KC_MS_RIGHT,           KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                        KC_TRNS,                                        KC_TRNS,    KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[SYMBOLS1] = LAYOUT_ansi_84(
//esc        F1         F2                 F3         F4         F5         F6         F7                 F8                 F9                 F10                F11                   F12        snap       del        bright
  KC_TRNS   ,KC_TRNS   ,KC_TRNS           ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS           ,KC_TRNS           ,KC_TRNS           ,KC_TRNS           ,KC_TRNS              ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS,
  KC_TRNS   ,KC_TRNS   ,KC_TRNS           ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS           ,KC_TRNS           ,KC_TRNS           ,KC_TRNS           ,KC_TRNS              ,KC_TRNS   ,KC_TRNS              ,KC_TRNS,
  KC_TRNS   ,KC_TRNS   ,KC_TRNS           ,S(KC_LBRC),S(KC_RBRC),KC_TRNS   ,KC_TRNS   ,KC_TRNS           ,XP(agrav, Agrav)  ,XP(ocirc, Ocirc)  ,XP(acirc, Acirc)  ,XP(icirc, Icirc)     ,KC_TRNS   ,KC_TRNS              ,KC_TRNS,
  KC_TRNS   ,KC_LBRC   ,KC_RBRC           ,S(KC_9)   ,S(KC_0)   ,KC_TRNS   ,KC_TRNS   ,XP(idiae, Idiae)  ,XP(eacut, Eacut)  ,XP(egrav, Egrav)  ,XP(ecirc, Ecirc)  ,XP(ediae, Ediae)     ,KC_TRNS                         ,KC_TRNS,
  KC_TRNS   ,KC_TRNS   ,XP(ccedi, Ccedi)  ,KC_EQL    ,S(KC_EQL) ,KC_TRNS   ,KC_TRNS   ,KC_TRNS           ,XP(ucirc, Ucirc)  ,XP(ugrav, Ugrav)  ,XP(udiae, Udiae)  ,KC_TRNS                                    ,KC_TRNS   ,KC_TRNS,
  KC_TRNS   ,KC_TRNS   ,KC_TRNS                                            ,KC_TRNS                                         ,KC_TRNS           ,KC_TRNS           ,KC_TRNS              ,KC_TRNS   ,KC_TRNS   ,KC_TRNS)

/* A blank layer
[<name>] = LAYOUT_ansi_84(
//esc        F1         F2         F3         F4         F5         F6         F7         F8         F9         F10        F11        F12        snap       del        bright
  KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS,
  KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS              ,KC_TRNS,
  KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS              ,KC_TRNS,
  KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS                         ,KC_TRNS,
  KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS                         ,KC_TRNS   ,KC_TRNS,
  KC_TRNS   ,KC_TRNS   ,KC_TRNS                                    ,KC_TRNS                                    ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS)
*/

};
