.syntax unified             @ unified syntax used
.cpu cortex-m4              @ cpu is cortex-m4
.thumb                      @ use thumb encoding

.text                       @ put code in the code section

.global red_led_setup               @ declare as a global variable
.type red_led_setup, %function      @ set to function type

@setup for red led
@Note: we will combine all led setup functions into one
red_led_setup:
    ldr r1, =0x40048038     @ System Clock Gate Control Register 5 (SIM_SCGC5)
    ldr r0, [r1]            @ read current register value
    orr r0, r0, #(1<<11)  @ For K66, red LED is at port C (bit 11) enable clock for port C
    str r0, [r1]            @ apply the new settings

    ldr r1, =0x4004B024    @ For K66, PTC9 Pin Control Register (PORTC_PCR9)
    mov r0, #0x00000100     @ set pin to GPIO mode
    str r0, [r1]            @ apply the new settings

    ldr r1, =0x400FF094    @ For K66, GPIOC Port Data Direction Register (GPIOC_PDDR)
    mov r0, #(1<<9)        @ For K66, set pin 9 to output mode
    str r0, [r1]            @ apply the new settings

    ldr r1, =0x400FF080     @ For K66, GPIOC Port Data Output Register (GPIOC_PDOR)
    mov r0, #(1<<9)         @ Set pin 9 output to HIGH (LED off initially)
    str r0, [r1]            @ Apply the settings

    bx  lr


@setup for green led
.global green_led_setup               @ declare as a global variable
.type green_led_setup, %function      @ set to function type

green_led_setup:
    ldr r1, =0x40048038     @ System Clock Gate Control Register 5 (SIM_SCGC5)
    ldr r0, [r1]            @ read current register value
    orr r0, r0, #(1<<13)  @ For K66, green LED is at port E (bit 11 enable clock for port E
    str r0, [r1]            @ apply the new settings

    ldr r1, =0x4004D018   @ For K66, Pin Control Register (PORTE_PCR6)
    mov r0, #0x00000100     @ set pin to GPIO mode
    str r0, [r1]            @ apply the new settings

    ldr r1, =0x400FF114    @ For K66, GPIOE Port Data Direction Register (GPIOE_PDDR for Port E)
    mov r0, #(1<<6)        @ For K66, set pin 9 to output mode
    str r0, [r1]            @ apply the new settings

    ldr r1, =0x400FF100     @ For K66, GPIOC Port Data Output Register (GPIOC_PDOR)
    mov r0, #(1<<6)         @ Set pin 9 output to HIGH (LED off initially)
    str r0, [r1]            @ Apply the settings

    bx  lr

@setup for blue led
.global blue_led_setup               @ declare as a global variable
.type blue_led_setup, %function      @ set to function type
blue_led_setup:
    ldr r1, =0x40048038     @ System Clock Gate Control Register 5 (SIM_SCGC5)
    ldr r0, [r1]            @ read current register value
    orr r0, r0, #(1<<9)  @ For K66, blue LED is at port A (bit 9) enable clock for port A
    str r0, [r1]            @ apply the new settings

    ldr r1, =0x4004902C    @ For K66, Pin Control Register (PORTA_PCR11)
    mov r0, #0x00000100     @ set pin to GPIO mode
    str r0, [r1]            @ apply the new settings

    ldr r1, =0x400FF014    @ For K66, GPIOA Port Data Direction Register (GPIOA_PDDR)
    mov r0, #(1<<11)        @ For K66, set pin 9 to output mode
    str r0, [r1]            @ apply the new settings

    ldr r1, =0x400FF000     @ For K66, GPIOC Port Data Output Register (GPIOC_PDOR)
    mov r0, #(1<<11)         @ Set pin 9 output to HIGH (LED off initially)
    str r0, [r1]            @ Apply the settings

    bx  lr

@turning red led on
.global func_red_led_on             @ declare as a global variable
.type func_red_led_on, %function    @ set to function type

func_red_led_on:
    ldr r1, =0x400FF080    @ For K66, GPIOC Port Data Output Register (GPIOC_PDOR)
    mov r0, #0              @ set output to LOW, LED on
    str r0, [r1]            @ apply settings
    bx  lr

@turning red led off
.global func_red_led_off            @ declare as a global variable
.type func_red_led_off, %function   @ set to function type

func_red_led_off:
    ldr r1, =0x400FF080    @ For K66, GPIOC Port Data Output Register (GPIOC_PDOR)
    mov r0, #(1<<9)        @ For K66, set pin 9 output to HIGH, LED off
    str r0, [r1]            @ apply settings
    bx  lr


@turning green on
.global func_green_led_on             @ declare as a global variable
.type func_green_led_on, %function    @ set to function type

func_green_led_on:
    ldr r1, =0x400FF100   @ For K66, GPIOC Port Data Output Register (GPIOC_PDOR)
    mov r0, #0              @ set output to LOW, LED on
    str r0, [r1]            @ apply settings
    bx  lr

@turning green off
.global func_green_led_off            @ declare as a global variable
.type func_green_led_off, %function   @ set to function type

func_green_led_off:
    ldr r1, =0x400FF100    @ For K66, GPIOC Port Data Output Register (GPIOC_PDOR)
    mov r0, #(1<<6)        @ For K66, set pin 9 output to HIGH, LED off
    str r0, [r1]            @ apply settings
    bx  lr


@turning blue on
.global func_blue_led_on             @ declare as a global variable
.type func_blue_led_on, %function    @ set to function type

func_blue_led_on:
    ldr r1, =0x400FF000    @ For K66, GPIOC Port Data Output Register (GPIOC_PDOR)
    mov r0, #0              @ set output to LOW, LED on
    str r0, [r1]            @ apply settings
    bx  lr

@turning blue off
.global func_blue_led_off            @ declare as a global variable
.type func_blue_led_off, %function   @ set to function type

func_blue_led_off:
    ldr r1, =0x400FF000    @ For K66, GPIOC Port Data Output Register (GPIOC_PDOR)
    mov r0, #(1<<11)        @ For K66, set pin 9 output to HIGH, LED off
    str r0, [r1]            @ apply settings
    bx  lr
