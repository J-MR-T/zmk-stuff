#ifndef SHARED_H
#define SHARED_H

// layer names
#define DEFAULT 0
#define NAV 1
#define SYMBOLS 2
#define MAGIC 3
#define UMLAUT 4

#define SHARED_MODTAP_COMPONENTS                 \
        compatible = "zmk,behavior-hold-tap"; \
        flavor = "balanced";                  \
        tapping-term-ms = <280>;              \
        quick-tap-ms = <175>;                 \
        require-prior-idle-ms = <60>;         \
        hold-trigger-on-release;

#define HRM_BEHAVIORS                                                   \
        hrms_l: hrms_l_behavior {                                       \
            SHARED_MODTAP_COMPONENTS                                       \
            #binding-cells = <2>;                 \
            bindings = <&kp>, <&kp>;              \
            hold-trigger-key-positions = <KEYS_MAIN_R KEYS_THUMBS_ALL>; \
        };                                                              \
        hrms_r: hrms_r_behavior {                                       \
            SHARED_MODTAP_COMPONENTS                                       \
            #binding-cells = <2>;                 \
            bindings = <&kp>, <&kp>;              \
            hold-trigger-key-positions = <KEYS_MAIN_L KEYS_THUMBS_ALL>; \
        };

#define NAV_LAYER_STICKY_SHIFT_BEHAVIOR \
        sticky_key_quick: sticky_key_quick_behavior { \
            compatible = "zmk,behavior-sticky-key"; \
            #binding-cells = <1>; \
            bindings = <&kp>; \
            /* these 2 lines are the actual changes */ \
            release-after-ms = <500>; \
            quick-release; \
            ignore-modifiers; \
        }; \
        nav_sticky_shift: nav_sticky_shift_behavior { \
            SHARED_MODTAP_COMPONENTS \
            #binding-cells = <2>; \
            bindings = <&mo>, <&sticky_key_quick>; \
            hold-trigger-key-positions = <KEYS_MAIN_ALL>; \
        };
        

#define DEFAULT_HOME_ROW_MAP \
        &hrms_l LCTRL ESC        &hrms_l LGUI A    &hrms_l LALT S       &hrms_l LCTRL D       &hrms_l LSHFT F       &kp G                               &kp H   &hrms_r RSHFT J   &hrms_r RCTRL K       &hrms_r LALT L       &hrms_r RGUI SEMI    &lt UMLAUT SQT
        

#endif // SHARED_H
