#include "quantum.h"

// Add function declaration for render_logo
void render_logo(void);

static uint16_t current_keycode = 0xFF;

static const char *depad_str(const char *depad_str, char depad_char) {
    while (*depad_str == depad_char)
        ++depad_str;
    return depad_str;
}

static void render_spacer(uint8_t char_length) {
    static const char PROGMEM spacer_char[] = {8, 8, 8, 8, 8, 8, 8};
    if (char_length > 5) {
        char_length = 5;
    }
    for (uint8_t i = 0; i < char_length; i++) {
        oled_write_raw_P(spacer_char, sizeof(spacer_char));
        oled_advance_char();
    }
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

char basic_codes_to_name[57] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/'};

const char *keycode_string(uint16_t keycode) {
    char       *keycode_str;
    static char key;
    switch (keycode) {
        case 0 ... 56:
            key = pgm_read_byte(&basic_codes_to_name[keycode]);
            return &key;
        case KC_CAPS:
            keycode_str = "Caps\0";
            break;
        case KC_SCRL:
            keycode_str = "Scrl\0";
            break;
        case KC_PAUS:
            keycode_str = "Pause\0";
            break;
        case KC_DEL:
            keycode_str = "Del\0";
            break;
        case KC_NUM:
            keycode_str = "Num\0";
            break;
        case KC_MUTE:
            keycode_str = "Mute\0";
            break;
        case KC_VOLU:
            keycode_str = "VolUp\0";
            break;
        case KC_VOLD:
            keycode_str = "VolD\0";
            break;
        case KC_MNXT:
            keycode_str = "Next\0";
            break;
        case KC_MPRV:
            keycode_str = "Prev\0";
            break;
        case KC_MSTP:
            keycode_str = "Stop\0";
            break;
        case KC_MPLY:
            keycode_str = "Play\0";
            break;
        case QK_MODS ... QK_MODS_MAX:
            keycode_str = "MOD()\0";
            break;
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            keycode_str = "MT()\0";
            break;
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            keycode_str = "LT()\0";
            break;
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            keycode_str = "LM()\0";
            break;
        case QK_TO ... QK_TO_MAX:
            keycode_str = "TO()\0";
            break;
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            keycode_str = "MO()\0";
            break;
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            keycode_str = "DF()\0";
            break;
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            keycode_str = "TG()\0";
            break;
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_MOD_MAX:
            keycode_str = "1SHOT\0";
            break;
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            keycode_str = "TT()\0";
            break;
        case QK_PERSISTENT_DEF_LAYER ... QK_PERSISTENT_DEF_LAYER_MAX:
            keycode_str = "PDF()\0";
            break;
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            keycode_str = "SWAP\0";
            break;
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            keycode_str = "TD()\0";
            break;
        case QK_MAGIC ... QK_MAGIC_MAX:
            keycode_str = "Magic\0";
            break;
        case QK_MIDI ... QK_MIDI_MAX:
            keycode_str = "Midi\0";
            break;
        case QK_SEQUENCER ... QK_SEQUENCER_MAX:
            keycode_str = "Seq\0";
            break;
        case QK_JOYSTICK ... QK_JOYSTICK_MAX:
            keycode_str = "Joy\0";
            break;
        case QK_PROGRAMMABLE_BUTTON ... QK_PROGRAMMABLE_BUTTON_MAX:
            keycode_str = "Prog\0";
            break;
        case QK_AUDIO ... QK_AUDIO_MAX:
            keycode_str = "Audio\0";
            break;
        case QK_STENO ... QK_STENO_MAX:
            keycode_str = "Steno\0";
            break;
        case QK_MACRO ... QK_MACRO_MAX:
            keycode_str = "Macro\0";
            break;
        case QK_CONNECTION ... QK_CONNECTION_MAX:
            keycode_str = "Conn\0";
            break;
        case QK_LIGHTING ... QK_LIGHTING_MAX:
            keycode_str = "Light\0";
            break;
        case QK_QUANTUM ... QK_QUANTUM_MAX:
            keycode_str = "Quant\0";
            break;
        case QK_KB ... QK_KB_MAX:
            keycode_str = "KB\0";
            break;
        case QK_USER ... QK_USER_MAX:
            keycode_str = "USER\0";
            break;
        case QK_UNICODEMAP ... QK_UNICODEMAP_PAIR_MAX:
            keycode_str = "Uni\0";
            break;
        default:
            keycode_str = "Undef\0";
            break;
    }

    return keycode_str;
}

const char *layer_string(uint32_t layer) {
    char *layer_str;
    switch (layer) {
        case 0:
            layer_str = "Zero\0";
            break;
        case 1:
            layer_str = "One\0";
            break;
        case 2:
            layer_str = "Two\0";
            break;
        case 3:
            layer_str = "Three\0";
            break;
        default:
            return get_u16_str(layer, ' ');
    }

    return layer_str;
}

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }

    oled_set_cursor(0, 10);
    switch (detected_os) {
        case OS_MACOS:
            oled_write_ln("MacOS", false);
        case OS_IOS:
            oled_write_ln("Apple", false);
            break;
        case OS_WINDOWS:
            oled_write_ln("Win", false);
            break;
        case OS_LINUX:
            oled_write_ln("Linux", false);
            break;
        case OS_UNSURE:
            oled_write_ln("Unkno", false);

            break;
    }

    return true;
}

void keyboard_post_init_kb(void) {
    if (!is_keyboard_master()) {
        render_logo();
    } else {
        oled_set_cursor(0, 0);
        oled_write("Layer", false);
        render_spacer(5);
        oled_write_ln(layer_string(get_highest_layer(layer_state)), false);

        oled_set_cursor(0, 4);
        oled_write_ln("Key", false);
        render_spacer(3);
        oled_advance_page(false);
        oled_write_ln("None", false);

        oled_set_cursor(0, 8);
        oled_write_ln("OS", false);
        render_spacer(2);
        oled_advance_page(false);
        oled_write_ln("Wait", false);

        oled_set_cursor(0, 12);
        oled_write_ln("WPM", false);
        render_spacer(3);
        oled_advance_page(false);
        oled_write_ln(depad_str(get_u16_str(get_current_wpm(), ' '), ' '), false);
    }
    keyboard_post_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    oled_set_cursor(0, 2);
    oled_write_ln(layer_string(get_highest_layer(state)), false);
    return state;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    current_keycode = keycode;
    return process_record_user(keycode, record);
};

void     housekeeping_task_kb(void) {
    if (is_oled_on() && last_input_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
    }
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    static uint16_t last_keycode         = 0xFF;

    if (is_keyboard_master()) {
        if (last_keycode != current_keycode) {
            oled_set_cursor(0, 6);
            if (current_keycode < ARRAY_SIZE(basic_codes_to_name)) {
                oled_write_char(basic_codes_to_name[current_keycode], false);
                oled_advance_page(true);
            } else {
                oled_write_ln(keycode_string(current_keycode), false);
            }
            last_keycode = current_keycode;
        }
        static uint16_t last_wpm = 0;
        if (last_wpm != get_current_wpm()) {
            last_wpm = get_current_wpm();
            if(is_oled_on()) {
                oled_set_cursor(0, 14);
                oled_write_ln(depad_str(get_u16_str(last_wpm, ' '), ' '), false);
            }
        }
    }
    return false;
}
