#define CUSTOM_KEY_DELAY 140
#define CUSTOM_KEY_INTERVAL 50

void handle_opening_pair(uint16_t keycode);

bool handle_closing_pair(void);

void set_repeat_custom_key(uint16_t keycode, keyrecord_t *record);

void try_repeat_custom_key(void);

bool handle_nonrepeatable_key(uint16_t keycode);
