#define SHARED_HRM_COMPONENTS                 \
        compatible = "zmk,behavior-hold-tap"; \
        #binding-cells = <2>;                 \
        flavor = "balanced";                  \
        tapping-term-ms = <280>;              \
        quick-tap-ms = <175>;                 \
        require-prior-idle-ms = <60>;         \
        bindings = <&kp>, <&kp>;              \
        hold-trigger-on-release;

#define HRM_BEHAVIORS                                                   \
        hrms_l: hrms_l_behavior {                                       \
            SHARED_HRM_COMPONENTS                                       \
            hold-trigger-key-positions = <KEYS_MAIN_R KEYS_THUMBS_ALL>; \
        };                                                              \
        hrms_r: hrms_r_behavior {                                       \
            SHARED_HRM_COMPONENTS                                       \
            hold-trigger-key-positions = <KEYS_MAIN_L KEYS_THUMBS_ALL>; \
        };

