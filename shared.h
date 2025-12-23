#define SHARED_HRM_COMPONENTS                 \
        compatible = "zmk,behavior-hold-tap"; \
        #binding-cells = <2>;                 \
        flavor = "balanced";                  \
        tapping-term-ms = <280>;              \
        quick-tap-ms = <175>;                 \
        require-prior-idle-ms = <60>;         \
        bindings = <&kp>, <&kp>;              \
        hold-trigger-on-release;

