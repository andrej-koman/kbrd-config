ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += keyboards/andrej/common/display_oled.c keyboards/andrej/common/blocksi.c
endif
