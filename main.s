.text
.global _start

// Define constants for system calls
.equ SYS_READ, 3
.equ SYS_WRITE, 4
.equ SYS_EXIT, 1
.equ STDIN_FILENO, 0

_start:
    // Buffer to store input (5 characters + newline + null terminator)
    adr x0, buffer
    mov x1, #6  // Length to read, including newline and null terminator
    mov x2, #0  // File descriptor for stdin (0)
    mov x16, #SYS_READ
    svc #0

    // Prepare the message to be printed
    adr x0, greeting
    mov x1, #20  // Adjust the length based on your greeting message length
    mov x2, #1   // File descriptor for stdout (1)
    mov x16, #SYS_WRITE
    svc #0

    // Exit system call
    mov x0, #0
    mov x16, #SYS_EXIT
    svc #0

.data
greeting:
    .ascii "Hello, "  // Static part of the greeting message
buffer:
    .skip 5         // Buffer to store 5 characters + newline + null terminator

