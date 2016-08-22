CC = gcc
CFLAGS = -Wall -c

TARGET = $(notdir $(CURDIR))
SOURCES := source source/model source/ui source/ui/pkm
INCLUDES := include

CFILES = $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
INCLUDE = $(foreach dir,$(INCLUDES),-I$(dir))

.PHONY: ui

all:
	tools/process_glade.py ui/ui.glade ui/out.glade
	$(CC) -std=c99 -o ./$(TARGET).exe $(CFILES) $(INCLUDE) `pkg-config --cflags --libs gtk+-3.0`

ui:
	tools/process_glade.py ui/ui.glade ui/out.glade

clean:
	rm $(TARGET).exe
