global inb
global outb

inb:
  mov dx, [esp + 4]
  in al, dx
  ret

; pass in data byte and port
outb:
  mov dx, [esp + 4] ; the port
  mov al, [esp + 8] ; the data
  out dx, al ; send data to port
  ret
